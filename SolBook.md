# Solución libro:
## Chapter 1: Introduction

1. What are the two main functions of an operating system?

Permitir al usuario acceder a los dispositivos I/O y ser una interfaz amigable para poder realizar
esta labor.
    
2. In Section 1.4, nine different types of operating systems are described. Give a list of
applications for each of these systems (one per operating systems type).

3. What is the difference between timesharing and multiprogramming systems?
 
Para el timesharing muchos usuarios pueden conectarse y realizar múltiples acciones en un mismo
sistema computacional, desde distintas terminales, mientras que la multiprogramacion es que
un mismo usuario pueda ejecutar multiples programas simultaneamente.


4. To use cache memory, main memory is divided into cache lines, typically 32 or 64
bytes long. An entire cache line is cached at once. What is the advantage of caching an
entire line instead of a single byte or word at a time?

Puedes acceder a las variables vecinas de una dirección de memoria, es decir, si tienes un arreglo
y accedes a la posicion 0 es posible que quieras acceder a las direcciones 1, 2, etc. Por lo que
traer la información a la caché en bloques facilita este proceso, pues evitar estar yendo a la
memoria RAM.

5. On early computers, every byte of data read or written was handled by the CPU (i.e.,
there was no DMA). What implications does this have for multiprogramming?

6. Instructions related to accessing I/O devices are typically privileged instructions, that
is, they can be executed in kernel mode but not in user mode. Give a reason why these
instructions are privileged.

Si un usuario pudiese acceder a estas funciones o alguna aplicación pudiera, se corre el riesgo de que este
se olvide de desbloquear el sistema en casos se haya bloqueado por un input/output, es darle demasiado
control al programador o a alguna aplicación que pueda usar este control en contra de la máquina.

Además es posible que el administrador del sistemas quiera restringir algunas funciones según sus políticas.
Estas políticas deben aplicarse para que los programas de usuario no puedan interferir con ellas.


7. The family-of-computers idea was introduced in the 1960s with the IBM System/360
mainframes. Is this idea now dead as a doornail or does it live on?

8. One reason GUIs were initially slow to be adopted was the cost of the hardware need-
ed to support them. How much video RAM is needed to support a 25-line × 80-row
character monochrome text screen? How much for a 1200 × 900-pixel 24-bit color bit-
map? What was the cost of this RAM at 1980 prices ($5/KB)? How much is it now?

9. There are several design goals in building an operating system, for example, resource
utilization, timeliness, robustness, and so on. Give an example of two design goals that
may contradict one another.




10.  What is the difference between kernel and user mode? Explain how having two distinct
modes aids in designing an operating system.



En kernel mode uno tiene más control para poder ejecutar distintas funciones, mientras que el user mode
está limitado, pues no se pueden acceder a todas las funciones desde ahí, un ejemplo son las interrupciones
de un proceso, un hilo que esté en modo usuario no puede realizar una interrupción que pare la ejecución
de los demás hilos de su proceso, esto sería muy riesgoso, a modo de ejemplo, 
una interrupción de teclado no tendría porque parar la ejecución de otros procesos.

11.  A 255-GB disk has 65,536 cylinders with 255 sectors per track and 512 bytes per sec-
tor. How many platters and heads does this disk have? Assuming an average cylinder
seek time of 11 ms, average rotational delay of 7 msec and reading rate of 100 MB/sec,
calculate the average time it will take to read 400 KB from one sector.

12.  Which of the following instructions should be allowed only in kernel mode?
(a) Disable all interrupts.
(b) Read the time-of-day clock.
(c) Set the time-of-day clock.
(d) Change the memory map.

13.  Consider a system that has two CPUs, each CPU having two threads (hyperthreading).
Suppose three programs, P0, P1, and P2, are started with run times of 5, 10 and 20
msec, respectively. How long will it take to complete the execution of these programs?
Assume that all three programs are 100% CPU bound, do not block during execution,
and do not change CPUs once assigned.

14.  A computer has a pipeline with four stages. Each stage takes the same time to do its
work, namely, 1 nsec. How many instructions per second can this machine execute?

1seg -> 10^(-9)ns 
10^(⁻9)nsegs=10^(⁻9)/8

4ns/2inst
5s/3ints
6ns/4ints
xns/x-2inst


