int mui(int d, int m){
	int k=1;
	if(ggT(d,m)!=1)
		return -1;
	while(1){
		if((m*k+1)%d==0)
			return ((m*k+1)/d);
		k++;
	}
}

