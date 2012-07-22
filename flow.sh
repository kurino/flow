#!/bin/bash

#
#
#

FLOW_HOME=/home/kurino/bin/lib/flow

#
#
#

FLOW_LIB=${FLOW_HOME}/lib/figures

#
#
#

FLOW=${FLOW_HOME}/build/flow
CPP="cpp -I${FLOW_LIB} -traditional-cpp"
NKF_EUC="nkf -e"

#
#
#

for i in $*
do
	b=`basename $i .flow`
	${CPP} $i | grep -v "^#" | ${NKF_EUC} | ${FLOW} > $b.pic
done

#
#
#
