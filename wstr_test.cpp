#include<bits/stdc++.h>
#include<locale>
#include<codecvt>
#include"wstr.hpp"
int main(){
    setlocale(LC_ALL,""); 
    string str="三天之内撒了你?";
    printf("%s\n",wstrpre(str,2).c_str());
}