#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include "Strsafe.h"
#include <string>
#include <vector>
#include <algorithm>

#pragma comment(lib, "Ws2_32.lib")

#define MAX_NAME 256
#define MAX_BUF_LEN 512
enum Action {CREATED, CLOSED, REOPENED, OPENED};

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

/*
struct charProcessAction {
	char createTime[MAX_BUF_LEN];
	char uptime[MAX_BUF_LEN];
	char username[MAX_BUF_LEN];
	char* exeFileName;
	char* action;
};*/

VOID filetimeToChar(FILETIME ft, char* result) {
	SYSTEMTIME st;
	char szLocalDate[255], szLocalTime[255];

	FileTimeToLocalFileTime(&ft, &ft);
	FileTimeToSystemTime(&ft, &st);
	GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &st, NULL, szLocalDate, 255);
	GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, NULL, szLocalTime, 255);
	std::string res = szLocalDate;
	res += " ";
	res += szLocalTime;
	strcpy_s(result, strlen(res.c_str()) + 1, res.c_str());
}

time_t filetimeToTimet(const FILETIME& ft)
{
	ULARGE_INTEGER ull;
	ull.LowPart = ft.dwLowDateTime;
	ull.HighPart = ft.dwHighDateTime;

	return ull.QuadPart / 10000000ULL - 11644473600ULL;
}

VOID getProcessUsername(DWORD processId, char* result)
{
    DWORD dwSize = 256;
    HANDLE hProcess;
    TOKEN_USER *pUserInfo;
	HANDLE TokenHandle;
    char name[MAX_NAME];
    char domain[MAX_NAME];
    int iUse;
 
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, processId);
    OpenProcessToken( hProcess, TOKEN_QUERY, &TokenHandle);
    pUserInfo = (PTOKEN_USER) GlobalAlloc( GPTR, dwSize );
    GetTokenInformation(TokenHandle, TokenUser, pUserInfo, dwSize, &dwSize );
	LookupAccountSid( 0, pUserInfo->User.Sid, name, &dwSize, domain, &dwSize, (PSID_NAME_USE)&iUse );
    strcpy_s(result, strlen(name) + 1, name);
    //printf( "%s\n", lpDomain, lpName );
    //result = staticName;
}

std::vector<processAction> getProcessList()
{
	HANDLE CONST hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	const int BUFFSIZE = 1024;
    PROCESSENTRY32 processList;
    TCHAR szBuff[BUFFSIZE];
    HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    HANDLE hProcess;
	FILETIME cpuTime;
	FILETIME sysTime;
	FILETIME createTime;
	FILETIME exitTime;
	char listProcessUsername[MAX_NAME];
	char currentProcessUsername[MAX_NAME];
	int processCounter = 0;
	std::vector<processAction> processes;
 
    processList.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnapshot, &processList);
    while(Process32Next(hSnapshot, &processList))
    {
		getProcessUsername(processList.th32ProcessID, listProcessUsername);
		getProcessUsername(GetCurrentProcessId(), currentProcessUsername);
		if (!strcmp(currentProcessUsername, listProcessUsername)) {
			processData pd;
			processAction pa;
			//if (processList.th32ProcessID == GetCurrentProcessId()){
				//printf(" | It's my process\n");
			//}

			//printf("ID: %08X;\n%s\r\n", processList.th32ProcessID, processList.szExeFile);

			//printf("User: %s \n", listProcessUsername);
			
			hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, processList.th32ProcessID);
			GetProcessTimes(hProcess, &createTime, &exitTime, &sysTime, &cpuTime);
			//printf("Uptime: ");
			//printf("%s", filetimeToChar(cpuTime));
			//printf("%d\n", filetimeToTimet(cpuTime));
			//printf("Created: ");
			//printf("%s", filetimeToChar(createTime));
			//printf("\n");

			processCounter++;

			pd.id = processList.th32ProcessID;
			strcpy_s(pd.exeFileName, strlen(processList.szExeFile) + 1, processList.szExeFile);
			strcpy_s(pd.username, strlen(currentProcessUsername) + 1, currentProcessUsername);
			pd.createTime = createTime;
			pd.uptime = cpuTime;

			pa.process = pd;
			pa.action = OPENED;
			processes.push_back(pa);
		}
    }

	printf("Total processes: %d\n", processCounter);
    CloseHandle(hSnapshot);
	return processes;
}

