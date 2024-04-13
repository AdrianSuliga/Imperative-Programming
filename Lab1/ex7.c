/*Znajdź pole powierzchni ograniczone osią Ox i wykresem funkcji sin(x) w przedziale [a,b] 
metodą Monte Carlo. Dane wejściowe: a,b,N (liczba losowanych punktów). */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double area(double a, double b, int n);

int main()
{
    double a = 0.0, b = 0.0;
    int n = 0;
    printf("Enter a: ");
    scanf("%lf", &a);
    printf("Enter b: ");
    scanf("%lf", &b);
    printf("Enter number of points to draw: ");
    scanf("%d", &n);
    if (a > b || n < 1)
    {
        printf("Invalid data\n");
        return 1;
    }
    double result = area(a, b, n);
    printf("Area under sinx; x = [a, b] is: %f\n", result);
    return 0;
}
double area(double a, double b, int n)
{
    srand(time(NULL));
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        double x = ((double)rand()/RAND_MAX) * (b-a) + a;
        double y = ((double)rand()/RAND_MAX) * 2.0;
        double sx = sin(x);
        if (sx < 0)
            sx = sx * (-1);
        if (y < sx)
            cnt += 1;
    }
    return 2*(b-a)*(double)cnt/(double)n;
}