#include "Quaternion.hpp"
#include <sstream>
#include <iostream>
using namespace std;


int getVariableLink(string variable);
bool stringIsNum(string str);
const int allBlockNum = 24;
const string operators[allBlockNum] = { "+","-","*","/","=","%"};
int *dynamicLabel; //Mark whether the element is active
string *dynamicLabelLink; //Record elements in base blocks


void Quaternion::updateFourFormula()
{
    newQuat = new string[stringNum];
    newQuatNum = 0;
    for(int i = 0; i<=quatNum;i++)
    {
        if(quat[4*i]!="$$$$$$$")
        {
            for(int j = 0; j < 4; j++)
            {
                newQuat[4*newQuatNum+j] = quat[4*i+j];
            }
            newQuatNum++;
        }
    }

    //Print newQuat
	/*
    for(int i = 0; i < newQuatNum; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cout<<newQuat[4*i+j]<<" ";
        }
        cout<<endl;
    }
	*/
}


void Quaternion::dag()
{
    for(int counts = 0; counts < blockNum; counts++)
    {
        int head = blockMarkPoint[2*counts];
        int tail = blockMarkPoint[2*counts+1];
        int blockLenth = tail - head + 1;
        int registeredNum = registerVariableLink(head, tail);
        dynamicLabel = new int[registeredNum];
        flag = new bool[quatNum+1];
        for (int i = 0; i < registeredNum; dynamicLabel[i] = 2, i++);
        for(int i = 0; i <= quatNum;flag[i] = true,i++);
        for (int i = tail; i >= head; i--)
        {
            if (quat[4*i+2] == "#")
            {
                if (stringIsNum(quat[4*i+1]))
                {
                    flag[i] = true;
                }
                else
                {
                    bool findExistedTemp = false;
                    for (int j = i; j >= head; j--)
                    {
                        if (quat[4*j+3] == quat[4*i+1] && quat[4*j+3].find("qtmp")!=string::npos)
                        {
                            findExistedTemp = true;
                            quat[4*j+3] = quat[4*i+3];
                        }
                    }
                    if(findExistedTemp)
                        flag[i] = false;
                    else flag[i] = true;
                }
            }
            else
            {
                int labelhere = dynamicLabel[getVariableLink(quat[4*i+3])];
                int linkhere3 = getVariableLink(quat[4*i+3]);
                int linkhere2 = getVariableLink(quat[4*i+2]);
                int linkhere1 = getVariableLink(quat[4*i+1]);
                if(labelhere==1 || labelhere==2)
                {
                    flag[i] = true;
                    dynamicLabel[linkhere3] = 0;
                    dynamicLabel[linkhere2] = 1;
                    dynamicLabel[linkhere1] = 1;
                }
            }
        }

        //Print dag's output
        
        for(int i = head; i <= tail; i++)
        {
            if(flag[i] == true)
            {
                for(int j = 0; j < 4; j++)
                    cout<<quat[4*i+j]<<" ";
                cout<<endl;
            }
        }
        

        for(int i = head; i <= tail; i++)
        {
            if(flag[i] == false)
            {
                quat[4*i] = "$$$$$$$";
            }
        }
    }
}



int Quaternion::registerVariableLink(int head, int tail)
{
    int registeredNum = 0;
    dynamicLabelLink = new string[3*(tail-head+1)];
    for(int i = head; i <= tail; i++)
    {
        for(int j = 1; j < 4; j++)
        {
            if(quat[4*i+j] != "#")
            {
                bool registered = false;
                for(int k = 0; !dynamicLabelLink[k].empty();k++)
                {
                    if(quat[4*i+j] == dynamicLabelLink[k]) {registered = true; break;};
                }
                if(!registered)
                {
                    dynamicLabelLink[registeredNum++] = quat[4*i+j];
                }
            }
        }
    }
    return registeredNum;
}



int getVariableLink(string variable)
{
    for(int i = 0; !dynamicLabelLink[i].empty(); i++)
    {
        if(dynamicLabelLink[i] == variable)
            return i;
    }
    cout<<"ERROR::at getVariableLink();"<<variable<< endl;
}



bool stringIsNum(string str)  
{  
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d))
        return false;
    if (sin >> c)
        return false;
    return true;  
}



void Quaternion::devideBasicBlock()
{
    blockNum = 0;
    blockMarkPoint = new int[2 * quatNum];
    for(int i = 0; i <= quatNum; i++)
    {
        if(stringIsOpera(quat[4 * i]))
        {
            blockMarkPoint[2*blockNum] = i;
            for(; stringIsOpera(quat[4 * i]) && i <= quatNum;i++);
            i--;
            blockMarkPoint[2*blockNum+1] = i;
            blockNum ++;
        }
    }
}


bool Quaternion::stringIsOpera(string str)
{
    for(int j = 0; j < allBlockNum;j++)
    {
        if(str == operators[j])
        {
            return true;
        }
    }
    return  false;
}