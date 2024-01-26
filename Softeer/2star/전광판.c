#include <stdio.h>

int main(void)
{
	int T;

	int segment[11][7] = {{1, 1, 1, 1, 1, 1, 0},
                     {0, 0, 1, 1, 0, 0, 0},
                     {0, 1, 1, 0, 1, 1, 1},
                     {0, 1, 1, 1, 1, 0, 1},
                     {1, 0, 1, 1, 0, 0, 1},
                     {1, 1, 0, 1, 1, 0, 1},
                     {1, 1, 0, 1, 1, 1, 1},
                     {1, 1, 1, 1, 0, 0, 0},
                     {1, 1, 1, 1, 1, 1, 1},
                     {1, 1, 1, 1, 1, 0, 1},
                     {0, 0, 0, 0, 0, 0, 0} }; // 1~9, 0, 입력x 총 11개

	scanf("%d",&T);

	for(int i=0; i<T; i++){
		int a,b,result = 0;
		int A[5],B[5];

		scanf("%d %d",&a,&b); 

		for(int j=4;j>=0;j--){
			if(a==0){
				A[j]=10;
			}
			else{
				A[j]=a%10;
				a /= 10;
			}
		
			if(b==0){
				B[j]=10;
			}
			else{
				B[j]=b%10;
				b /= 10;
			}
		}


		for(int j=0; j<5; j++){      // 각 A,B의 숫자 탐색

			if(A[j]==B[j]){
				continue;
			}

			for(int k =0; k<7; k++){    
				if(segment[A[j]][k] != segment[B[j]][k]){
					result++;
				}
			}

		}

		printf("%d\n",result);

	}
	return 0;
}
