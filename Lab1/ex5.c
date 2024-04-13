/*Program losuje liczbę X = <0; 100>. Napisz funkcję, która zgaduje wartość X. 
W pętli losujemy n∈[0,100]. Jeżeli X=n zgadliśmy X, jeżeli nie to na podstawie 
wartości X i n ograniczamy przedział, z którego losujemy kolejne n. */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void playGuessingGame()
{
    srand(time(NULL));
    int X = rand() % 101, n = rand() % 101, cnt = 1;
    while (n != X)
    {
        if (n < X)
            n = rand() % (X + 1 - n) + n;
        else if (n > X)
            n = rand() % (n + 1 - X) + X;
        ++cnt;
    }
    printf("Random num and counter: %d, %d\n", n, cnt);
}
int main()
{
    playGuessingGame();
    return 0;
}