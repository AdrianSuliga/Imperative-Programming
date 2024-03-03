/*Napisz program tabelaryzujący funkcję cosinus w zadanym przedziale. 
Dane wejściowe: początek przedziału, koniec przedziału, krok (przyrost x). 
Tabela powinna zawierać 3 kolumny: wartość argumentu x, wartość cos(x) 
policzoną z wykorzystaniem funkcji bibliotecznej oraz wartość cos(x) 
policzoną z rozwinięcia w szereg Taylora. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
double taylorCosx(double x);
long factorial(int n);
int main()
{
    double a = 0.0, b = 0.0, x = 0.0;
    printf("Podaj a: ");
    scanf("%lf", &a);
    printf("Podaj b: ");
    scanf("%lf", &b);
    printf("Podaj skok x: ");
    scanf("%lf", &x);

    printf("x           cosx            cosx\n");
    while (a <= b)
    {
        printf("%lf     %lf     %lf\n", a, taylorCosx(a), cos(a));
        a += x;
    }

    return 0;
}
double taylorCosx(double x)
{
    double result = 0.0;
    for (int i = 0; i < 5; i++)
    {
        result += pow(-1, i) * pow(x, 2*i) / factorial(2*i);
    }
    return result;
}
long factorial(int n)
{
    long res = 1;
    for (int i = 1; i<=n; i++)
        res *= i;
    return res;
}