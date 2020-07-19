---
title: 带修区间第k大
date: 2020-02-01
tags: 
  - 数据结构
  - 树
  - 算法

categories:
  - [算法,数据结构]
  - [note]
---
以[Dynamic Rankings](https://www.luogu.com.cn/problem/P2617)为例：

如果不带修改,那就是普通的主席树

待修改: 树状数组套动态开点权值线段树

对于修改$a_p$,

受影响的有$[p,n]$

但是我们不需要从$p$修改到$n$

可以套个树状数组记录修改位置

树状数组的每个节点都是一颗线段树

这样修改的时候就可以做到$\Theta(n \log^2 n)$

