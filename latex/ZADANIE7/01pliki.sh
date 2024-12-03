#!/bin/bash
i=1
for wiersz in $(cat dane.txt)
do
 echo -e "$i\t $wiersz"
 i=$(($i+1))
done
