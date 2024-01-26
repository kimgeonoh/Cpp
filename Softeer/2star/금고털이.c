#include <stdio.h>

int main(void) {
	unsigned int w,n, money=0, m[n],p[n];
	int c[10001]={0};

	scanf ("%d %d", &w,&n);

	for (int i=0; i<n; i++)
	{
		scanf ("%d %d", &m[i], &p[i]);
		c[p[i]] += m[i];
	}

	for (int i=10000; i>0; i--)
	{
		if (c[i] >= w)
		{
			money += w*i;
			break;
		}
		else
		{
			money += c[i]*i;
			w -= c[i];
		}
	}
	printf ("%d", money);
	return 0;
}
