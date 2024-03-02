/*Liczba doskonała jest to taka liczba naturalna, która jest sumą wszystkich swych dzielników właściwych (to znaczy od niej mniejszych). 
Najmniejszą liczbą doskonałą jest 6, ponieważ jej dzielnikami właściwymi są 1, 2, 3 i 1 + 2 + 3 = 6. 
Napisz program, który znajduje wszystkie liczby doskonałe w zadanym przedziale oraz ich liczbę. */
#include <stdio.h>
#include <stdbool.h>
bool isPerfect(int num)
{
    int it = 1, sum = 0;
    while (it < num)
    {
        if (num % it == 0)
            sum += it;
        it += 1;
    }
    if (sum == num)
        return true;
    else
        return false;
}
int main()
{
    int lowB = 0, upB = 0;
    printf("Lower bound: ");
    scanf("%d", &lowB);
    printf("Upper bound: ");
    scanf("%d", &upB);
    
    int cnt = 0;
    for (int i=lowB; i<=upB; ++i)
    {
        if (isPerfect(i))
        {
            printf("Perfect number found: %d\n", i);
            cnt += 1;
        }
    }
    printf("Number of perfect numbers: %d\n", cnt);
    return 0;
}