#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

int counter = 0; // Keeps track of where the next alarm should be placed
static struct {
    time_t time;
    pid_t pid;
} alarm_tuple[10];

void flush(void)
{
    int i;
    do {
        i = getchar();
    } while (i != '\n' && i != EOF);
}

void alarm_set(int sleeptime){
    sleep(sleeptime);

    // Playing alarm sound for MacOS
    execl("/usr/bin/afplay", "/usr/bin/afplay", "/Applications/OpSys/os1/tone.wav");

    printf("RING\n");
    exit(0);
}

void add_timestamps() // Legger til alarm i time_array
{
    char input[19];
    time_t alarm;
    struct tm time_tm;
    
    printf("Schedule alarm at which date and time? ");
    
    //fflush(stdin);
    scanf("%[^\n]", &input);
    flush();

    memset(&time_tm, 0, sizeof(struct tm)); // Trengs denne linjen??
    strptime(input, "%Y-%m-%d %H:%M:%S", &time_tm);
    alarm = mktime(&time_tm);

    long sec = alarm - time(NULL);

    printf("There are: %ld seconds until %s\n", sec, input);

    alarm_tuple[counter].time = alarm;

    pid_t childPID = fork();
    if (childPID) {
        alarm_tuple[counter].pid = childPID;
    } else {
        alarm_set(sec);
    }
    counter++;
}

void cancel_alarm(int alarm_number)
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
    return asctime(timeinfo);
}

void list_alarms() 
{
    for (int i = 0; i < counter; i++) {
        char out[19];
        strftime(out, 19, "%Y-%m-%d %H:%M:%S", localtime(&alarm_tuple[i].time));
        printf("Alarm %d is at %s\n", i, out);
    }
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
            flush();
            //fflush(stdin);
            add_timestamps();
        }
        else if (choice == 'c') {
            int cancel__num;
            list_alarms();
            printf("Choose which alarm you want to cancel from the alarms above: ");
            scanf("%d", &cancel__num);
            cancel_alarm(cancel__num);
        }
        else if (choice == 'l') {
            list_alarms();
        }
    } 
    return 0;
}