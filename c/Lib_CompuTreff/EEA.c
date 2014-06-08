//Erweiterte Euklidscher Algorithmus
const char g1[]="\
    y*ggt(a,b)           -x*ggT(a,b)        \n\
k<=------------  ||   k>=-----------        \n\
	a                       b               \n\
                                            \n\
";

typedef struct s_diophant{      //Struktur für eine Diophantische Gleichung der Form ax+by=c
        int a;                          //Wobei a,b Element N 
        int b;
        int c;
        int ggT_ab;
        int x;
        int y;
        int ganzzahligeloesung; //Entweder 1 fuer Ja oder 0 fuer nein (-1)fuer noch nicht berechnet;
}t_diophant;

int eea(t_diophant *var_dio1, int schalter){	//Wenn der Schalter a auf 1 gesetzt ist, gibt der Algorithmus seine ERgebnisse waehrend der Berechnung aus
	int x0=1,x1=0,y0=0,y1=1;
	int x2,y2,a=var_dio1->a,b=var_dio1->b;
	int tausch,zaehler=2,x4,y4;
	int q1,r0,r1,r2;
	if(a<b){
		tausch=a;
		a=b;
		b=tausch;
	}else if(a==b){
		var_dio1->ggT_ab=a;	//Wenn a = b dann ist der ggT(a,b)= a oder b;
		return 0;
	}
	printf("\n\n\n#############################################################################################################\n");
	while(a%b!=0){
		q1=a/b;r0=a;r1=b;r2=a%b;
		x2=x0-q1*x1; y2=y0-q1*y1;
		if(schalter==1){
			zaehler++;
			printf("Berechnungschritt Nr %i: %6i = %i * %4i + %4i \tx%i = %2i - %i * %i = %i,   y%i = %2i - %i * %i = %i\n",\
				   zaehler-2,r0,q1,r1,r2,zaehler,x0,q1,x1,x0+(-1*q1)*x1,zaehler,y0,q1,y1,y0+(-1*q1)*y1);
		}
		x4=x0+(-1*q1)*x1;y4=y0+(-1*q1)*y1;
		a=b;b=r2;x0=x1;x1=x2;y0=y1;y1=y2;
	}
	printf("\nX = %i ,Y = %i\n",x4,y4);
	var_dio1->ggT_ab=r2;
	var_dio1->x=x2;
	var_dio1->y=y2;
	if(var_dio1->c%var_dio1->ggT_ab==0)
		var_dio1->ganzzahligeloesung=1;
	else
		var_dio1->ganzzahligeloesung=0;
	if(schalter==1){
		printf("\n--- Zusammenfassung ---\n\n");
		if(var_dio1->c%var_dio1->ggT_ab==0){
			printf("\n#############################\nUrsprungsgleichung: %i*x+%i*y=%i",var_dio1->a,var_dio1->b,var_dio1->c);
			printf("\n#############################\n");
			printf("\nDer ggT(a,b)=%i",var_dio1->ggT_ab);
			printf("\nc=%i ist somit ein Vielfaches vom ggT(a,b).",var_dio1->c);
			printf("\nDamit gibt es ganzzahlige Loesungen fuer die Gleichung\nDamit: %i*x+%i*y=%i wahr wird",var_dio1->a,var_dio1->b,var_dio1->c);
			printf("\nNaemlich X=%i und Y=%i\n",var_dio1->x*(var_dio1->c/var_dio1->ggT_ab),var_dio1->y*(var_dio1->c/var_dio1->ggT_ab));
			printf("Jede weitere Loesung ist gegeben durch das intervall k fuer \ndas folgendes gilt:\n\nk<=%i  k>=%i\n\n%s",\
				   (var_dio1->y*(var_dio1->c/var_dio1->ggT_ab)*var_dio1->ggT_ab/var_dio1->a),\
				   (((-1)*var_dio1->x*(var_dio1->c/var_dio1->ggT_ab))*var_dio1->ggT_ab/var_dio1->b),g1);
			printf("\n\nLoesung im natuerlichen Zahlenbereich (nicht garantiert):");
			printf("\n\n\tX-Tilde=x+(kb/ggT(a,b))\n\tY-Tilde=y-(kb/ggT(a,b))\n\tFuer k im Intervall siehe oben\n\n");
			printf("");
		} else {
			printf("c ist teilerfremd zum ggT(a,b)\nes gibt deshalb mehrere oder keine Loesung fuer die Gleichung");
			printf("Der ggT(a,b)=%i\n",var_dio1->ggT_ab);
		}
	printf("#############################################################################################################\n");
	}
	return 1;
}


