#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_STR 256 
#define MAX_LINE 64
#define MAX_PROCS 256

#define BLOCK 0
#define READY 1
#define RUNNING 2

#define DEBUG true
#define true 1
#define false 0

/* Priority Hierarchy */
#define MAX_PRIORITY 4
#define CLASS_0 0
#define CLASS_1 1
#define CLASS_2 2
#define CLASS_3 3

/* Quick Call to ReporterProcess */
#define REPORT \
if (pipe(fd)) {	    \
    perror("pipe"); \
  } else if ((temp_pid = fork()) == -1) { \
    perror("fork"); \
  } else if (temp_pid == 0) { \
    close(fd[0]); \
    if(DEBUG) cpu2proc(&cpu, &pcbTable[cpu.pid]); \
    reporterProcess(fd[1], pcbTable, current_time, ta, \
		    running_states, ready_states, blocked_states); \
  } else { \
    close(fd[1]); \
    while(i=(read(fd[0],&c,1)) > 0); \
  }\
    
struct Cpu
{
  int pc;
  int pid;
  int value;
  int t_slice;
  int t_remain;
};

struct Proc
{
  int pid;
  int ppid;
  int pc;    // Initially started from zero.
  int value;
  int priority;
  int state;
  int t_start;
  int t_used;
  char fname[MAX_STR]; // Filename to read a program
  char prog[MAX_LINE][MAX_STR]; // Programs for simulated processes.
};

typedef struct Que {
  int pid;
  struct Proc proc;
  struct Que *next; /* pointer to next element in list */
} QUE;

struct TA_TIME{
  int times[MAX_PROCS];
  int count;
};

int readProgram(char *fname, char prog[][MAX_STR]);

char buffer[BUFSIZ];
int quantum[4];

/* Insert into a head */
QUE *insert_head(QUE **p, int pid)
{
  QUE *n = (QUE *) malloc(sizeof(QUE));
  if (n == NULL) return NULL;

  n->next = NULL;
  *p = n;

  n->pid = pid;
  //printf("supuesto null %d\n",(*p)->next);
  return n;
}
void reporterProcess(int wfd, struct Proc pcbTable[], int time, struct TA_TIME ta,
		     QUE *s_run, QUE *s_ready, QUE *s_block);

/* Enque into a tail */
/*QUE *enqueue(QUE **p, int pid,struct Proc *pcTable)
{
  //printf("Pid proceso 1: %d\n",pcTable[1].pid);
  //printf("LLegue sin revisar pid\n");
  QUE *tail = *p;
  //printf("LLegue");
  if(*p == NULL) // For initial setup
    return insert_head(p, pid);

  while(tail->next != NULL) //tail refers to a tail node
    tail = tail->next;
  
  QUE *n = (QUE *) malloc(sizeof(QUE));
  if (n == NULL) return NULL;

  n->pid = pid;
  n->next=NULL;

  QUE *recorrido = *p;
  QUE *sig=recorrido->next;
  int priority1, priority2;
  priority1 = pcTable[pid].priority;
  priority2 = pcTable[recorrido->pid].priority;

  while(recorrido){
    priority2=pcTable[recorrido->pid].priority;
    if(priority1>priority2){
      recorrido->next=n;
      if(priority2!=pcTable[tail->pid].priority){
        n->next=sig;
      }
      return *p;
    }
    recorrido=recorrido->next;
    if(recorrido)sig=recorrido->next;
  }

  recorrido->next = n;

  return *p;
}*/

QUE *enqueue(QUE **p, int pid,struct Proc *pcTable)
{
  //printf("Pid proceso 1: %d\n",pcTable[1].pid);
  //printf("LLegue sin revisar pid\n");
  QUE *tail = *p;
  //printf("LLegue");
  if(*p == NULL) // For initial setup
    return insert_head(p, pid);

  while(tail->next != NULL) //tail refers to a tail node
    tail = tail->next;
  
  QUE *n = (QUE *) malloc(sizeof(QUE));
  if (n == NULL) return NULL;

  n->pid = pid;
  n->next=NULL;

  QUE *recorrido = *p;
  QUE *sig=recorrido->next;
  int priority1, priority2;
  priority1 = pcTable[pid].priority;
  priority2 = pcTable[recorrido->pid].priority;

  if (priority1 > priority2) {
    n->next = *p;
    *p = n;
    return *p;
  }

  while (recorrido->next) {
    priority2 = pcTable[recorrido->next->pid].priority;
    if (priority1 > priority2) {
      n->next = recorrido->next;
      recorrido->next = n;
      return *p;
    }
    recorrido = recorrido->next;
    if (recorrido) sig = recorrido->next;
  }

  recorrido->next = n;

  return *p;
}
/* Enque into a tail */

