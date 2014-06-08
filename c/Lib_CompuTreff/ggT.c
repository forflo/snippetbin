//Uebergabeparameter: Die zwei natuerlichen Zahlen, von denen der ggT berechnet werden soll
int ggT(int x, int y){
	int z=1,b;
	if(x<y){b=x;x=y;y=b;}   //Ueberpruefung ob x groesser y, wenn ja dann unzulaessig d.h. muss getauscht werden
	while(z!=0){		//da z.B. 44 mod 3 nicht wirklich hilfreich ist
		z=x%y;
		x=y;
		y=z;
	}
	return x; 		//X ist der ggT von x und y
}
