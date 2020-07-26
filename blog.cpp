
#include<bits/stdc++.h>
#include<filesystem>
#include<yaml-cpp/yaml.h>
#include<md4c-html.h>
#include<ryml.hpp>

#include"md.hpp"
#include"encrypt.hpp"
#include"json.hpp"
#include"inja.hpp"
namespace fs=std::filesystem;
using std::vector,std::string,std::cout,std::endl,std::list,std::map;
using namespace inja;
using json=nlohmann::json;
vector<string>splitstr(const string&s,const string&c){
    string::size_type pos1,pos2;
    pos2=s.find(c);
    pos1=0;
    vector<string>v;
    while(string::npos!=pos2){
        v.push_back(s.substr(pos1,pos2-pos1));
        pos1=pos2+c.size();
        pos2=s.find(c,pos1);
    }
    if(pos1!=s.length())v.push_back(s.substr(pos1));
    return v;
}

// ryml::Tree config,t_config,t_setting;

string read(string file){
	std::ifstream t(file);
	string str((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
	return str;
}
ryml::Tree load(string file){
    return ryml::parse(c4::to_csubstr(read(file).c_str()));
}
typedef list<YAML::Node>Nlist;
Nlist posts,pages;
map<string,Nlist>tags;
struct Categories{
    map<string,Categories>sub;
    Nlist nodes;
}categories;
YAML::Node del_none(YAML::Node x){
    // for(YAML::const_iterator it=x.begin();it!=x.end();++it)
    //     cout<<it->second.as<string>()<<endl;
    return x;
}
// void get_md(Nlist&T,string pathstr){
//     fs::path path(pathstr);
// 	fs::directory_iterator filelist(path);
// 	for(auto it:filelist)
//     if(!it.is_directory()){
// 		string file=it.path().filename(),filename=it.path().stem();
//         if(!(filename+".md"==file))continue;

//         vector body=splitstr(read("source/_posts/"+file),"---\n");
//         YAML::Node x=del_none(YAML::Load(body[1]));

//         x["addr"]="/"+filename;
//         x["origin_addr"]=filename;
//         x["content"]=markdown(body[2].c_str());
//         x["preview"]=markdown(body[2].substr(0,config["preview_len"].as<int>()).c_str());
//         x["pure_content"]=body[2].c_str();

//         #define fill(key,val) if(!x[key])x[key]=val

//         fill("date","2020-02-02");
//         fill("title",filename);
//         fill("author",config["author"]);
//         // fill("tag",string []);
//         // fill("categories",string []);
//         fill("top",0);

//         T.push_back(x);
// 	}
// }
// bool cmp_date(YAML::Node x,YAML::Node y){
//     return x["date"].as<string>()<y["date"].as<string>();
// }
// bool cmp_date_top(YAML::Node x,YAML::Node y){
//     if(x["top"]){
//         if(y["top"]){
//             string tx=x["top"].as<string>(),ty=y["top"].as<string>();
//             if(tx==ty)return cmp_date(x,y);
//             else return tx>ty;
//         }
//         else return 1;
//     }
//     else if(y["top"])return 0;
//     else return cmp_date(x,y);
// }
// void gen_index(Nlist T){

// }

int main(){
    std::ios::sync_with_stdio(false);

    double st=clock();
    freopen("res.out","w",stdout);
    ryml::Tree config=load("config.yml");
    string theme_path="theme/"+config["theme"].val();
    // t_config=ryml::Tree(read(theme_path+"/config.yml").c_str());
    // t_setting=ryml::Tree(read(theme_path+"/setting.yml").c_str());
    
    // cout<<config["dest"]<<endl;

    // get_md(posts,"source/_posts");
    // get_md(pages,"source/_pages");

    return 0;

    // posts.sort(cmp_date);
    // int id=1;
    // for(Nlist::iterator it=posts.begin();it!=posts.end();++it,++id){
    //     YAML::Node x=*it;
    //     x["id"]=id;
    //     if(config["article_address"].as<string>()=="number")
    //         x["addr"]="/posts/"+std::to_string(id);
    //     else x["addr"]="/posts/"+x["origin_addr"].as<string>();
    // }
    // posts.sort(cmp_date_top);
    // for(auto x:posts){
    //     if(x["password"]){
    //         x["content"]=encrypt(x["content"].as<string>(),x["password"].as<string>());
    //         x["pure_content"]=x["preview"]="encrypted";
    //     }
    //     for(auto tag:x["tags"])
    //         tags[tag.as<string>()].push_back(x);
    //     for(auto node:x["categories"]){
    //         auto now=categories;
    //         for(auto j:node){
    //             string categorie=j.as<string>();
    //             now.sub[categorie]=(Categories){};
    //             now=now.sub[categorie];
    //         }
    //         now.nodes.push_back(x);
    //     }

    //     // if os.path.exists("source/_posts/"+x["origin_addr"]):
    //         // cp("source/_posts/"+x["origin_addr"],dest+x["addr"])
    // }

    // Environment env{theme_path+"/layout/"};
    // env.set_expression("{{","}}");
    // env.set_comment("{#","#}");
    // env.set_statement("{%","%}");
    // env.set_line_statement("##");

    // Template tpl=env.parse_template(t_setting["layout"]["post"].as<string>());
    // for(auto x:posts);

    printf("%.5fms\n",(clock()-st)/1000.0);
}