/*QUE *enqueue(QUE **p, int pid,struct Proc *pcTable)
{
  QUE *tail = *p;
  
  if(*p == NULL) // For initial setup
    return insert_head(p, pid);

  while(tail->next != NULL) //tail refers to a tail node
    tail = tail->next;

  QUE *n = (QUE *) malloc(sizeof(QUE));
  if (n == NULL)
    return NULL;

  n->next = NULL;
  tail->next = n;
  n->pid = pid;

  return n;
}*/

/* Dequeue from a head */
int dequeue(QUE **p){
  int pid = -1;
  if (*p != NULL){
    //printf("DEQ(pid=%d)\n", (*p)->proc.pid);
      pid = (*p)->pid;
      QUE *n = *p;
      if(n->next == NULL)printf("=============================duvarao");
      *p = n->next;
      free(n);
      if(n->next == NULL)printf("el valor de p es %d\n",*p);
      return pid;
  }else{
    //printf("cannot remove, because queue is empty\n");
    return pid;
  }
}

/* Create a new process with given parameters. */
struct Proc create_proc(int pid, int ppid, int priority, int pc, int value,
			int t_start, int t_used, char *fname){
  static struct Proc proc;
  proc.pid = pid;
  proc.ppid = ppid;
  proc.priority = priority;
  proc.pc = pc;
  proc.value = value;
  proc.t_start = t_start;
  proc.t_used = t_used;
  strcpy(proc.fname, fname);  
  readProgram(proc.fname, proc.prog);
  return proc;
}

/* Duplicate a process and change some parameters with given parameters. */
struct Proc dup_proc(struct Proc *pp, int new_pid,
		     int dup_times, int current_time){
  static struct Proc cp;
  cp.pid = new_pid;
  cp.ppid = pp->pid;
  cp.priority = pp->priority;
  cp.pc = pp->pc;  // Execute the instruction immediately after F instruction.
  cp.value = pp->value;
  cp.t_start = current_time;
  cp.t_used = 0;
  strcpy(cp.fname, pp->fname);
  printf("New pid %d\n",new_pid);
  readProgram(cp.fname, cp.prog);
  return cp;
} 

/* Show the status of a give queue. */
void show(QUE *n, struct Proc pcbTable[]){
  struct Proc proc;
  
  if (n == NULL){
    printf("queue is empty\n");
    return ;
  }
  while (n != NULL){
    proc = pcbTable[n->pid];
    printf("pc, pid, ppid, priority, value, start time, CPU time used so far\n");
    printf("%2d, %3d,  %3d, %8d, %5d, %10d, %3d\n",
	   proc.pc, proc.pid, proc.ppid, proc.priority,
	   proc.value, proc.t_start, proc.t_used);
    n = n->next;
  }
  printf("\n");
  return;
}

/* Show the status of a give queue by priority. */
void show_by_priority(QUE *n, struct Proc pcbTable[], int priority){
  struct Proc proc;
  int count = 0;
  
  while (n != NULL){
    if(pcbTable[n->pid].priority == priority){
      proc = pcbTable[n->pid];
      printf("pc, pid, ppid, priority, value, start time, CPU time used so far\n");
      printf("%2d, %3d,  %3d, %8d, %5d, %10d, %3d\n",proc.pc, proc.pid, proc.ppid, proc.priority,proc.value, proc.t_start, proc.t_used);
      count++;
    }
    n = n->next;
  }
  
  if (count == 0){
    printf("queue is empty\n");
    return ;
  }
  printf("\n");
  return;
}

/* Store a given cpu to a given process. */
void cpu2proc(struct Cpu *cpu, struct Proc *proc){
  proc->pc = cpu->pc;
  proc->pid = cpu->pid;
  proc->value = cpu->value;
  proc->t_used = cpu->t_remain;
  return;
}

