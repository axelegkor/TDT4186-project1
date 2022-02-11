#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


void add_timestamps(time_t alarm) 
{
    time_t time_array[10] = { 0 };

    int length = sizeof(time_array)/sizeof(time_array[0]);
    time_array[length + 1] = alarm;

     for (int k = 0; k < 5; k++) {
        printf("%ld, ", time_array[k]);
    } 
}

const char * current_time()
{
    time_t currentTime;
    struct tm * timeinfo;

    time (&currentTime);
    timeinfo = localtime(&currentTime);
    return "%s", asctime(timeinfo);
}

void print_menu()
{
    char choice;

    printf("Welcome to the alarm clock! It is currently %s \n Please enter 's' (schedule), 'l' (list), 'c' (cancel), 'x' (exit): ", current_time());
    scanf("%c", &choice);
    
    while(1) {
        scanf("%c", &choice);
        if (choice == 'x')
        {
            printf("Goodbye!");
            break;
        }
    }
}

int main()
{
    add_timestamps(33);    

    return 0;
}