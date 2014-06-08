
double mbincoeffd(const unsigned long int n, const unsigned long int k)
{
	return fakd((int)n)/(fakd((int)k)*fakd((int)n-(int)k));
}
