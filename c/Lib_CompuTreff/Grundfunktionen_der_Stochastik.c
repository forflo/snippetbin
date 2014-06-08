//Variation -> Reihenfolge wichtig Wiederholungen erlaubt
//m Elemente aus der Menge von n Elementen

long v1(int m,int n){
	long erg=1;
	int a;
	//Hier wird die m-te Potenz von n berechnet
	for(a=0;n<=m;a++){
		erg*=n;
	}
	return erg;
}

//Variation -> Reihenfolge wichtig -> Wiederholungen nicht erlaubt
//m Elemente aus der Menge von n Elementen
long v2(int m, int n){
	return faki(n)/faki(n-m);
}

//Biniomialkoeffizient

long bikoeff(int m, int n){
	return faki(n)/faki(m)*faki(n-m);
}

//Kombinationen -> Reihenfolge egal -> Wiederholungen erlaubt

long k1(int m, int n){
	return bikoeff(n-1,n+m-1); 
}

//Kombinationen -> Reihenfolge egal -> Wiederholungen nicht erlaubt

long k2(int m, int n){
	if(m>n){
		return -1; /*Bei dieser Art von Kombination muss m kleiner n sein. Siehe Buch Grundkurs Informatik von Ernst*/
	}
	return bikoeff(m,n);
}


/*
Anmerkung !
##########################################################################
Diese Funkionen wurden Noch nicht getestet. Benutzung auf eigene Gefahr !#
##########################################################################
*/
