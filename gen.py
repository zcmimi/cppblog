#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import os,json,time

st_time=time.time()

data=json.loads(open("data.json",encoding='utf-8').read())

print("finish in %.2fs"%(time.time()-st_time))

# print(data)