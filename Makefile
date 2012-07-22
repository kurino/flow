#
#	Makefile
#

BASE=$(notdir ${PWD})

#
#
#

SRC_DIR=src
INC_DIR=include
BLD_DIR=build
FDC_DIR=flowdoc

#
#
#

FDC_PDF=${FDC_DIR}/flowdoc.pdf
VER_HDR=${INC_DIR}/version.h
FLOW=${BLD_DIR}/${BASE}

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

all:	${FLOW}	${FDC_PDF}

#
#
#

clean	:	clean-${BLD_DIR}	#	clean-${FDC_DIR}
	rm *~ # *.pdf

#
#
#

${FLOW}:
	(cd ${BLD_DIR}; make)

clean-${BLD_DIR}:
	(cd ${BLD_DIR}; make clean)

#
#
#

${FDC_PDF}:
	(cd ${FDC_DIR}; make)

clean-${FDC_DIR}:
	(cd ${FDC_DIR}; make clean)

#
#
#

install	:	${FLOW}
	cp ${FLOW} ${BINDIR}

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

VER=$(shell grep -e 'VERSION[^_]' ${VER_HDR} | awk '{print $$3}' | sed 's/"//g')
TAR=archives/flow-${VER}.tar.gz

tar	:	${TAR}

${TAR}	:	COPYING Makefile genrule.mf README lib documents ${SRC_INC} ${INC_DIR} ${FDC_DIR} ${BLD_DIR} flow.sh
	tar --exclude-from=archives/exclude-from.txt -zvcf ${TAR} $^

#
#
#

ENV_TAR=ENV/env-${VER}.tar.gz

env	:	${ENV_TAR}

${ENV_TAR}	:	.gitignore TODO check sdoc archives/exclude-from.txt ENV/exclude-from.txt check/OLD/Makefile
	tar --exclude-from=ENV/exclude-from.txt -zvcf ${ENV_TAR} $^


#
#
#
