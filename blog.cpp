
#include<bits/stdc++.h>
#include<filesystem>
#include<md4c-html.h>

#include"md.hpp"
#include"encrypt.hpp"
#include"json.hpp"
#include"inja.hpp"
#include"YamlParser.hpp"
namespace fs=std::filesystem;
using std::vector,std::string,std::cout,std::endl,std::list,std::map,std::any,std::any_cast,std::to_string;
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

json config,t_config,t_setting;
int preview_len;
string rt;

string read(string file){
	std::ifstream t(file);
	string str((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
	return str;
}
typedef list<json>Nlist;
Nlist posts,pages;
json tags=json::object(),categories=json::object();
void get_md(Nlist&T,string pathstr){
    fs::path path(pathstr);
	fs::directory_iterator filelist(path);
	for(auto it:filelist)
    if(!it.is_directory()){
		string file=it.path().filename(),filename=it.path().stem();
        if(!(filename+".md"==file))continue;

        vector body=splitstr(read("source/_posts/"+file),"---\n");
        json x={
            {"addr","/"+filename},
            {"origin_addr",filename},
            {"content",str_markdown(body[2].c_str())},
            {"preview",str_markdown(body[2].substr(0,preview_len).c_str())},
            {"pure_content",body[2].c_str()},
            {"date","2020-02-02"},
            {"title",filename},
            {"tags",json::array()},
            {"categories",json::array()},
            {"author",config["author"]},
            {"top",0}
        };
        x.merge_patch(t_setting["defaut_front"]);
        x.merge_patch(YamlToJson(body[1].c_str()));;

        T.push_back(x);
	}
}
bool cmp_date(json x,json y){return x["date"]<y["date"];}
bool cmp_date_top(json x,json y){
    if(x.contains("top")){
        if(y.contains("top")){
            string tx=x["top"],ty=y["top"];
            if(tx==ty)return cmp_date(x,y);
            else return tx>ty;
        }
        else return 1;
    }
    else if(y.contains("top"))return 0;
    else return cmp_date(x,y);
}
json gen_index(string path,Nlist T){
    int num=atoi(config["page_articles"].get<string>().c_str()),tot=T.size(),TOT=tot/num;
    json res;
    for(int i=1;i<=TOT;++i){
        json nodes;
        for(int j=0;j<num;++j)
            if(T.empty())break;
            else nodes.push_back(T.front()),T.pop_front();
        string addr=(i==1)?path:path+"/page/"+to_string(i);

        json x={
            {"id",i},
            {"addr",addr},
            {"link",rt+addr},
            {"title",path},
            {"nodes",nodes}
        };
        res.push_back(x);
    }
    for(int i=0;i<TOT;++i){
        if(i)res[i]["pre"]=res[i-1];
        if(i+1<TOT)res[i]["nxt"]=res[i+1];
    }
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);

    double st=clock();
    freopen("res.out","w",stdout);

    config=YamlToJson(read("config.yml").c_str());

    string theme_path="theme/"+config["theme"].get<string>();

    t_config=YamlToJson(read(theme_path+"/config.yml").c_str());
    t_setting=YamlToJson(read(theme_path+"/setting.yml").c_str());

    rt=config["site_rt"];
    preview_len=atoi(config["preview_len"].get<string>().c_str());

    get_md(posts,"source/_posts");
    // get_md(pages,"source/_pages");

    posts.sort(cmp_date);
    int id=1;
    for(auto&x:posts){
        ++id;
        x["id"]=id;
        if(config["article_address"]=="number")
            x["addr"]="/posts/"+to_string(id);
        else x["addr"]="/posts/"+x["origin_addr"].get<string>();

        if(x.contains("password")){
            x["content"]=encrypt(x["content"],x["password"]);
            x["pure_content"]=x["preview"]="encrypted";
        }
    }
    posts.sort(cmp_date_top);
    for(auto&x:posts){
        for(auto&tag:x["tags"])tags[tag.get<string>()].push_back(x);
        for(auto node:x["categories"]){
            auto&now=categories;
            for(auto j:node){
                if(!now.contains("sub"))now["sub"]=json::object();
                now=now["sub"][j.get<string>()];
            }
            now["nodes"].push_back(x);
        }

        // if os.path.exists("source/_posts/"+x["origin_addr"]):
        //     cp("source/_posts/"+x["origin_addr"],dest+x["addr"])
    }

    Environment env{theme_path+"/layout/"};
    env.set_expression("{{","}}");
    env.set_comment("{#","#}");
    env.set_statement("{%","%}");
    env.set_line_statement("##");

    env.set_trim_blocks(true);
    env.set_lstrip_blocks(true);

    json global={
        {"config",config},
        {"t_config",t_config},
        {"t_setting",t_setting},
        {"data",{
            {"posts",posts},
            {"pages",pages},
            {"tags",tags},
            {"categories",categories}
        }}
    };

    gen_index("",posts);
    // Template tpl=env.parse_template(t_setting["layout"]["post"].get<string>());
    // for(auto x:posts){
    //     x.merge_patch(global);
    //     if(x.contains("layout"))env.render(
    //         env.parse_template(x["layout"].get<string>()),
    //         x
    //     );
    //     else env.render(tpl,x);
    // }

    // for(auto x:pages){
    //     x.merge_patch(global);
    //     if(x.contains("layout"))env.render(
    //         env.parse_template(x["layout"].get<string>()),
    //         x
    //     );
    //     else env.render(tpl,x);
    // }

    printf("%.5fms\n",(clock()-st)/1000.0);
}