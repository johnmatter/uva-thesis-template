# Makefile for a LaTeX document

TEXSRC  := main.tex
SRCNAME := ${TEXSRC:.tex=}

LATEX   := pdflatex
BIBTEX  := bibtex

.PHONY: all pdf clean

all: pdf

pdf:
	$(LATEX) $(SRCNAME)
	$(BIBTEX) $(SRCNAME)
	./mpost_all.sh
	$(LATEX) $(SRCNAME)
	$(LATEX) $(SRCNAME)
	mv main.pdf 1_Matter_John_2021_PhD.pdf

clean:
	rm -f *.{aux,log,ps,dvi,bbl,blg,brf,idx,ilg,ind,lof,lot,out,toc,thm}
	rm -f *~
