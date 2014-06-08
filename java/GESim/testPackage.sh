#/bin/bash

JCORE=org.junit.runner.JUnitCore
. setupEnv.sh
for i in `ls test*`; do
	java $JCORE $(echo $i | sed s/.class/""/g | sed s/"\/"/"\."/g)
done
