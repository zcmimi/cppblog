---
title: pbds 
date: 2020-03-27 19:24
author: 
avatar:
tags: 
 - stl

categories:
 - [note]

thumbnail: 
top: 0 
comment: 1
---

`pbds`是一个比stl还stl的东西

`__gnu_pbds`,全称: `Policy based data structures`

## 引入

按需引入:

```cpp
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp> //tree
#include<ext/pb_ds/hash_policy.hpp> //hash
#include<ext/pb_ds/trie_policy.hpp> //trie
#include<ext/pb_ds/priority_queue.hpp> //priority_queue
using namespace __gnu_pbds;
```
全部引入:

```cpp
#include<bits/extc++.h>
using namespace __gnu_pbds;
```

## Hash

封装的哈希表

可以代替`map`,而且比`map`快得多,$\mathcal{O(n)}$与$\mathcal{O(n \log n)}$的区别

```cpp
cc_hash_table<int,bool>h;
gp_hash_table<int,bool>h; //似乎更快一些
```

操作和`map`差不多,支持`[]`和`find`

## Tree

封装了三种平衡树,`rb_tree`,`splay_tree`,`ov_tree`,建议使用`rb_tree`

```cpp
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y) 
tree<pii,null_type,less<pii>,rb_tree_tag,tree_order_statistics_node_update> tr;
pii //存储的类型
null_type //无映射(低版本g++为null_mapped_type)
less<pii> //从小到大排序
rb_tree_tag //红黑树
tree_order_statistics_node_update //更新方式 
tr.insert(mp(x,y)); //插入
tr.erase(mp(x,y)); //删除
tr.order_of_key(pii(x,y)); //求排名 
tr.find_by_order(x); //找k小值,返回迭代器 
tr.join(b); //将b并入tr,前提是两棵树类型一样且没有重复元素 
tr.split(v,b); //分裂,key小于等于v的元素属于tr,其余的属于b
tr.lower_bound(x); //返回第一个大于等于x的元素的迭代器
tr.upper_bound(x); //返回第一个大于x的元素的迭代器
```

和`set`一样**不支持重复元素**,记住千万不要插入重复元素

[LG P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update>T;
int n;ll x,ans;
int main(){
    scanf("%d",&n);
    for(int i=1,opt;i<=n;++i){
        scanf("%d%lld",&opt,&x);
        if(opt==1)T.insert((x<<20)+i);
        if(opt==2)T.erase(T.lower_bound(x<<20));
        if(opt==3)printf("%d\n",T.order_of_key(x<<20)+1);
        if(opt==4)ans=*T.find_by_order(x-1),printf("%lld\n",ans>>20);
        if(opt==5)ans=*--T.lower_bound(x<<20),printf("%lld\n",ans>>20);
        if(opt==6)ans=*T.upper_bound((x<<20)+n),printf("%lld\n",ans>>20);
    }
}
```

这pbds速度还蛮快的

## Trie

字典树

```cpp
typedef trie<string,null_type,trie_string_access_traits<>,pat_trie_tag,trie_prefix_search_node_update>tr;
//第一个参数必须为字符串类型,tag也有别的tag,但pat最快,与tree相同,node_update支持自定义
tr.insert(s); //插入s 
tr.erase(s); //删除s 
tr.join(b); //将b并入tr 
pair//pair的使用如下：
pair<tr::iterator,tr::iterator>range=base.prefix_range(x);
for(tr::iterator it=range.first;it!=range.second;it++)
    cout<<*it<<' '<<endl;
//pair中第一个是起始迭代器,第二个是终止迭代器,遍历过去就可以找到所有字符串了。 
```

## priority_queue

```cpp
priority_queue<int,greater<int>,TAG>Q;//小根堆,大根堆写less<int>
/*其中的TAG为类型,有以下几种：
pairing_heap_tag
thin_heap_tag
binomial_heap_tag
rc_binomial_heap_tag 
binary_heap_tag
其中pairing_help_tag最快*/
Q.push(x);
Q.pop();
Q.top();
Q.join(b);
Q.empty();
Q.size(); 
Q.modify(it,x);
Q.erase(it);
//pbds里的优先队列还可以用迭代器遍历
```

部分内容引自https://www.luogu.com.cn/blog/Chanis/gnu-pbds