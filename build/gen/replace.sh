#
#
#

if [ "/$2/" = "//" ]; then
	echo Usage $0 Name Source
	exit -1
fi

#
#
#

N=$1
S=$2

#
#
#

NAME=$N
CAPITAL=`echo $N | sed 's/\([a-z]\)[a-z]*/\1/' | tr a-z A-Z``echo $N | sed 's/[a-z]\([a-z]*\)/\1/'`
UPPER=`echo $N | tr a-z A-Z`

#
#
#

# echo NAME=$NAME
# echo CAPTIAL=$CAPITAL
# echo UPPER=$UPPER

#
#
#

sed -e "s/%NAME%/$NAME/g" -e "s/%CAPITAL%/$CAPITAL/g" -e "s/%UPPER%/$UPPER/g" $S

#
#
#


