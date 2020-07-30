#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import os,json,time,math,shutil
from jinja2 import Environment,FileSystemLoader

def gen_index(path,a):
    num=config["page_articles"]
    tot=len(a)
    TOT=math.ceil(tot/num)
    res=[]
    for now,i in enumerate(range(0,tot,num),1):
        nodes=a[i:i+num]
        if now==1:addr=path
        else:addr=path+"/page/%d"%now

        res.append({
            "id":now,
            "addr":addr,
            "link":rt+addr,
            "title":path,
            "nodes":nodes,
            "pre":None,
            "nxt":None,
        })
    for id,x in enumerate(res):
        x["pre"]=res[id-1] if id else None
        x["nxt"]=res[id+1] if id+1<TOT else None
    return res

def gen_tags():
    for tag in tags:
        index=gen_index("/tags/"+tag,tags[tag])
        for i in index:
            op(dest+i["addr"],template.render(**i,tag=tag,total=len(index)))
            urls.append([config["site_url"]+i["addr"],last_build_time])
def gen_categories(path,cates):
    urls.append([config["site_url"]+path,last_build_time])
    if "sub" in cates:
        for cate in cates["sub"]:
            gen_categories(path+"/"+cate,cates["sub"][cate])
    if "nodes" in cates:
        index=gen_index(path,cates["nodes"])
        for i in index:
            op(dest+i["addr"],template.render(**i,path=path,total=len(index),sub=cates["sub"] if "sub" in cates else None))
    elif "sub" in cates:
        op(dest+path,template.render(title=path,path=path,sub=cates["sub"]))

def mkdir(path):
    if not os.path.exists(path): os.makedirs(path)
def cp(src,dst):
    if os.path.isdir(src):
        if os.path.exists(dst):shutil.rmtree(dst)
        shutil.copytree(src,dst)
    else:
        shutil.copyfile(src,dst)
def op(path,str):
    if path.endswith(".html"):
        t=path.split("/")
        mkdir("/".join(t[0:len(t)-2]))
    else:
        mkdir(path)
        path+="/index.html"
    open(path,"w",encoding="utf-8").write(str)

def work(i):
    global template
    op(dest+i["addr"],
        env.get_template(t_setting["layout"][i["layout"]]).render(**i) if "layout" in i
        else template.render(**i)
    )

st_time=time.time()

str=open("data.json",encoding="utf-8").read()
print("read in %.2fs"%(time.time()-st_time))
data=json.loads(str)
print("get in %.2fs"%(time.time()-st_time))

config=data["config"]
t_config=data["t_config"]
t_setting=data["t_setting"]
dest=config["dest"]
rt=config["site_rt"]
posts=data["posts"]
pages=data["pages"]
tags=data["tags"]
categories=data["categories"]
urls=[]
data["last_build_time"]=last_build_time=time.strftime("%Y-%m-%dT%H:%M:%SZ",time.localtime())

if not os.path.exists(dest):mkdir(dest)

for i in os.listdir('source'):
    if i=='_pages' or i=='_posts':continue
    cp('source/'+i,dest+'/'+i)

env=Environment(loader=FileSystemLoader("theme/%s/layout/"%config["theme"]))
env.trim_blocks=True
env.lstrip_blocks=True
env.globals.update(**{
    'config':config,
    't_config':t_config,
    'data':{
        'posts':posts,
        'pages':pages,
        'tags':tags,
        'categories':categories
    },
    'last_build_time': last_build_time
})

template=env.get_template(t_setting["layout"]["post"])
if t_setting["default_render"]["posts"]:
    for i in posts:work(i)

template=env.get_template(t_setting["layout"]["page"])
if t_setting["default_render"]["pages"]:
    for i in pages:work(i)

template=env.get_template(t_setting["layout"]["index"])
if t_setting["default_render"]["index"]:
    index=gen_index("",posts)
    for i in index:
        op(dest+i["addr"],template.render(**i,total=len(index)))

template=env.get_template(t_setting["layout"]["tag_index"])
if t_setting["default_render"]["tags"]:gen_tags()

template=env.get_template(t_setting["layout"]["categories"])
if t_setting["default_render"]["categories"]:
    gen_categories("/categories",categories)

for i in t_setting["extra_render"]:
    op(dest+i["path"],env.get_template(t_setting["layout"][i["layout"]]).render(title=i["title"]))

print("finish in %.2fs"%(time.time()-st_time))