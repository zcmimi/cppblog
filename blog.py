#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os,sys,time,shutil,glob,re,json,math,random,hashlib
from multiprocessing import Pool
import mistune,md_math,PyRSS2Gen,cmd

try:
    import yaml,pypinyin,requests
    from jinja2 import Environment,FileSystemLoader
    from encrypt import encrypt
except:
    print('未安装依赖,正在安装')
    print('pip install -r requirement.txt -i https://pypi.tuna.tsinghua.edu.cn/simple')
    try:import pip
    except:print('未安装pip'),sys.exit()
    try:
        pip._internal.main([
            'install','-r','requirement.txt',
            '-i','https://pypi.tuna.tsinghua.edu.cn/simple'
        ])
    except:
        try:
            os.system('pip3 install -r requirement.txt -i https://pypi.tuna.tsinghua.edu.cn/simple')
        except:
            os.system('pip install -r requirement.txt -i https://pypi.tuna.tsinghua.edu.cn/simple')
    import yaml,pypinyin,requests
    from jinja2 import Environment,FileSystemLoader
    from encrypt import encrypt

def rec(a):
    res=a
    try:res=time.strftime('%Y-%m-%dT%H:%M:%SZ',time.strptime(a,'%Y-%m-%d %H:%M:%S'))
    except:
        try:res=time.strftime('%Y-%m-%dT%H:%MZ',time.strptime(a,'%Y-%m-%d %H:%M'))
        except:
            try:res=time.strftime('%Y-%m-%d',time.strptime(a,'%Y-%m-%d %H'))
            except:return a
            else: return res
        else:return res
    else:return res

class _render_:
    def ng(self,text):
        return text
    def __init__(self):
        if not t_setting['markdown']:
            self.render=self.ng
            return
        if config['math']:
            self.render=md_math.parse
        else:self.render=mistune.Markdown()
    def gen(self,text):
        return self.render(text)
def del_none(a):
    c={}
    for x in a:
        if a[x]!=None:c.update({x:a[x]})
    return c
def genmd5(str):
    hl=hashlib.md5()
    hl.update(str.encode(encoding='utf-8'))
    return hl.hexdigest()
def geninfo(file):
    data=open(file,encoding='utf-8').read().split('---\n')
    meta=yaml.load(data[1])
    content=''.join(data[2:])
    filename=os.path.splitext(os.path.split(file)[1])[0]
    return {
        **{
            'md5':genmd5(content),
            'id':None,
            'origin_addr':filename,
            'addr':'/'+filename,
            'link':None,
            'pre':None,
            'nxt':None,
            'title': filename,
            'date': time.strftime('%Y-%m-%d %H:%M',time.localtime(os.stat(file).st_mtime)),
            'author': config['author'],
            'tags':[],
            'categories':[],
            'top':0,
            'pure_content':content,
            'content':rd.gen(content),
            'preview':rd.gen(content[0:min(len(content),config['preview_len'])])
        },
        **t_setting['defaut_front'],
        **del_none(meta)
    }
def topinyin(word):
    res=''
    for i in pypinyin.pinyin(word,style=pypinyin.NORMAL):
        res+=''.join(i)+'-'
    return res[0:len(res)-1].replace(' ','-')

def cmp2(x): # 置顶
    if x['top']!=None and x['top']>0:
        return '23333-12-31 '+str(x['top'])
    else: return str(x['date'])

def sort_posts():
    posts.sort(key=lambda x:str(x['date']),reverse=True) # 日期排序
    tot=len(posts)
    for id,x in enumerate(posts,1): # 按日期编号
        x['id']=id
        if   config['article_address']=='number':x['addr']='/posts/%d'%id
        elif config['article_address']=='pinyin':x['addr']='/posts/'+topinyin(x['origin_addr'])
        else:x['addr']='/posts/'+x['origin_addr']

        if 'permalink' in x:
            x['addr']='/posts/'+x['permalink']
        x['link']=rt+x['addr']
    for id,x in enumerate(posts): # 获取前后信息
        x['pre']=posts[(id-1+tot)%tot]
        x['nxt']=posts[(id+1)%tot]
    posts.sort(key=cmp2,reverse=True)

