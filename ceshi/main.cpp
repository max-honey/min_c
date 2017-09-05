#include"title.h"
using namespace std;
string sign[10];
extern string str[10];
extern int syn;
//string str[10];
typedef struct Lnode {
	string name;
	int value_i = 0;
	int kind=0;
	float value_real;
	string value_str;
	struct Lnode * next;
}Node,*LNode; 
LNode L,st,pause;//L为头指针，st为尾指针, node为新创建的指针, pause为每次找到的指针位置。
void create_node(string &ch,int kind,string value_str,int value) {//创建新的节点
	LNode node = new Node;
	//node = (LNode)malloc(sizeof(Lnode));
	node->kind = kind;
	node->name = ch;
	node->value_i = value;
	node->value_str = value_str;
	node->next = NULL;
	/*if (kind == 1)
		cout << "kind=1" << endl;
	else if (kind == 2)
		cout << "kind=2" << endl;
	else if (kind == 3) 
		cout << "kind=3" << endl;*/
	st->next = node;
	st = node;
}
bool search_L(string ch) {//在链表里面查询是否已有ch
	LNode p;
	p = L;
	while (p!= NULL) {
		if (p->name == ch) {
			pause = p;
			return true;
		}
		else {
			p = p->next;
		}
	}
	return false;
}
void in() {
	int i = 1,j=0;
	if (str[i] =="\"") {//in "请输入:",a;
		i++;
		while (str[i] != "\"") {
			sign[j++] = str[i++];
		}
		sign[j] = "\0";
		int k = 0;
		while (sign[k] != "")cout << sign[k++];
		i+=2;
		if (!search_L(str[i])) {//寻找a在链表中，没有的话创建节点；
			cout << "have not the variable of " << str[i] << endl;
		}
		else {
			if (pause->kind == 1) {
				cin >> pause->value_real;
			}
			else if (pause->kind == 2) {
				cin >> pause->value_str;
			}
			else if (pause->kind == 3) {
				cin >> pause->value_i;
			}
		}
	}
	else if(search_L(str[i])){
		if (pause->kind == 1) {
			cin >> pause->value_real;
		}
		else if (pause->kind == 2) {
			cin >> pause->value_str;
		}
		else if (pause->kind == 3) {
			cin >> pause->value_i;
		}
	}
	else {
		cout << "have not the variable of " << str[i] << endl;
	}
}
void out() {
	int i = 1, j = 0, flag = 0;
	char *ch0;
	string ch;
	int cl_num;
	int value_i;
	double value_r;
	string value_s;
	ch = str[i];
	if (ch == "\"") {//out "输出字符串";||out"输出字符串\n";
		i++;
		while (str[i] != "\"") {
			if (str[i] == "\n") {
				i++; continue;
			}
			value_s += str[i++];
		}
		if (str[--i] == "\n")
			cout << value_s << endl;
		else
			cout << value_s;
	}

	else if (ch[i] >= '0'&&ch[i] <= '9') {
		cl_num = atoi(ch.c_str());
		i += 2;
		if (str[i] == "\"") {//out 10,"start";||out 10,"start\n";
			i++;
			while (str[i] != "\"") {
				if (str[i] == "\n") {
					i++; continue;
				}
				value_s += str[i++];
			}
			if (str[--i] == "\n") {
				for (int i = 0; i < cl_num; i++) {
					cout <<value_s << endl;
				}
			}
			else
				for (int i = 0; i < cl_num; i++) {
					cout << value_s << endl;
				}
		}

		else if (search_L(str[i])) {//out 10,a;
			if (pause->kind == 1) {
				value_r = pause->value_real;
				for (int i = 0; i < cl_num; i++) {
					cout << value_r;
				}
			}
			else if (pause->kind == 2) {
				value_s = pause->value_str;
				for (int i = 0; i < cl_num; i++) {
					cout << value_s;
				}
			}
			else if (pause->kind == 3) {
				value_i = pause->value_i;
				for (int i = 0; i < cl_num; i++) {
					cout << value_i;
				}
			}
		}
		else {
			cout << "have not the variable of " << str[i] << endl;
		}
	}
	else if (search_L(str[i])) {//out a;
		if (pause->kind == 1) {
			value_r = pause->value_real;
			cout << value_r << endl;
		}
		else if (pause->kind == 2) {
			value_s = pause->value_str;
			cout << value_s << endl;
		}
		else if (pause->kind == 3) {
			value_i = pause->value_i;
			cout << value_i << endl;
		}
	}
	else {
		cout << "have not the variable of " << str[i] << endl;
	}
		
}
void grammer() {
	int i = 0,j=0;
	int value_int;
	while (str[i] != ";") {
		if (str[i] == "int") {
			i++;
			while (str[i] != ";"&&str[i] != "("&&str[i] != ")"&&str[i] != "{"&&str[i] != "}"&&str[i] != "main"&&str[i] != ";") {
				j = i+1;
				if (str[j] == "=") {//定义的时候赋初值eg: int a=4;
					value_int= atoi(str[++j].c_str());
					create_node(str[i], 3, "",value_int);
					i += 3;
					continue;
				}
				if (str[i] == ",") {
					i++;
					continue;
				}
				create_node(str[i], 3,"",0);
				i++;
			}
		}
		else if (str[i] == "string") {
			while (str[++i] != ";") {
				if (str[i] == ",") {
					i++;
					continue;
				}
				create_node(str[i], 2,"",0);
			}

		}
		else if (str[i] == "real") {
			while (str[++i] != ";") {
				if (str[i] == ",") {
					i++;
					continue;
				}
				create_node(str[i], 1,"",0);
			}
		}
		else if (str[i] == "in") {
			in();
			i++;
		}
		else if (str[i] == "out") {
			out();
			i++;
		}
		else if (str[i] == "while") {
			i++;
		}
		else if (str[i] == "if") {
			i++;
		}
		else {
			if (search_L(str[i])) {//变量赋值eg: a=4;
				j = i + 1;
				if (str[j] == "=") {
					//if(str[++j])
					value_int = atoi(str[++j].c_str());
					pause->value_i = value_int;
					i += 3;
				}
			}
			else {
				i++;
			}
		}

	}
}
int main() {
	for (int i = 0; i < 10; i++)str[i] ="";
	L = new Node;
	L->next = NULL;
	st = L;
	lex();
	getchar();

	cout << "添加了一些说明" << endl;
	return 0;
}