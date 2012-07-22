#
#	Makefile
#

BASE=$(notdir ${PWD})

#
#
#

.SUFFIXES: .tex .dvi .pdf

#
#
#

%.dvi	:	%.tex
	platex $*.tex
	platex $*.tex

%.pdf	:	%.dvi
	dvipdfmx $*.dvi

#
#
#

all:	${BASE}.pdf

#
#
#

clean	:
	rm *.log *.aux *.dvi *~ # *.pdf

#
#
#
