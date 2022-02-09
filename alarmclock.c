#include <stdio.h>

void print_menu(void)
{
    char choice;
    printf("Welcome! What do you wish to do?\n's' (schedule), 'l' (list), 'c' (cancel), 'x' (exit): ");
    scanf("%c", &choice);

    while (1)
    {
        scanf("%c", &choice);
        if (choice == 'x')
        {
            printf("You have exited.");
            break;
        }
    }
}

int main()
{
    print_menu();
    return 0;
}