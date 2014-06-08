;+----------+
;|Direktive |
;+----------+

SendMode Input
SetWorkingDir %A_ScriptDir%
;Sämtliche Hotkeys beginnen mit strg + h. h wird losgelassen und der eigentliche HK folgt
;
;   
;Errorcodes:  
; 1 = Falsche Plattform

programPath86 := 
programPath :=
globActiveWin = ""
isTransparent = 0
stdTransparency = 140
inboxTitle = Eingabedialog
msgboxTitle = Systemmeldung
skriptPath := "\\VBOXSVR\shared\acceleration\Skripte"
repoPath := "C:\Users\Florian\DesktopSubst\se2-wif-13-rios"
vDeli := "-"
hDeli := "|"
node := "+"

if (A_OSVersion == "WIN_XP"){
	programPath86 := "C:\Programme"
	programPath := programPath86
} else if (A_OSVersion = "WIN_7" || A_OSVersion = "WIN_8") {
	programPath86 := "C:\Program Files (x86)"
	programPath := "C:\Program Files"
} else {
	MsgBox, , %msgboxTitle%, Dieses Skript ist nicht auf dieser Plattform lauffähig!
	ExitApp, 1
}

;+---------+
;|Bootstrap|
;+---------+
;Load other Skripts

run %skriptPath%\executeShellCommand.ahk
run %skriptPath%\windowManager.ahk
;run %skriptPath%\logger.ahk

;+-------+
;|Klassen|
;+-------+
;>>> Color-Klasse
;<<<
class Color {
	__New(r, g, b){
		this.red := r
		this.green := g
		this.blue := b
	}
	
	ToString(){
		return this.red . "," . this.green . "," . this.blue
	}
}

cnt := 0

;+------------------------------------------+
;|für Hotkeys benötigte Hotkeys  Funktionen|
;+------------------------------------------+
;>>> Präfix-Hotkey
;    Alle weiteren Hotkeys funktionieren erst nach dem Senden
;    dieses Hotkeys
;<<<
^h::
	global cnt := cnt + 1
return

;>>> Funktion für die Präfix-Hotkey Funktionalität
;<<<
doit(){
	global cnt
	if (cnt == 0) {
		return 0
	} else {
		global cnt := 0
		return 1
	}
}

;-------------------------------------------------------------------
; Hotstrings
;-------------------------------------------------------------------
;>>> Sucht mithilfe des Browsers nach einer entlischen Übersetzung für eine dt. Vokabel
::detoen::
	InputBox, url, %Eingabedialog%, Bitte geben Sie eine deutsche Vokabel ein
	url := % "http://dict.leo.org/ende?lp=ende&lang=de&searchLoc=0&cmpType=relaxed&sectHdr=on&spellToler=&search=" . url
	Run %url%
return

;>>> Sucht mithilfe des Browsers nach einer deutschen Übersetzung für eine engl. Vokabel
::entode::
	InputBox, url, %Eingabedialog%, Bitte geben sie eine englische Vokabel ein
	url := % "http://dict.leo.org/ende?lp=ende&lang=en&searchLoc=0&cmpType=relaxed&sectHdr=on&spellToler=&search=" . url
	Run %url%
return

;>>> Startet den Taskmanager
;<<<
::monitor::
	Run taskmgr
return

