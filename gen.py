#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import os,json

str=open("data.json",encoding='utf-8').read()

data=json.loads(str)

print(data)