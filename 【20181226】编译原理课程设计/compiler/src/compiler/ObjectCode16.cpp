#include "ObjectCode16.hpp"
#include <iostream>
#include <fstream>
using namespace std;

extern vector<vector<SymbolTable>> synbl;

ObjectCode16::ObjectCode16(string *nquat, int nquatnum, int size,string outputFilename)
{
    storageSize = size;
    quat = nquat;
    quatNum = nquatnum;
	outputFileName = outputFilename;
    dx0Number = 1;
    dx1Number = 1;
    continueNumber = 1;
    cmpNumber = 1;
    startNumber = 1;
    endNumber = 1;
    incNumber = 1;
    jmpNumber = 1;
    whNumber = 1;
    whendNumber = 1;
    doNumber = 1;
    dowhendNumber = 1;
    dowhstartNumber = 1;
    programHaveOutput = false;
    programHaveJudge = false;
    index.push(0);
	functionIndex = new string[128];
	/*
	for (int i = 0; i < 128; i++)
	{
		functionIndex[i] = "####";
	}
	*/
}


ObjectCode16::~ObjectCode16()
{
    delete code;
}


void ObjectCode16::generateObjectCode()
{
    devideBasicBlock();
    initalizeObjectCode();
}


void ObjectCode16::initalizeObjectCode()
{
    //Potential BUG: Does a quaternion generate up to four object codes?
    code = new string[8*quatNum+128];
    insideBlockTempVariable = new string[quatNum];
    insideBlockTempVariableSize = registerTempVariables(0,quatNum);
    codeNumNow = 0;
    dealQuatNumNow = 0;
    //devideBasicBlock();
    //activeVariablesInformation = new bool[quatNum];
	
    //writeActiveInformation();
	
    int assignmentAtStart = 0;
    if(quat[0] == "=")
    {
        for(assignmentAtStart = 1;quat[assignmentAtStart]=="=";assignmentAtStart++);
        assignmentAtStart--;
    }
    string *assignmentAtStartString = new string[4*assignmentAtStart];
    for(int i = 0;i < 4*assignmentAtStart;i++)
        assignmentAtStartString[i] = quat[i];
    //Define global variables
    code[codeNumNow++] = "DSEG\tSEGMENT";
    for(int as=0;as<assignmentAtStart;as++)
    {
        code[codeNumNow++] = assignmentAtStartString[4*as+3]+"\tDW\t?";
    }
    code[codeNumNow++] = "STORE\tDW\t"+to_string(storageSize)+ " DUP(?)";
    code[codeNumNow++] = "TEMP\tDW\t64 DUP(?)";
    code[codeNumNow++] = "DSEG\tENDS";
    //Define local variables
    code[codeNumNow++] = "SSEG\tSEGMENT\tSTACK";
    code[codeNumNow++] = "FUNCST\tDW\t20 DUP(?)";
    code[codeNumNow++] = "SSEG\tENDS";
	code[codeNumNow++] = "CODE\tSEGMENT";
	code[codeNumNow++] = "\tASSUME\tCS:CODE";
	//Output function
	code[codeNumNow++] = "DISPLAY\tPROC\tFAR";
	code[codeNumNow++] = "MOV\tCX,0";
	code[codeNumNow++] = "DISP1:\tMOV\tDX,0";
	egisterOccupancyTable[3] = "0";
	code[codeNumNow++] = "DIV\tBX";
	code[codeNumNow++] = "PUSH\tDX";
	code[codeNumNow++] = "INC\tCX";
	code[codeNumNow++] = "OR\tAX,AX";
	code[codeNumNow++] = "JNE\tDISP1";
	code[codeNumNow++] = "DISP2:\tMOV\tAH,02H";
	code[codeNumNow++] = "POP\tDX";
	code[codeNumNow++] = "ADD\tDL,30H";
	code[codeNumNow++] = "INT\t21H";
	code[codeNumNow++] = "LOOP\tDISP2";
	code[codeNumNow++] = "RET";
	code[codeNumNow++] = "DISPLAY\tENDP";
	
    //Code Area
    //1. The Tail of Start AH,4CH
    //2. Will after an End is not another begin(except end of quat)?
    //3. Assignment statements for global variables???!!!at START
    //4. ReWrite on 12/20/2018!!!!!!!!!!!!!!!!!!!

	for (int k = 0; k < 4; k++)
		egisterOccupancyTable[k] = "0";
    for(int i = assignmentAtStart;i<quatNum;i++) //Deal every quat
    {
        for(int j=0;j<basicBlockNum;j++)
        {
            if(i==basicBlockMarkPoint[2*j])
            {
                int start = basicBlockMarkPoint[2*j];
                int end = basicBlockMarkPoint[2*j+1];
				//cout << "inputStart::" << start << "inputEnd::" << end << endl;
                DealBasicBlock(start,end,index.top());
                i = end+1;
                break;
            }
        }
		//cout << "NOW, I WILL DEAL i = " << i << endl;
        //Potential BUG: No assignment is allowed at the beginning of the file
        if(quat[4*i] == "func" && quat[4*i+1] == "main")
        {
            //insideBlockTempVariable = new string[64];
            //insideBlockTempVariableSize = registerTempVariables(basicBlockMarkPoint[2*i],basicBlockMarkPoint[2*i+1]);
			int indexhere = atoi(quat[4 * i + 3].c_str());
			index.push(indexhere);
			//functionIndex[indexhere] = "main";
			//cout << "INDEX.PUSH<====" << atoi(quat[4 * i + 3].c_str()) << endl;
            //Potential BUG: Start and End of Basic Block
			code[codeNumNow++] = "CODE\tENDS";
			code[codeNumNow++] = "CSEG\tSEGMENT";
			code[codeNumNow++] = "\tASSUME\tCS:CSEG,DS:DSEG,SS:SSEG";
            code[codeNumNow++] = "START:";
            code[codeNumNow++] = "MOV\tAX,DSEG";
            code[codeNumNow++] = "MOV\tDS,AX";
            code[codeNumNow++] = "MOV\tAX,SSEG";
            code[codeNumNow++] = "MOV\tSS,AX";
            code[codeNumNow++] = "MOV\tSI,OFFSET STORE";
            code[codeNumNow++] = "MOV\tDI,OFFSET TEMP";
            code[codeNumNow++] = "MOV\tSP,SIZE FUNCST";
            for(int as=0;as<assignmentAtStart;as++)
            {
                code[codeNumNow++] = "MOV\tDX,"+ assignmentAtStartString[4*as+1];
				egisterOccupancyTable[3] = assignmentAtStartString[4*as+1];
                code[codeNumNow++] = "MOV\t"+assignmentAtStartString[4*as+3]+",DX";
            }
            //delete insideBlockTempVariable;
        }

        //If this blcok is function
        else if(quat[4*i] == "func" && quat[4*i+1] != "main")
        {
            //insideBlockTempVariable = new string[64];
            //insideBlockTempVariableSize = registerTempVariables(basicBlockMarkPoint[2*i],basicBlockMarkPoint[2*i+1]);
			int indexhere = atoi(quat[4 * i + 3].c_str());
			index.push(indexhere);
			//functionIndex[indexhere] = quat[4 * i + 1];
			//cout << "INDEX.PUSH<====" << atoi(quat[4 * i + 3].c_str()) << endl;
            code[codeNumNow++] = quat[4*i+1] + "\tPROC\tFAR";
        }


		else if (quat[4 * i] == "re")
		{
			if (stringIsInt(quat[4 * i + 1]))
			{
				code[codeNumNow++] = "MOV\tDX," + quat[4 * i + 1];
				egisterOccupancyTable[3] = quat[4 * i + 1];
			}
			else
			{
				if (quat[4 * i + 1].find("qtmp") == string::npos)
				{
					offsetAddress = getOffset(quat[4 * i + 1], index.top());
					code[codeNumNow++] = "MOV\tDX,[SI+" + to_string(offsetAddress) + "]";
					egisterOccupancyTable[3] = quat[4 * i + 1];
				}
				else
				{
					for (int jj = 0; jj < insideBlockTempVariableSize; jj++)
					{
						if (quat[4 * i + 1] == insideBlockTempVariable[jj])
						{
							offsetAddress = jj;
							break;
						}
					}
					code[codeNumNow++] = "MOV\tDX,[DI+" + to_string(offsetAddress) + "]";
					egisterOccupancyTable[3] = quat[4 * i + 1];
				}
			}
		}
		else if (quat[4 * i] == "end")
		{
			index.pop();
			if (quat[4 * i + 3] != "main")
			{
				code[codeNumNow++] = "RET";
				code[codeNumNow++] = quat[4*i+3] + "\tENDP";
			}
			if (quat[4 * i + 3] == "main")
			{
				code[codeNumNow++] = "MOV\tAH,4CH";
				code[codeNumNow++] = "INT\t21H";
			}
		}
		else if (quat[4 * i] == "for")
		{
			i = dealFor(i);
		}
		else if (quat[4 * i] == "wh")
		{
			i = dealWhileDo(i);
		}
		else if (quat[4 * i] == "dowhile")
		{
			i = dealDoWhile(i);
		}
		else if (quat[4 * i] == "if")
		{
			i = dealIf(i);
		}
		else if (quat[4 * i] == "gt")
		{
			code[codeNumNow++] = "CMP\t" + quat[4*i+3];
		}
		else
		{
			cout << "ERROR::InitCode::" << quat[4 * i]<<endl;
		}
    }



    //End
    code[codeNumNow++] = "CSEG\tENDS";
    code[codeNumNow++] = "\tEND\tSTART";
	OutputCode();
}


