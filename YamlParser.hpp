#include<bits/stdc++.h>
#include<ryml.hpp>

using std::map,std::list,std::any,std::any_cast,std::cout,std::string,std::pair;
typedef pair<string,any> PR;
typedef map<string,any> MP;
typedef list<any>LT;

string get(c4::csubstr t){return string(t.str,t.str+t.len);}
string _str(any x){return any_cast<string>(x);}
MP _MP(any x){return any_cast<MP>(x);}
LT _LT(any x){return any_cast<LT>(x);}

LT turn_seq(ryml::NodeRef::children_view x);
MP turn_map(ryml::NodeRef::children_view x);
MP turn(ryml::Tree x);

MP turn_map(ryml::NodeRef::children_view x){
    MP res;
    for(ryml::NodeRef c:x){
        string key=get(c.key());
        if(c.has_val())res.insert(PR(key,get(c.val())));
        else if(c.is_map())res.insert(PR(key,turn_map(c.children())));
        else if(c.is_seq())res.insert(PR(key,turn_seq(c.children())));
    }
    return res;
}
LT turn_seq(ryml::NodeRef::children_view x){
    LT res;
    for(ryml::NodeRef c:x)
        if(c.is_val())res.push_back(get(c.val()));
        else if(c.is_map())res.push_back(turn_map(c.children()));
        else if(c.is_seq())res.push_back(turn_seq(c.children()));
    return res;
}

MP turn(ryml::Tree x){
    MP res;
    for(size_t i=x.first_child(x.root_id());i!=ryml::NONE;i=x.next_sibling(i)){
        auto t=x.get(i);
        string key=get(t->key());
        if(t->is_keyval())res.insert(PR(key,get(t->val())));
        else if(t->is_map())res.insert(PR(key,turn_map(x[c4::to_csubstr(key.c_str())].children())));
        else if(t->is_seq())res.insert(PR(key,turn_seq(x[c4::to_csubstr(key.c_str())].children())));
    }
    return res;
}

MP del_none(MP x){
    MP::iterator it;
    for(it=x.begin();it!=x.end();it++)
        if((*it).second.type()==typeid(string))
            if(_str((*it).second)=="")x.erase(it);
    return x;
}

MP YamlToMP(const char*str){return turn(ryml::parse(c4::to_csubstr(str)));}

#include"json.hpp"

using json=nlohmann::json;

json turn_map_json(ryml::NodeRef::children_view x);
json turn_seq_json(ryml::NodeRef::children_view x);
json turn_json(ryml::Tree x);

json turn_map_json(ryml::NodeRef::children_view x){
    json res;
    for(ryml::NodeRef c:x){
        string key=get(c.key());
        if(c.has_val())res[key]=get(c.val());
        else if(c.is_map())res[key]=turn_map_json(c.children());
        else if(c.is_seq())res[key]=turn_seq_json(c.children());
    }
    return res;
}
json turn_seq_json(ryml::NodeRef::children_view x){
    json res;
    for(ryml::NodeRef c:x)
        if(c.is_val())res.push_back(get(c.val()));
        else if(c.is_map())res.push_back(turn_map_json(c.children()));
        else if(c.is_seq())res.push_back(turn_seq_json(c.children()));
    return res;
}

json turn_json(ryml::Tree x){
    json res;
    for(size_t i=x.first_child(x.root_id());i!=ryml::NONE;i=x.next_sibling(i)){
        auto t=x.get(i);
        string key=get(t->key());
        if(t->is_keyval())res[key]=get(t->val());
        else if(t->is_map())res[key]=turn_map_json(x[c4::to_csubstr(key.c_str())].children());
        else if(t->is_seq())res[key]=turn_seq_json(x[c4::to_csubstr(key.c_str())].children());
    }
    return res;
}

json YamlToJson(const char*str){return turn_json(ryml::parse(c4::to_csubstr(str)));}