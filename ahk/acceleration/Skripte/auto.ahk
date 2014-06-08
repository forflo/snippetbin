globActiveWin = ""
isTransparent = 0
stdTransparency = 140
inboxTitle = Eingabedialog

::detoen::
	InputBox, url, %Eingabedialog%, Bitte geben Sie eine deutsche Vokabel ein
	url := % "http://dict.leo.org/ende?lp=ende&lang=de&searchLoc=0&cmpType=relaxed&sectHdr=on&spellToler=&search=" . url
	Run %url%
return

::entode::
	InputBox, url, %Eingabedialog%, Bitte geben sie eine englische Vokabel ein
	url := % "http://dict.leo.org/ende?lp=ende&lang=en&searchLoc=0&cmpType=relaxed&sectHdr=on&spellToler=&search=" . url
	Run %url%
return

^+s::
	;pfad = C:\cygwin\home\florian.mayer\.minttyrc
	;datei := FileOpen(pfad, "w", "UTF-8")
	;toWrite := % "Columns=100`nRows=50`nTerm=xterm-256color`nOpaqueWhenFocused=no`nTansparency=glass`nForegroundColor=0,255,0`n"
	;datei.Write(toWrite)
	;datei.close()
	Run C:\cygwin\bin\mintty.exe -
return

^+e::
	Run C:\Program Files\AutoHotkey\SciTE\SciTE.exe
return

^+g::
	Run C:\Program Files (x86)\Google\Google Talk\googletalk.exe
return
	
^+p::
	Run C:\Program Files (x86)\putty\putty.exe
return

^+o::
	Run C:\Program Files\Microsoft Office\Office14\outlook.exe
return

::monitor::
	Run taskmgr
	Run perfmon
return

^+d::
	Run C:\Program Files\AutoHotkey\AutoHotkey.chm
return

^+n::
	Run C:\Program Files (x86)\Notepad++\notepad++.exe
return

^+f::
	Run C:\Program Files (x86)\Mozilla Firefox\firefox.exe
return

^+r::
	Run C:\Users\florian.mayer\Documents\Referenzen
return

^+i::
	isRestorable = 0
	WinRestore, %globActiveWin%
return

^+m::
		isRestorable = 0
		WinRestore, %globActiveWin%
return

^+T::
	InputBox, stdTransparency, %inboxTitle%,  Bitte geben Sie die neue Transparenzgröße an...
return

^+l::
	if (%isTransparent% == 0) {
		WinGetActiveTitle, globActiveWin
		WinSet, transparent, %stdTransparency%, %globActiveWin%
		isTransparent = 1
	} else {
		WinSet, transparent, 255, %globActiveWin%
		isTransparent = 0 
	}
return

^+u::
	InputBox, url, %inboxTitle%, Bitte geben sie die zu öffnende URI bzw URL ein...w
	try {
		run %url%
	} catch e {
		MsgBox, Bitte geben sie eine gültige URL ein und Vergessen Sie das "www" nicht!
	}
return

GetWindow(){
	WinGetActiveTitle, result
	return result
}

PrintActiveWindow(){
	abc := GetWindow()
	MsgBox, %abc%
}

^+0::
	Shutdown 1
return

^+1::
	DllCall("PowrProf\SetSuspendState", "int", 0, "int", 0, "int", 0)
return

^+8::
	PrintActiveWindow()
return