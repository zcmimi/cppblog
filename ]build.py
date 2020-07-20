#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os

args=[
    # "clang++",
    "g++",
    "-I./thirdlib/yaml-cpp/include",
    "-I./thirdlib/md4c/include",
    "blog.cpp",
    "-L./thirdlib/yaml-cpp/lib",
    "-lyaml-cpp",
    "-L./thirdlib/md4c/lib",
    "-lmd4c",
    "-lmd4c-html",
    "-o blog",
    # "-std=c++20",
    "-std=c++17",
    # "-O3",
    "-g"
]

cmd=" ".join(args)
print(cmd)
os.system(cmd)