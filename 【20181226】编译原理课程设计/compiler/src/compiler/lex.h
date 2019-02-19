#pragma once
#include "SymbolTabClass.h"

class Lex: public Token { //语法分析，包含各种符号表
public:
	struct re_table {
		re_table(){}
		vector<pair<regex, TokenType>> table{
			make_pair(regex(R"QWERTY(//.*\n|/\*(.|[\r\n])*?\*/)QWERTY"), _notes), //匹配注释
			make_pair(regex("typedef|void|const|char|int|unsigned|signed|short|long|float|double|sizeof|struct|enum|union|if|else|do|for|while|return|switch|case|default|break|continue|static|include|define|pragma|goto|cin|cout"), _keyword),
			make_pair(regex("[a-zA-Z_][0-9a-zA-Z_]*"), _identifier),
			make_pair(regex("-?[0-9]+((\\.[0-9]+)([eE]-?[0-9]+)|(\\.[0-9]+)|([eE]-?[0-9]+))?[fF]?"), _constnum), //匹配浮点数
			make_pair(regex("-?(0|[1-9][0-9]*|0[xX][0-9a-fA-F]+|0[0-7]+)[uU]?[lL]{0,2}"), _constnum), //匹配整型数（含十进制、十六进制、八进制）
			make_pair(regex("\\+\\+|--|\\+=|-=|\\*=|/=|%=|<<=|>>=|\\|=|\\&=|\\^=|\\+|-|\\*|/|==|>>|<<|=|>=|>|<=|<|;|\\{|\\}|\\(|\\)|\\[|\\]|,|!|%|\\|\\||\\&\\&|\\||\\&|:|#|\\.|->|\\?|~|\\^"), _delimiter),
			make_pair(regex("['][\\s\\S^']?'"), _character),
			make_pair(regex("\".*\""), _string),
			make_pair(regex("\\s+"), _space) //匹配空白符
		};
	};
	Token tokenSeq[SIZE_OF_TOKEN]; //开辟token序列
	int index_of_token = 0;
	string keyword_table[SIZE_OF_KEYTAB] = { "typedef","void","const","char","int","unsigned","signed","short",
		"long","float","double","sizeof","struct","enum","union","if","else","do","for","while","return",
		"switch","case","default","break","continue","static","include","define","pragma","goto","cin","cout" }; //关键字表
	string delimiter_table[SIZE_OF_DELTAB] = { "++","--","+=","-=","*=", "/=","%=", "<<=", ">>=","|=","&=", 
		"^=","+","-","*","/","==",">>","<<","=",">=",">","<=","<",";","{","}","(",")","[","]",",","!","%",
		"||","&&","|","&",":","#",".","->","?","~","^" }; //界符表
	SymbolTable identifier_table[SIZE_OF_OTHERTAB]; 
	int index_of_idtfer = 0;//标识符表
	string constant_table[SIZE_OF_OTHERTAB];	    
	int index_of_const = 0;//常数表
	string character_table[SIZE_OF_OTHERTAB];		
	int index_of_char = 0;//字符表
	string string_table[SIZE_OF_OTHERTAB];			
	int index_of_string = 0;//字符串表
	void generateToken(string const &str, int &position);
	void lexicalAnalysis(string Filestream);  //词法扫描器的入口，调用generateToken()函数，生成四元式
	pair<string, Token::TokenType> NEXT(int pos_of_token);
	void showDelimiterTab(); //输出界符表
	void showKeywordTab();   //输出关键字表
};