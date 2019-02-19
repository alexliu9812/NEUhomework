#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

void wordFilter(int* tokens)
{
    char ch;
    string str;
    int token, tokenNumNow = 0;
    string fileName = "a.txt";
    ifstream infile;
    infile.open(fileName.data());
    assert(infile.is_open());
    infile >> noskipws;
    infile >> ch;
    string identifier[1024], constant[1024];
    int idNum = 0, conNum = 0, bounNum = 0;

    while(!infile.eof() && ch!=EOF)
    {
        //过滤换行、Tab或空格
        if(ch=='\n'||ch=='\t'||ch==' ')
        {
            infile >> ch;
        }

        //若是字母或下划线开头,是变量
        else if((ch>='a' && ch<='z') ||
            (ch>='A' && ch<='Z') ||
            (ch == '_'))
        {
            str = "";
            token = 0;
            while((
                (ch>='a' && ch<='z') ||
                (ch>='A' && ch<='Z') ||
                (ch == '_') ||
                (ch>='0'&&ch<='9')) &&
                (!infile.eof()) )
            {
                str = str + ch;
                infile >> ch;
            }
            cout<<"("<<str<<",";

            int haveId = 0;
            for(int i = 0; i < idNum; i++)
            {
                if(identifier[i] == str)
                {
                    token = 200 + i;
                    cout<<token<<")"<<endl;
                    tokens[tokenNumNow++] = token;
                    haveId = 1;
                    break;
                }
            }
            if(haveId == 0)
            {
                identifier[idNum++] = str;
                token = 200 + idNum;
                cout<<token<<")"<<endl;
                tokens[tokenNumNow++] = token;
            }
        }

        //若是数字开头，是数字常量
        else if(ch>='0' && ch<='9')
        {
            //token = 3;
            str = "";
            while(((ch>='0' && ch<='9')||(ch == '.')) && !(ch=='\n'||ch=='\t'||ch==' ') && (!infile.eof()) )
            {
                str = str + ch;
                infile >> ch;
            }
            constant[conNum++] = str;
            token = 300 + conNum;
            cout<<"("<<str<<","<<token<<")"<<endl;
            tokens[tokenNumNow++] = token;
        }

        //若是引号开头，是字符(串)常量
        else if(ch == '\'' || ch == '\"')
        {
           // token = 3;
            str = "";
            str = str + ch;
            infile >> ch;
            while(ch != '\'' && ch != '\"' && !infile.eof())
            {
                str = str + ch;
                infile >> ch;
            }
            str = str + ch;
            infile >> ch;
            constant[conNum++] = str;
            token = 300 + conNum;
            cout<<"("<<str<<","<<token<<")"<<endl;
            tokens[tokenNumNow++] = token;
        }

        //+-*/()#，是运算符(界符)
        else if(ch == '+'||ch == '-')
        {
            str = "";
            str = str + ch;
            infile >> ch;
            token = 401;
            cout<<"("<<str<<","<<token<<")"<<endl;
            tokens[tokenNumNow++] = token;
        }
        
        else if(ch == '*'||ch == '/')
        {
            str = "";
            str = str + ch;
            infile >> ch;
            token = 402;
            cout<<"("<<str<<","<<token<<")"<<endl;
            tokens[tokenNumNow++] = token;
        }

        else if(ch == '(')
        {
            str = "";
            str = str + ch;
            infile >> ch;
            token = 403;
            cout<<"("<<str<<","<<token<<")"<<endl;
            tokens[tokenNumNow++] = token;
        }

        else if(ch == ')')
        {
            str = "";
            str = str + ch;
            infile >> ch;
            token = 404;
            cout<<"("<<str<<","<<token<<")"<<endl;
            tokens[tokenNumNow++] = token;
        }        
        
        else if(ch == '#')
        {
            str = "";
            str = str + ch;
            infile >> ch;
            token = 405;
            cout<<"("<<str<<","<<token<<")"<<endl;
            tokens[tokenNumNow++] = token;
        }

        else
        {
            cout<<"ERROR!"<<endl;
            tokens[tokenNumNow++] = 999;
            infile >> ch;
        }
    }
    infile.close();
    /*
    for(int i = 0; i < tokenNumNow; i++)
    {
        cout<<"token"<<i<<":"<<tokens[i]<<endl;
    }
    */
}