#include <iostream>
#include <stack>
#include "WordFilter1.h"
using namespace std;
//算符优先关系表
int relationTable[6][6] = 
{
//  +,*,i,(,),#
    2,3,3,3,2,0,
    2,2,3,3,2,0,
    2,2,0,0,2,2,
    3,3,3,3,4,2,
    2,2,0,0,2,2,
    0,0,3,3,3,1
};//Error:0,OK:1,>:2,<:3,=:4
int getRelation(char x, int w);
char getSymbol(int w);
int tokens[1024], tokenNumNow = 0;
stack<char> symbolStack;
int flag = 2;

int main()
{
    char x;
    int w;
    wordFilter(tokens);
    symbolStack.push('#');
    x = symbolStack.top();
    w = tokens[tokenNumNow];
    while(flag!=0 && flag!=1)
    {
        x = symbolStack.top();
        w = tokens[tokenNumNow];
        if(x!='V')
        {
            int relation = getRelation(x,w);
            cout<<"x="<<x<<",w="<<w<<",r="<<relation<<",";
            if(relation==3 || relation==4) //移进
            {
                cout<<"Move In."<<endl;
                symbolStack.push(getSymbol(w));
                tokenNumNow++;
            }
            else if(relation==0 || relation==1)
            {
                flag = relation;
            }
            else if(relation == 2) //归约
            {
                cout<<"Reduction."<<endl;
                switch(x)
                {
                    case 'i':{symbolStack.pop();symbolStack.push('V');break;}
                    case ')':{symbolStack.pop();symbolStack.pop();symbolStack.pop();symbolStack.push('V');break;}
                    default:{flag = 0;cout<<"War::at Guiyue;"<<endl;break;}
                }
            }
        }

        else
        {
            cout<<"x="<<x<<",w="<<w<<",r=";
            symbolStack.pop();
            x = symbolStack.top();
            if(x == 'V') {flag = 0;cout<<"x2=V"<<endl;break;}
            int relation = getRelation(x,w);
            cout<<relation<<",";
            if(relation==3 || relation==4) //移进
            {
                cout<<"Move In."<<endl;
                symbolStack.push('V');
                symbolStack.push(getSymbol(w));
                tokenNumNow++;
            }
            else if(relation==0 || relation==1)
            {
                flag = relation;
            }
            else if(relation == 2) //归约
            {
                cout<<"Reduction."<<endl;
                if(x=='w' ||x=='m')
                {
                    symbolStack.pop();
                }
                else
                {
                    cout<<"?V,?!=+-*/"<<endl;
                    flag = 0;
                }
            }
        }
    }
    x = symbolStack.top();
    if(flag == 1 && w == 405 && x == '#')
        cout<<"Successful!"<<endl;
    else
        cout<<"Error!"<<endl;
    return 0;
}

//获取栈顶符号和当前输入符号的关系
int getRelation(char x, int w)
{
    int row, column;
    switch(x)
    {
        case 'w':{row = 0;break;}
        case 'm':{row = 1;break;}
        case 'i':{row = 2;break;}
        case '(':{row = 3;break;}
        case ')':{row = 4;break;}
        case '#':{row = 5;break;}
        default:{cout<<"Err::at getRelation();"<<endl;break;}
    }
    switch(w)
    {
        case 401:{column = 0;break;}
        case 402:{column = 1;break;}
        case 403:{column = 3;break;}
        case 404:{column = 4;break;}
        case 405:{column = 5;break;}
        default:{column = 2;break;}
    }
    return relationTable[row][column];
}

//获取token对应的符号
char getSymbol(int w)
{
    char symbol;
    switch(w)
    {
        case 401:{symbol = 'w';break;}
        case 402:{symbol = 'm';break;}
        case 403:{symbol = '(';break;}
        case 404:{symbol = ')';break;}
        case 405:{symbol = '#';break;}
        default:{symbol = 'i';break;}
    }
    return symbol;
}