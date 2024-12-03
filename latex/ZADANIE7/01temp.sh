#!/bin/bash

pliktex="pierwszy.tex"
plikpdf="pierwszy.pdf"

imie=$1

touch $pliktex

echo "\documentclass{article}"	> $pliktex
echo "\begin{document}"	>> $pliktex
echo "\begin{center}" >> $pliktex
echo "{\Large\textbf{Hello $imie}}" >> $pliktex
echo "\end{center}" >> $pliktex
echo "\end{document}" >> $pliktex

pdflatex $pliktex
pdflatex $pliktex

evince $plikpdf