VOID checkProcesses(std::vector<processAction> &oldProcesses, std::vector<processAction> &changedProcesses) {
	std::vector<processAction> newProcesses = getProcessList();
	std::vector<bool> checkedNewProc(newProcesses.size(), false);
	std::vector<bool> checkedOldProc(oldProcesses.size(), false);

	std::vector<processAction> actions;

	for (int i = 0; i < oldProcesses.size(); i++) {
		for (int j = 0; j < newProcesses.size(); j++) {
			if (!strcmp(oldProcesses[i].process.exeFileName, newProcesses[j].process.exeFileName) && CompareFileTime(&oldProcesses[i].process.createTime, &newProcesses[j].process.createTime)) {
				//processAction pa;
				//pa.action = REOPENED;
				//pa.process = newProcesses[j].process;
				//actions.push_back(pa);
				checkedNewProc[j] = true;
			}
			if (!strcmp(oldProcesses[i].process.exeFileName, newProcesses[j].process.exeFileName) && oldProcesses[i].process.id == newProcesses[j].process.id) {
				checkedOldProc[i] = true;
				checkedNewProc[j] = true;
			}
		}
	}

	for (int i = 0; i < oldProcesses.size(); i++) {
		if (!checkedOldProc[i]) {
			printf("Closed %s\n", oldProcesses[i].process.exeFileName);
			processAction pa;
			pa.action = CLOSED;
			pa.process = oldProcesses[i].process;
			actions.push_back(pa);
		}
	}

	for (int i = 0; i < newProcesses.size(); i++) {
		if (!checkedNewProc[i]) {
			printf("Opened %s\n", newProcesses[i].process.exeFileName);
			processAction pa;
			pa.action = CREATED;
			pa.process = newProcesses[i].process;
			actions.push_back(pa);
		}
	}

	oldProcesses = newProcesses;
	changedProcesses = actions;
}

/*
charProcessAction paToCpa(processAction pa) {
	charProcessAction cpa;
	strcpy_s(cpa.username, sizeof(cpa.username), pa.process.username);
	cpa.exeFileName = (char*)pa.process.exeFileName;
	filetimeToChar(pa.process.createTime, cpa.createTime);
	filetimeToChar(pa.process.uptime, cpa.uptime);
	cpa.action = pa.action == REOPENED ? "reopened" : pa.action == CLOSED ? "closed" : pa.action == CREATED ? "created" : NULL;
	return cpa;
}*/

VOID sendToServer(SOCKET clientSocket, processAction paData) {
	//charProcessAction cpa = paToCpa(paData);

	int iRes = 0;

	iRes = send(clientSocket, (char *)&paData, sizeof(paData), 0);

	printf("Bytes Sent: %ld\n", iRes);
}

VOID sendVectorToServer(SOCKET clientSocket, std::vector<processAction> currentProcesses) {
	for (int i = 0; i < currentProcesses.size(); i++) {
		sendToServer(clientSocket, currentProcesses[i]);
	}
}

int main() {
	setlocale(LC_ALL, "");
	DWORD timerTime = 5000;

	constexpr unsigned short int serverPort = 1234;
	constexpr char serverAddress[] = "127.0.0.1";

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in clientSocketAddr;
	clientSocketAddr.sin_family = AF_INET;
	clientSocketAddr.sin_addr.s_addr = inet_addr(serverAddress);
	clientSocketAddr.sin_port = htons(serverPort);
	int connectResult = connect(clientSocket, (SOCKADDR*)&clientSocketAddr, sizeof(clientSocketAddr));
	if (connectResult)
		return 0;

	printf("connected to %s\n", serverAddress);

	std::vector<processAction> currentProcesses = getProcessList();
	std::vector<processAction> changedProcesses;
    //Send StartSessionData To Server
	sendVectorToServer(clientSocket, currentProcesses);

	while (true) {
		Sleep(timerTime);
		checkProcesses(currentProcesses, changedProcesses);
		sendVectorToServer(clientSocket, changedProcesses);
	}

	closesocket(clientSocket);

	system("pause");
    return 0;
}