/* Store a given process to a given cpu. */
void proc2cpu(struct Proc *proc, struct Cpu *cpu){
  cpu->pc =  proc->pc;
  cpu->pid = proc->pid;
  cpu->value = proc->value;
  cpu->t_slice = quantum[proc->priority];
  if(proc->t_used > 0){ // When blocked process is assigned.
    printf("Blocked process was assigned to CPU.\n");
    cpu->t_remain = proc->t_used;
  }else{ // When new process is assigned.
    printf("New process was assigned to CPU.\n");
    cpu->t_remain = cpu->t_slice;
  }
  return;
}

/* Set next priority based on a give priority. */
void set_next_priority(struct Proc *p){
  if(p->priority == CLASS_3){
    p->priority = CLASS_3;
  }else{
    p->priority += 1;
  }
  return;
}

/* Calculate a turn around time by a given current time and process. */
int calc_ta_time(int current_time, struct Proc *p){
  return current_time - p->t_start;
}

/* Calculate an average turn around time between all processes. */
double calc_ta_time_avg(struct TA_TIME ta){
  int i;
  int total = 0;
  for(i=0; i<ta.count; i++){
    total += ta.times[i];
  }
  if(ta.count == 0){
    return 0;
  }else{
    return total/ta.count;
  }
}

/* Read a program by a given filename and store it to program arrays. */
int readProgram(char *fname, char prog[][MAX_STR]){
  FILE *fp;
  char buff[MAX_STR], *pp;
  int x, y, i, j;
  
  /* Initialize program arrays */
  for(x=0;x<MAX_LINE;x++){
    for(y=0;y<MAX_STR;y++){
      prog[x][y] = '\0';
    }
  }

  fp = fopen(fname, "r");
  if(fp == NULL){
    printf("Can't open the file: '%s'\n", fname);
    exit(1);
  }

  i=0;
  //if(DEBUG) printf("Read '%s' program:\n", fname);
  while(1){
    pp = fgets(buff, MAX_STR, fp);
    
    // delete '\n' character if exists.
    j=0;
    while(buff[j] != '\0'){
      if(buff[j] == '\n') buff[j] = '\0';
      j++;
    }
  
    strcpy(prog[i], buff);
    if(pp == NULL){
      break;
    }
    //if(DEBUG) printf("%3d: '%s'\n", i, buff);    
    i++;
  }

  fclose(fp);
  return(0);
}

/* Split a string by spaces and return array.*/
char **split(int *n, char *string)
{
  char **array=NULL;
  char *p=string;
  char *s;

  for(*n=0; (s = strtok(p, " ")) != NULL; (*n)++) {
    array = (char**)realloc(array, sizeof(char*) * (*n+1));
    array[*n] = s;
    p = NULL;
  }

  return array;
}

void initialize(int *pid_count,int *current_time,struct Cpu *cpu, 
                struct TA_TIME *ta,struct Proc *pcbTable,char *init_program){
  quantum[CLASS_0] = 1;
  quantum[CLASS_1] = 2;
  quantum[CLASS_2] = 4;
  quantum[CLASS_3] = 8;

  *pid_count = 0;
  ta->count = 0;
  ta->times[0] = 0;
  *current_time = 0;
  cpu->pc = 0;
  cpu->pid = 0; 
  cpu->value = 0;
  cpu->t_slice = quantum[CLASS_0];
  cpu->t_remain = cpu->t_slice;
    
  pcbTable[cpu->pid] = create_proc((*pid_count)++, -1, CLASS_0, cpu->pc, cpu->value,*current_time, quantum[CLASS_0]-*current_time,init_program);
}

/* Whenever comes into a given input file descriptor,
   gives it into a output file descriptor. */
void copy(FILE *fin, FILE *fout)
{ 
  while (fgets(buffer, BUFSIZ, fin) != NULL) {
    fputs(buffer, fout);    
    fflush(fout);
  }
}

int iswaiting4unblocking(int wait4unblocking){
  if(wait4unblocking == true){
      printf("Only blocked processes remain, so waiting for unblocking.\n");
      printf("\n");
      printf("> ");
      fflush(stdout);
      return 1;
  }
  return 0;
}

void searchprog(struct Proc *pcbTable,struct Cpu *cpu,int *err_flg,char ***cmd){
  int f;
  char **aux=NULL;
  if(!strcmp(pcbTable[cpu->pid].prog[cpu->pc],"")){
    //printf("Carga cmd 2");
    printf("Instructions unexpectedy finished, so exit forcedlly with printing.\n");
    sprintf(*cmd[0], "E");
    *err_flg = true;
  }else{
    //printf("Carga cmd");
    *cmd = split(&f, pcbTable[cpu->pid].prog[cpu->pc]);
    //for(int i= 0;i<f;i++)printf("%s\n",cmd[i]);
  }
  //printf("Cmd en split: %d\n",cmd);
  return;
}

