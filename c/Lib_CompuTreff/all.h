/* Grundfunktionen der Stochastik */
long v1(int m,int n);
long v2(int m, int n);
long bikoeff(int m, int n);
long k1(int m, int n);
long k2(int m, int n);

/*     */
long subfak(int n);

//ggT(a,b)

int ggT(int a,int b);

//Berechnung des Multiplikativen inversen für 2 TEILERFREMDE Zahlen !!!

int mui(int d, int m);

/* Berechnung der Fakultät auf double genauigkeit */
double fakd(int i);
/* Berechnung der Fakultät auf int genauigkeit */
int faki(int i);
/* Berechnung Binominalkoeffizient [nutzt fakd()] */
//double mbincoeffd(const unsigned long int n, const unsigned long int k);

/*
   Terminal Grafik:
*/
void tclr(void);

/*
##########
Verkettete
  Listen
##########
*/
//Typendefinition fuer den eea

typedef struct s_diophant{      //Struktur für eine Diophantische Gleichung der Form ax+by=c
        int a;                          //Wobei a,b Element N 
        int b;
        int c;
        int ggT_ab;
        int x;
        int y;
        int ganzzahligeloesung; //Entweder 1 fuer Ja oder 0 fuer nein (-1)fuer noch nicht berechnet;
}t_diophant;



//Typendefinitionen
#define LAENGE 80
typedef struct s_element
{
	char inhalt[LAENGE];
	struct s_element *next;
}t_element;

typedef struct
{
	struct s_element *erstesElement;
	struct s_element *letztesElement;
	int anzahlElemente;
}t_Listenkopf;

//Funktionsdeklarationen

void initListe(t_Listenkopf *li);
void pushFront(t_Listenkopf *li, char *str);
void pushBack(t_Listenkopf *li, char *str);
void printListe(t_Listenkopf *li);
void popFront(t_Listenkopf *li,char *str);
void popBack(t_Listenkopf *li,char *str);
void popX(t_Listenkopf *li,char *str,int x);