;>>> Sendet "Mit freundlichen Grüßen - Florian Mayer"
;<<<
::mfgfm::
	sleep 10
	SendPlay Mit freundlichen Grüßen
	SendPlay `nFlorian Mayer
return

;>>> Schreibt das aktuelle Datum in das aktive Fenster
;<<<
::date::
	if(doit()){
		sleep 10
		SendPlay %A_DD%.%A_MM%.%A_YYYY%
	} else {
		sleep 10
		SendPlay date
	}
return

;>>> Schreibt das aktuelle Datum + Zeit in das aktive Fenster
;<<<
::datetime::
	if(doit()){
		sleep 10
		SendPlay %A_DD%.%A_MM%.%A_YYYY% um %A_Hour%:%A_Min%:%A_Sec%
	} else {
		sleep 10
		SendPlay datetime
	}
return

;>>> Sendet "Sehr geehrter Herr"
;<<<
::sgh::
	if(doit()){
		sleep 10
		SendPlay Sehr geehrter Herr
	} else {
		sleep 10
		SendPlay sgh
	}
return

;>>> Sendet "Sehr geehrte Frau"
;<<<
::sgf::
	if(doit()){
		sleep 10
		SendPlay Sehr geehrte Frau
	} else {
		sleep 10
		SendPlay sgf
	}
return

;>>> if(doit()){ ... } produzieren
;<<<
::doit::
	Sleep, 30
	SendPlay `tif(doit()){{}
return

;-------------------------------------------------------------------
; Hotkeys
;-------------------------------------------------------------------

;+-------------+
;|Skripting    |
;+-------------+

;>>> Produziert eine Ascii-Überschrift
;<<<
::head::
	InputBox, headText, %inboxTitle%, Bitte geben sie einen Header-Text ein!
	headTextLength := Strlen(headText)
	sleep 10
	SendPlay `;{%node%}{%vDeli% %headTextLength%}{%node%}{Enter}`;%hDeli%%headText%%hDeli%{Enter}`;{%node%}{%vDeli% %headTextLength%}{%node%}{Enter}
return

;>>> Konfiguriert die Zeichen für die Abgrenzer-Hotstrings
;<<<
::conf::
	if(doit()){
		InputBox, vDeli, %inboxTitle%, Bitte geben sie den vertikalen Begrenzer ein
		InputBox, hDeli, %inboxTitle%, Bitte geben sie den horizontalen Begrenzer ein
		InputBox, node, %inboxTitle%, Bitte geben sie das Zeichen für einen Knoten ein
		if(Strlen(vDeli) > 1 || Strlen(hDeli) > 1 || Strlen(vDeli) == 0 || Strlen(hDeli) == 0){
			MsgBox, Die Begrenzer konnten nicht geändert werden. Bitte probieren sie es erneut
		} else {
			global vDeli := local vDeli
			global hDeli := local hDeli
			global node := local node
		}
	} else {
		SendPlay conf
	}
return

;>>> Produziert einen Abgrenzer mit eingebettetem Text als C-Blockkommentar.
;    Achtung! Nur für Visual-Studio, da die Routine die automatischen Einrückungen
;    des Editors berücksichtigt.
;<<<
::deli::
	InputBox, text, %inboxTitle%, Bitte geben sie einen Begrenzertext ein!
	sleep 10
	delimiterTextLength := Strlen(text)
	delimiterTextLength := delimiterTextLength + 4
	SendPlay /{* %delimiterTextLength%}{Enter}%text%{Space}*{Enter}{BS}{* %delimiterTextLength%}{BS}/
return

;>>> Produziert einen ASCII-Rahmen für Text
;<<<
::frame::
	if(doit()){
		InputBox, headText, %inboxTitle%, Bitte geben sie einen Header-Text ein!
		sleep 10
		headTextLength := Strlen(headText)
		SendPlay {%node%}{%vDeli% %headTextLength%}{%node%}{Enter}|%headText%|{Enter}{%node%}{%vDeli% %headTextLength%}{%node%}{Enter}{Enter}
	} else {
		sleep 10
		SendPlay frame
	}
return

;+------+
;|SYSTEM|
;+------+
;>>> Ausschalten
;<<<
^+0::
	if(doit()){
		Shutdown, 1
	}
return

;>>> Neustarten
;<<<
^+1::
	if(doit()){
		Shutdown, 2
	}
return 

;>>> Eine Inputbox zur besseren Kommandoeingabe öffnen
;<<<
^!i::
	if(doit()){
		InputBox, text, Prompt, Geben Sie ein Kommando ein!
	}
return

;>>> Eine Liste von Hotkeys ausgeben, die in dieser Datei deklariert sind
;<<<
::list::
	if(doit()){
		ListHotkeys	
	} else {
		sleep 10
		SendPlay list
	}
return

;+------------+
;|Productivity|
;+------------+
;>>> Cygwin-Tools installieren
;<<<
^!s::
	if(doit()){
		run C:\Users\Florian\Downloads\setup.exe
	} else {
	
	}
return 

;>>> Dieses Skript editieren
;<<<
^!e::
	if(doit()){
		run %programPath86%\Notepad++\notepad++.exe %A_ScriptFullPath%
	}
return	
	
;>>> Cygwin-Terminal starten
;<<<
^!t::
	if(doit()){
		randomNumber1 := 
		arr := [new Color(0, 255, 255), new Color(255,255,255), new Color(191,191,191), new Color(128, 255, 0), new Color(128,128,255), new Color(255,128,0), new Color(200,0,0)]

		Random, randomNumber1, 0, % arr.MaxIndex() - 1
		pfad = C:\cygwin\home\Florian\.minttyrc
		toWrite := "BoldAsFont=no`nFontHeight=9`nTransparency=high`nBackgroundColour=" . arr[randomNumber1].ToString() . "`nForegroundColour=0,0,0`n"
		datei := FileOpen(pfad, "w")
		datei.Write(toWrite)
		datei.close()
		Run C:\cygwin\bin\mintty.exe -
	}
