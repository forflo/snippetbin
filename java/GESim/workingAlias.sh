#/bin/bash

CLASSPATH=
alias clp="export CLASSPATH=~+/junit.jar:~+"
alias buildBridge="src/sqlitebridge/./kompileBridge.sh SqliteBridge.c"
alias testLoop="CNT=0; while :; do echo Test Nr: \$CNT starts in ; for i in \`seq 10 -1 1\`; do echo -n \$i \" \"; sleep 1; done ;say test \$CNT; CNT=\$((\$CNT + 1)); jTest ; if [ \$? != 0 ]; then for i in \`seq 1 10\`; do echo -e \"Fehler\a\";sleep 1; say test \$CNT was not successful ;done  ;fi; say test \$((\$CNT - 1)) was successful ;done"
alias getLines='CNT=0; for i in $(ls *java); do let CNT+=$(cat ~+/$i | wc -l | sed s/" "/""/g ); done ; let CNT+=$(cat ~+/SqliteBridge.c | wc -l | sed s/" "/""/g); echo $CNT'