void setInteger(char **cmd,struct Cpu *cpu){
    printf("Set the value of the integer variable to %d.\n", atoi(cmd[1]));
    int temp_value = cpu->value;
    cpu->value = atoi(cmd[1]);
    printf("CPU value: %d -> %d\n", temp_value, cpu->value);	
}

void addValue(char **cmd,struct Cpu *cpu){
  printf("Add %d to the value of the integer variable.\n", atoi(cmd[1]));
  int temp_value = cpu->value;
  cpu->value += atoi(cmd[1]);
  printf("CPU value: %d -> %d\n", temp_value, cpu->value);	
}

void substractValue(char **cmd,struct Cpu *cpu){
  int temp_value;
  printf("Substract %d from the value of the integer variable.\n", atoi(cmd[1]));
  temp_value = cpu->value;
  cpu->value -= atoi(cmd[1]);
  printf("CPU value: %d -> %d\n", temp_value, cpu->value);
}

void blockProcess(struct Cpu *cpu,QUE **blocked_states,QUE **running_states,
                  struct Proc *pcbTable){
  printf("Block this simulated process.\n");
  // Store CPU data to proc
  dequeue(running_states); 
  cpu2proc(cpu, &pcbTable[cpu->pid]);
  printf("Running Process(pid=%d) was blocked.\n", cpu->pid);
  enqueue(blocked_states, cpu->pid,pcbTable);
  // Scheduling required.	
}

void exitProcess(QUE **running_states,struct Cpu *cpu,struct TA_TIME *ta,int current_time,
                  struct Proc *pcbTable){
  printf("Terminate this simulated process.\n");
  printf("Running before: %d\n",*running_states);
  dequeue(running_states);
  printf("Running after: %d\n",*running_states);
  printf("pid=%d is Terminated.\n", cpu->pid);
  ta->times[(ta->count)++] = calc_ta_time(current_time, &pcbTable[cpu->pid]);
  // Scheduling required.	
}

void forkProcess(char **cmd,struct Cpu *cpu,struct Proc *pcbTable, int *pid_count,
                int *current_time,QUE **ready_states){
  printf("Create %d new simulated process(es).\n", atoi(cmd[1]));
  int arg = atoi(cmd[1]);	
  cpu2proc(cpu, &pcbTable[cpu->pid]);
  /* Duplicate a proc and enqueue it into Ready states queue. */
  pcbTable[*pid_count] = dup_proc(&pcbTable[cpu->pid], *pid_count,arg, *current_time);
  (*pid_count)++;
  enqueue(ready_states, *pid_count-1,pcbTable);
  printf("Created a process(pid=%d).\n", *pid_count-1);
  cpu->pc += arg; // Execute N instructions after the next instruction. 
  // Not necessary to schdule processes.	
}


void replaceImage(char **cmd,struct Cpu *cpu,struct Proc *pcbTable){
  char temp_fname[MAX_STR];
  printf("Replace the program of the simulated process with the program in the file '%s'.\n", cmd[1]);
  strcpy(temp_fname, cmd[1]);
  cpu->pc = 0;
  cpu->value = 0;
  readProgram(temp_fname, pcbTable[cpu->pid].prog);
  printf("Replaced the current program with the program in '%s' file.\n", temp_fname);
}

int processInstructions(char **cmd,struct Cpu *cpu,QUE **ready_states,QUE **blocked_states,QUE **running_states,
                        struct Proc *pcbTable,struct TA_TIME *ta,int *current_time,int *pid_count){
  int temp_value;
  if(!strcmp(cmd[0], "S")){
    setInteger(cmd,cpu);
    printf("Valor de cpu: %d\n",cpu->value);
  }else if(!strcmp(cmd[0], "A")){
    addValue(cmd,cpu);
  }else if(!strcmp(cmd[0], "D")){
    substractValue(cmd,cpu);
  }else if(!strcmp(cmd[0], "B")){
    blockProcess(cpu,blocked_states,running_states,pcbTable);
  }else if(!strcmp(cmd[0], "E")){
    exitProcess(running_states,cpu,ta,*current_time,pcbTable);
  }else if(!strcmp(cmd[0], "F")){
    forkProcess(cmd,cpu,pcbTable,pid_count,current_time,ready_states);	
  }else if(!strcmp(cmd[0],"R")){
    replaceImage(cmd,cpu,pcbTable);
  }else{
    printf("Unknown Instruction.\n");
    printf("Exited by error.\n");
    return 1;
  }
  return 0;
}

