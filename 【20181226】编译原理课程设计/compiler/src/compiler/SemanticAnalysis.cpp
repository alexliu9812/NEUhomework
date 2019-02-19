#include "Syntax.h"

extern vector<vector<SymbolTable>> synbl;       //各级符号表！！！！很重要！！！！
int curSynblLev = 0;						 //当前所在符号表的层次
int preSynblLev = -1;						 //前一层符号表的层次

Syntax::Syntax() {
	quat.open("quat.dat");
	TapelIndex = 4;
	Action_map["PUSH"] = _push;
	Action_map["POP"] = _pop;
	Action_map["LABER"] = _laber;
	Action_map["GOTO"] = _goto;
	Action_map["ASSI"] = _assi;
	Action_map["GEQ"] = _geq;
	Action_map["GEQ_UNARY"] = _geq_unary;
	Action_map["RELATION"] = _relation;
	Action_map["IF"] = _if;
	Action_map["ELSE"] = _else;
	Action_map["WHILE"] = _while;
	Action_map["DO"] = _do;
	Action_map["LOGIC"] = _logic;
	Action_map["SCOPEINIT"] = _scope_init;
	Action_map["PARAM"] = _param;
	Action_map["CALL"] = _call;
	Action_map["END"] = _end;
	Action_map["RETURN"] = _return;
	Action_map["FOR"] = _for;
	Action_map["FORINC"] = _for_inc;
	Action_map["FORSECPRE"] = _for_sec_pre;
	Action_map["FORSECPST"] = _for_sec_post;
	Action_map["FORTHDPRE"] = _for_third_pre;
	Action_map["FORTHDPST"] = _for_third_post;
	Action_map["DOWHILE"] = _do_while;
	Action_map["DOWHCMP"] = _do_while_cmp;
	Action_map["ENDDOWH"] = _end_dowh;
	Action_map["SCANF"] = _cin;
	Action_map["PRINT"] = _cout;
	Action_map["INITDECL"] = _init_decl;
	Action_map["INITARR"] = _init_arr;
	Action_map["GETFUNCNM"] = _get_func_name;
	Action_map["STRUCTINIT"] = _struct_scopeinit;

	Tapel[0].Tval = TypeTable::_int;
	Tapel[0].Tpoint = -1;
	Tapel[1].Tval = TypeTable::_float;
	Tapel[1].Tpoint = -1;
	Tapel[2].Tval = TypeTable::_double;
	Tapel[2].Tpoint = -1;
	Tapel[3].Tval = TypeTable::_long;
	Tapel[3].Tpoint = -1;
	Tapel[4].Tval = TypeTable::_short;
	Tapel[4].Tpoint = -1;
	Tapel[5].Tval = TypeTable::_char;
	Tapel[5].Tpoint = -1;
	SymbolTable tmpsymb; //初始化全局符号表
	tmpsymb.prelev = -1;
	vector<SymbolTable> tmpvec;
	tmpvec.push_back(tmpsymb);
	synbl.push_back(tmpvec);
}
//return pair<typeId, sizeof(dataType)> 
pair<int, int> Syntax::getTypeCode(string type) //返回类码及变量所占内存单元的长度
{
	if (type == "int") return make_pair(0, 2);
	else if (type == "float") return make_pair(1, 2);
	else if (type == "double") return make_pair(2, 4);
	else if (type == "long") return make_pair(3, 4);
	else if (type == "short") return make_pair(4, 1);
	else if (type == "char") return make_pair(5, 2);
	else if (type == "void") return make_pair(-1, 0); //用void定义变量，错
	/*else {
	//数组类型
	Tapel[TapelIndex++].Tval =
	}*/
}

bool Syntax::isExistInSynbl(string id, int index) {
	if (!synbl.empty() && index <= synbl.size()) {
		if (index >= synbl.size()) index = synbl.size() - 1;
		vector<SymbolTable>::iterator it = synbl[index].begin(), stor_it = it;
		for (; it != synbl[index].end(); it++) {
			if (it->name == id) {
				return true;
			}
		}
		if (it == synbl[index].end() || synbl[index][0].prelev != -1) {
			//当前作用域的符号表中未找到该标识符，且该作用域非全局作用域
			return isExistInSynbl(id, synbl[index][0].prelev);
		}
		else if (it == synbl[index].end() || synbl[index][0].prelev == -1) {
			return false;
		}
	}
	else return false;
}

