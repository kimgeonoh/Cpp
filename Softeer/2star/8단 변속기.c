#include <stdio.h>

int main(void)
{
   int number[8];
    int i, result, flag = 0;

    for (i = 0; i < 8; ++i)
    {
        scanf("%d", &number[i]);
    }

    for (i = 0; i < 7; ++i)
    {
        result = number[i] - number[i+1];
        if ( result == 1)   flag = 1;
        else if ( result == -1) flag = 2;
        else
        {
            flag = 3;
            printf("mixed\n");
            break;
        }
    }

    if (flag == 1)          printf("descending\n");
    else if (flag == 2)     printf("ascending\n");
   return 0;
}
