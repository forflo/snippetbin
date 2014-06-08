;Grid Window Manager
;author: florian mayer 		mayer.florian@web.de

;--------------object definitions ------------------

class Point {
	posX := ""
	posY := ""
	
	__New(x, y){
		this.posX := x
		this.posY := y
	}
}

class Dimension {
	width := ""
	height := ""
	
	__New(width, height){
		this.width := width
		this.height := height
	}
}

class WindowPref {
	dimension := ""
	point := ""
	title := ""
	
	__New(x, y, w, h, tit){
		this.dimension := new Dimension(w, h)
		this.Point := new Point(x,y)
		this.title := tit
	}
}

;--------------------- end of object definitions--------------------------

getGridSize(winCount){
	gSize := "2"
	expo := "1"
	while (winCount > gSize) {
		gSize := 2 ** ++expo
	}
	return expo
}

getGridClusterCount(winCount){
	return 2 ** getGridSize(winCount)
}

getWinCount(){
	WinGet, count, Count
	WinGet, liste, List
	cnt := "0"
	result := []
	Loop, %count% {
		WinGetTitle, title, % "ahk_id " . liste%A_Index%
		if (title && title != "Start" && title != "Program Manager"){
			cnt++
		}
	}
	
	return cnt
}

;returns an array of strings containing the titles of all windows on the system
getWindowTitles(){
	WinGet, count, Count
	WinGet, liste, List
	result := []
	Loop, %count% {
		WinGetTitle, title, % "ahk_id " . liste%A_Index%
		if (title && title != "Start" && title != "Program Manager"){
			result.Insert(title)
		}
	}
	
	return result
}

;returns a dimension object with the height and the length of a grid cluster
getChunkDimension(gridSize){
	result := new Dimension
	result.width := Round(A_ScreenHeight / gridSize)
	result.height := Round(A_ScreenWidth / gridSize)
	return result
}

;returns an array of WindowPref-Objects
getRestoreData() {
	resultArr := []
	allWindows := getWindowTitles()
	Loop, % allWindows.MaxIndex() {
		WinGetPos, x, y, w, h, % allWindows[A_Index]
		resultArr.Insert(new WindowPref(x,y,w,h, allWindows[A_Index]))
	}
	return resultArr
}

;returns an array containing the positions of the upper left points of
;the respective grid chunk. Since this Grid is alwas a power of two, 
;the resultin array will contain 2^getGridSize elements
getPositions(){
	resultArr := []
	runTo := getGridSize(getWinCount())
	dim := getChunkDimension(runTo)
	indexA := "0"
	indexB := "0"
	
	while (indexA < runTo) { 
		while(indexB < runTo) {
			resultArr.Insert(new Point(indexA * dim.height, indexB * dim.width))
			indexB++
		}
		indexB := "0"
		indexA++
	}
	
	return resultArr
}


setWindowToChunk(allWindows){
	tempDim := getChunkDimension(getGridSize(getWinCount()))
	Loop, % allWindows.MaxIndex() {
			WinMove, % allWindows[A_Index],,, % tempDim.width, % tempDim.height
	}
}

;---global vars def starts here----;
;restoreData := getRestoreData()
;---end---------------------MsgBox, 541238, ,

;view the restored WindowPref-Objects
^+5::
	Loop, % restoreData.MaxIndex() {
		MsgBox, % "width: " . restoreData[A_Index].dimension.width . " height: " . restoreData[A_Index].dimension.height . " pointX: " . 		restoreData[A_Index].point.posX . " pointY: " . restoreData[A_Index].point.posY . " Title: " . restoreData[A_Index].title
	}
return


;reset Window-States
^+3::
	Loop, % restoreData.MaxIndex() {
		WinMove, % restoreData[A_Index].title, , % restoreData[A_Index].point.posX , % 	restoreData[A_Index].point.posY , % restoreData[A_Index].dimension.width , % restoreData[A_Index].dimension.height
	
	}
return

;set window-position on grid nodes
^+6::
	debug := ""
	positions := getPositions()
	Loop, % restoreData.MaxIndex() {
		WinMove, % restoreData[A_Index].title,, % positions[A_Index].posX, % positions[A_Index].posY
	}
	MsgBox, %debug%
return

;save current Window-States
^+2::
	restoreData := getRestoreData()
return 

;do grid Layout 
^+4::
	if (getWinCount() < 3 ) {
		MsgBox, Es muessen mindestens drei Fenster gleichzeitig geöffnet sein`ndamit der Window-Manager richtig funktioniert
	} else {
		tempDim := getChunkDimension(getGridSize(getWinCount()))
		allWindows := getWindowTitles()
		positions := getPositions()
		Loop, % allWindows.MaxIndex() {
			WinMove, % allWindows[A_Index], % positions[A_Index].posX , % positions[A_Index].posY ;, % tempDim.width, % tempDim.height
		}
		
		MsgBox, % tempDim.width . " " . tempDim.height . " " . getGridSize(getWinCount())
	}
return

main(){
	
	return
}

main()