int ObjectCode16::dealFor(int i)
{
    index.push(atoi(quat[4*i+3].c_str()));
    i++;
    while(quat[4*i] == "=")
    {
        moveAToDX(i,index.top());
        saveResult(i);
        i++;
    }
    //label # # cmp
    if(quat[4*i] == "label")
    {
        code[codeNumNow++] = "CMP"+ to_string(cmpNumber) + ":";
        i++;
    }
    else {cout<<"ERROR::at dealFor()1;"<<endl;}
    for(int n=0;n<basicBlockNum;n++)
    {
        if(i==basicBlockMarkPoint[2*n])
        {
            DealBasicBlock(basicBlockMarkPoint[2*n],basicBlockMarkPoint[2*n+1],index.top());
            i = basicBlockMarkPoint[2*n+1];
            break;
        }
    }
	i++;
    //do qtmpX # #
    if(quat[4*i] == "do")
    {
        moveAToDX(i,index.top());
        code[codeNumNow++] = "CMP\tDX,01H";
        code[codeNumNow++] = "JNE\tEND"+ to_string(endNumber);
        code[codeNumNow++] = "JE\tSTART"+ to_string(startNumber);
        i += 3;
    }
    else{cout<<"ERROR::at dealFor()2"<<endl;}
    if(quat[4*i]=="label")
    {
        code[codeNumNow++] = "INC"+ to_string(incNumber) + ":";
        i++;
    }
    else{cout<<"ERROR::at dealFor()3"<<endl;}
    for(int n=0;n<basicBlockNum;n++)
    {
        if(i==basicBlockMarkPoint[2*n])
        {
            DealBasicBlock(basicBlockMarkPoint[2*n],basicBlockMarkPoint[2*n+1],index.top());
            i = basicBlockMarkPoint[2*n+1];
            break;
        }
    }
	i++;
    if(quat[4*i+0] == "jmp")
    {
        code[codeNumNow++] = "JMP\tCMP"+ to_string(cmpNumber);
        cmpNumber++;
        i++;
    }
    else{cout<<"ERROR::at dealFor()4"<<endl;}
    if(quat[4*i+0] == "label")
    {
        code[codeNumNow++] = "START"+ to_string(startNumber)+":";
        startNumber++;
        i++;
    }
    else{cout<<"ERROR::at dealFor()5"<<endl;}

    //FOR Main
    for(;quat[4*i]!="jmp" || quat[4*i+3]!="inc";i++)
    {
        i = qianTao(i);
    }
	i++;
    code[codeNumNow++] = "JMP\tINC"+to_string(incNumber);
    incNumber++;
    if(quat[4*i]=="end" && quat	[4*i+3] == "for")
    {
        code[codeNumNow++] = "END"+ to_string(endNumber)+":";
        endNumber++;
    }
	else { cout << "ERROR::at dealFor()6" << endl; }
    index.pop();
    return i;
}


