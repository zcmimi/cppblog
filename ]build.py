#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os

# name="yamlparsertest"
name="blog"

args=[
    # "clang++",
    "g++",
    "-I./thirdlib/md4c/include",
    "-I./thirdlib/ryml/include",
    name+".cpp",
    "-L./thirdlib/md4c/lib",
    "-lmd4c",
    "-lmd4c-html",
    "-L./thirdlib/ryml/lib",
    "-lryml",
    "-o "+name,
    # "-std=c++20",
    "-std=c++17",
    "-Ofast",
    # "-g",
    "-w"
]

cmd=" ".join(args)
print(cmd)
os.system(cmd)