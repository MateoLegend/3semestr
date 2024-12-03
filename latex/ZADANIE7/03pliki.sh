#!/bin/bash
#IFS=';'
while read line
do
 #wiersz=$line;
 IFS=':'
 read -ra wiersz <<< "$line"
 echo "${wiersz[0]} ma lat ${wiersz[1]}"
done < dane1.txt
