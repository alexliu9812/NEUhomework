//Copyright (C) 2016  Jubal
#include "conversion.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

Conversion::Conversion()
{
}

//  Convert acsii String Into Hex Representation
string Conversion::hex(string s){
    ostringstream oss (ostringstream::out);
    char byte;
    char *bytePtr = &byte;

    for(int i =0; i < s.length(); i++){
        if((i+1) % 36 == 0){    //  insert new lines
            oss << "\n";
        }

        *bytePtr = s[i];
        ostringstream tmp (ostringstream::out);
        tmp << std::hex << (int) *bytePtr;

        if(tmp.str().length() < 2){
            oss << 0 << tmp.str() << " ";
        }else{
            oss << tmp.str() << " ";
            }

    }
    return oss.str();
}

//  Convert From Hex Representation Back Into ascii
string Conversion::ascii(string s){
    ostringstream oss (ostringstream::out);
    char c;
    char *cPtr = &c;

    for(int i = 0; i < s.length(); i+=3){
        if(s[i] != '\n'){
            ostringstream css (ostringstream::out);
            css << s[i] << s[i+1];
            *cPtr = hexToInt(css.str());
            oss << *cPtr;
        }else{
            i -= 2;
        }
    }
    return oss.str();
}

// Convert Hexidecimal String Into Integer
int Conversion::hexToInt(string s){
    ostringstream c1 (ostringstream::out);
    ostringstream c2 (ostringstream::out);
    c1 << s[0];
    c2 << s[1];
    int fnum = 0, snum = 0;
    int *fPointer = &fnum;
    int *sPointer = &snum;
    char letters[6] = {'a','b','c','d','e','f'};

    for(int i = 0; i < 6; i++){
        if(letters[i] == s[0]){
            *fPointer = 10+i;
            break;
        }
    }

    if(*fPointer == 0){
            *fPointer = atoi(c1.str().c_str());
        }

    for(int i = 0; i < 6; i++){
        if(letters[i] == s[1]){
            *sPointer = 10+i;
            break;
          }
    }

    if(*sPointer == 0){
            *sPointer = atoi(c2.str().c_str());
        }

    int result = (*fPointer * 16) + *sPointer;
    return result;
}

//  Strips All Nonprintable ascii Characters From String
string Conversion::getStrings(string s){
    ostringstream oss;
    int len = s.length();
    for(int i = 0; i < len; i++){
        if(s[i] >= 32 && s[i] <= 126){
            oss << s[i];
        }else if(s[i] == 10){
            oss << "\n";
        }else{
            oss << "";
        }
    }
    return oss.str();
}