int ObjectCode16::dealWhileDo(int i)
{
    index.push(atoi(quat[4*i+3].c_str()));
    i++;
    code[codeNumNow++] = "WH"+ to_string(whNumber) + ":";
	while (quat[4 * i] != "do")
	{
		for (int n = 0; n < basicBlockNum; n++)
		{
			if (i == basicBlockMarkPoint[2 * n])
			{
				DealBasicBlock(i, basicBlockMarkPoint[2 * n + 1], index.top());
				i = basicBlockMarkPoint[2 * n + 1];
				break;
			}
		}
		i++;
	}
    moveAToDX(i,index.top());
    code[codeNumNow++] = "CMP\tDX,01H";
    code[codeNumNow++] = "JE\tDO"+ to_string(doNumber);
    code[codeNumNow++] = "JNE\tWHEND"+ to_string(whendNumber);
    code[codeNumNow++] = "DO"+ to_string(doNumber) + ":";
	i++;
    for(;!(quat[4*i+0]=="end" && quat[4*i+3]=="while");i++)
    {
        i = qianTao(i);
    }
    code[codeNumNow++] = "JMP\tWH"+ to_string(whNumber);
    code[codeNumNow++] = "WHEND"+ to_string(whendNumber) + ":";
    whNumber++;
    whendNumber++;
    doNumber++;
    index.pop();
    return i;
}


