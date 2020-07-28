
#include<bits/stdc++.h>
#include<filesystem>
#include<md4c-html.h>

#include"md.hpp"
#include"encrypt.hpp"
#include"YamlParser.hpp"

namespace fs=std::filesystem;
using std::vector,std::string,std::cout,std::endl,std::list,std::map,std::any,std::any_cast,std::to_string;

mpd config,t_config,t_setting;
int preview_len;
string rt;
mpd posts=MpdSeq,
    pages=MpdSeq,
    tags=MpdMap,
    categories=MpdMap,
    posts_index=MpdSeq,
    tags_index=MpdMap;

string read(const string&file){
	std::ifstream t(file);
	string str((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
	return str;
}

pair<string,string> mkdsplit(const string&s){
    string meta,body;
    const char *str=s.c_str();int len=strlen(str),ff=-1;
    for(int i=0;i<len;++i){
        if(s[i]=='-'&&s[i+1]=='-'&&s[i+2]=='-'){++ff;i+=2;continue;}
        if(ff)body+=s[i];
        else if(~ff)meta+=s[i];
    }
    return pair<string,string>(meta,body);
}

void get_md(mpd&T,string pathstr){
    fs::path path(pathstr);
	fs::directory_iterator filelist(path);
	for(auto&it:filelist)
    if(!it.is_directory()){
		string file=it.path().filename(),filename=it.path().stem();
        if(!(filename+".md"==file))continue;

        pair<string,string>mkd=mkdsplit(read("source/_posts/"+file));
        mpd x=YamlToMpd(mkd.first.c_str());
        x.rm_em();
        x.ins(t_setting["defaut_front"].mp);
        x.ins("addr","/"+filename);
        x.ins("origin_addr",filename);
        x.ins("content",str_markdown(mkd.second.c_str()));
        x.ins("preview",str_markdown(mkd.second.substr(0,preview_len).c_str()));
        x.ins("pure_content",mkd.second);
        x.ins("date","2020-02-02");
        x.ins("title",filename);
        x.ins("tags",MpdSeq);
        x.ins("categories",MpdSeq);
        x.ins("author",config["author"]);
        x.ins("top",0);

        T.push_back(x);
	}
}
inline bool cmp_date(mpd&x,mpd&y){return x["date"].str>y["date"].str;}
inline bool cmp_date_top(mpd&x,mpd&y){
    if(x.has("top")){
        if(y.has("top")){
            string tx=x["top"].str,ty=y["top"].str;
            if(tx==ty)return cmp_date(x,y);
            else return tx>ty;
        }
        else return 1;
    }
    else if(y.has("top"))return 0;
    else return cmp_date(x,y);
}
void gen_index(string path,mpd T,mpd&res){
    int num=config["page_articles"].val,tot=T.vc.size(),TOT=tot/num;
    for(int i=1;i<=TOT;++i){
        mpd nodes;
        for(int j=0;j<num;++j)
            if(T.vc.empty())break;
            else nodes.push_back(T.vc.front());
        string addr=(i==1)?path:path+"/page/"+to_string(i);

        mpd x=MpdMap;
        x["id"]=i;
        x["addr"]=addr;
        x["link"]=rt+addr;
        x["title"]=path;
        x["nodes"]=nodes;

        res.push_back(x);
    }
    for(int i=0;i<TOT;++i){
        if(i)res[i].ins("pre",res[i-1]);
        if(i+1<TOT)res[i].ins("nxt",res[i+1]);
    }
}
void gen_tags_index(){
    for(auto&tag:tags.mp)
        gen_index("/tags/"+tag.first,tag.second,tags_index[(string)tag.first]);  
}
void gen_categories_index(string path,mpd&cates){
    if(cates.has("sub"))
        for(auto&cate:cates["sub"].mp)
            gen_categories_index(path+'/'+cate.first,cate.second);
    if(cates.has("nodes"))
        gen_index(path,cates["nodes"],cates["index"]);
}

void gen_sitemap(){

}

void gen_rss(){

}

void expt(){
    mpd data=MpdMap;

    data["config"]=config;
    data["t_config"]=t_config;
    data["t_setting"]=t_setting;

    data["posts"]=posts;
    data["pages"]=pages;
    data["tags"]=tags;
    data["categories"]=categories;

    // data["posts_index"]=posts_index;
    // data["tags_index"]=tags_index;

    string res=data.dump_json();
    FILE *fp;fp=fopen("data.json","w");
    fwrite(res.c_str(),1,res.length(),fp);
    fclose(fp);
}
void expt_pure(){
    mpd pure_data=MpdSeq;
    for(auto&i:posts.vc){
        mpd x=MpdMap;
        x["title"]=i["title"];
        x["content"]=i["pure_content"];
        x["link"]=i["link"];
        x["tags"]=i["tags"];
        x["categories"]=i["categories"];
        pure_data.push_back(x);
    }
    string res=pure_data.dump_json();
    FILE *fp;fp=fopen("pure_data.json","w");
    fwrite(res.c_str(),1,res.length(),fp);
    fclose(fp);
}
int main(){
    std::ios::sync_with_stdio(false);

    double st=clock();

    config=YamlToMpd(read("config.yml").c_str());

    string theme_path="theme/"+config["theme"].str;

    t_config=YamlToMpd(read(theme_path+"/config.yml").c_str());
    t_setting=YamlToMpd(read(theme_path+"/setting.yml").c_str());

    rt=config["site_rt"].str;
    preview_len=config["preview_len"].val;

    get_md(posts,"source/_posts");
    get_md(pages,"source/_pages");

    sort(posts.vc.begin(),posts.vc.end(),cmp_date);
    int id=1;
    for(auto&x:posts.vc){
        ++id;
        x["id"]=id;
        if(config["article_address"]=="number")
            x["addr"]="/posts/"+to_string(id);
        else x["addr"]="/posts/"+x["origin_addr"].str;

        if(x.has("password")){
            x["content"]=encrypt(x["content"].str,x["password"].str);
            x["pure_content"]="encrypted";
            x["preview"]="encrypted";
        }
    }
    sort(posts.vc.begin(),posts.vc.end(),cmp_date_top);
    for(auto&x:posts.vc){
        for(auto&tag:x["tags"].vc){
            if(!tags.has(tag.str))tags.ins(tag.str,MpdSeq);
            tags[tag.str].push_back(x);
        }
        for(auto&node:x["categories"].vc){
            mpd *it=&categories;
            for(auto&j:node.vc){
                mpd&now=*it;
                if(!now.has("sub"))now.ins("sub",MpdMap);
                if(!now["sub"].has(j.str))now["sub"].ins(j.str,MpdMap);
                it=&now.mp["sub"].mp[j.str];
            }
            mpd&now=*it;
            if(!now.has("nodes"))now.ins("nodes",MpdSeq);
            now.mp["nodes"].push_back(x);
        }

        // if os.path.exists("source/_posts/"+x["origin_addr"]):
        //     cp("source/_posts/"+x["origin_addr"],dest+x["addr"])
    }

    // gen_index("",posts,posts_index);
    // gen_tags_index();
    // gen_categories_index("/categories",categories);

    printf("generate in %.5fms\n",(clock()-st)/1000.0);st=clock();

    expt();
    expt_pure();

    printf("export in %.5fms\n",(clock()-st)/1000.0);st=clock();
}