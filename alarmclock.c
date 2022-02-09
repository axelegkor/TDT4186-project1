#include <stdio.h>
#include <time.h>

void print_menu(void)
{
    char choice;

    printf("Welcome! What do you wish to do?. \n's' (schedule), 'l' (list), 'c' (cancel), 'x' (exit): ");
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

void display_current_time()
{
}

int main()
{
    /* print_menu();*/
    time_t current_time;

    time(&current_time);

    ctime(&current_time);

    printf("%s", ctime(&current_time));

    return 0;
}