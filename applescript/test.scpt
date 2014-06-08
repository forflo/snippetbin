#!usr/bin/osascript
on logger(x)
    log x
end logger

on usage()
    logger("usage: <Skriptname> -u <user> -p <port> <computernames>")
end logger

on run argv
    if count of argv is 0 then
        logger("usage: <Skriptname> -u <user> -p <port> <computernames>")
    else
        if item 1 of argv is not "-u" then
            usage()
        else if item 3 of argv is not "-p" then
            usage()
        else
            set user to item 2 of argv
            set sshport to item 4 of argv
        end if
    end if
	set cn to {}
    repeat with n from 5 to count of argv
        copy item n of argv to the end of cn
    end
    set cs to (count of cn)
    set h to 64
    set w to 278

	logger(cs)
	logger(h)
	logger(w)
	logger(cn)
	logger(user)
	logger(sshport)
end run
