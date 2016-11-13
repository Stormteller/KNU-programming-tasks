#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

const int M = 30000;

unsigned short memory[30000] = {0};
unsigned short variable = 0;
signed short pointer = 0;

void moveRight(){
	pointer = (pointer + 1) % M;
}

void moveLeft(){
	pointer == 0 ? pointer = 29999 : pointer--;
}

void moveToBegin(){
	pointer = 0;
}

void input(){
	cin >> memory[pointer];
	memory[pointer] %= 256;
}

void output(){
	cout << memory[pointer] << endl;
}

void prevToCur(){
	pointer == 0 ? memory[pointer] = memory[29999] : memory[pointer] = memory[pointer - 1];
}

void zeroCur(){
	memory[pointer] = 0;
}

void varToCur(){
	memory[pointer] = variable % 256;
}

void curToVar(){
	variable = memory[pointer];
}

void multiply(){
	pointer == 0 ? memory[pointer] = (memory[29999]*memory[0])%256 : memory[pointer] = (memory[pointer - 1]*memory[pointer])%256;
}

void division(){
	pointer == 0 ? memory[pointer] = memory[0] / memory[29999] : memory[pointer] = memory[pointer] / memory[pointer - 1];
}

void increase(){
	memory[pointer] = (memory[pointer] + 1) % 256;
}

void decrease(){
	memory[pointer] == 0 ? memory[pointer] = 0 : memory[pointer]--;
}

void outputVar(){
	cout << variable << endl;
}

void indexToVar(){
	variable = pointer;
}

int main(){
	string s;
	fstream fin("input.txt");
	fin >> s;
	vector<unsigned short> cycles;
	int brac_if = 0;
	int brac_while = 0;
	for (int i = 0; i < s.length(); i++){
		switch (s[i])
		{
		case '>': moveRight(); break;
		case '<': moveLeft(); break;
		case '|': moveToBegin(); break;
		case ',': input(); break;
		case '.': output(); break;
		case '=': prevToCur(); break;
		case '0': zeroCur(); break;
		case '!': curToVar(); break;
		case '?': varToCur(); break;
		case '*': multiply(); break;
		case '/': division(); break;
		case '+': increase(); break;
		case '-': decrease(); break;
		case '$': indexToVar(); break;
		case '^': outputVar(); break;
		case '(': {
			if (memory[pointer] == 0){
				while (s[i] != ')' || brac_if != 0) {
					i++;
					if (s[i] == '(') brac_if++;
					if (brac_if > 0 && s[i] == ')') brac_if--;
				}
			}
		} 
		break;
		case ')': break;
		case '[': {
			if (memory[pointer] != 0) cycles.push_back(i);
			else {
				while (s[i] != ']' || brac_while != 0) {
					i++;
					if (s[i] == '[') brac_while++;
					if (brac_while > 0 && s[i] == ']') brac_while--;
				}
			}
		}
		break;
		case ']': {
			if (memory[pointer] == 0) cycles.pop_back();
			else{
				i = cycles.back();
			}
		}
		default:
			break;
		}
	}
	system("pause");
	return 0;
}

