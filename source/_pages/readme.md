---
title: Readme
date: 2020-05-16 22:00
author:
avatar: 
tags: 
# - ***

thumbnail: 
comment: 1
html:
---
## 简介

[demo](https://blog.zcmimi.top/)

本博客生成器基于`python`,使用若干`pip`包,兼容`hexo`,`jekyll`等博客生成器

使用`markdown`,支持`LaTeX`

建议先了解下`markdown`和`yaml`等语法

---

目前的主题为基于`MDUI`的`material design`

## 依赖

### 必须

请先安装`python-frontmatter`

```bash
pip install frontmatter
```

建议先将`pip`换为国内源

### 可选功能

1. `htmlmin`

   用于压缩网页源代码

2. `pypinyin`

   用于生成博文的拼音地址

3. `PyRSS2Gen`

   用于生成博客的`rss`
   
4. `requests`

   用于百度推送

## 配置文件

`config.yml`

```yaml
site_name: "your blog name" # 站点名称
site_domain: "example.com" # 域名
site_rt: "" # 网站根目录位置
# 没有特殊情况请填 ""
# 比如你因为某些特殊原因,没法直接在域名根目录部署网站,位置变成了 example.com/web
#   那么:
#   site_domain: example.com
#   site_rt: "/web"
#   本地调试时请 site_rt: ""

site_icon: /img/avatar.webp # 博客图标图片地址
assets_rt: 
# 如果有cdn提高assets文件夹的加载速度,请填入地址
# 否则留空

avatar: /img/avatar.webp # 博客头像,默认头像地址
author: "your name" # 默认作者
theme: clean # 自带主题两种风格(beauty|clean)

article_address: number # 文章地址(number|pinyin)
# 若选择pinyin,请先pip install pypinyin

# 首页
page_articles: 10 # 首页每页文章数
preview_len: 100  # 首页文章预览字数

randomimg_type: folder # 随机图片地址类型(folder | list)
randomimg_list:        # 随机图片地址列表
# - url
randomimg_path: /img # 随机图片文件夹地址
randomimg_tot: 33    # 图片总数
randomimg_suf: webp  # 图片文件后缀名

htmlmin: False # 是否压缩源代码
# 若填1,请先pip install htmlmin

comment: False # 是否开启评论
comment_typ: valine # 目前仅支持valine
# Valine评论(请参考https://valine.js.org/configuration.html)
valine_appid: <your appid>
valine_appkey: <your appkey>
valine_placeholder: 来快活啊 # 提示语

pjax: False # 是否默认开启pjax

# 音乐播放器(使用MetingJS)
music_server: netease  # 服务器
music_id: 765727960    # 歌单id
music_order: random    # 随机/顺序
music_theme: '#f7a4b9' # 颜色
# 详见https://github.com/metowolf/MetingJS

baidu_push: True # 百度推送 请安装requests(pip install requests
baidu_push_url: http://data.zz.baidu.com/urls?site=<your site url>&token=<your token> #百度推送接口调用地址

rss: False # 生成rss(/atom.xml)
           # 请先pip install PyRSS2Gen

repo: # 可以同时推送至多个仓库
  - git@github.com:zcmimi/blog.git # 部署仓库地址
```



## 开始写作

### 新建文章: 

`python blog.py n/new xxxx`

将会在`source/_posts`文件夹创建`xxxx.md`

### 新建页面

`python blog.py np/newpage xxxx`

将会在`source/_pages`文件夹创建`xxxx.md`

### 预览

`python blog.py d/deploy`

---

### front-matter

使用`front-matter`记录文章信息

```yaml
---
title: {title} # 文章标题
date:  {date}  # 创建日期
author:        # 文章作者
               # (不填默认为配置文件中的作者)
               
avatar:        # 文章作者头像
               # (不填默认为配置文件中的头像)
               
tags:          # 文章标签
# - ***

categories:    # 文章所属分类
# - [***,***]

thumbnail:     # 文章缩略图
top: 0         # 首页置顶优先级
               # 0为关闭置顶
               # >0,越大优先级越高
               
comment: 1     # 开启/关闭评论
html:          # 在文章前加入html代码
---

你的文章
```

注意,分类使用方法:

```yaml
categories:
- [Diary, PlayStation]
- [Diary, Games]
- [Life]
```

此时这篇文章同时包括三个分类： `PlayStation` 和 `Games` 分别都是父分类 `Diary` 的子分类,同时 `Life` 是一个没有子分类的分类。

### 内容

使用`markdown`+`latex`

行内公式: `$...$`,$E=mc^2$

行外公式: `$$...$$`
$$
E=mc^2
$$

### 文章页面

生成的文件在`/posts/xxx`

支持标签和分类

如需在文章中引用图片或文件,请在`source/posts/`文件夹中新建一个以该篇文章标题命名的文件夹,放入文件即可直接引用,如`![233.png]`

### 其他页面

生成的文件在`/xxx`

支持标签,不支持分类,不会在首页显示

请不要新建叫做`links`的页面,会被友链页面覆盖

## 资源文件夹

在`source`文件夹中,除了`_posts`和`_pages`两个文件夹,其他文件夹会被复制到生成的文件夹的根目录

比如新建`source/img/`,就会被博客根目录,可以通过`/img/`访问

## 部署

首先渲染博客,`python blog.py`生成的博客文件在`web`文件夹中

`python blog.py s/server`可以预览生成的文件

您将它可以上传到您喜欢的地方

推荐部署到: 

1. `github pages`

2. `coding pages`

3. `netlify`

4. 腾讯云`cos`

5. `gitlab pages`

6. 用`rsync`或其他工具推送到您的服务器

---

目前支持`git`的方式部署,如部署到`github pages`(推荐)

请先填好`config.yml`中的`repo`

运行`python blog.py d`以部署博客

---

其他方式请自行上传`web`文件夹

## 自定义

### 自定义顶部应用栏

请修改`layout/appbar.html`

### 自定义侧边栏

请编辑`source/drawer.yml`

如果你不满意自带的模板,请删除`source/drawer.yml`,

新建`source/drawer.html`,自行编辑

### 自定义友情链接

修改`source/_pages/links.yml`

使用`yaml`语法

以我的友链为例子: 

```yaml
comment: 1 # 是否开启评论
info: # 添加友链部分下方的html代码
Friends: # 此栏目标题
  - name: zcmimi                 # 名称
    url: https://blog.zcmimi.top # 指向地址
    avatar: /img/avatar.webp     # 头像
    content: 一只可爱的菜鸡        # 描述
    background-color: "#ffe9f0"  # 卡片背景颜色
  # 下面以此类推

Websites: # 此栏目标题
  - name: Luogu
    url: https://www.luogu.com.cn
    avatar: /assets/icon/luogu.png
    content: 计算机科学教育新生态
    background-color: "#89aaff"
# 以此类推
```

### 添加自定义代码

1. 自定义`css`
   
   修改`assets/custom.css`,它会在源代码`head`部分被引入

2. 自定义`html`
   
   修改`layout/custom.html`,这部分代码会添加到源代码末尾(`</html>`的前面)

