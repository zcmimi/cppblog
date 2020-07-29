#include<bits/stdc++.h>
#include<ryml.hpp>
#include"str.h"
using std::map,std::vector,std::cout,std::string,std::pair;

const short
    mpd_null=-1,
    mpd_seq=0,
    mpd_map=1,
    mpd_str=2,
    mpd_int=3,
    mpd_bool=4;

struct mpd{
    mpd(){type=-1;}
    mpd(const short t){type=t;}
    mpd(const vector<mpd>&t){vc=t;type=mpd_seq;}
    mpd(const map<STR,mpd>&t){mp=t;type=mpd_map;}
    mpd(const STR&s){str=s;type=mpd_str;}
    mpd(const char*s){str=s;type=mpd_str;}
    mpd(const int&v){val=v;type=mpd_int;}
    mpd(const bool&f){flag=f;type=mpd_bool;}
    
    short type;
    STR str;
    map<STR,mpd>mp;
    vector<mpd>vc;
    int val;
    bool flag;

    bool is_null(){return type==mpd_null&&mp.empty()&&vc.empty();}
    bool is_seq(){return type==mpd_seq||!vc.empty();}
    bool is_map(){return type==mpd_map||!vc.empty();}
    bool is_str(){return type==mpd_str;}
    bool is_int(){return type==mpd_int;}
    bool is_bool(){return type==mpd_bool;}

    bool has(const STR&key){return mp.count(key);}
    bool has(const char*key){return mp.count(key);}

    mpd&operator[](const STR&key){return mp[key];}
    mpd&operator[](const char*key){return mp[key];}
    mpd&operator[](const int&id){return vc[id];}

    void operator=(vector<mpd>t){vc=t;type=mpd_seq;}
    void operator=(map<STR,mpd>t){mp=t;type=mpd_map;}    
    void operator=(const STR&s){str=s;type=mpd_str;}
    void operator=(const bool f){flag=f;type=mpd_bool;}
    void operator=(const int v){val=v;type=mpd_int;}    
    void operator=(const char*s){str=s;type=mpd_str;}
    
    
    bool operator==(const STR&s){return str==s;}
    bool operator==(const int&v){return val==v;}
    bool operator==(const bool&f){return flag==f;}

    void convert(){
        if(!is_str())return;
        if(str=="~"||str=="null")type=mpd_null;
        else if(str=="True"||str=="true")flag=true,type=mpd_bool;
        else if(str=="False"||str=="false")flag=false,type=mpd_bool;
        else{
            val=std::atoi(str.c_str());
            if((int)log10(val)==str.len-1||(int)log10(-val)==str.len-2||(val==0&&str=="0"))type=mpd_int;
        }
    }

    void ins(const STR key,const mpd&v){mp.insert(pair<STR,mpd>(key,v));}
    void ins(const map<STR,mpd>&x){mp.insert(x.begin(),x.end());}
    void push_back(const mpd&v){vc.push_back(v);}
    void push_back(const vector<mpd>&x){vc.insert(vc.end(),x.begin(),x.end());}    

    void rm_em(){
        if(type==mpd_map){
            std::list<map<STR,mpd>::iterator>T;
            for(map<STR,mpd>::iterator it=mp.begin();it!=mp.end();it++)
                if((*it).second.is_null())T.push_back(it);
            while(!T.empty())mp.erase(T.back()),T.pop_back();
        }
    }
    bool iscn(char c){
        // if(c&0x80)return 0;
        // else{
        //     bool res;
        //     utf[0]=str[i];
        //     utf[1]=str[i+1];
        //     utf[2]=str[i+2];
        //     i++;
        //     i++;
        //     unicode[0] = ((utf[0] & 0x0F) << 4) | ((utf[1] & 0x3C) >>2);
        //     unicode[1] = ((utf[1] & 0x03) << 6) | (utf[2] & 0x3F);
        //     //      printf("%x,%x\n",unicode[0],unicode[1]);
        //     //      printf("aaaa %x,%x,%x\n\n",utf[0],utf[1],utf[2]);
        //     if(unicode[0] >= 0x4e && unicode[0] <= 0x9f){
        //         if (unicode[0] == 0x9f && unicode[1] >0xa5)
        //             res = false;
        //     else         
        //        res = true;
        //     }else
        //     res = false;
        //     return res;
        // }
        return 0;
        return c<0||c>255;
    }
    
    STR dump_json(){
        if(is_null())return "null";
        if(is_int())return to_STR(val);
        if(is_bool())return flag?"true":"false";
        if(is_str()){
            STR res;
            for(auto i:str){
                if(i=='"')res+="\\\"";
                else if(i=='\t')res+="\\t";
                else if(i=='\n')res+="\\n";
                else if(i=='\f')res+="\\f";
                else if(i=='/')res+="\\/";
                else if(i=='\\')res+="\\\\";
                else res+=i.c;
            }
            res.push_front('"');
            res.push_back('"');
            return res;
        }

        if(is_seq()){
            STR res;
            for(vector<mpd>::iterator i=vc.begin();i!=vc.end();++i){
                if(i!=vc.begin())res+=',';
                res+=(*i).dump_json();
            }
            res.push_front('[');
            res.push_back(']');
            return res;
        }
        
        if(is_map()){
            STR res;
            for(map<STR,mpd>::iterator i=mp.begin();i!=mp.end();++i){
                if(i!=mp.begin())res+=',';
                
                res+='"';
                res+=(*i).first.c_str();
                res+="\":";
                res+=(*i).second.dump_json();
            }
            res.push_front('{');
            res.push_back('}');
            return res;
        }
    }
};
const mpd MpdSeq=mpd(mpd_seq),MpdMap=mpd(mpd_map);

mpd convert(STR str){
    mpd x=str;
    x.convert();
    return x;
}

typedef pair<STR,mpd> PR;
typedef map<STR,mpd> MP;
typedef vector<mpd> VC;

STR get(c4::csubstr t){return STR(t.str,t.len);}

VC turn_seq(ryml::NodeRef::children_view x);
MP turn_map(ryml::NodeRef::children_view x);
mpd turn(ryml::Tree x);

MP turn_map(ryml::NodeRef::children_view x){
    MP res;
    for(ryml::NodeRef c:x){
        STR key=get(c.key());
        if(c.has_val())
            res.insert(PR(key, convert( get(c.val()) ) ));
        else if(c.is_map())
            res.insert(PR(key, turn_map(c.children()) ));
        else if(c.is_seq())
            res.insert(PR(key, turn_seq(c.children()) ));
    }
    return res;
}
VC turn_seq(ryml::NodeRef::children_view x){
    VC res;
    for(ryml::NodeRef c:x)
        if(c.is_val())
            res.push_back( convert( get(c.val()) ) );
        else if(c.is_map())
            res.push_back( turn_map(c.children()) );
        else if(c.is_seq())
            res.push_back( turn_seq(c.children()) );
    return res;
}

mpd turn(ryml::Tree x){
    mpd res;res.type=mpd_map;
    for(size_t i=x.first_child(x.root_id());i!=ryml::NONE;i=x.next_sibling(i)){
        auto t=x.get(i);
        STR key=get(t->key());
        if(t->is_keyval())
            res.ins(key, convert( get(t->val()) ) );
        else if(t->is_map())
            res.ins(key, turn_map(x[t->key()].children()) );
        else if(t->is_seq())
            res.ins(key, turn_seq(x[t->key()].children()) );
    }
    return res;
}

mpd YamlToMpd(const char*str){return turn(ryml::parse(c4::to_csubstr(str)));}