def gen_index(path,a):
    num=config['page_articles']
    tot=len(a)
    TOT=math.ceil(tot/num)
    res=[]
    for now,i in enumerate(range(0,tot,num),1):
        nodes=a[i:i+num]
        if now==1:addr=path
        else:addr=path+'/page/%d'%now

        res.append({
            'id':now,
            'addr':addr,
            'link':rt+addr,
            'title':path,
            'nodes':nodes,
            'pre':None,
            'nxt':None,
        })
    for id,x in enumerate(res):
        x['pre']=res[id-1] if id else None
        x['nxt']=res[id+1] if id+1<TOT else None
    return res

def get_posts():
    global posts
    if pool==False:
        posts=[geninfo(i) for i in glob.glob(r'source/_posts/*.md')]
    else:
        res=[pool.apply_async(geninfo,(i,)) for i in glob.glob(r'source/_posts/*.md')]
        for i in res:
            i.wait(),posts.append(i.get())
    sort_posts()
    for x in posts:
        if 'password' in x and x['password']:
            x['content']=encrypt(x['content'],x['password'])
            x['pure_content']=x['preview']="encrypted"
        for tag in x['tags']:
            if tag in tags:tags[tag].append(x)
            else: tags.update({tag:[x]})
        for node in x['categories']:
            now=categories
            for categorie in node:
                if not 'sub' in now:now.update({'sub':{}})
                if not categorie in now['sub']: now['sub'].update({categorie:{}})
                now=now['sub'][categorie]
            if 'nodes' not in now:now.update({'nodes':[x]})
            else: now['nodes'].append(x)
        if os.path.exists('source/_posts/'+x['origin_addr']):
            cp('source/_posts/'+x['origin_addr'],dest+x['addr'])
            
        urls.append([config['site_url']+x['addr'],rec(str(x['date']))])
def get_pages():
    global pages
    if pool==False:
        pages=[geninfo(i) for i in glob.glob(r'source/_pages/*.md')]
    else:
        res=[pool.apply_async(geninfo,(i,)) for i in glob.glob(r'source/_pages/*.md')]
        for i in res:
            i.wait(),pages.append(i.get())
    for x in pages:
        x['link']=rt+x['addr']
        urls.append([config['site_url']+x['addr'],rec(str(x['date']))])

def gen_tags():
    for tag in tags:
        index=gen_index('/tags/'+tag,tags[tag])
        for i in index:
            op(dest+i['addr'],template.render(**i,tag=tag,total=len(index)))
            urls.append([config['site_url']+i['addr'],last_build_time])
def gen_categories(path,cates):
    urls.append([config['site_url']+path,last_build_time])
    if 'sub' in cates:
        for cate in cates['sub']:
            gen_categories(path+'/'+cate,cates['sub'][cate])
    if 'nodes' in cates:
        index=gen_index(path,cates['nodes'])
        for i in index:
            op(dest+i['addr'],template.render(**i,path=path,total=len(index),sub=cates['sub'] if 'sub' in cates else None))
    elif 'sub' in cates:
        op(dest+path,template.render(title=path,path=path,sub=cates['sub']))

def gen_pure_data():
    for x in posts:
        pure_data.append({
            'title':x['title'],
            'content':x['pure_content'],
            'link':x['link'],
            'tags':x['tags'],
            'categories':x['categories']
        })
    for x in pages:
        pure_data.append({
            'title':x['title'],
            'content':x['pure_content'],
            'link':x['link'],
            'tags':x['tags'],
            'categories':x['categories']
        })
    open(dest+'/pure_data.json',"w",encoding='utf-8').write(json.dumps(pure_data))

def gen_rss():
    rss_items=[]
    for i in pure_data:
        link=config['site_real_rt']+i['link']
        text=i['content'][0:config['preview_len']]
        res=''
        text=text.split('\n\n')
        for x in text: res+='<p>'+x+'</p>'
        res+="<a href=%s target='_blank'>阅读全文</a>"%link
        rss_items.append(PyRSS2Gen.RSSItem(
            title=i["title"],
            link=link,
            description=res,
            guid=PyRSS2Gen.Guid(link)
        ))
    rss=PyRSS2Gen.RSS2(
        title=config['site_name'],
        link=config['site_url'],
        description=config['site_name'],
        lastBuildDate=last_build_time,
        items=rss_items
    )
    rss.write_xml(open(dest+"/atom.xml","w",encoding='utf-8'),encoding='utf-8')
