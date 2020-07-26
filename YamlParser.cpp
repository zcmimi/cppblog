#include<bits/stdc++.h>
#include<ryml.hpp>
#include "YamlParser.hpp"
/*
void tr_map(MP x);
void tr_list(LT x);

void tr_map(MP x){
    for(auto i:x){
        cout<<i.first<<": ";
        if(i.second.type()==typeid(string))cout<<_str(i.second)<<"\n";
        else if(i.second.type()==typeid(MP))cout<<"MP\n",tr_map(_MP(i.second));
        else if(i.second.type()==typeid(LT))tr_list(_LT(i.second));
    }
}
void tr_list(LT x){
    for(auto i:x){
        if(i.type()==typeid(string))cout<<_str(i)<<"\n";
        else if(i.type()==typeid(MP))tr_map(_MP(i));
        else if(i.type()==typeid(LT))tr_list(_LT(i));
    }
}
*/

string read(string file){
	std::ifstream t(file);
	string str((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
	return str;
}
int main(){
    json data=YamlToJson(read("config.yml").c_str());
    cout<<data;
}