#include <stdio.h>
#include <time.h>
#include <stdbool.h>

const char * current_time()
{
    time_t currentTime;
    struct tm * timeinfo;

    time (&currentTime);
    timeinfo = localtime (&currentTime);
    return "%s", asctime (timeinfo);
}

void print_menu(void)
{
    char choice;

    printf("Welcome to the alarm clock! It is currently %s \n Please enter 's' (schedule), 'l' (list), 'c' (cancel), 'x' (exit): ", current_time());
    scanf("%c", &choice);
    
    while(1) {
        if (choice == 'x')
        {
            printf("You have exited.");
        }
    }
}

int main()
{
    print_menu();

    return 0;
}