15.   Consider a computer system that has cache memory, main memory (RAM) and disk,
and an operating system that uses virtual memory. It takes 1 nsec to access a word
from the cache, 10 nsec to access a word from the RAM, and 10 ms to access a word
from the disk. If the cache hit rate is 95% and main memory hit rate (after a cache
miss) is 99%, what is the average time to access a word?

Av erage access time =
0.95×1nsec (word is in the cache)+
0.05x0.99×10 nsec (word is in RAM, but not in the cache)
+0.05×0.01×10,000,000 nsec (word on disk only)
=5001.445 nsec
=5.001445 µ sec

16.   When a user program makes a system call to read or write a disk file, it provides an
indication of which file it wants, a pointer to the data buffer, and the count. Control is
then transferred to the operating system, which calls the appropriate driver. Suppose
that the driver starts the disk and terminates until an interrupt occurs. In the case of
reading from the disk, obviously the caller will have to be blocked (because there are
no data for it). What about the case of writing to the disk? Need the caller be blocked
awaiting completion of the disk transfer?


17.  What is a trap instruction? Explain its use in operating systems.
La instrucción trap sirve para cambiar de modo usuario a modo kernel, es decir se podrán ejecutar todas las system calls
privilegiadas, por ejemplo, al querer realizar alguna instalación de driver, el modo usuario no puede ejecutar las system calls
respectivas pues el so no lo permite, para ello se necesita acceder al modo administrador para poder estar en modo kernel y así
tener acceso a dichas calls.

18.  Why is the process table needed in a timesharing system? Is it also needed in personal
computer systems running UNIX or Windows with a single user?

La tabla de procesos se usa para guardar información de los procesos suspendidos, listos o bloqueados. Nos permite tener más
información y control de los procesos en el sistema operativo. Es necesario en todos los sistemas operativos pues siempre se ejecutan
procesos aunque el usuario no haga nada(espera de correos, actualizaciones, etc).

19.  Is there any reason why you might want to mount a file system on a nonempty direc-
tory? If so, what is it?

Porque quiero montar mi USB en una carpeta para poder utilizarla.

20.  For each of the following system calls, give a condition that causes it to fail: fork, exec,
and unlink.

fork: ya se superó la cantidad de procesos máxima del sistema operativo.
exec: no existe el proceso indicado
unlink: el directorio no existe o no se tienen los permisos para deslinkearlo. 

21.  What type of multiplexing (time, space, or both) can be used for sharing the following
resources: CPU, memory, disk, network card, printer, keyboard, and display?

CPU: time
Memory: space
Disk: space
Network: time
Card: time
printer: time
keyboard: time
display: time

22.  Can the
count = write(fd, buffer, nbytes);
call return any value in count other than nbytes? If so, why?

Puede retornar -1 en caso la función falle

23.  A file whose file descriptor is fd contains the following sequence of bytes: 3, 1, 4, 1, 5,
9, 2, 6, 5, 3, 5. The following system calls are made:
lseek(fd, 3, SEEK SET);
read(fd, &buffer, 4);

where the lseek call makes a seek to byte 3 of the file. What does buffer contain after
the read has completed?
1 5 9 2

24.  Suppose that a 10-MB file is stored on a disk on the same track (track 50) in consecu-
tive sectors. The disk arm is currently situated over track number 100. How long will
it take to retrieve this file from the disk? Assume that it takes about 1 ms to move the
arm from one cylinder to the next and about 5 ms for the sector where the beginning of
the file is stored to rotate under the head. Also, assume that reading occurs at a rate of
200 MB/s.

//dudo que esto venga

25.  What is the essential difference between a block special file and a character special
file?

Los special files se crean para para hacer parecer a los dispositivos I/O como archivos. De tal forma que se puedan leer y 
escribir como si fueran archivos.

El block special file se usa para modelar dispositivos que constan de bloques de dirección aleatorios, como los discos.
Con una llamada al bloque 4 se lee directamente el bloque 4 sin importar la estructura del sistema de archivos.

El character special file se usa para modelar impresoras, modems y otros dispositivos que reciben o dan outputs como
flujo de caracteres.  Se guardan en /dev.

26.  In the example given in Fig. 1-17, the library procedure is called read and the system
call itself is called read. Is it essential that both of these have the same name? If not,
which one is more important?

