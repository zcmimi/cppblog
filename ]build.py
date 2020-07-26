#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os

args=[
    # "clang++",
    "g++",
    "-I./thirdlib/yaml-cpp/include",
    "-I./thirdlib/md4c/include",
    "-I./thirdlib/ryml/include",
    "blog.cpp",
    "-L./thirdlib/yaml-cpp/lib",
    "-lyaml-cpp",
    "-L./thirdlib/md4c/lib",
    "-lmd4c",
    "-lmd4c-html",
    "-L./thirdlib/ryml/lib",
    "-lryml",
    "-o blog",
    # "-std=c++20",
    "-std=c++17",
    # "-O3",
    "-g",
    "-w"
]

cmd=" ".join(args)
print(cmd)
os.system(cmd)