doBashCommand(command, hid){
	additionalCommand := ". /etc/bash.bashrc; . /etc/profile; . /home/florian.mayer/.bash_profile; shopt -s expand_aliases; " . command
	flag := "-c"
	target := "C:\cygwin\bin\bash.exe"
	if (hid) {
		Run, %target% %flag% "%additionalCommand%", , Hide
	} else {
		Run, %target% %flag% "%additionalCommand%"	
	}
}

^+q::
	Inputbox, text, Eingabefenster, Bitte geben Sie den auszuführenden Kommandostring an! 
	doBashCommand(text, "0")
return

