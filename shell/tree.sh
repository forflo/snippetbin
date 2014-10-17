#!/bin/bash

TREE_DELIM="  "

##
# This function intends to print a full recursive
# collected directory structrure to stdout
# Param: 
#   $1: <directory> Startpoint 
#   $2: <int> Control variable for indendation
# Return:
#   <void>
##
function tree__ {
	if [ -d "$1" ]; then
		for ((k=1; k<$2; k++)); do
			echo -n "$TREE_DELIM"
		done

		[ $2 -gt 0 ] && echo "|--(folder)-> $1" || echo "(folder)-> $1"

		for i in "$1"/*; do
			tree__ "$i" "$(($2+1))"
		done
	else
		for ((k=1; k<$2; k++)); do
			echo -n "$TREE_DELIM"
		done
		echo "  |--(file)-> $1"
	fi
	return 1
}

function tree {
	[ ! -d "$1" -a -z "$3" ] && {
		echo you have to specify a directory
		return 1
	}

	tree__ "$1" 0 && return 0
	return 1
}
