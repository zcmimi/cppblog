---
title: 数论工具 
date: 2020-07-08 08:05
tags: 
 - 数论

categories:
# - [***,***]

top: 0 
html:
---

<ul class="mdui-list">
    <li class="mdui-list-item mdui-ripple">
        <i class="mdui-list-item-icon mdui-icon material-icons" style="color: #1abc9c">check_circle</i>
        <div class="mdui-list-item-content">质数检测</div>
        <div class="mdui-list-item mdui-textfield">
            <input class="mdui-textfield-input" placeholder="请输入要检验的数字" onchange="prime_chk(this.value)">
        </div>
    </li>
    <li class="mdui-list-item mdui-ripple">
        <i class="mdui-list-item-icon mdui-icon material-icons" style="color: #1abc9c">check_circle</i>
        <div class="mdui-list-item-content">求原根</div>
        <div class="mdui-list-item mdui-textfield">
            <input class="mdui-textfield-input" placeholder="请输入模数" onchange="get_primitive_root(this.value)">
        </div>
    </li>
</ul>

<script>
function prime_chk(x){
    if(isNaN(x)||x<0){mdui.alert('请输入有效数字!');node.value="";return;}
    if(x<=1){mdui.alert(x.toString()+'不是质数');return;}
    for(i=2;i*i<=x;++i)if(x%i==0){
        mdui.alert(x.toString()+'不是质数,可以被'+i.toString()+'整除');
        return;
    }
    mdui.alert(x.toString()+'是质数!');
}
function pw(x,b,p){
    var res=1;
    while(b){
        if(b&1)res=res*x%p;
        b>>=1,x=x*x%p;
    }
    return res;
}
function get_primitive_root(m){
    var a=[],tt=0;
    for(var i=2;i<=m-2;++i)
        if((m-1)%i==0)a[++tt]=i;
    for(var i=2;i<=10000;++i){
        var ff=1;
        for(var j=1;j<=tt;++j)
            if(pw(i,a[j],m)==1){ff=0;break;}
        if(ff){
            mdui.alert(m.toString()+'的原根是'+i.toString());
            return;
        }
    }
    return -1;
}
</script>