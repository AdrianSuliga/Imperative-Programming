/*Dana jest liczba całkowita dodatnia n. 
Napisz program, który znajduje wszystkie liczby pierwsze mniejsze od n, 
których cyfry tworzą ciąg niemalejący*/
#include <stdio.h>
#include <stdbool.h>

bool isPrime(int num)
{
    if (num == 2)
        return true;
    else if (num < 2 || num % 2 == 0)
        return false;
    int b = 3;
    while (b*b <= num)
    {
        if (num % b == 0)
            return false;
        b += 2;
    }
    return true;
}
bool hasOnlyDecreasingDigits(int num)
{
    int prev = 10;
    while (num != 0)
    {
        if (num % 10 > prev)
            return false;
        prev = num % 10;
        num /= 10;
    }
    return true;
}

int main()
{
    int n = 0;
    printf("Enter n: ");
    scanf("%d", &n);
    for(int i=1; i<n; ++i)
    {
        if (hasOnlyDecreasingDigits(i) && isPrime(i))
        {
            printf("%d\n", i);
        }
    }
    return 0;
}