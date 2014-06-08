#include "baum.h"
#include <stdlib.h> 

struct knoten *erzeuge_knoten(int wert, char operation, int leaf, struct knoten *left, struct knoten *right){
	struct knoten *result = (struct knoten *) malloc(sizeof(struct knoten) * 1);
	result->wert = wert;
	result->operation = operation;
	result->leaf = leaf;
	result->left = left;
	result->right = right;
	return result;
}
