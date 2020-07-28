#include<bits/stdc++.h>
#include "YamlParser.hpp"

string read(string file){
	std::ifstream t(file);
	string str((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
	return str;
}
int main(){
    mpd data=YamlToMpd(read("test.yml").c_str());
    cout<<data.dump_json();
}