#pragma once
#include "c_head.h"

#define SIZE_OF_TOKEN    500				//Token数组的大小
#define SIZE_OF_KEYTAB   33
#define SIZE_OF_DELTAB   45
#define SIZE_OF_OTHERTAB 50

class Token {		  //Token类
public:
	enum TokenType {  //类码对应值
		_keyword = 1, //关键字
		_identifier,  //标识符
		_delimiter,   //界符
		_constnum,    //算术常数
		_character,   //字符
		_string,      //字符串
		_notes,       //注释(不会出现在Token中)
		_space        //空白符(不会出现在Token中)
	};
	TokenType type;   //类码
	int id;			  //对应符号表中的下标
	int row;          //该单词在源程序文件中的行数，用于检错时输出错误出现的行数
	Token() { row = 0; } 		    //无参构造方法
	Token(TokenType type, int id) { //有参构造方法
		this->type = type, this->id = id;
		this->row = 0;
	}
};

class SymbolTable {   //符号表总表类（标识符表）
public:
	/*enum Category {
		_function = 1, //函数类型
		_constant,	   //常量类型
		_type,		   //类型类型
		_variable,     //变量类型
		_vn,           //换名形参
		_vf,           //赋值形参
		_domain        //域名类型
	};*/
	string name;       //标识符源码
	int typ;           //指向类型表下标
	//Category cat;	   //种类编码
	int offset;        //偏移量
	int prelev;        //前一级符号表
	string domainName; //域名
	SymbolTable() {
		this->offset = 0; 
		this->prelev = -1;
	}
};

struct TypeTable {	   //类型表类
	enum VarType {	   //变量类型
		_int,          //整型
		_float,		   //浮点型
		_double,	   //双精度
		_long,		   //长
		_short,        //短
		_char,		   //字符型
		_void,         //空类型
	};
	VarType Tval;      //类码（类型编码）
	int Tpoint;        //基本变量类型指向空（-1），还指向数组表
};