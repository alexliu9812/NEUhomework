#include <string>
#include <stack>
#include "SymbolTabClass.h"
using namespace std;

const int blockMarkNum = 24;
const string blockBeginSymbol[blockMarkNum] = {"+","-","*","/","=","%","&","|","!","&&","||",">","<",">=","<=","==","shr","shl","cin","cout","mov","movs","call"};
//const string blockEndSymbol[blockMarkNum] = {"re","endfor","endwhile","endelse","enddoit"};

class ObjectCode16:public SymbolTable
{
public:
    string *quat; //Optimized quaternion
    int quatNum; //Number of Optimized quaternion
    int basicBlockNum;
    int *basicBlockMarkPoint;
    string *code; //Object code
    int codeNumNow;
    int dealQuatNumNow;
    int storageSize;
    int insideBlockTempVariableSize;
    string *insideBlockTempVariable;
    string *cacheString;
    string egisterOccupancyTable[4]; //Which variable occupies the register?
    //bool *activeVariablesInformation; //Variable Active Table <=> quat
    string *variablesTable; //Variables table
    ObjectCode16(string *nquat, int nquatnum, int size,string outputFilename);
    ~ObjectCode16();
    void generateObjectCode();
    void initalizeObjectCode();
    void devideBasicBlock();
    bool stringIsBlockBegin(string str);
    //bool stringIsBlockEnd(string str);
    int registerTempVariables(int head,int tail);
    //void writeActiveInformation();
    int registerActiveChangeTable(int head, int tail);
    void DealBasicBlock(int head,int tail,int index);
    void moveAToDX(int i,int index);
    void moveBToBX(int i,int index);
    void OutputCode();
	string outputFileName;
    string DecIntToHexStr(int num);
    int getOffset(string id, int index);
    void jumpStatementOfIf();
    bool stringIsInt(string str);
    bool programHaveOutput,programHaveJudge;
    int offsetAddress;
    //int index;
    stack<int> index;
    int dealFor(int i);
    int dealWhileDo(int i);
    int dealIf(int i);
    int dealDoWhile(int i);
    int qianTao(int i);
    void saveResult(int i);
    int dx1Number,dx0Number,continueNumber; //In If
    int cmpNumber,startNumber,endNumber,incNumber,jmpNumber; //In For
    int whNumber,whendNumber,doNumber;//In While
    int dowhstartNumber,dowhendNumber;// In DoWhile
	string *functionIndex;
};