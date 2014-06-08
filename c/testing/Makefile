
OUT=comment_scanner
IN=comment.l

comment: 
	flex comment.l
	gcc -o $(OUT) str_dyn.c lex.yy.c -lfl

tarech:
	bison -d tarech.y
	flex tarech.l
	gcc -o tarech baum.c tarech.tab.c lex.yy.c -lfl -ly
