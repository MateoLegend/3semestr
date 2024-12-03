#!/bin/bash

FILE="daneStudenci.csv"
pliktex="rekrutuj.tex"
plikpdf="rekrutuj.pdf"


echo "\documentclass[12pt,a4paper]{article}" > $pliktex

echo "\usepackage[margin=2cm]{geometry}" >> $pliktex
echo "\usepackage[utf8]{inputenc}" >> $pliktex
echo "\usepackage{polski}" >> $pliktex
echo "\usepackage{enumerate}" >> $pliktex

echo "\begin{document}" >> $pliktex

while IFS="," read -r lp katalog nazwisko imie wydzial wiek plec
do

echo "\hfill Płock, 20 listopada 2024 r.\\\\" >> $pliktex

if [ $plec="M" ]; then
	uszanowanko="Szanowny Pan"
	informowanko="Pana"
	zostawianko="został Pan przyjęty"
elif [ $plec="K" ]; then
	uszanowanko="Szanowna Pani"
	informowanko="Panią"
	zostawianko="została Pani przyjęta"
else 
	uszanowanko="Klops"
	informowanko="Klops"
	zostawianko="Klops"
fi

	echo "\noindent " >> $pliktex
	echo "$uszanowanko \\\\" >> $pliktex
	echo "$imie $nazwisko \\\\" >> $pliktex
	echo "wiek: $wiek" >> $pliktex
	
	echo "\bigskip" >> $pliktex

	echo "\begin{center}" >> $pliktex
	echo " 	{\Large\textbf{Zawiadomienie}}" >> $pliktex
	echo "\end{center}" >> $pliktex

	echo "\bigskip" >> $pliktex

	echo "Z radością chcielibyśmy poinformować $informowanko, że w wyniku procesu rekrutacyjnego " >> $pliktex
	echo "\begin{center}" >> $pliktex
	echo "\textsf{\textbf{$zostawianko}} " >> $pliktex
	echo "\end{center}" >> $pliktex
	echo "na Wydział $wydzial z identyfikatorem \verb|$katalog|. " >> $pliktex

	echo "\vspace{2cm}" >> $pliktex

	echo "\noindent" >> $pliktex
	echo "Z poważaniem,\\\\" >> $pliktex
	echo "Dziekan" >> $pliktex
	echo "Wydziału $wydzial" >> $pliktex
	echo "\newpage" >> $pliktex
i=$(($i+1))
done < $FILE

echo "\end{document}" >> $pliktex


pdflatex $pliktex
pdflatex $pliktex

evince $plikpdf
