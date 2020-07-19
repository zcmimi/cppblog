#!/bin/bash
for i in $(seq 20 33) 
do
cwebp $i.jpg -o $i.webp 
done

