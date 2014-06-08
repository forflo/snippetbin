/*
Subfakultae
Anwendung in der Kombinatorik.
Man hat 6 verschiedene Kaestchen in einer jeweils anderen Farbe und dazu jeweils farbengleiche
Kugeln.
Frage: Wieviele verschiedene Moechkeiten gibt es alle 6 Kugeln in den Kaestchen zu kombinieren.
Mit der Bedingung, dass keine Kul die gleiche Farbe hat, wie das Käsaestchen in der sie liegt
Antwort !n n=6 !n=265
*/

long subfak(int n){
        double subf=0;
        int a,f;
        if(n<0)  return -1;
                		//Keine negativen Werte erlaubt !
        for(a=0;a<=n;a++){
                if((a+2)%2==0)
                        f=-1;   /*Immer wenn a gerade ist ist f=-1 ungerade und umgekehrt, das bedeutet, dass in jedem zweiten Schritt*/
                else
                        f=1;    /*Der Zähler der Summe negativ wird. Genauso wie es laut der mathematischen Definition sein soll   */
                subf+=(-1)*f/(double)faki(a);
        }
        subf=subf*(double)faki(n);
        return (long)subf;
}

