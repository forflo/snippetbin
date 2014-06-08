double fakd(int i)
{
	int loop;
	double fakultaet=1;

	if(1==i)
	return 1;

	for(loop=i; loop>=1; loop--)
		fakultaet *= loop;

	return fakultaet;
}

