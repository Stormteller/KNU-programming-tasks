#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <stdio.h>
#include <iostream>
#include "sqlite3.h"
#include <vector>
#include <string>

#pragma comment(lib, "Ws2_32.lib")
#define MAX_BUF_LEN 512

using uint16 = unsigned short int;

constexpr uint16 serverPort = 1234;
constexpr char serverAddress[] = "127.0.0.1";

enum Action { CREATED, CLOSED, REOPENED, OPENED};

/*struct charProcessAction {
	char createTime[MAX_BUF_LEN];
	char uptime[MAX_BUF_LEN];
	char username[MAX_BUF_LEN];
	char exeFileName[MAX_BUF_LEN];
	char action[MAX_BUF_LEN];
};*/

struct processData {
	DWORD id;
	FILETIME createTime;
	FILETIME uptime;
	TCHAR username[MAX_BUF_LEN];
	TCHAR exeFileName[MAX_PATH];
};

struct processAction {
	processData process;
	Action action;
};

time_t filetimeToTimet(const FILETIME& ft)
{
	ULARGE_INTEGER ull;
	ull.LowPart = ft.dwLowDateTime;
	ull.HighPart = ft.dwHighDateTime;

	return ull.QuadPart / 10000000ULL - 11644473600ULL;
}


void saveToDB(processAction pa)
{
	sqlite3* db;
	char* err;
	std::string SQLCreate = "CREATE TABLE IF NOT EXISTS " + std::string(pa.process.username) + " (name,action,createTime,uptime);";

	if (sqlite3_open("db.sqlite", &db)) {
		fprintf(stderr, "Open/Create error: %s\n", sqlite3_errmsg(db));
	}
	else
	{
		if (sqlite3_exec(db, SQLCreate.c_str(), 0, 0, &err)) {
			fprintf(stderr, "SQL error: %s\n", err);
			sqlite3_free(err);
		}
		else {
			std::string status = "";
			long int tCreate = static_cast<long int>(filetimeToTimet(pa.process.createTime));
			long int tUptime = static_cast<long int>(filetimeToTimet(pa.process.uptime));
			if (pa.action == CREATED) status = "created";
			if (pa.action == OPENED) status = "opened";
			if (pa.action == REOPENED) status = "reopened";
			if (pa.action == CLOSED) status = "closed";

			std::string SQLSave = "INSERT INTO " + std::string(pa.process.username) + " (name,action,createTime,uptime)"
				+ " VALUES ('" 
				+ std::string(pa.process.exeFileName)
				+ "','" + status
				+ "','" + std::to_string(tCreate)
				+ "','" + std::to_string(tUptime)
				+ "');";
			if (sqlite3_exec(db, SQLSave.c_str(), 0, 0, &err)) {
				fprintf(stderr, "SQL error: %s\n", err);
				sqlite3_free(err);
			}
			
		}
	}
	sqlite3_close(db);
}



void receive(SOCKET clientSocket) {
	const int DEFAULT_BUFLEN = 512;
	char recvbuf[DEFAULT_BUFLEN * 5];
	int iResult = 0;
	int recvbuflen = DEFAULT_BUFLEN * 5;
	do {
		processAction pa;
		iResult = ::recv(clientSocket, (char*)&pa, sizeof(pa), MSG_WAITALL);
		std::string status = "";
		if (pa.action == CREATED) status = "created";
		if (pa.action == OPENED) status = "opened";
		if (pa.action == REOPENED) status = "reopened";
		if (pa.action == CLOSED) status = "closed";
		saveToDB(pa);
		printf("%s %s\n", pa.process.exeFileName, status.c_str());
	} while (iResult > 0);

}

int main()
{
	setlocale(LC_ALL, "");
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in serverSocketAddr;
	serverSocketAddr.sin_family = AF_INET;
	serverSocketAddr.sin_addr.s_addr = inet_addr(serverAddress);
	serverSocketAddr.sin_port = htons(serverPort);

	int bindResult = bind(serverSocket, (SOCKADDR*)&serverSocketAddr, sizeof(serverSocketAddr));
	if (bindResult)
		return 0;

	
	printf("listening...\n");
	int listenResult = listen(serverSocket, 0);
	if (listenResult)
		return 0;

	sockaddr clientSocketAddr = { 0 };
	int clientSocetAddrSize = sizeof(clientSocketAddr);
	SOCKET clientSocket = accept(serverSocket, &clientSocketAddr, &clientSocetAddrSize);
	if (clientSocket == INVALID_SOCKET) {
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(listenResult);
		WSACleanup();
		return 1;
	}

	printf("connected\n");


	receive(clientSocket);

	closesocket(clientSocket);

	return 0;
}