void finishExecution(int *err_flg,int *fd,struct Cpu *cpu,struct Proc *pcbTable,int *current_time,struct TA_TIME ta,
                    QUE **running_states,QUE **ready_states,QUE **blocked_states){
  if(*err_flg == false) printf("Program was successfully executed.\n");
  printf("\n");
  printf("=== RESULT ===\n");
  int temp_pid,i;
  char c;
  if (pipe(fd)) {
      perror("pipe");
  } else if ((temp_pid = fork()) == -1) {
      perror("fork");
  } else if (temp_pid == 0) {
      close(fd[0]);
      if(DEBUG) cpu2proc(cpu, &pcbTable[cpu->pid]);
      reporterProcess(fd[1], pcbTable, *current_time, ta,(QUE*)running_states, (QUE*)ready_states, (QUE*)blocked_states);
  } else {
      close(fd[1]);
      while((i=read(fd[0],&c,1)) > 0); // Pipe Synchronization
  }
  printf("=== END OF SYSTEM ===\n");
}

void processBloqued(QUE **ready_states,QUE **running_states,struct Proc *pcbTable,struct Cpu *cpu){
  printf("There are no process running, so assign the first process in the queue to CPU.\n");
  int temp_pid = dequeue(ready_states);
  proc2cpu(&pcbTable[temp_pid], cpu);
  enqueue(running_states, temp_pid,pcbTable);
  printf("Assigned: cpu <--- pcbTable[%d]\n", temp_pid);
}

void quantumExpired(struct Proc *pcbTable,struct Cpu *cpu,QUE **ready_states,QUE **running_states){
  printf("Quantum was expired, so assign the first process in the que to CPU.\n");
  set_next_priority(&pcbTable[cpu->pid]);
  printf("Pid(%d)'s priority class was raised to %d.\n",cpu->pid, pcbTable[cpu->pid].priority);
  int pid_cpu=cpu->pid;
  cpu2proc(cpu, &pcbTable[cpu->pid]);
  int temp_pid = dequeue(running_states);	


  proc2cpu(&pcbTable[dequeue(ready_states)], cpu);
  enqueue(running_states, cpu->pid,pcbTable);


  enqueue(ready_states, pid_cpu,pcbTable);
  //printf("encolé otro proceso en ready\n");

  
  
  
  printf("Swithed: cpu(%d) <--> pid(%d)\n", temp_pid, cpu->pid);	
}

int doScheduling(QUE **ready_states,QUE **running_states,QUE **blocked_states,int *wait4unblocking,int *fd,int *err_flg,
                  struct Cpu *cpu,char ***cmd,struct Proc *pcbTable,int *current_time,struct TA_TIME *ta){
  int temp_pid,i; 
  char c;                 
  //printf("El valor de la cola running es: %d\n",running_states);
  if(*ready_states == NULL){ // No processes in the Ready queue, so skipped.
    printf("Llegue schedule\n");
    if(*running_states != NULL){
      printf("No ready processes, so continue to run the current process.\n");
    }else if(*blocked_states != NULL){
      printf("Only blocked processes remain, so waiting for unblocking.\n");
      *wait4unblocking = true;
    }else{ // All processes were finished -> finished execution.
      finishExecution(err_flg,fd,cpu,pcbTable,current_time,*ta,running_states,ready_states,blocked_states);
      return 1;
    }		
  }else if(*running_states == NULL){ // When process was blocked or terminated.
    //printf("================================================================\n====================\n");
    processBloqued(ready_states,running_states,pcbTable,cpu);	
  }else if(cpu->t_remain <= 0) { // When quantum expired
    quantumExpired(pcbTable,cpu,ready_states,running_states);
  }else if(cpu->t_remain > 0){
    printf("CPU Time is still remained, so continue to run the current process.\n");	
  }else{
    printf("Unknown condition to schedule.\n");
  }
  /*** End of Scheduling ***/
  free(*cmd);
  /* End of One Unit of Time*/ 
  return 0;     
}

