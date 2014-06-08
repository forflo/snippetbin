#!/usr/bin/osascript

on logger(x)
	log x
end logger

on usage()
	logger("usage: <Skriptname> -u <user> -p <port> <computernames> -c <cols>")
end logger

on run argv
	set cn to {}
	if count of argv is 0 then
		usage()
	else
		if item 1 of argv is not "-u" then
			usage()
			set user to "root"
		else if item 3 of argv is not "-p" then
			usage()
			set sshport to 22
		else if item 5 of argv is not "-c" then
			usage()
			set cols to 4
		else
			set user to item 2 of argv
			set sshport to item 4 of argv
			set cols to item 6 of argv
		end if
	end if
	repeat with n from 7 to count of argv
		copy item n of argv to the end of cn
	end	

	set cs to (count of cn)
	set h to 64
	set w to 278
	if (count of cn) mod cols is 0 then
		set rows to (count of cn) div cols
	else
		set rows to (count of cn) div cols + 1
	end if

	logger("running with")
	logger("port: " & sshport)
	logger("user: " & user)
	logger("cols: " & cols)
	logger("rows: " & rows)
	logger("Window: " & w & "x" & h)

	tell application "iTerm"
		activate
		
		tell (make new terminal)
			set number of columns to w
			set number of rows to h
			launch session "Simple"
			
			-- setup panes
			my logger("create rows")
			repeat rows - 1 times
				tell i term application "System Events" to keystroke "d" using {command down, shift down}
			end repeat
			my logger("create columns")
			repeat rows times
				repeat cols - 1 times
					tell i term application "System Events" to keystroke "d" using {command down}
				end repeat
				tell i term application "System Events" to key code 126 using {command down, option down}
			end repeat

			-- terminate unused sessions
			repeat (rows * cols - cs) times
				my logger("remove unused")
				terminate last item of sessions
			end repeat

			-- open sessions
			repeat with k from 1 to cs
				set temps to item k of cn
				my logger("open session " & k & " -> ssh " & user & "@" & temps)
				tell item k of sessions to write text "ssh " & user & "@" & temps
			end repeat
			
	
			-- start broadcast mode
			delay 1 
			tell i term application "System Events" to keystroke "I" using {command down, shift down}
		end tell
	end tell
end run

