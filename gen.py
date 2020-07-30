#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import os,json,time
import jinja2

st_time=time.time()

str=open("data.json",encoding='utf-8').read()

print("read in %.2fs"%(time.time()-st_time))

data=json.loads(str)

print("get in %.2fs"%(time.time()-st_time))

# print(data)