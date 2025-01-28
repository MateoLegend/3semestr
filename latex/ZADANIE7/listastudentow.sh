#!/bin/bash

pliktex="studenci.tex"
plikpdf="studenci.pdf"

dane="daneStudenci.csv"



touch $pliktex

echo "\documentclass[12pt,a4paper]{article}

\usepackage[margin=2cm]{geometry}
\usepackage[utf8]{inputenc}
\usepackage{polski}
\usepackage{enumerate}
\usepackage{longtable}
\usepackage{array}
\begin{document}
\begin{center}
	{\large\textbf{Lista studentów}}
\end{center}

\renewcommand\arraystretch{1.5}
\begin{center}
	\setlength{\tabcolsep}{5pt}
	\begin{longtable}{|m{0.7cm}|m{2cm}|m{5cm}|b{3cm}|m{2cm}|m{3cm}|}\hline
		\textbf{L.p.} & \textbf{Katalog} & \textbf{Nazwisko i imię}& \textbf{Wydział} & {\raggedleft\textbf{Wiek}} &{\raggedleft\textbf{Płeć}} \\\\ \hline 
		\hline
		\endfirsthead
		\hline
		\textbf{L.p.} & \textbf{Katalog} & \textbf{Nazwisko i imię}& \textbf{Wydział} & {\raggedleft\textbf{Wiek}} &{\raggedleft\textbf{Płeć}} \\\\ \hline 
		\hline
		\endhead
		\endlastfoot" > $pliktex



while IFS=',' read -r lp katalog nazwisko imie wydzial wiek plec
do
    if [ $lp = "Lp." ] ; then
        continue
    fi

    echo "        \centering $lp. &  $katalog&  $imie $nazwisko  & $wydzial & $wiek & $plec \\\\ \hline" >> $pliktex

done < $dane



echo "    \end{longtable}
\end{center}
\end{document}" >> $pliktex




pdflatex $pliktex
pdflatex $pliktex

evince $plikpdf # otwiera pdf