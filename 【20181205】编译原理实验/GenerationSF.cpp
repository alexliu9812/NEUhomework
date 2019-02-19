#include <iostream>
#include <stack>
#include "WordFilter1.h"
using namespace std;
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
stack<int> symbol, wm;
int flag = 2;
int temp = 1001;

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
            cout<<"x="<<x<<",w="<<w<<",r="<<relation<<endl;
            if(relation==3 || relation==4) //移进
            {
                symbolStack.push(getSymbol(w));
                if(w>200 && w<400)
                    symbol.push(w);
                else if(w==401||w==402)
                    wm.push(w);
                tokenNumNow++;
            }
            else if(relation==0 || relation==1)
            {
                flag = relation;
            }
            else if(relation == 2) //归约
            {
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
            symbolStack.pop();
            x = symbolStack.top();
            if(x == 'V') {flag = 0;cout<<"x2=V"<<endl;break;}
            int relation = getRelation(x,w);
            if(relation==3 || relation==4) //移进
            {
                symbolStack.push('V');
                symbolStack.push(getSymbol(w));
                if(w>200 && w<400)
                    symbol.push(w);
                else if(w==401||w==402)
                    wm.push(w);
                tokenNumNow++;
            }
            else if(relation==0 || relation==1)
            {
                flag = relation;
            }
            else if(relation == 2) //归约
            {
                if(x=='w' ||x=='m')
                {
                    symbolStack.pop();
                    cout<<"("<<wm.top()<<" "<<symbol.top();
                    wm.pop();
                    symbol.pop();
                    cout<<" "<<symbol.top()<<" "<<temp<<")"<<endl;
                    temp++;
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

void intoStack(int relation)
{
    switch(relation)
    {
        case 3:{}
    }
}

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