#include <string>
#include <iostream>
using namespace std;

string keywords[73] = 
{
    "asm",
    "do",
    "if",
    "return",
    "typedef",
    "auto",
    "double",
    "inline",
    "short",
    "typeid",
    "bool",
    "dynamic_cast",
    "int",
    "signed",
    "typename",
    "break",
    "else",
    "long",
    "sizeof",
    "union",
    "case",
    "enum",
    "mutable",
    "static",
    "unsigned",
    "catch",
    "explicit",
    "namespace",
    "static_cast",
    "using",
    "char",
    "export",
    "new",
    "struct",
    "virtual",
    "class",
    "extern",
    "operator",
    "switch",
    "void",
    "const",
    "false",
    "private",
    "template",
    "volatile",
    "const_cast",
    "float",
    "protected",
    "this",
    "wchar_t",
    "continue",
    "for",
    "public",
    "throw",
    "while",
    "default",
    "friend",
    "register",
    "true",
    "delete",
    "goto",
    "reinterpret_cast",
    "try",
    "alignas",
    "alignof",
    "char16_t",
    "char32_t",
    "constexpr",
    "decltype",
    "noexcept",
    "nullptr",
    "static_assert",
    "thread_local"
};

int isKeywords(string str)
{
    for(int i = 0; i < 72; i++)
    {
        if(str == keywords[i])
        return (101 + i);
    }
}