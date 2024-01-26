#include <stdio.h>
int main(void)
{
	int M, N, K;
	scanf("%d %d %d", &M, &N, &K);
	int secret[M];
	for (int i=0; i!=M; i++)
	{
		int num;
		scanf("%d", &num);
		secret[i] = num;
	}
	int menu[N];
	for (int j=0; j!=N; j++)
	{
		int num2;
		scanf("%d", &num2);
		menu[j] = num2;
	}
	int flag;
	flag = 0;
	for (int k=0; k<N-M+1; k++)
	{
		int cnt;
		cnt = 0;
		for (int l=0; l!=M; l++)
		{
			int a, b;
			a = secret[l];
			b = menu[l+k];
			if (a==b)
			{
				cnt = cnt + 1;
			}
			else if (a!=b&&cnt>0)
			{
				cnt = 0;
			}
			if (cnt == M)
			{
				flag = 1;
				break;
			}
		}
		if (flag==1)
		{
			break;
		}
	}
	char s[7]="secret";
	char n[7]="normal";
	if (flag==1)
	{
		printf("%s", s);
	}
	else
	{
		printf("%s", n);
	}
	return 0;
}