def gen_sitemap():
    a=open(dest+'/sitemap.xml',"w",encoding='utf-8')
    b=open(dest+'/sitemap.txt',"w",encoding='utf-8')
    a.write('''<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">\n''')
    for i in urls:
        a.write("<url><loc>%s</loc><lastmod>%s</lastmod></url>\n"%(i[0],i[1]))
        b.write(i[0]+'\n')
    a.write("</urlset>")

def baidu_push():
    print("是否百度推送?y|N")
    if input()!="y": return
    print("百度推送中……")
    if os.path.exists('baidu_push_last.txt'):
        oldurls=open("baidu_push_last.txt","r",encoding='utf-8').read()
    else: oldurls=""
    newurls=""
    for i in urls:
       if not i[0] in oldurls:
           newurls+=i[0]+'\n'
    open("baidu_push_last.txt","w",encoding='utf-8').write(newurls)
    r=requests.post(config["baidu_push"]['url'],files={'file': open('baidu_push_last.txt','rb')})
    print("推送结果:\n%s\n"%r.text)
    open("baidu_push_last.txt","w",encoding='utf-8').write(oldurls+newurls)

def mkdir(path):
    if not os.path.exists(path): os.makedirs(path)
def cp(src,dst):
    if os.path.isdir(src):
        if os.path.exists(dst):shutil.rmtree(dst)
        shutil.copytree(src,dst)
    else:
        shutil.copyfile(src,dst)
def op(path,str):
    if path.endswith('.html'):
        t=path.split('/')
        mkdir('/'.join(t[0:len(t)-2]))
    else:
        mkdir(path)
        path+='/index.html'
    open(path,"w",encoding='utf-8').write(str)
def work(i):
    global template
    op(dest+i['addr'],
        env.get_template(t_setting['layout'][i['layout']]).render(**i) if 'layout' in i
        else template.render(**i)
    )

####################################################################################

try:yaml.warnings({'YAMLLoadWarning': False})
except: pass

if __name__=='__main__':

    config=yaml.load(open('config.yml',encoding='utf-8').read())
    dest=config['dest']

    cmd.work(config)

    st_time=time.time()

    rt=config['site_rt']
    if config['article_address']=='pinyin':
        import pypinyin
    t_config=yaml.load(open('theme/%s/config.yml'%config['theme'],encoding='utf-8').read())
    t_setting=yaml.load(open('theme/%s/setting.yml'%config['theme'],encoding='utf-8').read())
    rd=_render_()
    posts=[]
    pages=[]
    tags={}
    categories={}
    pure_data=[]
    urls=[]
    last_build_time=time.strftime('%Y-%m-%dT%H:%M:%SZ',time.localtime())
    env=Environment(loader=FileSystemLoader('theme/%s/layout/'%config['theme']))
    env.trim_blocks=True
    env.lstrip_blocks=True

    if not os.path.exists(dest):mkdir(dest)

    try:
        if config['multithreading']:pool=Pool()
        else:pool=False
    except:
        pool=False
        print('不支持多线程')

    for i in glob.glob('theme/%s/source'%config['theme']):cp(i,dest)

    get_posts()
    get_pages()

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

    for i in os.listdir('source'):
        if i=='_pages' or i=='_posts':continue
        cp('source/'+i,dest+'/'+i)

    template=env.get_template(t_setting['layout']['post'])
    if t_setting['default_render']['posts']:
        for i in posts:work(i)

    template=env.get_template(t_setting['layout']['page'])
    if t_setting['default_render']['pages']:
        for i in pages:work(i)

    template=env.get_template(t_setting['layout']['index'])
    if t_setting['default_render']['index']:
        index=gen_index('',posts)
        for i in index:
            op(dest+i['addr'],template.render(**i,total=len(index)))

    template=env.get_template(t_setting['layout']['tag_index'])
    if t_setting['default_render']['tags']:gen_tags()

    template=env.get_template(t_setting['layout']['categories'])
    if t_setting['default_render']['categories']:
        gen_categories('/categories',categories)

    for i in t_setting['extra_render']:
        op(dest+i['path'],env.get_template(t_setting['layout'][i['layout']]).render(title=i['title']))

    gen_pure_data()
    if config['rss']:gen_rss()
    if config['sitemap']:gen_sitemap()

    print("finish in %.2fs"%(time.time()-st_time))

    if config['baidu_push']['enable']:baidu_push()