int Syntax::getOffset(string id, int index) {
	if (!synbl.empty() && index <= synbl.size()) {
		if (index >= synbl.size()) index = synbl.size() - 1;
		vector<SymbolTable>::iterator it = synbl[index].begin(), stor_it = it;
		for (; it != synbl[index].end(); it++) {
			if (it->name == id) {
				return it->offset;
			}
		}
		if (it == synbl[index].end() || synbl[index][0].prelev != -1) {
			//当前作用域的符号表中未找到该标识符，且该作用域非全局作用域
			return getOffset(id, synbl[index][0].prelev);
		}
		else if (it == synbl[index].end() || synbl[index][0].prelev == -1) {
			return -1;
		}
	}
	else return -1;
}

bool isExistInCurDomain(string id, int index) {
	if (!synbl.empty() && index <= synbl.size()) {
		if (index >= synbl.size()) index = synbl.size() - 1;
		for (vector<SymbolTable>::iterator it = synbl[index].begin(); it != synbl[index].end(); it++) {
			if (it->name == id) {
				return true;
			}
		}
		return false;
	}
}

int token_ptr = 0; //token索引
static int qtmpID = 0;
string tmpstr;
int paramId = 1; //标记第几个参数
pair<string, int> tmp, funcName;
extern int off; //暂存偏移量
bool isElif = false;
void Syntax::Call(string Action, int TokenIndex, string curstr) {
	vector<SymbolTable> tmpSynbl; //临时单符号表
	SymbolTable tmpNode; //临时单符号表结点
	stack<pair<string, int>> tmpStack;
	if (!quat) {
		cout << "四元式文件打开出错！" << endl;
		exit(1);
	}
	//cout << "*****************语义栈内容SEM***********************" << endl;
	switch (Action_map[Action])
	{
	case Action_id::_push: SEM.push(make_pair(curstr, TokenIndex));
		//for test
		//cout << curstr << "压入语义栈SEM" << endl;
		//for test
		break;
	case Action_id::_pop:
		while (!SEM.empty()) {
			if (tokenSeq[SEM.top().second].type == _constnum)
			{	//赋值语句 stack<pair<string, int>> SEM;
				string constnum = SEM.top().first; //记录下该常数
				SEM.pop(); //值出栈
				token_ptr = SEM.top().second; //id的Token索引
				int i;
				for (i = 0; !synbl.empty() && curSynblLev < synbl.size() && i < synbl[curSynblLev].size(); i++) {
					//检查该变量是否已经定义过
					if (synbl[curSynblLev][i].name == identifier_table[tokenSeq[SEM.top().second].id].name) {
						//重复定义
						cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
						cout << "error C2086: “int " << identifier_table[tokenSeq[SEM.top().second].id].name << "”: 重定义." << endl;
						//SEM.pop();
						exit(1); //重定义直接停止编译
						//break;
					}
				}
				//if (!synbl.empty() && i < synbl[curSynblLev].size()) continue; //存在重定义
				tmpNode.name = SEM.top().first;
				tmpNode.prelev = preSynblLev;
				//cout << "tmpNode.prelev = " << tmpNode.prelev << endl;//for test
				SEM.pop(); //id出栈
				stack<pair<string, int>> tmpSEM;
				while (!SEM.empty() && tokenSeq[SEM.top().second].type != _keyword) {
					tmpSEM.push(SEM.top());
					SEM.pop();
				} //暂且过滤掉同一行代码前面的定义性语句
				string tmptype = "";
				while (!SEM.empty() && tokenSeq[SEM.top().second].type == _keyword) {
					//填符号表的Type类型区，该区链接到类型表
					tmptype += (SEM.top().first + " ");
					tmpSEM.push(SEM.top());
					SEM.pop();
				}
				tmptype = tmptype.substr(0, tmptype.size() - 1); //去掉最后面的空格
				tmpNode.typ = getTypeCode(tmptype).first; //填写符号表的TYP类型区 
				//identifier_table[synbl_ptr].typ = getTypeCode(tmptype);   
				if (tmpNode.typ == -1) {
					//void类型被用于定义变量，错误处理
					cout << "Line " << tokenSeq[token_ptr].row << ": " << endl;
					cout << "error C2182: “" << SEM.top().first << "”: 非法使用“void”类型" << endl;
					exit(1);
				}
				tmpNode.offset = off;
				off += getTypeCode(tmptype).second;
				//cout << "$$$$$$$$$$$$$$$$$$$$$$$$$ off = " << off << endl; //for test
				if (!synbl.empty() && curSynblLev < synbl.size()) {
					synbl[curSynblLev].push_back(tmpNode); //单符号表已经存在的情况
				}
				//if (curSynblLev >= synbl.size()) {
				else {
					//当前层次是首次填写，即单符号表不存在的情况
					tmpSynbl.push_back(tmpNode); //当前结点加入单符号表中
					synbl.push_back(tmpSynbl);
					//cout << "创建新节点" << synbl.size() - 1 << ": prelev = " << tmpNode.prelev << endl;//for test
				}
				quat << "= " << constnum << " # " << tmpNode.name << endl; //生成四元式
				while (!tmpSEM.empty()) { //暂存的项倒回原语义栈中
					SEM.push(tmpSEM.top());
					tmpSEM.pop();
				}
			}
			else if (tokenSeq[SEM.top().second].type == _identifier) {
				//定义性语句 int b;
				int i;
				for (i = 0; !synbl.empty() && curSynblLev < synbl.size() && i < synbl[curSynblLev].size(); i++) {
					//检查该变量是否已经定义过
					if (synbl[curSynblLev][i].name == SEM.top().first) {
						//重复定义
						cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
						cout << "error C2086: “int " << SEM.top().first << "”: 重定义." << endl;
						//SEM.pop();
						//break;
						exit(1); //重定义直接停止编译
					}
				}
				//if (!synbl.empty() && i < synbl[curSynblLev].size()) continue; //存在重定义
				tmpNode.name = SEM.top().first;
				tmpNode.prelev = preSynblLev;
				//cout << "tmpNode.prelev = " << tmpNode.prelev << endl; //for test
				//synbl_ptr = tokenSeq[SEM.top().second].id;
				token_ptr = SEM.top().second;
				SEM.pop(); //id出栈
				stack<pair<string, int>> tmpSEM;
				while (!SEM.empty() && tokenSeq[SEM.top().second].type != _keyword) {
					tmpSEM.push(SEM.top());
					SEM.pop();
				}
				string tmptype = "";
				while (!SEM.empty() && tokenSeq[SEM.top().second].type == _keyword) {
					//填符号表的Type类型区，该区链接到类型表
					tmptype += (SEM.top().first + " ");
					tmpSEM.push(SEM.top());
					SEM.pop();
				}
				tmptype = tmptype.substr(0, tmptype.size() - 1); //去掉最后面的空格
				tmpNode.typ = getTypeCode(tmptype).first; //填写符号表的TYP类型区
														  //identifier_table[synbl_ptr].typ = getTypeCode(tmptype);   //填写符号表的TYP类型区
				if (tmpNode.typ == -1) {
					//void类型被用于定义变量，错误处理
					cout << "Line " << tokenSeq[token_ptr].row << ": " << endl;
					cout << "error C2182: “" << tmpNode.name << "”: 非法使用“void”类型." << endl;
					exit(1);
				}

				//for test
				//cout << tmpNode.typ << "填入符号表TYP区, " << endl;
				//for test
				tmpNode.offset = off; //记录之前的偏移量
				//cout << "当前偏移量为：" << tmpNode.offset << endl; //for test
				off += getTypeCode(tmptype).second; //更新当前偏移量
				//cout << "$$$$$$$$$$$$$$$$$$$$$$$$$ off = " << off << endl; //for test
				if (!synbl.empty() && curSynblLev < synbl.size()) {
					synbl[curSynblLev].push_back(tmpNode); //单符号表已经存在的情况
				//	cout << endl << tmpNode.name << "进入synbl[" << curSynblLev << "]" << endl; //for test
				}
				//if (curSynblLev >= synbl.size()) {
				else {
					//当前层次是首次填写，即单符号表不存在的情况
					tmpSynbl.push_back(tmpNode); //当前结点加入单符号表中
					synbl.push_back(tmpSynbl);
				//	cout << "创建总表新节点" << synbl.size() - 1 << ": " << tmpNode.name << "进入";
				//	cout << ", prevel = " << tmpNode.prelev << endl;//for test
				}

				while (!tmpSEM.empty()) { //暂存的项倒回原语义栈中
					SEM.push(tmpSEM.top());
					tmpSEM.pop();
				}
			}
			else SEM.pop();
		}
		break;
	case Action_id::_laber: quat << "label # # " << SEM.top().first << endl;
		SEM.pop();
		break;
	case Action_id::_goto: quat << "gt # # " << curstr << endl;
		break;
	case Action_id::_assi:
		if (!SEM.empty()) {
			tmp = SEM.top();
			SEM.pop(); //number is out!
		/*	if (tmp.first == "1")
				cout << "stop";*/
			if (tmp.first == "return_val") {
				SEM.pop(); //pop =
				if (!SEM.empty() && tokenSeq[SEM.top().second].type == _identifier) {
					quat << "mov " << SEM.top().first << " # DX" << endl;
				}
			}
			else if (!SEM.empty() && SEM.top().first == "=") {
				//quat << SEM.top().first << " " << tmp.first << " # ";
				SEM.pop(); //= is out
				//cout << "curSynblLev = " << curSynblLev << endl;//for test
				//cout << "preSynblLev = " << preSynblLev << endl;//for test
				/*if (SEM.top().first == "b")
					cout << "stop";*/
				if (!SEM.empty() && tokenSeq[SEM.top().second].type == _constnum) {
					//数组赋值
					pair<string, int> arroffset = SEM.top();
					SEM.pop(); //a[index]的index出栈
					//if(stoi(arroffset.first)>=)//@@@@@@未解决用户操作数组越界的情况
					quat << "movs " << to_string(getOffset(SEM.top().first, curSynblLev) + stoi(arroffset.first)*2) << " # " << tmp.first << endl;
					//目前支持int型数组，int长度为2
				}
				else if (!SEM.empty() && (tokenSeq[SEM.top().second].type == _identifier || SEM.top().second == -1)) {
					quat << "= " << tmp.first << " # ";
					if (SEM.top().second != -1 && !isExistInSynbl(SEM.top().first, curSynblLev)) {
						//常规变量赋值
						cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
						cout << "error C2065: “" << SEM.top().first << "”: 未声明的标识符" << endl;
						exit(1);
					}
					quat << SEM.top().first << endl;
				}
				//SEM.pop(); //delete it!
			}
			else if (!SEM.empty() && regex_match(SEM.top().first, regex("\\+=|-=|\\*=|/=|%=|&=|\\|=|^=|>>=|<<="))) {
				if (regex_match(SEM.top().first, regex("\\+=|-=|\\*=|/=|%=")))
					quat << SEM.top().first[0] << " ";
				else if (SEM.top().first == "&=") quat << "and ";
				else if (SEM.top().first == "|=") quat << "or ";
				else if (SEM.top().first == "^=") quat << "not ";
				else if (SEM.top().first == ">>=") quat << "shr ";
				else if (SEM.top().first == "<<=") quat << "shl ";
				SEM.pop();
				if (SEM.top().second != -1 && !isExistInSynbl(SEM.top().first, curSynblLev)) {
					cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
					cout << "error C2065: “" << SEM.top().first << "”: 未声明的标识符" << endl;
					exit(1);
				}
				quat << SEM.top().first << " " << tmp.first << " qtmp" + to_string(qtmpID) << endl;
				quat << "= qtmp" + to_string(qtmpID) << " # " << SEM.top().first << endl;
				//SEM.pop();//delete it!
				qtmpID++;
			}
			else if (!SEM.empty() && tokenSeq[SEM.top().second].type == _identifier && tokenSeq[tmp.second].type == _constnum) {
				//数组元素赋值给一个变量,arr_index is out in tmp, int b = a .1
				int memPos = getOffset(SEM.top().first, curSynblLev) + stoi(tmp.first) * 2;
				pair<string, int> tmpa = SEM.top();
				SEM.pop(); //a is out
				if (!SEM.empty() && SEM.top().first == "=") {
					SEM.pop();//= is out
					quat << "movs " << SEM.top().first << " # " << to_string(memPos) << endl;
				}
				else {
					SEM.push(tmpa);
					SEM.push(tmp);
				}
			}
			else SEM.push(tmp);
		}
		break;
	case Action_id::_geq:
		tmpstr = SEM.top().first + " "; //cout << tmpstr << "is out!" << endl;//for test
		SEM.pop();
		quat << SEM.top().first << " ";   //cout << SEM.top().first << "is out!" << endl;//for test
		SEM.pop();
		quat << SEM.top().first << " " << tmpstr << "qtmp" + to_string(qtmpID) << endl;
		//cout << SEM.top().first << "is out!" << endl; //for test
		SEM.pop();
		SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
		qtmpID++;
		break;
	case Action_id::_geq_unary:
		if (!SEM.empty() && (SEM.top().first == "++" || SEM.top().first == "--")) {
			quat << SEM.top().first[0] << " ";
			SEM.pop();
			quat << SEM.top().first << " 1 " << "qtmp" + to_string(qtmpID) << endl;
			tmp = SEM.top();
			SEM.pop();
			quat << "= " << "qtmp" + to_string(qtmpID) << " # " << tmp.first << endl;
			SEM.push(tmp);
			qtmpID++;
		}
		else if (!SEM.empty() && (tokenSeq[SEM.top().second].type == _identifier || SEM.top().second == -1)) {
			tmp = SEM.top();
			SEM.pop();
			if (!SEM.empty() && (SEM.top().first == "++" || SEM.top().first == "--")) {
				quat << SEM.top().first[0] << " " << tmp.first << " 1 " << "qtmp" + to_string(qtmpID) << endl;
				quat << "= " << "qtmp" + to_string(qtmpID) << " # " << tmp.first << endl;
				SEM.pop();
				SEM.push(tmp);
				qtmpID++;
			}
			else SEM.push(tmp);
		}
		else if (!SEM.empty() && (SEM.top().second == -1 || tokenSeq[SEM.top().second].type == _identifier || tokenSeq[SEM.top().second].type == _constnum)) {
			tmp = SEM.top();
			SEM.pop();
			if (!SEM.empty() && SEM.top().first == "~") {
				quat << "not " << tmp.first << " # qtmp" + to_string(qtmpID) << endl;
				SEM.pop();
				SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
				qtmpID++;
			}
			else SEM.push(tmp);
		}
		break;
	case Action_id::_relation:
		if (SEM.top().second == -1 || tokenSeq[SEM.top().second].type == _identifier || tokenSeq[SEM.top().second].type == _constnum) {
			if (tokenSeq[SEM.top().second].type == _identifier) {
				//检查是否未定义
				if (SEM.top().second != -1 && !isExistInSynbl(SEM.top().first, curSynblLev)) {
					cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
					cout << "error C2065: “" << SEM.top().first << "”: 未声明的标识符" << endl;
					exit(1);
				}
			}
			tmp = SEM.top();
			SEM.pop();
			if (SEM.top().first == "<" || SEM.top().first == ">" || SEM.top().first == "<=" || SEM.top().first == ">="
				|| SEM.top().first == "==" || SEM.top().first == "!=") {
				quat << SEM.top().first << " ";
				SEM.pop();
				if (tokenSeq[SEM.top().second].type == _identifier) {
					//检查是否未定义
					if (SEM.top().second != -1 && !isExistInSynbl(SEM.top().first, curSynblLev)) {
						//cout << "!isExistInSynbl(" << SEM.top().first << ", " << curSynblLev << ")" << endl;
						cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
						cout << "error C2065: “" << SEM.top().first << "”: 未声明的标识符" << endl;
						exit(1);
					}
				}
				quat << SEM.top().first << " " << tmp.first << " qtmp" + to_string(qtmpID) << endl;
				SEM.pop();
				SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
				qtmpID++;
			}
			else SEM.push(tmp);
		}
		break;
	case Action_id::_if:
		if (!SEM.empty() && SEM.top().second == -1) {
			if (isElif == false) { //只有if
				//cout << "------------IF------------" << endl;
				/*if (synbl.size() == 5)
					cout << "stop";*/
				preSynblLev = curSynblLev;
				//cout << "preSynblLev = " << preSynblLev << endl;//for test
				curSynblLev = synbl.size(); //出了函数作用域后，要cur = pre;
				//cout << "curSynblLev = " << curSynblLev << endl;//for test
				//tmpNode.name = nullptr;
				tmpNode.prelev = preSynblLev;
				tmpNode.domainName = "if";
				tmpSynbl.push_back(tmpNode);
				synbl.push_back(tmpSynbl);
				//cout << "符号总表创建新节点" << synbl.size() - 1 << ": prelev = " << tmpNode.prelev << endl;//for test
				//cout << "------------IF------------" << endl;//for test

				quat << "if " << SEM.top().first << " # " << curSynblLev << endl;
				SEM.pop();
			}
			else {
				//else if...
				synbl[curSynblLev][0].domainName = "if";
				quat << "if " << SEM.top().first << " # " << curSynblLev << endl;
				SEM.pop();
			}
		}
		break;
	case Action_id::_else:
		preSynblLev = curSynblLev;
		curSynblLev = synbl.size(); //出了函数作用域后，要cur = pre;
		tmpNode.prelev = preSynblLev;
		tmpNode.domainName = "else";
		tmpSynbl.push_back(tmpNode);
		synbl.push_back(tmpSynbl);
		isElif = true;
		quat << "el # # " << curSynblLev << endl;
		break;
	case Action_id::_while:
		preSynblLev = curSynblLev;
		curSynblLev = synbl.size(); //出了函数作用域后，要cur = pre;
		tmpNode.prelev = preSynblLev;
		tmpNode.domainName = "while";
		tmpSynbl.push_back(tmpNode);
		synbl.push_back(tmpSynbl);

		quat << "wh # # " << curSynblLev << endl;
		break;
	case Action_id::_do:
		if (SEM.top().second == -1) {
			quat << "do " << SEM.top().first << " # #" << endl;
			SEM.pop();
		}
		break;
	case Action_id::_logic:
		if (!SEM.empty() && (SEM.top().second == -1 || tokenSeq[SEM.top().second].type == _identifier || tokenSeq[SEM.top().second].type == _constnum))
		{
			tmp = SEM.top();
			SEM.pop();
			if (!SEM.empty() && (SEM.top().first == "&&" || SEM.top().first == "&")) {
				SEM.pop(); //&& is out!
				quat << "and " << SEM.top().first << " " << tmp.first << " qtmp" + to_string(qtmpID) << endl;
				SEM.pop();
				SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
				qtmpID++;
			}
			else if (!SEM.empty() && (SEM.top().first == "||" || SEM.top().first == "|")) {
				SEM.pop(); //|| is out!
				quat << "or " << SEM.top().first << " " << tmp.first << " qtmp" + to_string(qtmpID) << endl;
				SEM.pop();
				SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
				qtmpID++;
			}
			else if (!SEM.empty() && (SEM.top().first == "^")) {
				SEM.pop(); //^ is out!
				quat << "xor " << SEM.top().first << " " << tmp.first << " qtmp" + to_string(qtmpID) << endl;
				SEM.pop();
				SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
				qtmpID++;
			}
			else if (!SEM.empty() && (SEM.top().first == "<<")) {
				SEM.pop();
				quat << "shl " << SEM.top().first << " " << tmp.first << " qtmp" + to_string(qtmpID) << endl;
				SEM.pop();
				SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
				qtmpID++;
			}
			else if (!SEM.empty() && (SEM.top().first == ">>")) {
				SEM.pop();
				quat << "shr " << SEM.top().first << " " << tmp.first << " qtmp" + to_string(qtmpID) << endl;
				SEM.pop();
				SEM.push(make_pair("qtmp" + to_string(qtmpID), -1));
				qtmpID++;
			}
			else SEM.push(tmp);
		}
		break;
	case Action_id::_scope_init:
		if (tokenSeq[SEM.top().second].type == _identifier) {
			preSynblLev = curSynblLev;   //当前层次变为上一层
			curSynblLev = synbl.size();  //当前层为符号总表中最新开辟的一层
			tmpNode.prelev = preSynblLev;//新作用域表的指针域记录上一层的索引号
			tmpNode.domainName = SEM.top().first;//记录新作用域的域名
			tmpSynbl.push_back(tmpNode);
			synbl.push_back(tmpSynbl);   //在符号总表中为新作用域开辟空间

			tmp = SEM.top();
			SEM.pop();
			if (tokenSeq[SEM.top().second].type == _keyword) {
				quat << "func " << tmp.first << " # " << curSynblLev << endl;
				//quat << "func "<<curSynblLev<<" # " << tmp.first << endl; //generate function quat
				SEM.pop(); //data type is out of stack!
				while (!SEM.empty()) { //开启一个新的作用域--函数，把SEM栈中之前的内容全部清空
					SEM.pop();
				}
			}
			else SEM.push(tmp);
		}
		break;
	case Action_id::_get_func_name:
		if (!SEM.empty() && tokenSeq[SEM.top().second].type == _identifier) {
			paramId = 1;
			funcName = SEM.top();
		}
		break;
	case Action_id::_param:
		//生成实参四元式
		if (SEM.top().second == -1 || tokenSeq[SEM.top().second].type == _identifier || tokenSeq[SEM.top().second].type == _constnum) {
			//quat << "param # # " << SEM.top().first << endl;
			int i;
			for (i = 0; i < synbl.size(); i++) {
				if (synbl[i][0].domainName == funcName.first) {
					quat << "mov " << synbl[i][paramId].offset << " # " << SEM.top().first << endl;
					break;
				}
			}
			if (i < synbl.size()) //找到了
				SEM.pop();
			else {
				//没找到该函数
				cout << "Line " << tokenSeq[funcName.second].row << ": ";
				cout << "'" << funcName.first << "' was not declared in this scope" << endl;
				exit(1);
			}
			paramId++;
		}
		break;
	case Action_id::_call:
		if (tokenSeq[SEM.top().second].type == _identifier) {
			quat << "call # # " << SEM.top().first << endl;
			SEM.pop();
			SEM.push(make_pair("return_val", -3));
		}
		break;
	case Action_id::_end:
		//cout << "---------END---------" << endl;//for test
		/*if (synbl[curSynblLev][0].domainName == "max")
			cout << "stop";*/
		quat << "end # # " << synbl[curSynblLev][0].domainName << endl;
		//cout<< "end # # " << synbl[curSynblLev][0].domainName << endl;//for test
		curSynblLev = preSynblLev;					//恢复当前作用域为上一层作用域
		preSynblLev = synbl[preSynblLev][0].prelev; //恢复上一层作用为上上层作用域
		//cout << "preSynblLev = " << preSynblLev << endl;//for test
		//cout << "---------END---------" << endl;//for test
		break;
	case Action_id::_return:
		if (!SEM.empty() && (SEM.top().second == -1 || tokenSeq[SEM.top().second].type == _identifier || tokenSeq[SEM.top().second].type == _constnum)) {
			quat << "re " << SEM.top().first << " # #" << endl;
		}
		else if (SEM.empty()) {
			quat << "re void # #" << endl;
		}
		break;
	case Action_id::_for:
		preSynblLev = curSynblLev;
		curSynblLev = synbl.size();
		tmpNode.prelev = preSynblLev;
		tmpNode.domainName = "for";
		tmpSynbl.push_back(tmpNode);
		synbl.push_back(tmpSynbl);
		quat << "for # # " << curSynblLev << endl;
		break;
	case Action_id::_for_inc:
		if (synbl[curSynblLev][0].domainName == "for") {
			quat << "jmp # # inc" << endl;
		}
		break;
	case Action_id::_for_sec_pre:
		if (synbl[curSynblLev][0].domainName == "for") {
			quat << "label # # cmp" << endl;
		}
		break;
	case Action_id::_for_sec_post:
		if (synbl[curSynblLev][0].domainName == "for") {
			if (SEM.top().second == -1) {
				quat << "do " << SEM.top().first << " # #" << endl;
				quat << "jmp # # end" << endl;
				quat << "jmp # # start" << endl;
			}
		}
		break;
	case Action_id::_for_third_pre:
		if (synbl[curSynblLev][0].domainName == "for") {
			quat << "label # # inc" << endl;
		}
		break;
	case Action_id::_for_third_post:
		if (synbl[curSynblLev][0].domainName == "for") {
			quat << "jmp # # cmp" << endl;
			quat << "label # # start" << endl;
		}
		break;
	case Action_id::_do_while:
		preSynblLev = curSynblLev;
		curSynblLev = synbl.size(); //出了函数作用域后，要cur = pre;
		tmpNode.prelev = preSynblLev;
		tmpNode.domainName = "dowhile";
		tmpSynbl.push_back(tmpNode);
		synbl.push_back(tmpSynbl);

		quat << "dowhile # # " << curSynblLev << endl;
		quat << "label # # start" << endl;
		break;
	case Action_id::_do_while_cmp:
		if (synbl[curSynblLev][0].domainName == "dowhile") {
			quat << "dowhcmp # # #" << endl;
		}
		break;
	case Action_id::_end_dowh:
		if (SEM.top().second == -1) {
			quat << "do " << SEM.top().first << " # #" << endl;
			quat << "jmp # # start" << endl;
			//quat << "end # # dowhile" << endl;
		}
		break;
	case Action_id::_cin:
		if (tokenSeq[SEM.top().second].type == _identifier) {
			quat << "cin # # " << SEM.top().first << endl;
		}
		break;
	case Action_id::_cout:
		if (!SEM.empty() && (tokenSeq[SEM.top().second].type == _identifier || tokenSeq[SEM.top().second].type == _constnum)) {
			tmp = SEM.top();
			if (tokenSeq[SEM.top().second].type = _identifier) {
				//输出的是变量的值
				if (!isExistInSynbl(SEM.top().first, curSynblLev)) {
					cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
					cout << "error C2065: “" << SEM.top().first << "”: 未声明的标识符" << endl;
					exit(1);
				}
			}
			SEM.pop(); //输出内容出栈
			if (!SEM.empty() && tokenSeq[SEM.top().second].type == _constnum)
			{
				quat << "cout " << SEM.top().first << " # " << tmp.first << endl;
				SEM.pop();
			}
			//else SEM.push(tmp);
			else quat << "cout 10 # " << tmp.first << endl;
		}
		break;
	case Action_id::_init_decl:
	{
		if (!SEM.empty() && tokenSeq[SEM.top().second].type != _keyword) {
			int i;
			for (i = 1; !synbl.empty() && curSynblLev < synbl.size() && i < synbl[curSynblLev].size(); i++) {
				//检查该变量是否已经定义过
				if (synbl[curSynblLev][i].name == SEM.top().first) {
					//重复定义
					cout << "Line " << tokenSeq[SEM.top().second].row << ": ";
					cout << "error C2086: “int " << SEM.top().first << "”: 重定义." << endl;
					exit(1); //重定义直接停止编译
				}
			}
			tmp = SEM.top();
			tmpNode.prelev = preSynblLev;
			tmpNode.name = tmp.first;
			stack<pair<string, int>> tmpSEM;
			while (!SEM.empty() && tokenSeq[SEM.top().second].type != _keyword) {
				tmpSEM.push(SEM.top());
				SEM.pop();
			}
			tmpNode.typ = getTypeCode(SEM.top().first).first; //填写符号表的TYP类型区
			if (tmpNode.typ == -1) {
				//void类型被用于定义变量，错误处理
				cout << "Line " << tokenSeq[tmp.second].row << ": ";
				cout << "error C2182: “" << tmpNode.name << "”: 非法使用“void”类型." << endl;
				exit(1);
			}
			tmpNode.offset = off; //记录之前的偏移量
			off += getTypeCode(SEM.top().first).second; //更新当前偏移量
			//cout << "$$$$$$$$$$$$$$$$$$$$$$$$$ off = " << off << endl; //for test
			//SEM.pop(); //int出栈，数据类型出栈????????????????????????
			if (!synbl.empty() && curSynblLev < synbl.size()) {
				synbl[curSynblLev].push_back(tmpNode); //单符号表已经存在的情况
			//	cout << endl << tmpNode.name << "进入synbl[" << curSynblLev << "]" << endl; //for test
			}
			else {
				//当前层次是首次填写，即单符号表不存在的情况
				tmpSynbl.push_back(tmpNode); //当前结点加入单符号表中
				synbl.push_back(tmpSynbl);
				//	cout << "创建总表新节点" << synbl.size() - 1 << ": " << tmpNode.name << "进入";
				//	cout << ", prevel = " << tmpNode.prelev << endl;//for test
			}
			while (!tmpSEM.empty()) { //暂存的项倒回原语义栈中
				SEM.push(tmpSEM.top());
				tmpSEM.pop();
			}
		}
	}
	break;
	case Action_id::_init_arr:
		if (!SEM.empty() && tokenSeq[SEM.top().second].type == _constnum) {
		//	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$ off = " << off << endl; //for test
			tmp = SEM.top();
			SEM.pop();
			if (!SEM.empty() && tokenSeq[SEM.top().second].type == _identifier) {
				//vector<SymbolTable> tmpSynbl; //临时单符号表
				//SymbolTable tmpNode; //临时单符号表结点
				tmpNode.name = SEM.top().first;
				pair<string, int> idtmp = SEM.top();
				SEM.pop();//id is out!
				tmpNode.prelev = preSynblLev;
				tmpNode.offset = off;
				if (!SEM.empty() && tokenSeq[SEM.top().second].type == _keyword) {
					tmpNode.typ = getTypeCode(SEM.top().first).first;
					off += getTypeCode(SEM.top().first).second * (stoi(tmp.first));
					synbl[curSynblLev].push_back(tmpNode);
					//SEM.pop();//int is out
					//SEM.push(idtmp);
				}
			}
		}
		break;
	case Action_id::_struct_scopeinit:
		preSynblLev = curSynblLev;
		curSynblLev = synbl.size(); //开辟一个新的域，结构体作用域
		tmpNode.prelev = preSynblLev;
		if (!SEM.empty() && tokenSeq[SEM.top().second].type == _identifier) {
			tmp = SEM.top();
			tmpNode.domainName = tmp.first;
			SEM.pop(); //id is out!
			if (!SEM.empty() && SEM.top().first == "struct") {
				quat << "struct " << tmp.first << " # " << curSynblLev << endl;
				SEM.pop(); //'struct' is out!
				tmpSynbl.push_back(tmpNode);
				synbl.push_back(tmpSynbl);
			}
			else SEM.push(tmp);
		}
		break;
	}
	
	//for test
	/*stack<pair<string, int>> tmpStack2;
	while (!SEM.empty()) {
		tmpStack2.push(SEM.top());
		SEM.pop();
	}
	while (!tmpStack2.empty()) {
		cout << tmpStack2.top().first << ", ";
		SEM.push(tmpStack2.top());
		tmpStack2.pop();
	}cout << endl;*/
	//showSynbl();
	////for test
	//cout << "****************END********************" << endl;
}

