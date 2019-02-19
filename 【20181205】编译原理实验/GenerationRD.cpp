#include <iostream>
#include <string>
#include <stack>
#include "WordFilter1.h"
using namespace std;
int tokens[1024], tokenNumNow = 0;
void functionE();
void functionT();
void functionF();
bool flag = 1;
stack<int> symbol, wm;
int temp = 1001;

int main()
{
    wordFilter(tokens);
    functionE();
    if(flag == 1 && tokens[tokenNumNow] == 405)
        cout<<"Successful!"<<endl;
    else
        cout<<"Error!"<<endl;
    return 0;
}

void functionE()
{
    functionT();
    while(tokens[tokenNumNow]==401)
    {
        //cout<<tokens[tokenNumNow]<<endl;
		wm.push(tokens[tokenNumNow]);
        tokenNumNow++;
        functionT();
        //从E进入的T子程序跳出时，输出四元式
		cout<<"("<<wm.top()<<" "<<symbol.top();
		wm.pop();
		symbol.pop();
		cout<<" "<<symbol.top()<<" "<<temp<<")"<<endl;
		symbol.pop();
		symbol.push(temp);
		temp = temp+1;
    }
}

void functionT()
{
    functionF();
    while(tokens[tokenNumNow] == 402)
    {
        //cout<<tokens[tokenNumNow]<<endl;
		wm.push(tokens[tokenNumNow]);
        tokenNumNow++;
        functionF();
        //从T进入的F子程序跳出时，输出四元式
		cout<<"("<<wm.top()<<" "<<symbol.top();
		wm.pop();
		symbol.pop();
		cout<<" "<<symbol.top()<<" "<<temp<<")"<<endl;
		symbol.pop();
		symbol.push(temp);
		temp = temp+1;
    }
}

void functionF()
{
    int flagF1=0,flagF2=0;    
    if(tokens[tokenNumNow]>=200 && tokens[tokenNumNow]<=399)
    {
        flagF1=1;
        //cout<<tokens[tokenNumNow]<<endl;
		symbol.push(tokens[tokenNumNow]);
        tokenNumNow++;
    }
    else if(tokens[tokenNumNow]==403)
    {
        //cout<<tokens[tokenNumNow]<<endl;
        tokenNumNow++;
        functionE();
        if(tokens[tokenNumNow]==404)
        {
            flagF2 = 1;
            //cout<<tokens[tokenNumNow]<<endl;
            tokenNumNow++;
        }
    }
    else
    {
        flag = 0;
    }
    if(!flagF1 && !flagF2)
    {
        flag = 0;
    }
}