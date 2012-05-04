#
#
#

CFLAGS=-DKURINO
BINDIR=~/bin

#
#
#

all:	flow	flowdoc.pdf

#
#
#

flow	:	flow.o	# drum.pic
	${CC} -o $@ $<

#
#
#

clean	:
	rm flow *.o *.dvi

#
#
#

%.pic	:	 %.fig
	fig2dev -L epic $*.fig > $*.pic

%.pdf	:	%.tex
	platex $*.tex
	platex $*.tex
	dvipdfmx $*.dvi

#
#
#

install	:	flow
	cp flow ${BINDIR}

#
#
#

git-push:
	git push origin master

#
#
#