int ObjectCode16::dealDoWhile(int i)
{
    index.push(atoi(quat[4*i+3].c_str()));
    i++;
    if(quat[4*i+0] == "label")
    {
        code[codeNumNow++] = "DOWHSTART"+ to_string(dowhstartNumber) + ":";
    }
	i++;
    for(;quat[4*i+0]!="end" || quat[4*i+3]!="dowhile";i++)
    {
      i = qianTao(i);
    }
    i++;
	
    for(int n=0;n<basicBlockNum;n++)
    {
        if(i==basicBlockMarkPoint[2*n])
        {
            DealBasicBlock(i,basicBlockMarkPoint[2*n+1],index.top());
			
			i = basicBlockMarkPoint[2 * n + 1];
            break;
        }
    }
	i++;
    moveAToDX(i,index.top());
    if(quat[4*i] == "do")
    {
        code[codeNumNow++] = "CMP\tDX,01H";
        code[codeNumNow++] = "JE\tDOWHSTART"+ to_string(dowhstartNumber);
        code[codeNumNow++] = "JNE\tDOWHEND"+ to_string(dowhendNumber);
    }
    else{cout<<"ERROR::at dealDowhile()2"<<endl;}
    i++;
    if(quat[4*i]=="jmp")
    {
        code[codeNumNow++] = "DOWHEND"+ to_string(dowhendNumber) + ":";
    }
    else{cout<<"ERROR::at dealDowhile()3"<<endl;}
    index.pop();
    return i;
}

int ObjectCode16::dealIf(int i)
{
    index.push(atoi(quat[4*i+3].c_str()));
    moveAToDX(i,index.top());
    code[codeNumNow++] = "CMP\tDX,01H";
    code[codeNumNow++] = "JE\tDX1"+ to_string(dx1Number);
    code[codeNumNow++] = "JNE\tDX0"+ to_string(dx0Number);
    code[codeNumNow++] = "DX1"+ to_string(dx1Number)+ ":";
	i++;
	
    //If Main
    for(;!(quat[4*i]=="end" && quat[4*i+3]=="if");i++)
    {
		//cout << "come to qian:::" << i << endl;
        i = qianTao(i);
    }
	
    index.pop();
    code[codeNumNow++] = "DX0"+ to_string(dx0Number)+":";
    dx0Number++;
	dx1Number++;
	if (quat[4 * (i + 1)] == "el")
		i++;
    //Else Main
    if(quat[4*i] == "el")
    {
        index.push(atoi(quat[4*i+3].c_str()));
		i++;
        for(;!(quat[4*i]=="end" && quat[4*i+3]=="else");i++)
        {
            qianTao(i);
        }
        index.pop();
    }
    return i;
}


int ObjectCode16::qianTao(int i)
{
    int cachei;
    if(quat[4*i] == "for")
    {
        cachei = dealFor(i);
    }
    else if(quat[4*i] == "while")
    {
        cachei = dealWhileDo(i);
    }
    else if(quat[4*i] == "dowhile")
    {
        cachei = dealDoWhile(i);
    }
    else if(quat[4*i] == "if")
    {
        cachei = dealIf(i);
    }
    else
    {
        for(int n=0;n<basicBlockNum;n++)
        {
            if(i==basicBlockMarkPoint[2*n])
            {
				//cout << "I IM QIANTAO" << endl;
                DealBasicBlock(basicBlockMarkPoint[2*n],basicBlockMarkPoint[2*n+1],index.top());
                cachei = basicBlockMarkPoint[2*n+1];
                break;
            }
        }
    }
    return cachei; //i is "end # # xxx"
}