int endOfUnitOfTime(int *wait4unblocking,struct Proc *pcbTable,struct Cpu *cpu,char ***cmd,
                      int *err_flg,QUE **ready_states,QUE **blocked_states,QUE **running_states,struct TA_TIME *ta,int *current_time,
                      int *pid_count){
  
  if(iswaiting4unblocking(*wait4unblocking))return 1;
  
  printf("End of one unit of time.\n");
  printf("Instruction = '%s'\n", pcbTable[cpu->pid].prog[cpu->pc]);

  searchprog(pcbTable,cpu,err_flg,cmd);
  (*current_time)++;
  (cpu->pc)++;
  (cpu->t_remain)--;

  if(processInstructions(*cmd,cpu,ready_states,blocked_states,running_states,pcbTable,ta,current_time,pid_count))return 1;

  return 0;
}

void unblockProcess(QUE **blocked_states,QUE **ready_states,int *wait4unblocking,struct Proc *pcbTable){
  printf("Unblock the first simulated process in blocked queue.\n");
  int temp_index = dequeue(blocked_states);
  if(temp_index == -1){
    printf("There are no states in blocked queue.\n");
  }else{
    printf("pid=%d moves from blocked queue to ready queue.\n", temp_index);
    enqueue(ready_states, temp_index,pcbTable);
    *wait4unblocking = false;
  }     
}

void printCurrentState(int *fd,struct Cpu *cpu,struct Proc *pcbTable,int current_time,struct TA_TIME ta,
                        QUE **running_states, QUE **ready_states,QUE**blocked_states){
  int temp_pid,i;
  char c;
  printf("Print the current state of the system.\n");
  if (pipe(fd)) {
    perror("pipe");
  } else if ((temp_pid = fork()) == -1) {
    perror("fork");
  } else if (temp_pid == 0) {
    close(fd[0]);
    if(DEBUG) cpu2proc(cpu, &pcbTable[cpu->pid]);
    reporterProcess(fd[1], pcbTable, current_time, ta,*running_states, *ready_states, *blocked_states);
  } else {
    close(fd[1]);
    while((i=read(fd[0],&c,1)) > 0); // Pipe Synchronization
  }
}

void helpOption(){
  printf("\
    The following commands are accepted:\n\
    Q:End of one unitof time\n\
    - CPU consumes 1 instruction from programs, andexecuteit.\n\
    U: Unblockthe first simulated process in blocked queue\n\
    - If there is ablockedprocess, move its statefrom Blocked toReady.\n\
    P: Print the current state of the system.\n \
    - The state include PC, PID, PPID, Priority, Value, Time, etc.\n\
    T: Terminate the system after printing the current state.\n\
    - The printing is same as 'P' command.\n");          
}

void printAverageTurnaroundTime(struct TA_TIME ta,int *fd,struct Cpu *cpu,struct Proc *pcbTable,int current_time,
                                QUE **running_states,QUE **ready_states,QUE **blocked_states){
  int temp_pid,i;
  char c;
  printf("Print the average turnaround time, and terminate the system.\n");
  // Calculating average turnaround time.
  printf("Average turn around time is %f.\n", calc_ta_time_avg(ta));
  if (pipe(fd)) {
    perror("pipe");
  } else if ((temp_pid = fork()) == -1) {
    perror("fork");
  } else if (temp_pid == 0) {
    close(fd[0]);
    if(DEBUG) cpu2proc(cpu, &pcbTable[cpu->pid]);
    reporterProcess(fd[1], pcbTable, current_time, ta,*running_states, *ready_states, *blocked_states);
  } else {
    close(fd[1]);
    while((i=read(fd[0],&c,1)) > 0); // Pipe Synchronization
  }
  printf("\n");
  printf("Terminate the system.\n");
}

/* Commander process that manipulates inputs from users,
   and send them to Process Manager process. */
void commanderProcess(int wfd)
{
  FILE *fp = fdopen(wfd, "w");
  int status;
  
  if (fp == NULL) {
    perror("parent: fdopen");
    exit(3);
  }
  copy(stdin, fp);
  fclose(fp);

  if(wait(&status) == -1) {
    perror("wait");
    exit(4);
  }
}