No es necesario, solo importa la llamada del sistema operativo pues la decodificación de la instrucción es la que va a indicar
la función a realizar con el opcode, se puede poner cualquier nombre en varios lenguajes pero se hace referencia a una misma función.

27.  Modern operating systems decouple a process address space from the machine’s physi-
cal memory. List two advantages of this design.

 This allows an executable program to be loaded in different parts of the ma-chine’smemory in different runs. Also, it enables program size 
 to exceed thesize of the machine’smemory.

28.  To a programmer, a system call looks like any other call to a library procedure. Is it
important that a programmer know which library procedures result in system calls?
Under what circumstances and why?

Si, es importante que el programador sepa qué libreria es la que tiene los distintos system calls.
Esto para que el pueda hacer pruebas de programas, ver programación concurrente y entender mejor el sistema operativo que está
manejando.

29.  Figure 1-23 shows that a number of UNIX system calls have no Win32 API equiv-
alents. For each of the calls listed as having no Win32 equivalent, what are the conse-
quences for a programmer of converting a UNIX program to run under Windows?

-   Link: no se puede bloquear los archivos con link, ejem abrir en txt y eliminar el archivo del directorio
-   Mount and umount: un programa de Windows no puede hacer suposiciones sobre nombres de ruta estándar porque 
en sistemas con múltiples unidades de disco la parte del nombre de la unidad de la ruta puede ser diferente.
- Chmod:  Windows utiliza listas de control de acceso.
- Kill: Los programadores de Windows no pueden matar a un programa que se comporta mal y no coopera.

30.  A portable operating system is one that can be ported from one system architecture to
another without any modification. Explain why it is infeasible to build an operating
system that is completely portable. Describe two high-level layers that you will have in
designing an operating system that is highly portable.

Los sistemas operativos tienen algunas instrucciones que son únicas y no pueden ejecutarse en otros sistemas operativos.
Además existen diferencias en las arquitecturas que son muy importantes, como el tamaño del bus, el tamaño del word.
Por ende no es viable crear un sistema operativo completamente portable.

Un sistema operativo altamente portable constará de dos capas de alto nivel: una capa dependiente de la máquina y una capa 
independiente de la máquina. La capa dependiente de la máquina se ocupa de las especiﬁcaciones del hardware y debe implementarse 
por separado para cada arquitectura. Esta capa proporciona una interfaz uniforme sobre la que se construye la capa independiente de 
la máquina. La capa independiente de la máquina sólo debe implementarse una vez. Para que sea altamente portable, el tamaño de la 
capa dependiente de la máquina debe ser lo más pequeño posible.

31.  Explain how separation of policy and mechanism aids in building microkernel-based
operating systems.


La separación de política y mecanismo permite a los diseñadores de SO implementar un pequeño número de primitivas básicas en el 
núcleo. Estas primitivas están simplificadas, porque no dependen de ninguna política específica. Luego pueden utilizarse para 
implementar mecanismos y políticas más complejos a nivel de usuario.


32.  Virtual machines have become very popular for a variety of reasons. Nevertheless,
they have some downsides. Name one.

Necesitas pasar varias capas para poder llegar al kernel del sistema y poder ejecutar las system calls que requieras.
Además estas no cuentan con un propio kernel, pues este depende del kernel de la capa más baja.

La capa de virtualización introduce un mayor uso de memoria y sobrecarga del procesador, así como una mayor 
sobrecarga de rendimiento.

33.  Here are some questions for practicing unit conversions:
(a) How long is a nanoyear in seconds?

1 año*10^-9
365 dias*10^-9
365*24h*10^-9
365*24*60min*10^-9
365*24*60 * 60 *10^-9 second

(b) Micrometers are often called microns. How long is a megamicron?

1 metro *10^-6*10^6

(c) How many bytes are there in a 1-PB memory?

10^15 bytes

(d) The mass of the earth is 6000 yottagrams. What is that in kilograms?

6000*10^21 kilogramos

34.  Write a shell that is similar to Fig. 1-19 but contains enough code that it actually works
so you can test it. You might also add some features such as redirection of input and
output, pipes, and background jobs.

35.  If you have a personal UNIX-like system (Linux, MINIX 3, FreeBSD, etc.) available
that you can safely crash and reboot, write a shell script that attempts to create an
unlimited number of child processes and observe what happens. Before running the
experiment, type sync to the shell to flush the file system buffers to disk to avoid84
ruining the file system. You can also do the experiment safely in a virtual machine.
Note: Do not try this on a shared system without first getting permission from the sys-
tem administrator. The consequences will be instantly obvious so you are likely to be
caught and sanctions may follow.

