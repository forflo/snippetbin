#/bin/bash

if [ "$1" = "" ]; then
	echo parameter is missing ...
	echo exit...
	exit
fi

for i in `ls ~+/*.java`; do
	if [ "`head -n 1 $i | awk '{printf "%s", $2}'`" = "$1;" ]; then
		echo $i
	fi
done
