/*-------词法分析扫描器-------*/
#include"lex.h"

ofstream outLex;

void Lex::lexicalAnalysis(string Filestream) {
	int pos = 0;
	outLex.open("Token.csv");
	outLex << "Symbol,TokenType,List-ID,Line-Number" << endl;
	while (pos < Filestream.size()) {
		generateToken(Filestream, pos);
	}
	outLex.close();
}

void Lex::generateToken(string const &str, int &position)
{
	static const re_table reg;
	if (position > str.size() || position < 0) return;
	auto it = str.begin() + position; //当前带匹配串的起始位置
	bool ismatched;//出错处理
	static int row = 1;   //记录行数
	for (auto &e : reg.table) //e -- regex RE
	{
		smatch sm; //match_result
		ismatched = false;//出错处理
		if (regex_search(it, str.end(), sm, e.first, regex_constants::match_continuous)) {
			ismatched = true; //出错处理
			string str_match = sm[0].str();
			if (e.second == _space && (str_match == "\n\t"||str_match == "\n")) {
				row++;
			}
			if (e.second != _space && e.second != _notes)
			{
				tokenSeq[index_of_token].type = e.second;
				tokenSeq[index_of_token].row = row; //记录代码行数
				if (e.second == _keyword) {  //关键字
					for (int i = 0; i < SIZE_OF_KEYTAB; i++) 
						if (str_match == keyword_table[i]) {
							tokenSeq[index_of_token].id = i;
							break;
						}
				}
				else if (e.second == _delimiter) { //界符
					for (int i = 0; i < SIZE_OF_DELTAB; i++)
						if (str_match == delimiter_table[i]) {
							tokenSeq[index_of_token].id = i;
							break;
						}
				}
				else if (e.second == _identifier) { //标识符
					bool exist = false;
					for (int i = 0; i < index_of_idtfer; i++)
					{
						if (identifier_table[i].name == str_match) //该标识符在之前已经定义过
						{
							exist = true;
							tokenSeq[index_of_token].id = i;
							break;
						}
					}
					if (!exist) { //该标识符为新出现标识符，填入表标识符表
						identifier_table[index_of_idtfer].name = str_match; //填标识符表
						tokenSeq[index_of_token].id = index_of_idtfer++;	//在token中记录该标识符在标识符表中的位置
					}
				}
				else if (e.second == _constnum) {
					constant_table[index_of_const] = str_match;   //填常数表（ATTENTION：存在问题，现在仍是字符串类型，为未转成数类型！）
					tokenSeq[index_of_token].id = index_of_const++;
				}
				else if (e.second == _character) {
					character_table[index_of_char] = str_match.substr(1, str_match.length()-2);   //填字符表
					tokenSeq[index_of_token].id = index_of_char++;
				}
				else if (e.second == _string) {
					string_table[index_of_string] = str_match.substr(1, str_match.length()-2);   //填字符串表
					tokenSeq[index_of_token].id = index_of_string++;
				}
				//--------OUTPUT---------
				outLex << str_match << "," << tokenSeq[index_of_token].type << "," << tokenSeq[index_of_token].id << "," << tokenSeq[index_of_token].row << endl;
				//cout << setw(10) << str_match << setw(7) << "{" << tokenSeq[index_of_token].type << "," << tokenSeq[index_of_token].id << "}\t";
				//cout << "row = " << tokenSeq[index_of_token].row << endl;
				//--------OUTPUT---------
				index_of_token++;
			}
			position += str_match.size();
			break;
		}
	}
	if (!ismatched) { //出错处理
		cout << "ERROR" << endl; exit(1);
	}
}

void Lex::showKeywordTab() {   //输出关键字表
	ofstream key;
	key.open("keyword.csv");
	for (int i = 0; i < SIZE_OF_KEYTAB; i++) {
		key << keyword_table[i] << endl;
	}
	key.close();
}

void Lex::showDelimiterTab() { //输出界符表
	ofstream del;
	del.open("delimiter.csv");
	for (int i = 0; i < SIZE_OF_DELTAB; i++) {
		del << delimiter_table[i] << endl;
	}
	del.close();
}

pair<string, Token::TokenType> Lex::NEXT(int pos_of_token)
{
	pair<string, Token::TokenType> w;
	if (tokenSeq[pos_of_token].type == _keyword) //关键字
		w = make_pair(keyword_table[tokenSeq[pos_of_token].id], _keyword);
	else if (tokenSeq[pos_of_token].type == _delimiter) //界符
		w = make_pair(delimiter_table[tokenSeq[pos_of_token].id], _delimiter);
	else if (tokenSeq[pos_of_token].type == _identifier) //标识符
		w = make_pair(identifier_table[tokenSeq[pos_of_token].id].name, _identifier);
	else if (tokenSeq[pos_of_token].type == _constnum) //常数
		w = make_pair(constant_table[tokenSeq[pos_of_token].id], _constnum);
	else if (tokenSeq[pos_of_token].type == _character) //字符
		w = make_pair(character_table[tokenSeq[pos_of_token].id], _character);
	else if (tokenSeq[pos_of_token].type == _string) //字符串
		w = make_pair(string_table[tokenSeq[pos_of_token].id], _string);
	return w;
}
