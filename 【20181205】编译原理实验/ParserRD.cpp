#include <iostream>
#include <string>
#include "WordFilter1.h"
using namespace std;
int tokens[1024], tokenNumNow = 0;
void functionE();
void functionT();
void functionF();
bool flag = 1;

int main()
{
    //生成TOKEN串并保存在全局变量tokens中
    wordFilter(tokens);
    //进入子程序E
    functionE();
    //如果没有发生错误并且最后token只剩下#
    if(flag == 1 && tokens[tokenNumNow] == 405)
        cout<<"Successful!"<<endl;
    else
        cout<<"Error!"<<endl;
    return 0;
}

void functionE()
{
    //进入子程序T
    functionT();
    //如果从T出来后，紧接着后面字符是+或者-
    while(tokens[tokenNumNow]==401)
    {
        cout<<tokens[tokenNumNow]<<endl;
        tokenNumNow++;
        //继续进入子程序T
        functionT();
    }
}

void functionT()
{
    //进入子程序T
    functionF();
    //如果从T出来后，紧接着后面字符是*或者/
    while(tokens[tokenNumNow] == 402)
    {
        cout<<tokens[tokenNumNow]<<endl;
        tokenNumNow++;
        //继续进入子程序T
        functionF();
    }
}

void functionF()
{
    int flagF1=0,flagF2=0;
    //如果当前字符是一个变量或者常量I
    if(tokens[tokenNumNow]>=200 && tokens[tokenNumNow]<=399)
    {
        flagF1=1;
        cout<<tokens[tokenNumNow]<<endl;
        tokenNumNow++;
    }
    //若当前字符是{
    else if(tokens[tokenNumNow]==403)
    {
        cout<<tokens[tokenNumNow]<<endl;
        tokenNumNow++;
        //进入子程序E
        functionE();
        //从T出来后，紧接着后面字符是否是}
        if(tokens[tokenNumNow]==404)
        {
            flagF2 = 1;
            cout<<tokens[tokenNumNow]<<endl;
            tokenNumNow++;
        }
    }
    else
    {
        flag = 0;
    }
    //进入F后字符要么是变量/常量要么是{，否则出错
    if(!flagF1 && !flagF2)
    {
        flag = 0;
    }
}