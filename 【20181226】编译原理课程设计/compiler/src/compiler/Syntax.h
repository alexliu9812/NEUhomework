#pragma once
#include "lex.h"

#define NUM_OF_PRODUTIONS 500
#define SIZE_OF_TAPEL     30  //类型表大小
#define C_RULES "Cgrammer.txt"

enum Action_id {
	_push,
	_pop,
	_laber,
	_goto,
	_assi,
	_geq,
	_geq_unary,
	_relation,
	_if,
	_else,
	_while,
	_do,
	_logic,
	_scope_init,
	_param,
	_call,
	_end,
	_return,
	_for,
	_for_inc,
	_for_sec_pre,
	_for_sec_post,
	_for_third_pre,
	_for_third_post,
	_do_while,
	_do_while_cmp,
	_end_dowh,
	_cin,
	_cout,
	_init_decl,
	_init_arr,
	_get_func_name,
	_struct_scopeinit
};


class Syntax: public Lex { 
public:
	typedef struct production {
		string left; //产生式左部
		vector<string> right;// [10]; //产生式右部
	}production;
	production prod[NUM_OF_PRODUTIONS];      //产生式数组，用于存放预处理后的产生式
	int size_of_prod = 0;                    //产生式数组下标
	set<string> terminators, non_terminators;//终结符集合和非终结符集合	 
	map<string, set<string>> First, Follow;  //first集合、follow集合 [for example: First(alpha), map(alpha, {First(alpha})
	map<int, set<string>> Select;            //Select set
	map<string, bool> is_deduced_epsilon;    //非终结符是否可以推空
	map<string, vector<string>> tmpStorage;  //临时存储求解一个左部非终结符的first集合所需的右部非终结符first集合
	map<string, bool> visited;               //访问标记，用于深搜
	map<string, int> Action_map;             //语义动作标志映射
	stack<pair<string, int>> SEM;            //语义栈
	TypeTable Tapel[SIZE_OF_TAPEL];          //类型表
	ofstream quat;							 //四元式文件流写入
	int TapelIndex;                          //类型表访问下标
	Syntax();                                //构造函数
	void preProcess(); 
	void dataRevision();
	void DFS_First();
	void getFirst(string curSymbol);
	set<string> int_first(vector<string> alpha);
	void DFS_Follow();
	void getFollow(string curSymbol);
	void getSelect();
	int list_of_LL1(string A, string a);
	map<pair<string, string>, int> CreateLL1List();
	bool LL1_Analyse();
	pair<int,int> getTypeCode(string type);
	void Call(string Action, int TokenIndex, string curstr);
	bool isExistInSynbl(string id, int index);
	int getOffset(string id, int index);
	void showSynbl();
};