void ObjectCode16::DealBasicBlock(int head,int tail,int index)
{
    for(int i=head;i<=tail;i++)
    {
        //Potential BUG: All quaternions except =/!/cin/cout/call are four elements?
        //deal (w,A,B,Q)
        //Potential BUG: All data use 16 bit
        if(quat[4*i+2] != "#")
        {
            moveAToDX(i,index);
            moveBToBX(i,index);
            //Execute the operation!
            if(quat[4*i+0] == "+")
                code[codeNumNow++] = "ADD\tDX,BX";
            else if(quat[4*i+0] == "-")
                code[codeNumNow++] = "SUB\tDX,BX";
            else if(quat[4*i+0] == "*")
            {
                code[codeNumNow++] = "MOV\tAX,DX";
                code[codeNumNow++] = "MUL\tBX";
                code[codeNumNow++] = "MOV\tDX,AX";
				egisterOccupancyTable[3] = "#####";
            }
            else if(quat[4*i+0] == "/")
            {
                code[codeNumNow++] = "MOV\tAX,DX";
                code[codeNumNow++] = "MOV\tDX,0H";
                code[codeNumNow++] = "DIV\tBX";
                code[codeNumNow++] = "MOV\tDX,AX";
				egisterOccupancyTable[3] = "#####";
            }
            else if(quat[4*i+0] == "%")
            {
				code[codeNumNow++] = "MOV\tAX,DX";
				code[codeNumNow++] = "MOV\tDX,0H";
				code[codeNumNow++] = "DIV\tBX";
				egisterOccupancyTable[3] = "#####";
            }
            else if(quat[4*i+0] == "&" || quat[4*i+0] == "&&")
            {
                code[codeNumNow++] = "AND\tDX,BX";
            }
            else if(quat[4*i+0] == "||"||quat[4*i+0] == "|")
            {
                code[codeNumNow++] = "OR\tDX,BX";
            }
            else if(quat[4*i+0] == ">")
            {
                programHaveJudge = true;
                code[codeNumNow++] = "CMP\tDX,BX";
                code[codeNumNow++] = "JA\tDX1"+ to_string(dx1Number);
                code[codeNumNow++] = "JBE\tDX0"+to_string(dx0Number);
                jumpStatementOfIf();
            }
            else if(quat[4*i+0] == ">=")
            {
                programHaveJudge = true;
                code[codeNumNow++] = "CMP\tDX,BX";
                code[codeNumNow++] = "JBA\tDX1"+ to_string(dx1Number);
                code[codeNumNow++] = "JE\tDX0"+ to_string(dx0Number);
                jumpStatementOfIf();
            }
            else if(quat[4*i+0] == "<")
            {
                programHaveJudge = true;
                code[codeNumNow++] = "CMP\tDX,BX";
                code[codeNumNow++] = "JB\tDX1"+ to_string(dx1Number);
                code[codeNumNow++] = "JAE\tDX0"+ to_string(dx0Number);
                jumpStatementOfIf();                
            }
            else if(quat[4*i+0] == "<=")
            {
                programHaveJudge = true;
                code[codeNumNow++] = "CMP\tDX,BX";
                code[codeNumNow++] = "JBE\tDX1"+ to_string(dx1Number);
                code[codeNumNow++] = "JA\tDX0"+ to_string(dx0Number);
                jumpStatementOfIf();                
            }
            else if(quat[4*i+0] == "==")
            {
                programHaveJudge = true;
                code[codeNumNow++] = "CMP\tDX,BX";
                code[codeNumNow++] = "JE\tDX1"+ to_string(dx1Number);
                code[codeNumNow++] = "JNE\tDX0"+ to_string(dx0Number);
                jumpStatementOfIf();                
            }
            else if(quat[4*i+0] == "shl")
            {
				code[codeNumNow++] = "MOV\tCL,BL";
                code[codeNumNow++] = "SHL\tDX,CL";
            }
            else if(quat[4*i+0] == "shr")
            {
				code[codeNumNow++] = "MOV\tCL,BL";
				code[codeNumNow++] = "SHR\tDX,CL";
            }
            else
            {
                cout<<"ERROR::at DealBasicBlock()::";
                cout<<"You use undifined symbol."<<endl;
            }
        }

        //Processing Monocular Operators
        if(quat[4*i+2] == "#")
        {
			//if (quat[4 * i + 0] != "cin")
			//{
				//moveAToDX(i, index);
			//}
			//else
			//{ }
            if(quat[4*i+0] == "=")
            {
				moveAToDX(i, index);
			}
            else if(quat[4*i+0] == "!")
            {
				moveAToDX(i, index);
                programHaveJudge = true;
                code[codeNumNow++] = "CMP\tDX,0H";
                code[codeNumNow++] = "JE\tDX0"+dx0Number;
                code[codeNumNow++] = "JNE\tDX1"+dx1Number;
                jumpStatementOfIf();
            }
            else if(quat[4*i+0] == "cin")
            {
                string inputstream;
                cin>>inputstream;
                code[codeNumNow++] = "MOV\tDX," + inputstream;
				egisterOccupancyTable[3] = inputstream;
            }
            else if(quat[4*i+0] == "cout")
            {
                programHaveOutput = true;
                code[codeNumNow++] = "MOV\tBX," + quat[4*i+1];
				egisterOccupancyTable[1] = quat[4 * i + 1];
                if(stringIsInt(quat[4*i+3]))
                {
                    code[codeNumNow++] = "MOV\tAX,"+quat[4*i+3];
                }
                else
                {
                    offsetAddress = getOffset(quat[4*i+3],index);
                    code[codeNumNow++] = "MOV\tAX,[SI+" + to_string(offsetAddress)+"]";
                }
                code[codeNumNow++] = "CALL\tFAR PTR\tDISPLAY";
            }
			//TODO
            else if(quat[4*i+0] == "call")
            {
				code[codeNumNow++] = "CALL\tFAR PTR\t" + quat[4 * i + 3];
            }
			else if (quat[4 * i + 0] == "mov")
			{
				if (quat[4 * i + 3] == "DX")
				{
					offsetAddress = getOffset(quat[4*i+1],index);
					code[codeNumNow++] = "MOV\t[SI+" + to_string(offsetAddress) + "],DX";
				}
				else
				{
					if (stringIsInt(quat[4 * i + 3]))
					{
						code[codeNumNow++] = "MOV\tDX," + quat[4 * i + 3];
						egisterOccupancyTable[3] = quat[4*i+3];
						code[codeNumNow++] = "MOV\t[SI+" + quat[4 * i + 1] + "],DX";
					}
					else
					{
						if (quat[4 * i + 3].find("qtmp") != string::npos)
						{
							for (int jj = 0; !insideBlockTempVariable[jj].empty(); jj++)
							{
								if (insideBlockTempVariable[jj] == quat[4 * i + 3])
								{
									offsetAddress = jj;
									code[codeNumNow++] = "MOV\tDX,[DI+" + to_string(offsetAddress) + "]";
									egisterOccupancyTable[3] = quat[4 * i + 3];
									code[codeNumNow++] = "MOV\t[SI+" + quat[4 * i + 1] + "],DX";
									//cout << "MOV\t[DI+" + to_string(offsetAddress) + "],DX" << endl;
									break;
								}
							}
						}
						else
						{
							offsetAddress = getOffset(quat[4 * i + 3], index);
							code[codeNumNow++] = "MOV\tDX,[SI+" + to_string(offsetAddress) + "]";
							egisterOccupancyTable[3] = quat[4 * i + 3];
							code[codeNumNow++] = "MOV\t[SI+" + quat[4 * i + 1] + "],DX";
						}
					}
				}
			}
			else if (quat[4 * i + 0] == "movs")
			{
				if (stringIsInt(quat[4 * i + 1]))
				{
					if (stringIsInt(quat[4 * i + 3]))
					{
						code[codeNumNow++] = "MOV\tDX,"+ quat[4*i+3];
						egisterOccupancyTable[3] = quat[4 * i + 3];
						code[codeNumNow++] = "MOV\t[SI+" + quat[4*i+1]+"],DX";
					}
					else
					{
						offsetAddress = getOffset(quat[4*i+3],index);

						code[codeNumNow++] = "MOV\tDX,[SI+"+to_string(offsetAddress)+"]";
						egisterOccupancyTable[3] = quat[4 * i + 3];
						code[codeNumNow++] = "MOV\t[SI+"+quat[4*i+1] +"],DX";
					}
				}
				else
				{
					offsetAddress = getOffset(quat[4 * i + 1], index);
					code[codeNumNow++] = "MOV\tDX,[SI+"+quat[4*i+3] + "]";
					egisterOccupancyTable[3] = quat[4 * i + 3];
					code[codeNumNow++] = "MOV\t[SI+"+to_string(offsetAddress)+"],DX";
				}
			}
        }
		//cout << "BLOCK::" << i << endl;
		if (quat[4 * i] != "cout"&&quat[4 * i] != "mov"&&quat[4 * i] != "call"&&quat[4*i]!="movs")
		{
			saveResult(i);
			//cout << "saveResult=:" << i << endl;
		}
    }
}


