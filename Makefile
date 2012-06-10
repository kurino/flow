#
#	Makefile
#

BASE=$(notdir ${PWD})

#
#
#

CFLAGS=-DKURINO	# -DDEBUG_PRINT
BINDIR=~/bin

#
#
#

include genrule.mf

#
#
#

all:	${BASE}	flowdoc.pdf

#
#
#

include depends.mf

#
#
#

${BASE}	:	${OBJS}	# drum.pic
	${CC} -o $@ ${OBJS}

#
#
#

clean	:
	rm ${BASE} *.o *~ # *.pdf

#
#
#

install	:	${BASE}
	cp ${BASE} ${BINDIR}

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

VER=$(shell grep -e 'VERSION[^_]' version.h | awk '{print $$3}' | sed 's/"//g')
TAR=archives/flow-${VER}.tar.gz

tar	:	${TAR}

${TAR}	:	COPYING Makefile genrule.mf depends.mf README lib documents *.c *.h flowdoc.pdf flowdoc.tex flow.sh
	tar --exclude-from=archives/exclude-from.txt -zvcf ${TAR} $^

#
#
#

