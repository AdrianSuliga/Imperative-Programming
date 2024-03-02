/*Napisz program, który dla zadanej liczby naturalnej n odpowiada na pytanie, 
czy liczba ta jest iloczynem dowolnych dwóch kolejnych wyrazów ciągu Fibonacciego. 
Zakładamy, że pierwsze dwa wyrazy ciągu Fibonacciego to 0 i 1.*/
#include <stdio.h>
int main()
{
    int fibL = 0, fibM = 1, fibR = 1, input = 0;
    printf("Enter number : ");
    scanf("%d", &input);
    while (1)
    {
        if (fibL * fibM == input)
        {
            printf("YES: %d * %d\n", fibL, fibM);
            break;
        }
        else if (fibR > input)
        {
            printf("NO\n");
            break;
        }
        fibL = fibM;
        fibM = fibR;
        fibR = fibL + fibM;
    }
    return 0;
}