#include <stdio.h>

int h,h2,m,m2,sum;

int main(){

 for (int i=1; i<6; i++){
  scanf("%d:%d %d:%d", &h,&m,&h2,&m2);
  sum +=((h2-h)*60)+(m2-m);
  }

 printf("%d",sum);
 
 return 0;
}
