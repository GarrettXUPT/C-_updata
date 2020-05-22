
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define Max_size 100 /*最多可以使得n＝100 */

void value(char*, int i, int n);

//void main(void)
//{
//    int n, k;
//    char list[Max_size]; /*用字符数组存储字符，‘T’代表true， ‘F’代表false*/
//    printf("input the number of Booleans: \n");
//    scanf("%d", &n);
//    if (n<1 || n>Max_size)
//    {
//        printf("\nImproper number n!\n");
//        exit(1);
//    }
//    for (k = 0; k < n; k++)
//    {
//        list[k] = '0';
//    }
//    value(list, 0, n - 1);
//    
//}

void value(char* list, int i, int n)
{
    int j;
    if (i == n + 1) /*已经递归完毕， 输出序列*/
    {
        for (j = 0; j <= n; j++)
        {
            printf("%c", list[j]);
        }
        printf("     ");
    }
    else {
        list[i] = '0';
        value(list, i + 1, n);
        list[i] = '1';
        value(list, i + 1, n);
    }
}
