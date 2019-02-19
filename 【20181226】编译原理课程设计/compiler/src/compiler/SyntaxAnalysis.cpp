/*-------语法分析和翻译制导-------*/
#include "Syntax.h"

map<pair<string, string>, int> LL1List; //LL1分析表
map<pair<string, string>, int> Syntax::CreateLL1List() {
	preProcess();
	dataRevision(); //数据预处理
	DFS_First();
	DFS_Follow();
	getSelect();
	//for test
	/*for (int i = 0; i < size_of_prod; i++)
	{
		cout << "Select(" << i << ") = ";
		for (set<string>::iterator it = Select[i].begin(); it != Select[i].end(); it++)
			cout << *it << ",";
		cout << endl;
	}*/
	//for test
	map<pair<string, string>, int> tmp;
	set<string> column_of_LL1_list = terminators;
	column_of_LL1_list.insert("#");
	map<pair<string, string>, int> LL1List;
	for (set<string>::iterator it_nt = non_terminators.begin(); it_nt != non_terminators.end(); it_nt++)
		for (set<string>::iterator it_t = column_of_LL1_list.begin(); it_t != column_of_LL1_list.end(); it_t++)
			//if (list_of_LL1(*it_nt, *it_t) != -1) 
			tmp.insert(make_pair(make_pair(*it_nt, *it_t), list_of_LL1(*it_nt, *it_t)));
	return tmp;
}

bool Syntax::LL1_Analyse()
{
	//生成LL1分析表
	LL1List = CreateLL1List();
	stack<string> SYN;
	SYN.push("#"); //# 压栈
	SYN.push(prod[0].left); //开始符号压栈
	int pos = 0;
	pair<string, Token::TokenType> curstr = NEXT(pos);
	string curstate;
	while (!(SYN.top() == "#" && curstr.first == "#")) {
		curstate = SYN.top();
		//for test
//		cout << curstate << "出栈！";
//		cout << "当前从程序中读到的符号为：" << curstr.first << ",类型：" << curstr.second << endl;
		//for test
		SYN.pop();
		//for test
/*		cout << "栈中剩余元素为：";
		stack<string> tmpStack;
		while (!SYN.empty()) {
			tmpStack.push(SYN.top());
			SYN.pop();
		}
		while (!tmpStack.empty()) {
			cout << tmpStack.top() << ", ";
			SYN.push(tmpStack.top());
			tmpStack.pop();
		}cout << endl;
*/		//for test		
		if (terminators.find(curstate) != terminators.end())
		{	//终结符，比对
			if (curstate == "id"&&curstr.second == Token::_identifier 
				|| curstate == "float_const"&&curstr.second == Token::_constnum
				|| curstate == "char_const"&&curstr.second == Token::_character
				|| curstate == "string"&&curstr.second == Token::_string
				|| curstate == curstr.first)
			{	
				pos++;
				curstr = NEXT(pos);
			}
			else return false;
		}
		else if (non_terminators.find(curstate) != non_terminators.end())
		{	//非终结符，产生式逆序压栈
			int id_of_pord;
			if (curstr.second == Token::_identifier) 
				id_of_pord = LL1List[make_pair(curstate, "id")];
			else if(curstr.second == Token::_constnum)
				id_of_pord = LL1List[make_pair(curstate, "float_const")];//如何区分float_const, int_const
			else if(curstr.second == Token::_character)
				id_of_pord = LL1List[make_pair(curstate, "char_const")];
			else if(curstr.second == Token::_string)
				id_of_pord = LL1List[make_pair(curstate, "string")];
			else id_of_pord = LL1List[make_pair(curstate, curstr.first)]; 
			//检错
			if (id_of_pord == -1) {
				cout << "SYNTAX ERROR! Line: " << tokenSeq[pos].row << endl;
				exit(1);
			}
			//for test
/*			cout << "需要查看" << id_of_pord << "产生式:";
			cout << prod[id_of_pord].left << " --> ";
			for (int i = 0; i < prod[id_of_pord].right.size(); i++)cout << prod[id_of_pord].right[i] << " ";
			cout << endl;
*/			//for test
			if (id_of_pord != -1) {
				if (prod[id_of_pord].right[0] == "epsilon") continue;
				for (int i = prod[id_of_pord].right.size() - 1; i >= 0; i--) {//逆序压栈
					SYN.push(prod[id_of_pord].right[i]); 
					//for test
//					cout << prod[id_of_pord].right[i] << "进栈！" << "  ";
					//for test
				}
				//for test
/*				cout << "\n栈中剩余元素为：";
				stack<string> tmpStack;
				while (!SYN.empty()) {
					tmpStack.push(SYN.top());
					SYN.pop();
				}
				while (!tmpStack.empty()) {
					cout << tmpStack.top() << ", ";
					SYN.push(tmpStack.top());
					tmpStack.pop();
				}
				cout << "\n---------------------------------------------------\n\n";
*/				//for test	
			}
			else return false;
		}
		else { 
			//语义动作标号
			Call(curstate, pos, curstr.first); //调用对应的语义动作函数
		}
	}
	return true;
}

