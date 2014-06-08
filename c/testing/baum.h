struct knoten {
 	int wert;
	char operation; /* unnötig */
	int leaf;
	struct knoten *left;
	struct knoten *right;
};

struct knoten *erzeuge_knoten(int wert, char operation, int leaf, struct knoten *left, struct knoten *right);