/* Report the current status of system. */
void reporterProcess(int wfd, struct Proc pcbTable[], int time, struct TA_TIME ta,
		     QUE *s_run, QUE *s_ready, QUE *s_block){
  int i;
  printf("*********************************************\n");
  printf("The current system state is as follows:\n");
  printf("*********************************************\n");
  printf("CURRENT TIME: %d\n", time);
  printf("AVERAGE TURN AROUND TIME: %f.\n", calc_ta_time_avg(ta));
  printf("\n");
  printf("RUNNING PROCESS:\n");
  show(s_run, pcbTable);
  
  printf("\n");
  printf("BLOCKED PROCESSES:\n");
  printf("Queue of blocked processes:\n");
  show(s_block, pcbTable);
  
  printf("\n");
  printf("PROCESSES READY TO EXECUTE:\n");
  for(i=0; i<MAX_PRIORITY; i++){
    printf("Queue of processes with priority %d:\n", i);
    show_by_priority(s_ready, pcbTable, i);
  }
  
  close(wfd); // Pipe Synchronized.
  exit(3);
}

/* Based on inputs from Commander process,
   manage all processes and share a CPU between them. */
void processManagerProcess(int rfd, char *init_program)
{
  FILE *fp = fdopen(rfd, "r");
  int fd[2];
  
  // iterators
  int c, n,pid_count,arg,i,temp_value,temp_pid,temp_index,current_time;
  // For skipping instructions when only blocked processes are remained.
  int wait4unblocking = false,err_flg = false;
  
  // For calculating average turn around time
  struct TA_TIME ta;
  
  char temp_fname[MAX_STR],**cmd;
  
  /* ProcessManager's 6 Data Structures*/
  struct Cpu cpu;
  struct Proc pcbTable[MAX_PROCS];

  QUE *ready_states, *blocked_states,*running_states;
  /**************************************/
  
  /* Initializing */
  initialize(&pid_count,&current_time,&cpu,&ta,pcbTable,init_program);
  //pcbTable[cpu.pid] = create_proc((pid_count)++, -1, CLASS_0, cpu.pc, cpu.value,current_time, quantum[CLASS_0]-current_time,init_program);
  //printf("pid count: %d current_time: %d",pid_count,current_time);
  ready_states = NULL;
  blocked_states = NULL;
  running_states = NULL;
  // TODO: Re-thinking of this structure needed.
  enqueue(&running_states, cpu.pid,pcbTable);
  /****************/
  //if(DEBUG) show(running_states, pcbTable);
  
  while (fgets(buffer, BUFSIZ, fp) != NULL) {
    
    printf("Command = %s",buffer);
    if(!strcmp(buffer, "Q\n") || !strcmp(buffer, "q\n")){
      printf("enter to Q\n");
      if(endOfUnitOfTime(&wait4unblocking,pcbTable,&cpu,&cmd,&err_flg,&ready_states,&blocked_states,&running_states,&ta,&current_time,&pid_count))continue;
      /*** Do scheduling ***/
      printf("go to scheduling\n");
      //COMPLETAR
      if(doScheduling(&ready_states,&running_states,&blocked_states,&wait4unblocking,fd,&err_flg,&cpu,&cmd,pcbTable,&current_time,&ta))return;     
    } else if(!strcmp(buffer, "U\n") || !strcmp(buffer, "u\n")){
      unblockProcess(&blocked_states,&ready_states,&wait4unblocking,pcbTable);
    }else if(!strcmp(buffer, "P\n") || !strcmp(buffer, "p\n")){
      printCurrentState(fd,&cpu,pcbTable,current_time,ta,&running_states,&ready_states,&blocked_states);
    }else if(!strcmp(buffer, "help\n")){
      helpOption();
    }else if(!strcmp(buffer, "T\n") || !strcmp(buffer, "t\n")){
      printAverageTurnaroundTime(ta,fd,&cpu,pcbTable,current_time,&running_states,&ready_states,&blocked_states);
      return;      
    }else{
      printf("Unknown command.\n");
    }
    //fputs(buffer, stdout);
    printf("\n");
    printf("> ");
    fflush(stdout);
  }
  fclose(fp);
}

int main(int argc, char *argv[]){
  int rv = 0, fd[2], pid;
  char fname[MAX_STR];

  if(argc != 2){
    printf("USAGE: ./a.out INIT_PROGRAM_NAME\n\n");
    return -1;
  }
  printf("> ");
  strcpy(fname, argv[1]);

  if (pipe(fd)) {
    perror("pipe");
    rv = 1;
  } else if ((pid = fork()) == -1) {
    perror("fork");
    rv = 2;
  } else if (pid > 0) {
    close(fd[0]);
    commanderProcess(fd[1]);
  } else {
    close(fd[1]);
    processManagerProcess(fd[0], fname);
  }
  return rv;
}

