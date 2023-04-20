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
tool like the UNIX od program. (Hint: How you do sthis will depend upon what the OS
allows. One trick that may work is to create a directory on a USB stick with one oper-
ating system and then read the raw device data using a different operating system that
allows such access.

## Chapter 2

