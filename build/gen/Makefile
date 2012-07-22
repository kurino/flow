#
#
#

CLASSES=mark figure macro

#
#
#

SRC=${CLASSES:%=%list.c}
INC=${SRC:%.c=%.h}

#
#
#

GEN=${INC} ${SRC}

#
#
#

all	:	inc src

#
#
#

src : ${SRC}

inc : ${INC}

#
#
#

${SRC}	:	./replace.sh list.c.SKEL Makefile
	./replace.sh `echo $@ | sed 's/list.c//'` list.c.SKEL > $@

${INC}	:	./replace.sh list.h.SKEL Makefile
	./replace.sh `echo $@ | sed 's/list.h//'` list.h.SKEL > $@

#
#
#

clean	:
	-rm ${GEN}

#
#
#

