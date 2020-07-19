
#include<bits/stdc++.h>
#include<filesystem>
#include "yaml-cpp/yaml.h"
using namespace std;
namespace fs=std::filesystem;
string read(string file){
	ifstream t(file);
	string str((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
	return str;
}
void getfile(){
	
}
int main(){
	YAML::Node config=YAML::LoadFile("config.yml");

	fs::path str("source/_posts");
	if(!fs::exists(str))return 1;
	fs::directory_entry entry(str);
	fs::directory_iterator list(str);

	freopen("out.out","w",stdout);
	for(auto it:list){
		string file=it.path().filename().string();
		cout<<file<<endl;
		cout<<read("source/_posts/"+file)<<endl;
	}
}