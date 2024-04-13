/*Szyfr Cezara polega na szyfrowaniu kolejnych liter (pozostałe znaki pozostawiamy bez zmian). 
Każda litera zostaje zamieniona w k-tą następną w alfabecie (k jest stałą szyfru), 
przy czym jeżeli taka nie istnieje (wychodzimy za 'z'), to odliczanie jest kontynuowane 
z powrotem od 'a'. Szyfrowanie zachowuje wielkość liter. 
Napisz funkcję, która szyfruje ciąg znaków podany jako argument. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* encrypt(char* word, int size, int k)
{
    
}
int main()
{
    int k = 0;
    char word[100];
    printf("encryption constant: ");
    scanf("%d", &k);
    printf("word to encrypt: ");
    scanf("%s", &word);
    printf("%s\n", encrypt(word, strlen(word), k));
    return 0;
}