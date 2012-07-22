#
#	Makefile
#

GEN_DIR=gen

#
#
#

all:	dogen build

#
#
#

dogen	:
	( cd ${GEN_DIR} ; make )

build	:
	make -f Makefile.build

#
#
#

clean	:
	( cd ${GEN_DIR} ; make clean )
	make -f Makefile.build clean

#
#
#

install	:
	make -f Makefile.build install

#
#
#
