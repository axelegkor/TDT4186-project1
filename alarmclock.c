#include <stdio.h>
int main()
{
    char choice;
    printf("Welcome! What do you wish to do?\n's' (schedule), 'l' (list), 'c' (cancel), 'x' (exit)");
    scanf("%c", &choice);                          // skal tillate brukeren å skrive inn en char
    printf("You chose %c from the menu.", choice); // printer kun ut for å teste at riktig output har blitt lagret
    return 0;
}