void ObjectCode16::saveResult(int i)
{
    //Save result
    if(quat[4*i+3].find("qtmp")==string::npos)
    {
        offsetAddress = getOffset(quat[4*i+3],index.top());
		//cout << "OFFSET::" << offsetAddress <<"index::"<<index.top()<< endl;
        code[codeNumNow++] = "MOV\t[SI+"+ to_string(offsetAddress) + "],DX";
    }
    else
    {
		/*
		for (int jj = 0; !insideBlockTempVariable[jj].empty(); jj++)
		{
			cout << insideBlockTempVariable[jj] << endl;
		}
		*/
        for(int jj=0;!insideBlockTempVariable[jj].empty();jj++)
        {
            if(insideBlockTempVariable[jj] == quat[4*i+3])
            {
                offsetAddress = jj;
                code[codeNumNow++] = "MOV\t[DI+"+ to_string(offsetAddress)+"],DX";   
				//cout << "MOV\t[DI+" + to_string(offsetAddress) + "],DX" << endl;
                break;
            }
        }
    }
}

void ObjectCode16::moveAToDX(int i,int index)
{
    //A must in DX
    if(stringIsInt(quat[4*i+1]))
    {
		//if(egisterOccupancyTable[3] != quat[4*i+1])
			code[codeNumNow++] = "MOV\tDX,"+quat[4*i+1];
    } 
    else
    //if(egisterOccupancyTable[3]!=quat[4*i+1])
    {
        if(quat[4*i+1].find("qtmp")==string::npos)
        {
            offsetAddress = getOffset(quat[4*i+1],index);
			int egisOff = getOffset(egisterOccupancyTable[3], index);
			//if(offsetAddress != egisOff)
				code[codeNumNow++] = "MOV\tDX,[SI+"+ to_string(offsetAddress) + "]";
        }
        else
        {
            for(int jj=0;!insideBlockTempVariable[jj].empty();jj++)
            {
                if(insideBlockTempVariable[jj] == quat[4*i+1])
                    {offsetAddress = jj;break;}
            }
			int egisOff = getOffset(egisterOccupancyTable[3], index);
			//if (offsetAddress != egisOff)
				code[codeNumNow++] = "MOV\tDX,[DI+"+ to_string(offsetAddress)+"]";
        }
    }
	egisterOccupancyTable[3] = quat[4 * i + 1];
}


