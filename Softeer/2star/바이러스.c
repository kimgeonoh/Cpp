#include <stdio.h>

int main(void){
	
	long long k,p,n;

	scanf("%lld %lld %lld",&k,&p,&n);

	long long mod=1000000007;

	for(int i=1;i<=n;i++){
		k*=p;
		k%=mod;
	}

	if(k<=mod) {printf("%lld",k);}
	
	else if(k>mod) {
		k%=mod;
		printf("%lld",k);}

	return 0;
}
