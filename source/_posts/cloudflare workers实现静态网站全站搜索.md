---
title: cloudflare workers实现静态网站全站搜索
date: 2020-06-15 10:29
tags:
 - 前端
 - 技术

categories:
 - [技术分享]

top: 0
html:
---

## 背景

静态博客实现搜索一直是一件很困扰人的事

之前使用的方案:

1. 静态文件实现搜索

   将所有文章数据记录到一个json文件中,

   前端加载该文件,本地进行搜索

   ---

   不是长久之计

   当文字量较小时看不出什么问题

   文字量变大时,json文件也随之变大,搜索前用户需要加载整个文件,消耗流量大,加载较慢,增大网站负载,而且如果网站带宽较小,用户需要加载非常久,体验极差

   我的博客的数据文件已经达到`3.2MB`,若部署在github pages,国内访问体验非常差劲

2. 采用百度,google等搜索引擎的全站搜索

   google体验不错,可是国内需要使用魔法才可以访问

   baidu收录慢,体验差

   而且各大搜索引擎自定义性不高

3. algolia

   一个非常不错的自定义搜索api

   还可以自定义数据中心位置(如:香港),挺良心的

   可惜额度有点低,免费版支持上传10000条索引,每个月只有10000次请求

4. site search 360

   免费版每个月只有1000次请求,无法使用api

   图个方便

偶然看到cloudflare的workers项目,想到可以用来实现静态网站支持搜索

## cloudflare workers

> 通过 Workers 在边缘运行 JavaScript

免费计划:

> Free
>
> 用于个人用途和简单应用
>
> 计划功能
>
> - 包括**100,000个请求/天**(UTC+0)1
> - 每个请求最多占用 10 毫秒 CPU 时间
> - 第一个请求后的延迟最低
> - 最多 30 个 Worker


## 思路

首先还是将所有文章数据记录到一个json文件中

让worker预读取文件,缓存,worker是一直运行着的,之后不用再读取数据文件

worker搜索时

用关键词分别匹配标题、标签、分类、内容

然后返回匹配成功的所有文章

只返回所需信息: 标题、链接、内容预览

## 实现

将json数据文件按以下格式记录

```json
[
    {
        "title":"<title>",             // 标题
        "link":"<link>",               // 链接
        "tags":["tag1","tag2",/*...*/],// 标签
        "categories":[                 // 分类
            ["xx","xxx","xxxx",/*...*/],
            ["yy","yyy","yyyy"],
            /*...*/
        ],
        "content":"<content>"          // 内容
    },
    /*...*/
]
```

将下面代码粘贴到worker中运行

```javascript
const file='https://zcmimi.github.io/pure_data.json', // json数据文件位置
    addr='https://blog_search.zcmimi.workers.dev', // 当前worker网址
    preview_len=50; // 预览字数
var data,url;
async function getdata(){
    await fetch(file).
            then(res=>res.json()).
            then(json=>data=json);
}
function chk(content,text,typ=0){
    content=content.toLowerCase();
    if(typ==0)return content.indexOf(text)!=-1;
    else if(typ==1){
        for(var i=0,j=0;i<content.length;++i)
            if(content[i]==text[j])
                if(++j==text.length)return 1;
    }
    return 0;
}
async function search(text,typ=0){
    text=text.toLowerCase();
    if(!data)await getdata();
    var res=[];
    for(i in data){
        var f=0;
        if(chk(data[i].title,text,typ))f=1;
        else for(j in data[i].tags)
            if(chk(data[i].tags[j],text,typ)){
                f=1;
                break;
            }
        else for(j in data[i].categories)
            for(k in data[i].categories[j])
                if(chk(data[i].categories[j][k],text,typ)){
                    f=1;
                    break;
                }
        else if(chk(data[i].content,text,typ))f=1;
        if(f)res.push([data[i].link,data[i].title,data[i].content.substring(0,preview_len)]);
    }
    return JSON.stringify(res);
}
function geturl(keyword){
    var vars=url.split("&");
    for(var i=0;i<vars.length;++i){
        var pair=vars[i].split("=");
        if(pair[0]==keyword)return pair[1];
    }
    return 0;
}
/*------------------------------------------------------------*/
addEventListener('fetch',event=>{
    event.respondWith(handleRequest(event.request))
})
async function handleRequest(request){
    var res="usage:\n\
?keyword=<keyword>&typ=<typ>\n\
required: keyword";
    url=decodeURI(request.url);
    if(chk(url,"keyword")){
        url=url.substr(addr.length+2,url.length);
        res=await search(geturl("keyword"),geturl("typ"));
    }
    return new Response(res,{
        status:200,
        headers:new Headers({
            // 允许跨域访问,也可自定义域名
            'access-control-allow-origin': '*',
            'access-control-allow-methods': 'GET,POST,PUT,PATCH,TRACE,DELETE,HEAD,OPTIONS',
            'access-control-max-age': '1728000',
        }),
    });
}
```

使用:

workers地址+`/?keyword=<keyword>&typ=<typ>`

会返回查询结果的json,格式如下:

```json
[
    [
        "<link>",  // 链接
        "<title>", // 标题
        "<preview>"// 预览
    ],
    /*...*/
]
```

其中`<keyword>`为查询关键词,必填

`typ`为匹配模式,选填,默认`typ=0`

`typ=0`: 子串匹配

`typ=1`: 子序列匹配

前端使用示范:

```html
<div class="mdui-progress" id='loading-progress' style="position: fixed;top:0;z-index: 999999;"><div class="mdui-progress-indeterminate"></div></div>
<div class="mdui-dialog" id="search_dialog">
    <div class="mdui-dialog-title">Search</div>
    <div class="mdui-dialog-content">
        <div class="mdui-textfield">
            <i class="mdui-icon material-icons">search</i>
            <input id="search_input" class="mdui-textfield-input" placeholder="搜索">
        </div>
        <div id="search_result" class="mdui-list"></div>
    </div>
</div>
```

```javascript
function search(api){ //api为worker地址
    document.getElementById('loading-progress').hidden=0;
    var text=document.getElementById("search_input").value.toLowerCase(),
        res=document.getElementById("search_result"),
        xhr=new XMLHttpRequest();
    res.innerHTML='';
    xhr.open('GET',api+'/?keyword='+text,true);
    xhr.onreadystatechange=function(){
        if(xhr.readyState==4){
            document.getElementById('loading-progress').hidden=1;
            var data=JSON.parse(this.responseText);
            for(i in data){
                var a=document.createElement('a'),
                    content=document.createElement('div'),
                    Title=document.createElement('div'),
                    Text=document.createElement('div');
                
                a.classList.add('mdui-list-item');
                Title.classList.add('mdui-list-item-title');
                Text.classList.add('mdui-list-item-text');
                content.classList.add('mdui-list-item-content');
                a.href=data[i][0];
                Title.innerText=data[i][1];
                Text.innerText=data[i][2].replace(/[\r\n]/g," ");
                
                content.appendChild(Title),content.appendChild(Text);
                a.appendChild(content);
                
                res.appendChild(a);
            }
            search_dialog.handleUpdate();
        }
    }
    xhr.send();
}
```

## 结语

有了cloudflare workers的帮助,终于解决了静态网站全站搜索的问题

加载速度也得到有效提升

一天10万次的搜索对于个人博客已经绰绰有余了

对于这个结果我算是挺满意的了