36.  Examine and try to interpret the contents of a UNIX-like or Windows directory with a
tool like the UNIX od program. Hint: How you do sthis will depend upon what the OS
allows. One trick that may work is to create a directory on a USB stick with one oper-
ating system and then read the raw device data using a different operating system that
allows such access.

## Chapter 2

1. In Fig. 2-2, three process states are shown. In theory, with three states, there could be
six transitions, two out of each state. However, only four transitions are shown. Are
there any circumstances in which either or both of the missing transitions might occur?

La transición de bloqueado a en ejecución es concebible. Supongamos que un proceso está bloqueado en E/S y 
que la E/S finaliza; si la CPU está inactiva, el proceso podría pasar directamente de bloqueado a en 
ejecución. La otra transición que falta, de listo a bloqueado, es imposible.

2. Suppose that you were to design an advanced computer architecture that did process
switching in hardware, instead of having interrupts. What information would the CPU
need? Describe how the hardware process switching might work.

Podría tener un registro que contuviera un puntero a la entrada actual de la tabla de procesos. Cuando se completara la E/S, la CPU almacenaría el estado actual de la máquina en la entrada actual de la tabla de procesos. Luego iría al vector de interrupción para el dispositivo de interrupción y obtendría un puntero a otra entrada de la tabla de procesos (el procedimiento de servicio).
 
3. On all current computers, at least part of the interrupt handlers are written in assembly
language. Why?

Porque el uso de ensamblador nos permite manipular directamente los registros con la información que 
recibiremos. Con lenguaje ensamblador podemos manipular la pila de forma más directa, además de tener un acceso más directo
de los dipositivos I/O, es por ello que este manejo de I/O se ve programado en el kernel con ensamblador.
Por ejemplo, un manejador de interrupciones puede ser necesario para activar y desactivar la interrupción que 
da servicio a un dispositivo en particular, o para manipular datos dentro del área de pila de un proceso. 
Además, las rutinas de servicio de interrupción deben ejecutarse lo más rápidamente posible.

4. When an interrupt or a system call transfers control to the operating system, a kernel
stack area separate from the stack of the interrupted process is generally used. Why?

Esto es para que el kernel tenga toda la información correspondiente a la llamada de manera cercana
y así no tenga que andar consultado a la pila del proceso, pues él mismo estaría guardando la información.
El gestiona su forma de ejecutar las instrucciones y no depende de una pila que puede ser usada por un
programador. Por otro lado si el kernel apila datos en el return de la system call se puede usar esta 
información de manera inadecuada.

5. A computer system has enough room to hold five programs in its main memory. These
programs are idle waiting for I/O half the time. What fraction of the CPU time is
wasted?

1/32

6. A computer has 4 GB of RAM of which the operating system occupies 512 MB. The
processes are all 256 MB (for simplicity) and have the same characteristics. If the goal
is 99% CPU utilization, what is the maximum I/O wait that can be tolerated?

puede tener 14 procesos

0.01 = (x)^14

7. Multiple jobs can run in parallel and finish faster than if they had run sequentially.
Suppose that two jobs, each needing 20 minutes of CPU time, start simultaneously.
How long will the last one take to complete if they run sequentially? How long if they
run in parallel? Assume 50% I/O wait.

40 minutos por proceso
Si es secuencial entonces demora 80 min
Si se ejecutan en paralelo:
20 min -> un hilo ->10min
20 min I/O->10 min


8. Consider a multiprogrammed system with degree of 6 (i.e., six programs in memory at
the same time). Assume that each process spends 40% of its time waiting for I/O. What
will be the CPU utilization?

1-0.4^6
Tiempo ejecutado = tiempo total - tiempo en I/O.

9. Assume that you are trying to download a large 2-GB file from the Internet. The file is
available from a set of mirror servers, each of which can deliver a subset of the file’s
bytes; assume that a given request specifies the starting and ending bytes of the file.
Explain how you might use threads to improve the download time.

Usaria distintos hilos para leer la información de los distintos subconjuntos del file.
Luego los escribiría en un buffer también con varios hilos de escritura para finalmente tener otro hilo
que se encargue de enviar el file ya descargado.


