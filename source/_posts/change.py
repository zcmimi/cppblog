import os
import sys
import time
import shutil
import json
import yaml
import random
import math
from frontmatter import Frontmatter

list=os.listdir('.')

for i in list:
    if 'の' not in i:continue
    node=Frontmatter.read(open(i,encoding='utf-8').read())
    x={**node['attributes'],**{'permalink':node['attributes']['title'].strip()}}
    open(i,"w",encoding='utf-8').write('---\n'+yaml.dump(x)+'---\n'+node['body'])