void ObjectCode16::moveBToBX(int i,int index)
{
    //B must in BX
    if(stringIsInt(quat[4*i+2]))
    {
		//if (egisterOccupancyTable[1] != quat[4 * i + 2])
			code[codeNumNow++] = "MOV\tBX,"+quat[4*i+2];
    } 
    else
    {
        egisterOccupancyTable[1] = quat[4*i+2];
        if(quat[4*i+2].find("qtmp")==string::npos)
        {
            offsetAddress = getOffset(quat[4*i+2],index);
			int egisOff = getOffset(egisterOccupancyTable[1], index);
			//if (offsetAddress != egisOff)
				code[codeNumNow++] = "MOV\tBX,[SI+"+ to_string(offsetAddress)+"]";
        }
        else
        {
            for(int jj=0;!insideBlockTempVariable[jj].empty();jj++)
            {
                if(insideBlockTempVariable[jj] == quat[4*i+2])
                    {offsetAddress = jj;break;}
               
            }
			int egisOff = getOffset(egisterOccupancyTable[1], index);
			//if (offsetAddress != egisOff)
				code[codeNumNow++] = "MOV\tBX,[DI+"+ to_string(offsetAddress)+"]";
        }
    }
	egisterOccupancyTable[1] = quat[4 * i + 2];
}


void ObjectCode16::jumpStatementOfIf()
{
	code[codeNumNow++] = "DX1" + to_string(dx1Number) + ":";
	code[codeNumNow++] = "MOV\tDX, 01H";
	egisterOccupancyTable[3] = "1";
    code[codeNumNow++] = "JMP\tCONTINUE"+ to_string(continueNumber);
	code[codeNumNow++] = "DX0" + to_string(dx0Number) + ":";
	code[codeNumNow++] = "MOV\tDX, 00H";
	egisterOccupancyTable[3] = "0";
    code[codeNumNow++] = "JMP\tCONTINUE"+ to_string(continueNumber);
    code[codeNumNow++] = "CONTINUE"+ to_string(continueNumber)+":";
	dx0Number++;
	dx1Number++;
    continueNumber++;
}



int ObjectCode16::registerActiveChangeTable(int head, int tail)
{
    int registerNumber = 0;
    for(int i = head; i<= tail;i++)
    {
        for(int j=1;j<4 && quat[4*i+j]!="#";j++)
        {
            bool haveRegisterThis = false;
            int k;
            for(k=0;!cacheString[k].empty();k++)
            {
                if(quat[4*i+j]==cacheString[k])
                    haveRegisterThis = true;
            }
            if(!haveRegisterThis)
            {
                cacheString[k] = quat[4*i+j];
            }
        }
    }
    return registerNumber;
}


int ObjectCode16::registerTempVariables(int head,int tail)
{
    int tempNumHere = 0;
    for(int i = head;i<tail;i++)
    {
        if(quat[4*i+3].find("qtmp")!=string::npos)
        {
            bool thisTempHaveInside = false;
            for(int i = 0;i<tempNumHere;i++)
            {
                if(insideBlockTempVariable[i] == quat[4*i+3])
                    thisTempHaveInside == true;
            }
            if(!thisTempHaveInside)
            {
                insideBlockTempVariable[tempNumHere] = quat[4*i+3]; 
                tempNumHere++;
            }
        }
    }
    return tempNumHere;
}