10. In the text it was stated that the model of Fig. 2-11(a) was not suited to a file server
using a cache in memory. Why not? Could each process have its own cache?

Por supuesto que cada proceso puede tener su propia caché, pero manejar los hilos así no tiene sentido
pues la finalidad de los hilos es que compartan un espacio de memoria definido, no que cada uno use su caché.
Además que esto restringiría a los demás procesos a ejecutar una labor conjunta y secuencial, cada proceso muere 
con su propia cache y esto hace que las llamadas a la ram se sigan dando, no cumpliendo la finalida
de la memoria cache.


11. If a multithreaded process forks, a problem occurs if the child gets copies of all the
parent’s threads. Suppose that one of the original threads was waiting for keyboard
input. Now two threads are waiting for keyboard input, one in each process. Does this
problem ever occur in single-threaded processes?

Los single threads no pueden forkear una vez estén bloqueados.


12. In Fig. 2-8, a multithreaded Web server is shown. If the only way to read from a file is
the normal blocking read system call, do you think user-level threads or kernel-level
threads are being used for the Web server? Why?

Se usan hilos a nivel del kernel pues debe haber una gran protección de parte del servidor, cualquier solicitud
entrante no debe ser ejecutada, sino que primero debe ver si las instrucciones requeridas
Además en caso se reciba una instrucción de I/O que necesite ser bloqueada
no hay necesidad de bloquear todos los hilos, sino solo el que se necesita
y los demás pueden seguir ejecutándose. Este control solo lo da el kernel en el 
user space se bloquearían todos los hilos de un mismo proceso.


13. In the text, we described a multithreaded Web server, showing why it is better than a
single-threaded server and a finite-state machine server. Are there any circumstances in
which a single-threaded server might be better? Give an example.

Es mejor debido a que nos facilita realizar los procesos, dividiendo ciertas etapas en distintos hilos con la finalidad 
de que si alguno se interrumpa o tenga tiempo de espera, sus funciones más pequeñas puedan ser redistribuidas. Como es el caso
de una colmena donde no todo es un proceso lineal sino que se dividen las tareas en áreas y se agiliza así el desarrollo del proceso.




14. In Fig. 2-12 the register set is listed as a per-thread rather than a per-process item.
Why? After all, the machine has only one set of registers.

Cuando un hilo se detiene, tiene valores en los registros. Deben ser guardados, al igual que cuando se detiene el proceso. 
Los registros deben ser guardados. La multiprogramación de hilos no difiere de la multiprogramación de procesos, por lo que cada 
hilo necesita su propia área de guardado de registros.

15. Why would a thread ever voluntarily give up the CPU by calling thread yield? After
all, since there is no periodic clock interrupt, it may never get the CPU back.

Esto es para dar facilidades al programador, por ejemplo, si tenemos 2 procesos relacionados como el de el productor y el cliente.
Un caso sería que el hilo del cliente realize un thread join para esperar que otro hilo le confirme que hay un producto despachado.
Pues no tiene sentido que el cliente recoja un producto que ni siquiera exista. Este tipo de lógica debe ser implementada por el 
programador y las funciones *thread_yield* y *thread_join* ayudan a esto.

16. Can a thread ever be preempted by a clock interrupt? If so, under what circumstances?If not, why not?

Los hilos de usuario no pueden ser adelantados por el reloj a menos que se haya agotado el quantum de todo el proceso 
(aunque pueden producirse interrupciones transparentes del reloj).Los hilos del núcleo pueden ser adelantados individualmente.En 
este último caso, si un hilo se ejecuta demasiado tiempo, el reloj interrumpirá el proceso actual y, por tanto, el hilo actual. El 
núcleo es libre de elegir un hilo diferente del mismo proceso para ejecutarlo a continuación si así lo desea.


17. In this problem you are to compare reading a file using a single-threaded file server
and a multithreaded server. It takes 12 msec to get a request for work, dispatch it, and
do the rest of the necessary processing, assuming that the data needed are in the block
cache. If a disk operation is needed, as is the case one-third of the time, an additional
75 msec is required, during which time the thread sleeps. How many requests/sec can
the server handle if it is single threaded? If it is multithreaded?

18.  What is the biggest advantage of implementing threads in user space? What is the
biggest disadvantage?

