#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int counter = 0; // Holder styr på hvor neste alarm legges til i time_array
//time_t time_array[10] = {0}; // Inneholder alarmene
//int pid_array[10] = {0};
static struct {
    time_t time;
    pid_t pid;
} alarm_tuple[10];

void alarm_set(int sleeptime)
{
    sleep(sleeptime);
    printf("RING");
    exit(0);
}

void add_timestamps() // Legger til alarm i time_array
{
    if (counter < 10){
        char input[19];
        time_t alarm;
        struct tm time_tm;
        printf("Schedule alarm at which date and time? ");
        scanf("%s", &input);

        memset(&time_tm, 0, sizeof(struct tm));
        strptime(input, "%Y-%b-%d %T", &time_tm);
        alarm = mktime(&time_tm);

        alarm_tuple[counter].time = alarm;
        
        pid_t childPID = fork();
        if (childPID) { //if in parent process
            alarm_tuple[counter].pid = childPID;
        } else { //if in child process
            alarm_set(5);
        }
        counter++;

    } else {
        printf("Too many alarms scheduled. Cancel an alarm before scheduling a new one.");
    }
        
    /* evt. print how many sec from now */
}

void cancel_alarm(int alarm_number) // Fjerner en alarm fra time_array
{
    pid_t killpid = alarm_tuple[alarm_number].pid;
    for (int i = alarm_number; i < 9; i++) {
        alarm_tuple[i].time = alarm_tuple[i + 1].time;
        alarm_tuple[i].pid = alarm_tuple[i + 1].pid;
        alarm_tuple[9].time = 0;
        alarm_tuple[9].pid = 0;
    }
    counter--;
    kill(killpid, SIGKILL);
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
                printf("%ld", &alarm_tuple[i].time);
            }
        }
    }
    return 0;
}