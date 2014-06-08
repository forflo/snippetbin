//Hier werden, wie unschwer erkennbar, die nötigen Struk-
//tur Definitionen angeführt

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
