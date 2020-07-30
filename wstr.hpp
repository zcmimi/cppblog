#ifndef WSTR_H
#define WSTR_H

#include<bits/stdc++.h>
#include<locale>
#include<codecvt>
using std::string,std::wstring;
std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>strconverter;
string to_string(const wstring&wstr){return strconverter.to_bytes(wstr);}
wstring to_wstring(const string&str){return strconverter.from_bytes(str);}

string wstrpre(const string&str,int len){return to_string(to_wstring(str).substr(0,len));}

#endif