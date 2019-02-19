#include <iostream>
#include <stack>
#include "WordFilter1.h"
using namespace std;
int analysisTable[12][9] = 
{
//   I  W0  W1   (   )   #   E   T   F  
    105,400,400,104,400,400,  1,  2,  3,
    400,106,400,400,400,300,400,400,400,
    400,202,107,400,202,202,400,400,400,
    400,204,204,400,204,204,400,400,400,
    105,400,400,104,400,400,  8,  2,  3,
    400,206,206,400,206,206,400,400,400,
    105,400,400,104,400,400,400,  9,  3,
    105,400,400,104,400,400,400,400, 10,
    400,106,400,400,111,400,400,400,400,
    400,201,107,400,201,201,400,400,400,
    400,203,203,400,203,203,400,400,400,
    400,205,205,400,205,205,400,400,400
};
int getPlusCode(int x, int w);
int getReduceCode(int x, char c);
char getSymbol(int w);
void reduceSymbolStack(int order);
int tokens[1024], tokenNumNow = 0, flag = 2, temp = 1001;
stack<int> statusStack, symbol, wm;
stack<char> symbolStack;

int main()
{
    wordFilter(tokens);
    statusStack.push(0);
    symbolStack.push('#');
    int x, w, code1, code2;
    char c;
    while(flag!=0 && flag!=1)
    {
        x = statusStack.top();
        w = tokens[tokenNumNow];
        c = symbolStack.top();
        code1 = getPlusCode(x,w);
        //cout<<"code1="<<code1<<endl;
        if(code1 == 400)
            flag = 0;
        else if(code1 == 300)
            flag = 1;
        else if(code1>100 && code1<200)
        {
            //移进
            statusStack.push(code1 - 100);
            symbolStack.push(getSymbol(w));
            if(w>200 && w<400)
                symbol.push(w);
            else if(w==401||w==402)
                wm.push(w);
            tokenNumNow++;
        }
        else if(code1>200 && code1<300)
        {
            //归约
            reduceSymbolStack(code1 - 200);
            //四元式输出
            if(code1-200==1||code1-200==3)
            {
                cout<<"("<<wm.top()<<" "<<symbol.top();
                wm.pop();
                symbol.pop();
                cout<<" "<<symbol.top()<<" "<<temp<<")"<<endl;
                temp++;
            }

            c = symbolStack.top();
            x = statusStack.top();
            code2 = getReduceCode(x,c);
            cout<<"status:"<<code2<<endl;
            if(code2 > 10 || code2 < 0)
                flag = 0;
            else
            {
                statusStack.push(code2);
            }
        }
        else
        {
            flag = 0;
        }
    }
    if(flag == 1)
        cout<<"Successful"<<endl;
    else
        cout<<"Error"<<endl;
    return 0;
}


int getPlusCode(int x, int w)
{
    int row, column;
    row = x;
    switch(w)
    {
        case 401:{column = 1;break;}
        case 402:{column = 2;break;}
        case 403:{column = 3;break;}
        case 404:{column = 4;break;}
        case 405:{column = 5;break;}
        default:{column = 0;break;}
    }
    return analysisTable[row][column];
}


int getReduceCode(int x, char c)
{
    int row, column;
    row = x;
    switch(c)
    {
        case 'E':{column = 6;break;}
        case 'T':{column = 7;break;}
        case 'F':{column = 8;break;}
        default:{cout<<"ERROR::at getReduceCode();"<<endl;flag = 0;break;}
    }
    return analysisTable[row][column];
}


char getSymbol(int w)
{
    char res;
    switch(w)
    {
        case 401:{res = 'w';break;}
        case 402:{res = 'm';break;}
        case 403:{res = '(';break;}
        case 404:{res = ')';break;}
        case 405:{res = '#';break;}
        default:{res = 'i';break;}
    }
    return res;
}

void reduceSymbolStack(int order)
{
    switch(order)
    {
        case 1:{symbolStack.pop();symbolStack.pop();statusStack.pop();statusStack.pop();statusStack.pop();break;}
        case 2:{symbolStack.pop();symbolStack.push('E');statusStack.pop();break;}
        case 3:{symbolStack.pop();symbolStack.pop();statusStack.pop();statusStack.pop();statusStack.pop();break;}
        case 4:{symbolStack.pop();symbolStack.push('T');statusStack.pop();break;}
        case 5:{symbolStack.pop();symbolStack.pop();symbolStack.pop();symbolStack.push('F');statusStack.pop();statusStack.pop();statusStack.pop();break;}
        case 6:{symbolStack.pop();symbolStack.push('F');statusStack.pop();break;}
        default:{cout<<"ERROR::at reduceSymbolStack()"<<endl;flag = 0;break;}
    }
}