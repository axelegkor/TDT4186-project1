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
    char out[19];
    time_t alarm;
    struct tm time_tm;
    
    printf("Schedule alarm at which date and time? ");
    fflush(stdin);
    scanf("%20[^", &input);

    // memset(&time_tm, 0, sizeof(struct tm)); // Trengs denne linjen??
    strptime(input, "%Y-%m-%d %H:%M:%S", &time_tm);
    alarm = mktime(&time_tm);


    strftime( out, 19, "%Y-%m-%d %H:%M:%S", localtime (&alarm) );
    printf("%s\n", out);

    long sec = alarm - time(NULL);

    //printf("There are: %ld seconds until %s\n", sec, input);
    // printf("sec: %ld", sec);

    time_array[counter] = alarm;
    counter++;
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

int main()
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
            for (int i = 0; i < counter; i++) {
                //printf("%ld", &time_array[i]);
                char out[17];
                strftime( out, 17, "%Y-%m-%d %H:%M:%S", localtime (&time_array[i]));
                printf("%s\n", out);
            }
        }
    }
    /*time_t alarm;
    struct tm time_tm;

    printf("skriv noe: ");
    scanf("%19[^\n", alarm);

    strptime(alarm, "%Y-%m-%d %H:%M:%S", &time_tm);

    time_t unix_time = mktime(&time_tm);
    long sec = unix_time - time(NULL);

    printf("det er: %ld", sec);*/
    
    //add_timestamps();

    return 0;
}