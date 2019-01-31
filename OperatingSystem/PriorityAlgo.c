//@Ghazi Khan
//operating system non preemptive priority scheduling algorithm
#include<stdio.h>
#include<string.h>
typedef struct Pro pro;

int i,j;        //for loops.
float avg_wt=0.0,avg_tat=0.0;     //intial waiting time and turn around time.

//Creating the Process of struct type.
struct Pro{
char pName[5];
int pri;
int b_time;
int w_time;
int t_time;
};

//Taking input for each Process.
void takeInput(int n,pro p[]){
    printf("Enter the following details for each processes\n----------------------------------------------\n");
    for(i=0;i<n;i++){
        printf("Processes id: ");
        scanf("%s",p[i].pName);
        printf("Processes priority: ");
        scanf("%d",&p[i].pri);
        printf("Processes burst time: ");
        scanf("%d",&p[i].b_time);
    }
}

//Sort the Processes as per there priority.
void sort(int n,pro p[]){
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++){
            if(p[i].pri < p[j].pri)         //sorting in desc order.
            {
                struct Pro t=p[i] ;
                p[i]=p[j];
                p[j]= t;
            }
        }
}

 //calculate waiting time of processes
void waitingTime(int n,pro p[]){
    p[0].w_time = 0;    //first process no need to wait, so it's waiting time is 0.

    for (i = 1; i < n; i++)                            //i =1 because first process waiting time is aleady calculated.
        p[i].w_time = p[i-1].w_time +p[i-1].b_time;   //waiting time of i th process is 
}                                                    //(waiting time of i-1 process + burst time of i-1 process).

//turnAroundTime
void turnAroundTime(int n,pro p[]){
    for (i = 0; i < n; i++)                        //TurnAroundTime = waiting time + burst time.
        p[i].t_time = p[i].w_time +p[i].b_time;
}

//avgTimes
void avgTimes(int n,pro p[]){
    for (i = 0; i < n; i++){
        avg_wt+= p[i].w_time;
        avg_tat+= p[i].t_time;
    }
    avg_wt/=n;
    avg_tat/=n;
}

//Print the output
void showProDet(int n,pro p[]){
    for(i=0;i<n;i++){
        printf("\n                          Processes                        \n");
        printf(" -----------------------------------------------------------\n");    
        printf("| p_id   |  p_priority |  waiting time  |  turnAround time  |\n");
        printf("|-----------------------------------------------------------|\n");
    
        for(i=0;i<n;i++)
            printf("|   %s   |      %d       |       %d        |        %d          |\n",p[i].pName,p[i].pri,p[i].w_time,p[i].t_time); 
        printf(" -----------------------------------------------------------\n");    
        
        // AvgTimes
        printf("\n                          Avg Times                        \n");
        printf(" -----------------------------------------------------------\n"); 
        printf("| Avg Waiting time: %f                                |\n| Avg turnAround time: %f                             |\n",avg_wt,avg_tat);  
        printf(" ------------------------------------------------------------");
    }
}

int main()
{
    int num_pro,i,j;
    
    //Taking the number of processes.
    printf("Enter the number of processes: ");
    scanf("%d",&num_pro);

    //Creating n number of processes of struct type
    pro p[num_pro];

    // arrays to store waiting time and turnaround time.
    int w_time[num_pro],t_time[num_pro];
    
    //Taking input
    takeInput(num_pro,p);

    //sorting as per the priority of Process
    sort(num_pro,p);

    //calculate waiting time of processes
    waitingTime(num_pro,p);

    //calculate turnAroundTime time of processes
    turnAroundTime(num_pro,p);

    //calculate the avg waiting time and avg turn around time
    avgTimes(num_pro,p);

    //Print the output
    showProDet(num_pro,p);
    
    return 0;
}
