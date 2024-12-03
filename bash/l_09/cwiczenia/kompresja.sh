#!/bin/bash
cd ~
cd /tmp

random="/tmp/data/random/"
empty="/tmp/data/empty/"
various="/tmp/data/various/"

tmp_dir=$(mktemp -d)

tar cvf "$tmp_dir/random.tar" $random

for FILE in $random
do
    gzip $FILE
done