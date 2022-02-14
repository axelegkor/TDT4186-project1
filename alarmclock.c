#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int counter = 0; // Holder styr på hvor neste alarm legges til i time_array
time_t time_array[10] = {0}; // Inneholder alarmene

void add_timestamps() // Legger til alarm i time_array
{
    char input[19];
    time_t alarm;
    struct tm time_tm;
    
    printf("Schedule alarm at which date and time? ");
    scanf("%s", &input);

    memset(&time_tm, 0, sizeof(struct tm));
    strptime(input, "%Y-%b-%d %T", &time_tm);
    alarm = mktime(&time_tm);

    time_array[counter] = alarm;
    printf("Added %s to list\n", &alarm);
    counter++;
    /* evt. print how many sec from now */
}

void list_alarms() 
{
    for (int i = 0; i < counter; i++) {
        char readable_alarm[19];
        strftime(readable_alarm, 19, "Alarm at %Y-%b-%d %T", &time_array[i]);
        printf("%s \n", readable_alarm);
    }
}

void cancel_alarm(int alarm_number) // Fjerner en alarm fra time_array
{
    for (int i = alarm_number; i < 9; i++) {
        time_array[i] = time_array[i + 1];
        time_array[9] = 0;
    }
    counter--;
}

const char * current_time()
{
    time_t currentTime;
    struct tm * timeinfo;

    time (&currentTime);
    timeinfo = localtime(&currentTime);
    return "%s", asctime(timeinfo);
}

int main() // 2022-05-03 14:14:12
{
    char choice;
    printf("Welcome to the alarm clock! It is currently %s\n Please enter 's' (schedule), 'l' (list), 'c' (cancel), 'x' (exit): ", current_time());

    while (1)
    {
        scanf("%c", &choice);
        
        if (choice == 'x')
        {
            printf("Goodbye!");
            break;
        }
        else if (choice == 's') {
            add_timestamps();
        }
        else if (choice == 'c') {
            int cancel__num;
            printf("Choose which alarm you want to cancel: ");
            scanf("%d", &cancel__num);
            cancel_alarm(cancel__num);
        }
        else if (choice == 'l') {
            list_alarms();
        }
    }
    return 0;
}