Se pueden crear y eliminar hilos de manera muy fáciles, las ejecuciones son más rápidas ya que el kernel no sabe de ellos.
Por ende los procesos crean y destruyen hilos de manera muy frecuente con la finalidad de ejecutar sus procesos.
No se necesitan traps al kernel para cambiar de hilos.

Sin embargo, ante las interrupciones una interrupcion de I/O de un hilo puede hacer que se bloqueen todos los procesos de un mismo
hilo, dejando hilos bloqueados cuando podrían ejecutarse sin problema, si solo se bloqueara el hilo que realizó la solicitud.

19.  In Fig. 2-15 the thread creations and messages printed by the threads are interleaved at
random. Is there a way to force the order to be strictly thread 1 created, thread 1 prints
message, thread 1 exits, thread 2 created, thread 2 prints message, thread 2 exists, and
so on? If so, how? If not, why not?

Si, mediante la función *thread_join*, cada hilo creado desde la 2da iteración esperaría al hilo anterior.

20.  In the discussion on global variables in threads, we used a procedure create global to
allocate storage for a pointer to the variable, rather than the variable itself. Is this es-
sential, or could the procedures work with the values themselves just as well?

1.  Consider a system in which threads are implemented entirely in user space, with the
run-time system getting a clock interrupt once a second. Suppose that a clock interrupt
occurs while some thread is executing in the run-time system. What problem might oc-
cur? Can you suggest a way to solve it?
1.  Suppose that an operating system does not have anything like the select system call to
see in advance if it is safe to read from a file, pipe, or device, but it does allow alarm
clocks to be set that interrupt blocked system calls. Is it possible to implement a
threads package in user space under these conditions? Discuss.
1.  Does the busy waiting solution using the turn variable (Fig. 2-23) work when the two
processes are running on a shared-memory multiprocessor, that is, two CPUs sharing a
common memory?
1.  Does Peterson’s solution to the mutual-exclusion problem shown in Fig. 2-24 work
when process scheduling is preemptive? How about when it is nonpreemptive?
1.  Can the priority inversion problem discussed in Sec. 2.3.4 happen with user-level
threads? Why or why not?
1.  In Sec. 2.3.4, a situation with a high-priority process, H, and a low-priority process, L,
was described, which led to H looping forever. Does the same problem occur if round-
robin scheduling is used instead of priority scheduling? Discuss.
1.  In a system with threads, is there one stack per thread or one stack per process when
user-level threads are used? What about when kernel-level threads are used? Explain.

