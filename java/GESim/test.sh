#!/bin/bash

JCORE=org.junit.runner.JUnitCore

. setupEnv.sh
java $JCORE $(echo $1 | sed s/.class/""/g)

