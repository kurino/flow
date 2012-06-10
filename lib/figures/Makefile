#
#
#

GRPS=${wildcard jis/*.grp}

#
#
#

jis.grp	:	jis.skel.h	jis.skel.t jis Makefile
	cat jis.skel.h > $@
	for f in ${GRPS}; do echo "#include \"$$f\""; done >> $@
	cat jis.skel.t >> $@

#
#
#

