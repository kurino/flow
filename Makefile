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
			vcell.o vlist.o strlist.o \
			tracksymb.o \
			figure.o \
			docommand.o	\
			drawarrow.o	\
			drawfigure.o \
			texpicture.o \
			figurelist.o \
			flowcom.o \
			token.o	\
			dofigure.o \
			dodraw.o \
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
	rm flow *.o *~ # *.pdf

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

commit:	git-commit
push:	git-push

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

VERSION				=	flow.o
PIC					=	docommand.o flow.o pic.o drawfigure.o
TRACKSYMB			=	docommand.o drawarrow.o tracksymb.o
DIRECS				=	docommand.o	drawarrow.o
ATAG				=	docommand.o
INFILE				=	docommand.o flow.o infile.o
ERROUT				=	docommand.o errout.o tempfile.o infile.o \
						getcommand.o drawfigure.o dodraw.o
EOS					=	docommand.o dotext.o infile.o getcommand.o	\
						token.o	dodraw.o
LINETHICKNESS		=	docommand.o linethickness.o drawarrow.o
DOTEXT				=	docommand.o dotext.o
DOCOMMAND			=	docommand.o flow.o
DRAWARROW			=	docommand.o drawarrow.o
DRAWFIGURE			=	docommand.o drawfigure.o dodraw.o
XALLOC				=	docommand.o vcell.o vlist.o strlist.o figure.o
TEXPICTURE			=	texpicture.o drawarrow.o drawfigure.o figure.o \
						dodraw.o
FIGURELIST			=	figurelist.o
DOFIGURE			=	dofigure.o gotcommand.o
#
FIGURE				=	docommand.o figure.o figurelist.o ${DOFIGURE}
STRLIST				=	strlist.o dodraw.o ${FIGURE}
VLIST				=	vlist.o ${STRLIST} figurelist.o dodraw.o
VCELL				=	vcell.o ${VLIST} dodraw.o
#
TEMPFILE			=	flow.o tempfile.o texpicture.o
APPLAYPICWRAPPER	=	applaypicwrapper.o ${TEMPFILE}
BOUNDINGBOX			=	bundingbox.o ${APPLAYPICWRAPPER} drawfigure.o
DODRAW				=	dodraw.o	docommand.o
#
GETCOMMAND			=	flow.o getcommand.o
PARAM				=	docommand.o flow.o ${GETCOMMAND}
FLOWCOM				=	docommand.o flow.o flowcom.o \
						${GETCOMMAND} ${FIGURE} ${DOFIGURE}
THECOMMANDS			=	docommand.o ${FLOWCOM}
COORD				=	${FLOWCOM} ${ATAG} ${BOUNDINGBOX} ${PIC} \
						${DRAWARROW} ${DRAWFIGURE} ${DODRAW}
BOOL				=	${FLOWCOM} ${ERROUT} ${FIGURE} vlist.o
TOKEN				=	token.o	dofigure.o gotcommand.o docommand.o \
						dodraw.o

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
${VCELL}			:	vcell.h
${VLIST}			:	vlist.h
${STRLIST}			:	strlist.h
${FIGURE}			:	figure.h
${TEXPICTURE}		:	texpicture.h
${FIGURE}			:	figure.h
${FIGURELIST}		:	figurelist.h
${DOFIGURE}			:	dofigure.h
${TOKEN}			:	token.h
${DODRAW}			:	dodraw.h

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