return

;>>> MS Visual Studio 2012 starten
;<<<
^+!d::
	if(doit()){
		run %programPath86%\Microsoft Visual Studio 11.0\Common7\IDE\devenv.exe
	}
return

;>>> Keil IDE starten
;<<<
^!k::
	if(doit()){
		run %programPath86%\Keil\UV4\Uv2.exe
	}
return

;>>> Firefox starten
;<<<
^!f::
	if(doit()){
		run %programPath86%\Mozilla Firefox\firefox.exe
	}
	return

;>>> Thunderbird starten
;<<<
::mail::
	global cnt := 0
	run %programPath86%\Mozilla Thunderbird\thunderbird.exe
return

;>>> Autohotkey Hilfedatei öffnen
;<<<
^!h::
	if(doit()){
		if (A_OSVersion == "WIN_8") {
			run %programPath%\AutoHotkey\AutoHotkey.chm
		} else {
			run %programPath86%\AutoHotkey\AutoHotkey.chm
		}
	}
return

;>>> Entfernen senden
;<<<
^'::
	if(doit()){
		send {del}
	}
return

;>>> Die Drucktaste senden
;<<<
^!p::
	if(doit()){
		send #{PrintScreen}
	}
return 

;>>> Dieses Skript neustarten
;<<<
^!l::
	if(doit()){
		run %A_ScriptFullPath%
	} else {
		sleep 10
		SendPlay {^!l}
	}
return

;>>> Öffnet Gvim
;<<<
^!g::
	if(doit()){
		run %programPath86%\Vim\vim73\gvim.exe
	}
return

;>>> Eine URI bzw. URL aufrufen
;<<<
^+u::
	if(doit()){
		InputBox, uri, %inboxTitle%, Bitte geben sie die zu öffnende URI bzw URL ein...
		try {
			run %uri%
		} catch e {
			try {
				uri := "www."uri
				run %uri%
			} catch e {
				MsgBox, Bitte geben sie eine gültige URI ein und Vergessen Sie das "www" nicht!
			}
		}
	}
return

;+----+
;|Repo|
;+----+
;>>> Update eines TSVN-Repos
;<<<
^!u::
	if(doit()){
		run %programPath%\TortoiseSVN\bin\TortoiseProc /command:update /path:%repoPath%
	}
return

^!c::
	if(doit()){
		run %programPath%\TortoiseSVN\bin\TortoiseProc /command:commit /path:%repoPath%
	}
return

;>>> Repo im Explorer öffnen
;<<<
^!o::
	if(doit()){
		run %repoPath%
	}
return

;>>> Log öffnen
;<<<
::log::
	if(doit()){	
		run %programPath%\TortoiseSVN\bin\TortoiseProc /command:log /path:%repoPath%
	} else {
		Sendplay log
	}
return
