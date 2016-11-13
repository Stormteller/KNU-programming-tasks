#include <iostream>
#include "queue.h"
#include <map>

using namespace std;

List<int> list_of_elems[1000];
map<int,bool> global_set;
int num = -1;

void printMenu(){
cout << "a - add pair\np - print list\n";
};

void setSet(){
	int c = 0;
	while(true){
	cin >> c;
	if(c == -1) break;
	global_set[c] = true; 
	};
};

void outputSet(){
	cout << "Your set is:\n"; 
	map<int,bool>::iterator it;
	for(it = global_set.begin(); it != global_set.end(); it++){
		cout << it->first << ' ';
	};
	cout << endl;
};

int addElem(int a){
	list_of_elems[++num].AddHead(a);
	return num;
};

void setRelation(int index_a, int b){
	list_of_elems[index_a].AddTail(b);
}

int inSetIndex(int a){
	for(int i = 0; i <= num; i++){
		if(list_of_elems[i].Head()->data == a) return i;
	}
	return -1;
};

bool isRelation(int index_a,int b){
	Node<int>* cur = list_of_elems[index_a].Head()->next;
	while(cur){
		if(cur->data == b) return true;
		cur = cur->next;
	}
	return false;
};

void addPair(){
int a,b;
cin >> a >> b;
if(inSetIndex(a) == -1) {
	int index_a = addElem(a);
	setRelation(index_a,b);
}
else {
	int index_a = inSetIndex(a);
	if(!isRelation(index_a,b))
	setRelation(index_a,b);
}
};

void printList(){
	cout << "Relation:\n";
	for(int i = 0; i <= num; i++){
		cout << list_of_elems[i].Head()->data << "->";
		Node<int>* cur = list_of_elems[i].Head()->next;
		while(cur){
			cout << cur->data << ' ';
			cur = cur->next;
		}
		cout << endl;
	}
	cout << endl;
	//system("pause");
};

bool isReflexive(){
	for(int i = 0; i <= num; i++){
	bool reflex = false;
	int cur_head = list_of_elems[i].Head()->data;
	Node<int>* cur_elem = list_of_elems[i].Head()->next;
		while(cur_elem){
			if(cur_head == cur_elem->data) reflex = true;
			cur_elem = cur_elem->next;
		}
		if(!reflex) return false;
	}
	return true;
};

bool isSymetric() {
	map<pair<int,int>,bool> set_of_pairs;
	for(int i = 0; i <= num; i++){
		Node<int>* cur_first = list_of_elems[i].Head();
		Node<int>* cur_second = list_of_elems[i].Head()->next;
		while(cur_second){
			set_of_pairs[pair<int,int>(cur_first->data,cur_second->data)]=true;
			cur_second = cur_second->next;
		}
	}
	for(int i = 0; i <= set_of_pairs.size() / 2 + 1; i++){
		if(!set_of_pairs.empty()){
			pair<int,int> cur_pair = set_of_pairs.begin()->first;
			if(cur_pair.first == cur_pair.second) {
				set_of_pairs.erase(set_of_pairs.find(cur_pair));
				continue;
			};
			if(set_of_pairs[pair<int,int>(cur_pair.second,cur_pair.first)]){
				set_of_pairs.erase(set_of_pairs.find(pair<int,int>(cur_pair.second,cur_pair.first)));
				set_of_pairs.erase(set_of_pairs.find(cur_pair));
			}
			else return false;
		}
	}
	return true;
};
/*
bool isTransitive(){
	for(int i = 0; i <= num; i++){
		Node<int>* cur_head_first = list_of_elems[i].Head();
		Node<int>* cur_tail_first = cur_head_first->next;
		while(cur_tail_first){
			



			cur_tail_first = cur_tail_first->next;
		}
	};
};
*/
int main()
{
char c = 'd';
cout << "Determine set" << endl;
setSet();
while(c != 'q'){
	system("cls");
	//printMenu();
	outputSet();
	printList();
	isReflexive()?cout << "Reflexive" << endl: cout << "Not reflexive" << endl;
	isSymetric()?cout << "Symetric" << endl: cout << "Not symetric" << endl;
	cin >> c;
	if(c == 'a') addPair();
}

system("pause");
return 0;
}