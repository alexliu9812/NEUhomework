#include "Quaternion.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


Quaternion::Quaternion(std::string fileName)
{
    readFromFile(fileName);

} 


Quaternion::~Quaternion()
{
    delete quat;
    delete blockMarkPoint;
    delete flag;
    delete newQuat;
}


void Quaternion::readFromFile(string fileName)
{
    //Statistical line number, potential BUG: The last line has a newline symbol
    fstream fin(fileName,ios::in);
    if(!fin)
    {
        cerr<<"ERROR::Cannot open Quat File, at Quaternion::readFromFile"<<endl;
        exit(1);
    }
    char ch;
    int row = 0;
    while(fin.get(ch))
	{	
		if(ch == '\n')
		row++;
	}
    fin.close();

    //Initialize Quaternion
	quatNum = row - 1;
    stringNum = (quatNum + 1) * 4;
    quat = new string[4*(quatNum+1)+1];
	//cout << "quatNum+1=" << quatNum+1<< endl;
    //Read in Quaternion from file
    ifstream infile;
    infile.open(fileName.data());
    infile >> noskipws;
    infile >> ch;
    for(int i = 0; i < stringNum;i++)
    {
        while(ch!=' ' && ch!='\n' && !infile.eof() && ch!=EOF)
        {
            quat[i] += ch;
            infile >> ch;
        }
        infile >> ch;
    }
    infile.close();
	quat[4 * (quatNum + 1)] = "";

    //Print Quaternion
    /*
    for(int i = 0; i <= row; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cout<<quat[4*i+j]<<" ";
        }
        cout<<endl;
    }
	*/
    
}