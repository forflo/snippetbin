#include <stdio.h>

int chinrest(int *ak, int *mk, int anz){
	int i,x=0,m=1,Mk[50],Nk[50];
	for(i=0;i<anz;i++){
		m*=mk[i];
	}
	for(i=0;i<anz;i++){
		Mk[i]=m/mk[i];
	}
	for(i=0;i<anz;i++){
		Nk[i]=mui(Mk[i],mk[i]);
	}
	for(i=0;i<anz;i++){
		x+=ak[i]*Mk[i]*Nk[i];
	}
	return x%m;
}