void ObjectCode16::devideBasicBlock()
{
    basicBlockNum = 0;
    basicBlockMarkPoint = new int[2 * quatNum];
    for(int i = 0; i < quatNum; i++)
    {
        if(stringIsBlockBegin(quat[4 * i]))
        {
            basicBlockMarkPoint[2*basicBlockNum] = i;
            for(;i < quatNum && stringIsBlockBegin(quat[4 * i]);i++);
            i--;
            basicBlockMarkPoint[2*basicBlockNum+1] = i;
            basicBlockNum ++;
        }
    }
	/*
	for (int i = 0; i < basicBlockNum; i++)
	{
		cout << "blockBegin:" << basicBlockMarkPoint[2 * i] << endl;
		cout << "blockEnd:" << basicBlockMarkPoint[2 * i + 1] << endl;;
	}
	*/
}


bool ObjectCode16::stringIsBlockBegin(string str)
{
    for(int j = 0; !blockBeginSymbol[j].empty();j++)
    {
        if(str == blockBeginSymbol[j])
        {
            return true;
        }
    }
    return  false;
}


void ObjectCode16::OutputCode()
{
	//cout << "wojinlaile!!!!!!" << endl;
	string asmfilename = outputFileName + ".asm";
    ofstream fout(asmfilename);
    for(int i = 0;i<codeNumNow;fout<<code[i]<<endl, i++);
    fout.close();
}


string ObjectCode16::DecIntToHexStr(int num)  
{
    string str;
    string stradd0;
    int Temp = num / 16;
    int left = num % 16;
    if (Temp > 0)
        str += DecIntToHexStr(Temp);
    if (left < 10)
        str += (left + '0');
    else
        str += ('A' + left - 10);
    stradd0 = "0"+str;
    return stradd0;
}

bool ObjectCode16::stringIsInt(string str)
{
    for(int i = 0;i<str.length();i++)
    {
        if(str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

int ObjectCode16::getOffset(string id, int index) {
	if (!synbl.empty() && index <= synbl.size()) {
		if (index >= synbl.size()) index = synbl.size() - 1;
		vector<SymbolTable>::iterator it = synbl[index].begin(), stor_it = it;
		for (; it != synbl[index].end(); it++) {
			if (it->name == id) {
				return it->offset;
			}
		}
		if (it == synbl[index].end() || synbl[index][0].prelev != -1) {
			return getOffset(id, synbl[index][0].prelev);
		}
		else if (it == synbl[index].end() || synbl[index][0].prelev == -1) {
			return -1;
		}
	}
	else return -1;
}


/*
void ObjectCode16::writeActiveInformation()
{
	for(int i = 0;i < basicBlockNum; i++)
	{
		//Potential BUG: After the beginning + 1 must be the beginning of the basic block?
		int waiHead = basicBlockMarkPoint[2*i];
		int waiTail = basicBlockMarkPoint[2*i+1];
		cacheString = new string[3*(waiTail-waiHead+1)];
		bool *cacheStringInformation = new bool[3*(waiTail-waiHead+1)];
		int variablesInBlock = registerActiveChangeTable(waiHead, waiTail);
		//Initialize true or false
		for(int kk=0;kk<variablesInBlock;kk++)
		{
			if(cacheString[kk].find("qtmp")!=string::npos) //it is qtmpX
			{
				cacheStringInformation[kk] = false;
			}
			else
			{
				cacheStringInformation[kk] = true;
			}
		}
		//Active Information Labeling
		for(int j=waiTail;j>=waiHead;j++)
		{
			for(int k=1;k<4 && quat[4*j+k]!="#";k++)
			{
				for(int m=0;m<variablesInBlock;m++)
				{
					if(quat[4*j+k] == cacheString[m])
					{
						activeVariablesInformation[4*j+k] = cacheStringInformation[m];
						if(k==3)
						{
							cacheStringInformation[m] = false;
						}
						else
						{
							cacheStringInformation[m] = true;
						}
						break;
					}
					cout<<"ERROR::at writeActiveInformation()"<<endl;
				}
			}
		}
		delete cacheString;
	}
}
*/


/*
bool ObjectCode16::stringIsBlockEnd(string str)
{
	for(int j = 0; j < blockMarkNum;j++)
	{
		if(str == blockEndSymbol[j])
		{
			return true;
		}
	}
	return  false;
}
*/