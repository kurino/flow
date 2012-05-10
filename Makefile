#
#
#

CFLAGS=-DKURINO	# -DDEBUG_PRINT
BINDIR=~/bin

#
#
#



#
#
#

OBJS	=	boundingbox.o	\
			tempfile.o infile.o errout.o	\
			applaypicwrapper.o	\
			getcommand.o	\
			dotext.o	\
			linethickness.o	\
			pic.o	\
			docommand.o	\
			drawarrow.o	\
			drawfigure.o \
			flow.o

#
#
#

all:	flow	flowdoc.pdf

#
#
#

flow	:	${OBJS}	# drum.pic
	${CC} -o $@ ${OBJS}

#
#
#

clean	:
	rm flow *.o *.pdf *~

#
#
#

install	:	flow
	cp flow ${BINDIR}

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

git-commit:	check/check
	git commit
	touch git-commit

git-push:	git-commit
	git push origin master
	touch git-push

#
#
#

amend:
	git commit --amend
	touch git-commit

status:
	git status

#
#
#

PIC					=	docommand.o flow.o pic.o drawfigure.o
VERSION				=	flow.o
GETCOMMAND			=	flow.o getcommand.o
FLOWCOM				=	docommand.o flow.o ${GETCOMMAND}
TEMPFILE			=	docommand.o flow.o drawfigure.o drawarrow.o tempfile.o
APPLAYPICWRAPPER	=	applaypicwrapper.o ${TEMPFILE}
BOUNDINGBOX			=	bundingbox.o ${APPLAYPICWRAPPER} drawfigure.o
COORD				=	${FLOWCOM} ${ATAG} ${BOUNDINGBOX} ${PIC} \
						${DRAWARROW} ${DRAWFIGURE}
BOOL				=	${FLOWCOM} ${ERROUT}
PARAM				=	docommand.o flow.o ${GETCOMMAND}
TRACKSYMB			=	docommand.o drawarrow.o
THECOMMANDS			=	docommand.o ${FLOWCOM}
DIRECS				=	docommand.o	drawarrow.o
ATAG				=	docommand.o
INFILE				=	docommand.o flow.o infile.o
ERROUT				=	docommand.o errout.o tempfile.o infile.o getcommand.o
EOS					=	docommand.o dotext.o infile.o getcommand.o
LINETHICKNESS		=	docommand.o linethickness.o drawarrow.o
DOTEXT				=	docommand.o dotext.o
DOCOMMAND			=	docommand.o flow.o
DRAWARROW			=	docommand.o drawarrow.o
DRAWFIGURE			=	docommand.o drawfigure.o
XALLOC				=	docommand.o

#
#
#

${PIC}				:	pic.h
${VERSION}			:	version.h
${FLOWCOM}			:	flowcom.h
${ATAG}				:	atag.h
${BOOL}				:	bool.h
${COORD}			:	coord.h
${PARAM}			:	param.h
${TRACKSYMB}		:	tracksymb.h
${THECOMMANDS}		:	thecommands.h
${DIRECS}			:	direcs.h
${BOUNDINGBOX}		:	boundingbox.h
${INFILE}			:	infile.h
${TEMPFILE}			:	tempfile.h
${APPLAYPICWRAPPER}	:	applaypicwrapper.h
${ERROUT}			:	errout.h
${GETCOMMAND}		:	getcommand.h
${EOS}				:	eos.h
${LINETHICKNESS}	:	linethickness.h
${DOTEXT}			:	dotext.h
${DOCOMMAND}		:	docommand.h
${DRAWARROW}		:	drawarrow.h
${DRAWFIGURE}		:	drawfigure.h
${XALLOC}			:	xalloc.h

#
#
#

VER=$(shell grep -e 'VERSION[^_]' version.h | awk '{print $$3}' | sed 's/"//g')
TAR=archives/flow-${VER}.tar.gz

tar	:	${TAR}

${TAR}	:	COPYING Makefile README documents *.c *.h flowdoc.pdf flowdoc.tex
	tar --exclude-from=archives/exclude-from.txt -zvcf ${TAR} $^

#
#
#
