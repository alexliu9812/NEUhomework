#include "Syntax.h"
#include "Quaternion.hpp"
#include "ObjectCode16.hpp"
#define SOURCE_FILE_NAME "program.cpp" //用户源程序文件的文件名

int off = 0; //暂存偏移量
vector<vector<SymbolTable>> synbl;
const string fileName = "quat.dat";
Quaternion *Quat;
ObjectCode16 *Code;


int main(int argc, char *argv[]) 
{
	int position = 0;
	ifstream in(argv[1], ios::in);
	//ifstream in(SOURCE_FILE_NAME, ios::in);
	if (!in.is_open()) {
		cout << "源文件读取失败，请检查源程序代码文件是否存在！" << endl;
		return -1;
	}
	istreambuf_iterator<char> beg(in), end;
	string code(beg, end);
	in.close();
	code += "#"; //给程序最后添加一个#
				 //词法分析
	Syntax test;
	test.lexicalAnalysis(code);
	if (test.LL1_Analyse() == true)cout << "right" << endl;
	else cout << "error" << endl;
	
	//cout << "off = " << off << endl;
	test.showSynbl();

	//DAG Start
	Quat = new Quaternion(fileName); //Initialize Quaternion Storage
	Quat->devideBasicBlock(); //Dividing Quaternion into Basic Blocks

	Quat->dag(); //Local optimization based on DAG for each basic block

	Quat->updateFourFormula(); //Updating Quaternion

	int size = off;
	//cout <<"SIZE="<< size << endl;
	//cout << Quat->newQuatNum << endl;

	string outputfilename = argv[1];
	//string outputfilename = "out";
	Code = new ObjectCode16(Quat->newQuat, Quat->newQuatNum, size, outputfilename);
	//Code->initalizeObjectCode();
	Code->generateObjectCode();
	return 0;
}