void Syntax::showSynbl() {
	ofstream outSynbl;
	outSynbl.open("synbl.csv");
	for (int i = 0; i < synbl.size(); i++)
	{
		if (i == 0) {
			outSynbl << "Scope " + to_string(i) << ": Global Scope" << endl;
			//cout << "Scope " + to_string(i) << ": Global Scope" << endl;
		}
		else {
			outSynbl << "Scope " + to_string(i) << ": " << synbl[i][0].domainName << endl;
			//cout << "Scope " + to_string(i) << ": " << synbl[i][0].domainName << endl;
		}
		if (synbl[i].size() > 1)outSynbl << "Name,DataType,Offset,Pre-domain" << endl;
		for (int j = 1; j < synbl[i].size(); j++) {
			outSynbl << synbl[i][j].name << ",";
			if (synbl[i][j].typ == 0)outSynbl << "int,";
			else if (synbl[i][j].typ == 1)outSynbl << "float,";
			else if (synbl[i][j].typ == 2)outSynbl << "double,";
			else if (synbl[i][j].typ == 3)outSynbl << "long,";
			else if (synbl[i][j].typ == 4)outSynbl << "short,";
			else if (synbl[i][j].typ == 5)outSynbl << "char,";
			else if (synbl[i][j].typ == -1)outSynbl << "void,";
			outSynbl << synbl[i][j].offset << ",";
			outSynbl << synbl[i][j].prelev << "," << endl;
		}
	}
}
