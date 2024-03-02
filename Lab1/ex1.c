/*Napisz program, który wczytuje liczbę całkowitą N a następnie oblicza i drukuje na ekran wartość N!. 
Uwaga: silnia bardzo szybko powoduje przepełnienie całkowitoliczbowe. Sprawdź dla jakich wartości N program wyprowadza prawidłowy wynik. 
Przetestuj działanie programu dla różnych typów danych (dla ułatwienia można zastosować definicję typedef)*/
#include <stdio.h>
int main()
{
    long n = 0, result = 1;
    printf("Podaj liczbe n: ");
    scanf("%lu", &n);
    for (int i = 1; i <= n; ++i)
    {
        result = result * i;
    }
    printf("n! = %lu\n", result);
    return 0;
}