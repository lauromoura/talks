
.PHONY: all

all: main.pdf


main.pdf: main.tex talk.tex
	xelatex main.tex

view: main.pdf
	evince main.pdf

talk.tex: talk.md
	pandoc talk.md --slide-level 2 -t beamer -o talk.tex --listings
	# pandoc talk.md --slide-level 2 -t beamer+pandoc_title_block --template=main.tex --standalone -o talk.tex --listings

slides.pdf: main.tex talk.tex
	mkdir -p slides
	lualatex --jobname=slides --output-directory=./slides main.tex
	# biber --input-directory=./slides slides.bcf
	lualatex --jobname=slides --output-directory=./slides main.tex

notes.pdf: main.tex talk.tex
	lualatex main.tex --jobname=notes.pdf
	biber main.bcf
	lualatex main.tex --jobname=notes.pdf
