#include <iostream>
#include <stack>
#include "WordFilter1.h"
using namespace std;
void reverseStack(int order);
int lookupTable(char x, int w);
bool endIsRight(char x, int w);
stack<char> s;
int tokens[1024], tokenNumNow = 0;
bool flag = 1;
//产生式逆序压栈
char E[2] = {'T','R'};
char R[3] = {'W','T','R'};
char T[2] = {'F','Y'};
char Y[3] = {'M','F','Y'};
char F[3] = {'(','E',')'};
//终结符表
char endSymbol[6] = {'I','W','M','(',')','#'};
//LL（1）分析表
int analysisTable[5][6] = 
{
    1, 0, 0, 1, 0, 0,
    0, 2, 0, 0, 3, 3,
    4, 0, 0, 4, 0, 0,
    0, 6, 5, 0, 6, 6,
    7, 0, 0, 8, 0, 0
};

int main()
{
    char x;
    int w;
    wordFilter(tokens);
    s.push('#');
    s.push('E');

    while(x != '#')
    {
        x = s.top();
        s.pop();
        w = tokens[tokenNumNow];
        cout<<"x="<<x<<","<<"w="<<w<<endl;
        bool xIsEndSymbol = 0;
        for(int i = 0; i < sizeof(endSymbol);i++)
        {
            //若栈顶符号是终结符，当前token移进
            if (x == endSymbol[i])
            {
                xIsEndSymbol = 1;
                if(endIsRight(x,w)) {tokenNumNow++; break;}
                else {flag = 0;break;}
            }
        }
        //若x不是中介符号，逆序压栈
        if(xIsEndSymbol == 0)
        {
            int orderhere = lookupTable(x,w);
            if(orderhere == 0){flag = 0; break;}
            else{reverseStack(orderhere);}
        }
    }
    if(flag == 1 && x == '#' && w == 405)
        cout<<"Successful!"<<endl;
    else
        cout<<"Error!"<<endl;
    return 0;
}

//返回选择的产生式序号
int lookupTable(char x, int w)
{
    int row, column;
    switch(x)
    {
        case 'E':{row = 0;break;}
        case 'R':{row = 1;break;}
        case 'T':{row = 2;break;}
        case 'Y':{row = 3;break;}
        case 'F':{row = 4;break;}
        default:{cout<<"ERROR::at LookupTable();"<<endl;break;}
    }
    switch(w)
    {
        case 401:{column = 1;break;}
        case 402:{column = 2;break;}
        case 403:{column = 3;break;}
        case 404:{column = 4;break;}
        case 405:{column = 5;break;}
        default:{column = 0;break;}
    }
    cout<<"choose:"<<analysisTable[row][column]<<endl;
    return analysisTable[row][column];
}

//按照产生式序号进行逆序压栈
void reverseStack(int order)
{
    switch(order)
    {
        case 1:{for(int i = sizeof(E)-1; i>=0;s.push(E[i]), i--);break;}
        case 2:{for(int i = sizeof(R)-1; i>=0;s.push(R[i]), i--);break;}
        case 4:{for(int i = sizeof(T)-1; i>=0;s.push(T[i]), i--);break;}
        case 5:{for(int i = sizeof(Y)-1; i>=0;s.push(Y[i]), i--);break;}
        case 8:{for(int i = sizeof(F)-1; i>=0;s.push(F[i]), i--);break;}
        case 3:{break;}
        case 6:{break;}
        case 7:{s.push('I');break;}
        default:{cout<<"ERROR!"<<endl;break;}
    }
}

//判断栈顶符号（终结符）与当前token是否对应
bool endIsRight(char x, int w)
{
    switch(x)
    {
        case 'I':{if(w >= 200 && w < 399) return 1;else return 0;break;}
        case 'W':{if(w == 401) return 1;else return 0;break;}
        case 'M':{if(w == 402) return 1;else return 0;break;}
        case '(':{if(w == 403) return 1;else return 0;break;}
        case ')':{if(w == 404) return 1;else return 0;break;}
        case '#':{if(w == 405) return 1;else return 0;break;}
        default:{cout<<"ERROR::at endIsRight();"<<endl;return 0;break;}
    }
}