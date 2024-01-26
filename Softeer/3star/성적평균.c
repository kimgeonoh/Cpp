int main(void)
{
  // 정수와 실수 구분
  // 소수셋째자리에서 반올림 or 24.00 -> %0.3f
  
	int N,K;
	scanf("%d %d",&N,&K);

	int S[N];
	for(int i=0;i<N;i++){
		scanf("%d",&S[i]);
	}
	
	int p,q;
	for(int i=0;i<K;i++){
		double sum=0,len=0;
		scanf("%d %d",&p,&q);
		len = q-p+1;
		for(int i = p-1; i<q; i++){
			sum += S[i]; 
		}
		
		printf("%0.2f\n",sum/len);
	}

	return 0;
}