1.  When a computer is being developed, it is usually first simulated by a program that
runs one instruction at a time. Even multiprocessors are simulated strictly sequentially
like this. Is it possible for a race condition to occur when there are no simultaneous
events like this?
1.  The producer-consumer problem can be extended to a system with multiple producers
and consumers that write (or read) to (from) one shared buffer. Assume that each pro-
ducer and consumer runs in its own thread. Will the solution presented in Fig. 2-28,
using semaphores, work for this system?
1.  Consider the following solution to the mutual-exclusion problem involving two proc-
esses P0 and P1. Assume that the variable turn is initialized to 0. Process P0’s code is
presented below.
/* Other code */
while (turn != 0) { } /* Do nothing and wait. */
Critical Section /* . . . */
turn = 0;
/* Other code */
For process P1, replace 0 by 1 in above code. Determine if the solution meets all the
required conditions for a correct mutual-exclusion solution.
1.  How could an operating system that can disable interrupts implement semaphores?
2.  Show how counting semaphores (i.e., semaphores that can hold an arbitrary value) can
be implemented using only binary semaphores and ordinary machine instructions.
1.  If a system has only two processes, does it make sense to use a barrier to synchronize
them? Why or why not?
1.  Can two threads in the same process synchronize using a kernel semaphore if the
threads are implemented by the kernel? What if they are implemented in user space?
Assume that no threads in any other processes have access to the semaphore. Discuss
your answers.
1.  Synchronization within monitors uses condition variables and two special operations,
wait and signal. A more general form of synchronization would be to have a single
primitive, waituntil, that had an arbitrary Boolean predicate as parameter. Thus, one
could say, for example,
waituntil x < 0 or y + z < n
The signal primitive would no longer be needed. This scheme is clearly more general
than that of Hoare or Brinch Hansen, but it is not used. Why not? (Hint: Think about
the implementation.)
1.  A fast-food restaurant has four kinds of employees: (1) order takers, who take custom-
ers’ orders; (2) cooks, who prepare the food; (3) packaging specialists, who stuff the
food into bags; and (4) cashiers, who give the bags to customers and take their money.
Each employee can be regarded as a communicating sequential process. What form of
interprocess communication do they use? Relate this model to processes in UNIX.
1.  Suppose that we have a message-passing system using mailboxes. When sending to a
full mailbox or trying to receive from an empty one, a process does not block. Instead,
it gets an error code back. The process responds to the error code by just trying again,
over and over, until it succeeds. Does this scheme lead to race conditions?
1.  The CDC 6600 computers could handle up to 10 I/O processes simultaneously using
an interesting form of round-robin scheduling called processor sharing. A process
switch occurred after each instruction, so instruction 1 came from process 1, instruc-
tion 2 came from process 2, etc. The process switching was done by special hardware,
and the overhead was zero. If a process needed T sec to complete in the absence of
competition, how much time would it need if processor sharing was used with n proc-
esses?
1.  Consider the following piece of C code:
void main( ) {
fork( );
fork( );
exit( );
}
How many child processes are created upon execution of this program?
1.  Round-robin schedulers normally maintain a list of all runnable processes, with each
process occurring exactly once in the list. What would happen if a process occurred
twice in the list? Can you think of any reason for allowing this?
1.  Can a measure of whether a process is likely to be CPU bound or I/O bound be deter-
mined by analyzing source code? How can this be determined at run time?
1.  Explain how time quantum value and context switching time affect each other, in a
round-robin scheduling algorithm.
1.  Measurements of a certain system have shown that the average process runs for a time
T before blocking on I/O. A process switch requires a time S, which is effectively
wasted (overhead). For round-robin scheduling with quantum Q, give a formula for
the CPU efficiency for each of the following:
(a) Q = ∞
(b) Q > T
(c) S < Q < T
(d) Q = S
(e) Q nearly 0
1.  Five jobs are waiting to be run. Their expected run times are 9, 6, 3, 5, and X. In what
order should they be run to minimize average response time? (Your answer will
depend on X.)
1.  Five batch jobs. A through E, arrive at a computer center at almost the same time.
They have estimated running times of 10, 6, 2, 4, and 8 minutes. Their (externally de-
termined) priorities are 3, 5, 2, 1, and 4, respectively, with 5 being the highest priority.
For each of the following scheduling algorithms, determine the mean process
turnaround time. Ignore process switching overhead.
(a) Round robin.
(b) Priority scheduling.
(c) First-come, first-served (run in order 10, 6, 2, 4, 8).
(d) Shortest job first.
For (a), assume that the system is multiprogrammed, and that each job gets its fair
share of the CPU. For (b) through (d), assume that only one job at a time runs, until it
finishes. All jobs are completely CPU bound.
1.  A process running on CTSS needs 30 quanta to complete. How many times must it be
swapped in, including the very first time (before it has run at all)?
1.  Consider a real-time system with two voice calls of periodicity 5 msec each with CPU
time per call of 1 msec, and one video stream of periodicity 33 ms with CPU time per
call of 11 msec. Is this system schedulable?
1.  For the above problem, can another video stream be added and have the system still be
schedulable?
1.  The aging algorithm with a = 1/2 is being used to predict run times. The previous four
runs, from oldest to most recent, are 40, 20, 40, and 15 msec. What is the prediction of
the next time?
1.  A soft real-time system has four periodic events with periods of 50, 100, 200, and 250
msec each. Suppose that the four events require 35, 20, 10, and x msec of CPU time,
respectively. What is the largest value of x for which the system is schedulable?
1.  In the dining philosophers problem, let the following protocol be used: An even-num-
bered philosopher always picks up his left fork before picking up his right fork; an
odd-numbered philosopher always picks up his right fork before picking up his left
fork. Will this protocol guarantee deadlock-free operation?
1.  A real-time system needs to handle two voice calls that each run every 6 msec and con-
sume 1 msec of CPU time per burst, plus one video at 25 frames/sec, with each frame
requiring 20 msec of CPU time. Is this system schedulable?
1.  Consider a system in which it is desired to separate policy and mechanism for the
scheduling of kernel threads. Propose a means of achieving this goal.