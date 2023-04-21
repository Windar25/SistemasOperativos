# PROCESSES AND THREADS

Ahora vamos a ver en detalle como un sistema operativo 
está diseñado y construido.
Un proceso es una abstracción de como correr un programa.
Es la abstracción más antigua y más importante que el sistema
operativo provee.

Permite el diseño concurrente incluso cuando solo se tenga una CPU
disponible, transforma una sola CPU a muchas CPUS virtuales. Sin
el proceso de abstraction las computadoras modernas no existirian.

Vamos entrar en detalle sobre los procesos y sus hermanos, los hilos o threads.

## 2.1 PROCESSES
---

Las computadoras pueden hacer muchas cosas al mismo tiempo, por ejemplo.
Consideremos un servidor web, le llegan solicitudes de todas partes 
pidiendo páginas web. Cuando llega la solicitud, el servidor revisa
que la página se encuentre en la cache, si se encuentra, la envía de vuelta
sino se realiza una solicitud en el disco. Esta solicitud en el disco
demora mucho, por lo que mientras se espera una respuesta a esta solicitud
muchas otras llegan de parte de las páginas web. Es posible que los primeros discos 
apunten a los más antiguos antes de resolver la primera solicitud.

Otro ejemplo se puede dar a la hora de prender una CPU, donde muchos
procesos son iniciados en secreto(para esperar emails, esperar actualizaciones
del antivirus, escribiendo y haciendo backups de el USB) mientras el usuario navega 
en internet. Para esto se realiza la multiprogramación,
la cual soporta múltiples procesos simultaneamente.

El paralelismo se realiza hardware de los multiproccesor systems(el cual tiene 2 o más CPUs
compartiendo la misma memoria física).


### 2.1.1 The Process Model
---

En este modelo, todos los procesos de la computadora, se organizan en 
un numero de procesos secuenciales. Un proceso es sólo una instancia 
de un programa en ejecución, incluyendo los valores actuales del 
contador de programa, registros y variables. En realidad, la CPU cambia
de proceso en proceso.  Para entenderlo mejor veamos que son varios procesos
corriendo en (pseudo) paralelismo, los cuales tratan de seguir como 
trabaja el CPU cuando cambia rápidamente de un programa a otro.

Este cambio rápido se denomina multiprogramming.

En la figura 2-1(a) vemos un computadora con multiprogramming para 
4 programas en memoria, en la figura 2-1(b) vemos 4 procesos los cuales
tiene su propio flow de control, el cual tambien tiene su propio timer counter,
por lo que cuando cada proceso corra, sus logical program counters van
a ser cargados en el real program counter. Cuando este termina, el program
counter físico es guardado en el proceso del programm counter lógico de la memoria.

En la figura 2-1(c) vemos que los procesos van progresadon pero ninguno se
ejecuta continuamente.
 
![imagen2.1](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-1.png?raw=true)
En este capitulo vamos a asumir que solo habrá una CPU, asumiremos que
 no habrán multicores.

Al ir cambiando de proceso en proceso, la velocidad de cálculo no será uniforme,
incluso, probablemente será irrepetible. Por ende, los programas no se deben 
programar con suposiciones incorporadas sobre el tiempo. Consideremos un audio 
que se reproduce juntamente con un video. Como el audio debe empezar 
un poco más tarde que el vídeo, indica al servidor de vídeo que 
empiece a reproducir, y luego ejecuta un bucle inactivo 10.000 
veces antes de reproducir el audio. Si la CPU realiza otros procesos
durante el bucle inactivo, el audio probablemente no corra correctamente 
y se verá desfasado junto al video. En estos casos deben tomarse medidas especiales
para garantizar que estos procesos cumplan sus requisitos de tiempos críticos.

Aunque, usualmente los programas no se ven afectados por el multiprogramming
o alguna diferencia de procesos.

Imaginemos un ingeniero informático el cual va a preparar un pastel para
su pequeño hijo. Él tiene una receta y una cocina con todos los ingredientes
necesarios para preparar el pastel. En esta analogía, la receta es el programa
, el ingeniero informático es la CPU y los ingredientes son los input data.
El proceso es la actividad en la cual el cocinero, usando la receta y los ingredientes
va a preparar el pastel.

Ahora, imaginemos que le pica una avispa al informático, por ende el ingeniero recuerda 
en que parte de la receta se quedó(estado del proceso actual se guarda) y agarra un libro de primeros auxilios y comienza
a hacer lo que el libro dice. Vemos que el procesador cambia de un proceso(preparar el pastel)
a otro más importante(realizar primeros auxilios), cada uno en un diferente programa(receta y 
libro de primeros auxilios). Luego la picadura de la abeja cesa y el informático
vuelve a cocinar, continuando en el lugar donde lo dejó.

Es decir, el proceso es la actividad de algo, este tiene su programa,
su input, output y estado. Un único procesador puede cambiar entre
varios procesos, donde el algoritmo se encargará de determinar cuando
parar la ejecución de algún proceso y realizar otro. Es decir un programa es algo que
se encuentra en el disco, y no hace nada.

Si un programa se ejecuta 2 veces, este cuenta como 2 procesos. Por ejemplo, se puede imprimir 2 archivos simultanemente en 2 impresoras.
El hecho de que 2 procesos parezcan que ejecutan el mismo programa, no es muy relevante, se está ejecutando 2 procesos.
El sistema operativo puede compartir el codigo entre los 2, por lo que solo habrá una copia en memoria, 
pero esos detalles técnicos no quitan el hecho de que se están realizando 2 procesos.

### 2.1.2 Procces Creation

Se necesita una forma de crear y terminar procesos durante las operaciones.

Existen 4 eventos principales que producen la creación de procesos:

- Inicialización del sistema
- Ejecución de la llamada de creación de proceso por un procesos ya en ejecución.
- La solicitud de un usuario de crear un nuevo proceso.
- Inicialización de un batch job.

Cuando el sistema arranca se crean muchos procesos de los cuales un porcentaje se ejecuta en primer plano,
estos son los proceso que interactuan con el usuario y le realizan trabajos para él. Otros se ejecutan en segundo plano
pero no tienen relación con el usuario, sin embargo tienen funciones específicas.
Por ejemplo: aceptar llegadas de correos(los cuales saltan cuando llega un email).
Otros procesos en segundo plano se pueden usar para recibir solicitudes de paginas web.
Los procesos que permanecen en segundo plano para gestionar alguna actividad como el correo electrónico, We bpages, noticias, impresión, etc. se denominan daemons.

En UNIX se puede usar ps para listar los procesos, en Windows se puede usar el task manager.


Además de los procesos creados al arrancar el sistema, se pueden crear más procesos.
Un proceso en ejecución puede realizar system calls para crear nuevos procesos y terminar su trabajo.

La creación de procesos es útil cuando el trabajo a realizar se puede realizar en pequeños procesos relacionados pero que funcionan independientemente.
Por ejemplo, si se desea obtener una gran cantidad de datos de una network para luego procesarla, es conveniente crear un proceso que 
obtenga los datos y los coloque en un buffer compartido, mientras que un segundo proceso procesa los datos, para luego eliminar los elementos de dato.

En un multiproccesor permitir que cada proceso vaya en una CPU distinta puede acelerar el proceso.

En los sistemas UNIX basados en comandos que ejecutan X, el nuevo proceso toma el control de la ventan que inició.
En Windows, esta no tiene ventana, pero puede crear uno o más ventanas. Pero en ambos sistemas operativos el usuario puede tener varias ventanas abiertas.


La otra situación para crear procesos es en el batch system. Imaginemos una cadena de tiendas y su manejo de almacenes, donde los usuario pueden ingresar lotes de trabajo al sistema.
Cuando el sistema operativo decide que tiene los recursos necesarios para realizar otro trabajo, este crea un nuevo proceso y ejecuta el siguiente proceso de la cola.

Técnicamente un nuevo proceso se crea cuando otro proceso llama al system call de creación de proceso. Cuando el sistema operativo crea un nuevo proceso indica directa o indirectamente qué programa lo va a ejecutar.
En UNIX solo se pueden crear nuevos procesos con el fork, donde el proceso padre y el proceso hijo terminan siendo idénticos menos con el pid.
Por ejemplo, cuando un usuario ingresa el comando "sort" en el shell. El shell crea un proceso hijo y el hijo ejecuta el sort. 
La razon para esta forma de ejecutar procesos es pra permitir al hijo manipular el file descriptor después del fork, pero antes del execve para realizar la redireccion del standard input, standard output y standard error.

Por otro lado, en Windows, la función CreateProcess se encarga de crear el oricesi y cargar el programa correcto en el proceso.
Esta llamada tiene 10 parámetros. Windows tiene otras 100 funciones más para manejar y sincronizar procesos.

En UNIX y en Windows después de crear un proceso, el padre y el hijo tienen distintos espacios de memoria. Se vuelven independientes.
El hijo debe tener la memoria del padre, por lo que se copia todo lo del padre para dárselo al hijo, pero las direcciones de memoria de ambos son distintas.

### 2.1.3 Process Termination
---
Una vez se cree un proceso este comienza a ejecutarse y hace lo que tenga que hacer, pero estos procesos también deben terminarse, existen forman de terminar procesos:
#### Normal exit (voluntary)
  Muchos procesos terminan simplemente por que ya hicieron su trabajo.
  Por ejemplo cuando el compilador termina de compilar un programa le indica esto al sistema operativo mediante la call exit, la cual es ExitProcess en Windows.
  Muchos programas también tiene esta función. 

#### Error exit (voluntary)
Otra forma de terminación es porque el proceso encontró un error fatal.
Por ejemplo, si ejecutamos el comando cc foo.c
Para complilar el programa foo.c, si este no existe el compilar simplemente dirá esto y dará un exit.

Usualmente programas interactivos de pantalla no mandan un exit, sino que crean un pop up indicando que hay algún error. 


#### Fatal error (involuntary)
Esta terminación consta en un error causado por el proceso, un bug del 
programa. Por ejemplo, ejecutar una instrucción ilegal, referirse a un
 espacio de memoria no existente o dividir por cero. En UNIX un proceso 
 puede decirle al sistema operativo que desea manejar los errores por sí mismo
 en cuyo caso el programa se interrumpe en lugar de terminarse al encontrar un error.

#### Killed by another process (involuntary)

El proceso puede terminar si es que se ejecuta alguna system call indicando
al sistema operativo que se debe matar algún proceso. En UNIX esta call es 
kill, en Win32 es TerminateProcess. En ambos casos el kiler debe tener la autorización
de matar al otro proceso. En algunos sistemas operativos cuando un proceso 
muere, todos los procesos que creo también mueren. Pero esto no 
pasa ni en UNIX ni en Windows.

### 2.1.4 Process Hierarchies

En algunos sistemas cuando un proceso padre crea un proceso hijo, estos
siguen relacionados de alguna forma. El proceso hijo puede crear más procesos, 
creando una jerarquía de procesos. Un proceso puede tener solo un padrea, 
pero muchos más hijos.

En UNIX un proceso y todos sus hijos forman un grupo. Cuando un usuario crea una señal 
para el teclado, esta señal se envía a todo un grupo de procesos asociados con el teclado.
Individualmente, cada proceso puede captar la señal, ignorarla o tomar la acción por defecto,
 que es ser eliminado por la señal.

 Otro ejemplo es el arranque de UNIX. Un proceso especial llamado "init"
 es presente es esta etapa. Cuando la computadora arranca, esta función 
 lee un archivo viendo cuántas terminales existentes hay. Luego forkea un nuevo proceso
 por cada terminal. Este proceso es para esperar a alguien para loggearse. 
 Si alguien se loggea el proceso de loggin ejecuta el shell para poder aceptar comandos.
 Este comando permite crear más procesos, entonces todos los procesos del sistema pertenecen a un
 único arbol el cual tiene a init como raíz.

 Windows no tiene este concepto de jerarquía de procesos, todos los procesos
 son iguales, solo existe jerarquía de procesos cuando se crea un proceso, pues el 
 padre tiene un token especial que se usa para controlar al hijo. Igualmente este token
 se puede pasar a otro proceso, destruyendo la jerarquía. 
 Los procesos en UNIX no pueden desheredar a sus hijos.

 ### 2.1.5 Process States

Como cada proceso es indendiente, este tiene su propio timer counter
y su estado interno, además que muchas veces un proceso necesita
interactuar con otro. Este generará un output que para otro será un
input.

Un ejemplo en el shell:

    cat chapter1 chapter2 chapter3 | grep tree

El primer proceso cat, concatena 3 archivos, el segundo proceso grep
selecciona todas las lineas que contengan la palabra tree.
Dependiendo de la velocidad de los 2 procesos, puede suceder que grep
esté listo para ejecutarse o que no haya un input esperando. En el 
último caso, este se bloqueará hasta que el input esté disponible.

Es posible que un proceso que esté listo para ejecutarse sea detenido
pues el CPU está ejecutando otro proceso. El motivo de la detención puede ser
por un problema no depende del sistema y en el otro caso sí.

Existen 3 estados en los que un programa puede estar:

- Ejecutándose(usa la CPU en cada instante)
- Listo para ejecutar(temporalmente detenido pues otro proceso se está ejecutando)
- Bloqueado(imposibilitado de ejecutarse hasta que suceda algún evento externo)
  
![imagen2.2](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-2.png?raw=true)

La transición 1 ocurre cuando el sistema operativo se da cuenta que el proceso no puede continuar.
El algunos sistemas operativos se puede ejecutar la system call pause para entrar al estado de
bloqueo, en otros sistemas como UNIX cuando se trata de leer del pipe y no hay información el sistema se bloquea.

Las transiciones 2 y 3 se dan por el process scheduler. La transición 2 ocurre cuando el scheduler
decide que el proceso en curso ha sido ejecutado por suficiente tiempo y es tiempo para que otro
proceso tome el CPU. La transición 3 se da cuando todos los demás procesos 

La transición 3 se produce cuando todos los demás procesos han tenido 
su parte justa y es el momento de que el primer proceso consiga que la
 CPU vuelva a funcionar.

El concepto de scheduling consiste en decidir qué programas deben ejecutarse
y cuánto tiempo deben ejecutarse. 

Muchos algoritmos han tratado de ver la eficiencia para manejar los procesos.

La transición 4 ocurre cuando sucede un evento externo por el cual estaba
esperando un proceso. Si no hay ningún otro proceso en ejecución en ese instante, se activará la transición 3 y el proceso comenzará a ejecutarse.
Sino, se quedará esperando en ready hasta que la CPU esté disponible.

Algunos procesos corren programas que reciben inputs del usuario, otros son parte del sistema que manejan solicitudes de archivos o manejan detalles
del disco. Cuando el disco realiza alguna interrupcion el systema detiene el proceso actual y ejecuta el proceso del disco.Entonces respecto a interrupciones
podemos pensar acerca de procesos de usuario, procesos del disco, procesos de la terminal, los cuales se bloquean cuando esperan que suceda algo.
(ejem del teclado cuando se escribe alguna tecla). Todo el manejo de interrupciones, incluyendo detalles acerca del iniciar y detener procesos están guardados en el 
scheduler(planificador), el cual no tiene mucho código.  El resto del sistema operativo está estructurado en forma de procesos. 

![figure2.3](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-3.png?raw=true)

### 2.1.6 Implementation of Processes
---

Para implementar el modelo de procesos, el sistema operativo maneja una tabla(un arreglo de estructuras), llamada la tabla de procesos, con una entrada por
proceso(algunos llaman a estas entradas process control blocks). Esta entrada contiene información importante acerca del proceso como el estado, el program
counter, el stack pointer, memory allocation, el estado del file abierto, 
su información contable y de calendario y todo lo demás sobre el proceso que debe guardarse cuando el proceso pasa del estado en ejecución al 
estado listo o bloqueado, de modo que pueda reiniciarse más tarde como si nunca se hubiera detenido.

La figura 2.4 muestra algunas llaves en un sistema tipico. Los campos de la primera columna están relacionados al manejo de procesos, los otros 
se refieren al manejo de memoria y de archivos. Hay que tener en cuenta que los campos exactos de la tabla de procesos dependen en gran medida 
del sistema, pero esta figura da una idea general del tipo de información necesaria.

![figure2.4](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-4.png?raw=true)

Existe un lugar llamado interrupt vector el cual está asociado con cada clase
de dispositivo I/O. Este contiene la direccion de los procesos del
I/O que realiza la interrupción.
Supongamos que el proceso 3 se está ejecutando y ocurre una 
interrupción de parte del disco. Se guardan los datos respectivos
en el stack mediante el interrupt hardware. Luego la computadora salta
a la dirección especificada en el interrupt vector. Luego todo lo demás
está en manos del software y de los procesos del interruptor.

Todas las interrupciones comienzan guardando los registros, a menudo 
en la entrada de la tabla de procesos para el proceso actual. A 
continuación, la información introducida en la pila por la 
interrupción se elimina y el puntero de la pila se establece 
para apuntar a una pila temporal utilizada por el controlador 
del proceso. El proceso de guardar los registros y cambiar el stack
pointer no se pueden realizar en lenguajes de alto nivel, sino que se realizan
en pequeñas rutinas de lenguaje ensamblador. 
Luego de realizar esta rutina se llama a la función de C para que siga
haciendo su trabajo para ese tipo especifico de interrupt. Cuando se termina el trabajo,
el scheduler que se debe realizar ahora. Luego se le da control al
codigo de lenguaje ensamblador para cargar los registros y la memoria
para el nuevo proceso y que la comience ejecutar. El manejo de interrupciones
y el planificador se pueden ver en la imagen 2.5(os detalles varían
de sistema en sistema).

Un proceso puede interrumpirse miles de veces durante su ejecución
pero la idea principal es que después de cada interrupción el proceso
debe retornar exactamente donde se quedó.

### 2.1.7 Modeling Multiprogramming

Cuando se utiliza la multiprogramación, se puede mejorar la utilización de la CPU.

Visto de una forma, si un proceso promedio ocupa el 20% de la CPU, se podrían ejecutar 5
procesos en memoria para que esta esté llena. Esto es poco realista pues
asume que estos 5 procesos nunca estará esperando entradas I/O.

![figure2-5](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-5.png?raw=true)

Es mejor ver la CPU desde un modelo probabilistico. Supongamos que un proceso espera
una fracción p de su tiempo para que un I/O se complete. Si tenemos
n interrupciones, entonces:

CPU utilization = 1 - p^n

La figura 2.6 nos muestra el uso de la CPU en función de n, el cual
se llama grado de multiprogramación.
![figure2.6](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-6.png?raw=true)

De la figura se deduce claramente que si los procesos pasan el 80% 
de su tiempo esperando la E/S, al menos 10 procesos deben estar 
en memoria a la vez para que el desperdicio de CPU sea inferior al
10%. Al darnos cuenta que existen muchos procesos que esperan por el 
ingreso de datos del usuario, nos damos cuenta que los procesos no tiene
un tiempo de uso de interrupciones del 80%. Pero en servidores que 
usan bastante los discos duros, sí es usual, pueden tener este porcentaje
o más.

Este modelo asume que se pueden correr n procesos en memoria, donde se pueden tener
3 ejecutandose y 2 en memoria. Sin embargo en una única CPU, no podemos tener
3 procesos al mismo tiempo, tendríamos procesos listos para ejecutarse
que se encuentra a la espera de la disponibilidad del CPU, por lo tanto,
los procesos no son independientes. Se puede realizar un mejor modelo 
con la queueing theory, pero el punto que mostramos aún se mantiene válido solo que 
con pequeñas diferencias respecto al gráfico.

Por otro lado, el fin de este gráfico no es ser especifico, sino de 
dar una aproximación del rendimiento de la CPU. 

Supongamos que tenemos una CPU con 8 GB de memoria, donde el SO y sus tablas usan
2GB y cada programa del usuario usa 2GB. Este tamaño de memoria permite tener 3 programas
del usuario abiertos. Con un rendimiento del 80% de espera de I/0, tenemos un
uso del CPU del 1 - (0.8)³ el cual es alrededor del 49%. Si le agregamos
otra memoria de 8GB tenemos una posibilidad de 7 caminos de multiprogramación,

el cual aumenta el rendimiento de la CPU a un 79%. En otras palabras las 8GB 
adicionales mejoran el rendimiento en un 30%.

Añadiendo otros 8GB, el uso del CPU aumenta de 79% a 91%. Con este modelo
los usuarios pueden ver que la primera inversión es mejor que la segunda.

## 2.2 THREADS

En los sistemas operativos tradicionales cada proceso tiene un solo
espacio de memoria y un único hilo de control. Sin embargo, en muchas
situaciones es posible tener muchos hilos de control trabajando
en el mismo espacio de memoria, corriendo de forma casi paralela, como si
fueran procesos separados(excepto por el espacio de memoria compartido).

### Thread Usage

¿Por qué querría alguien tener una especie de proceso dentro de otro proceso?

Hay muchas razones para tener esos miniprocesos llamados threads(hilos).
La principal razón para tener hilos es que en varias aplicaciones, múltiples actividades
van en una sola. Algunas de ellas se pueden bloquear de vez en cuando.
Dividir una aplicación en multiples hilos que corren de manera casi paralela
hacen al modelo mucho más simple.

Con los hilos ahora podemos tener entidades paralelas que compartan un mismo
espacio de memoria entre ellos. Esta habilidad es necesaria para ciertas
aplicaciones, las cuales si tuvieran múltiples procesos sin memoria
compartida, simplemente no podrían trabajar.

Otro argumento para tener hilos es debido a que son menos pesados que
los procesos, son más fáciles de crear y de destruir en comparación a los procesos.
En muchos sistemas crear un thread es mucho más rápido que crear un proceso,
Cuando el numero de threads necesarios necesita cambios dinamicos y 
rapidos, esta propiedad ayuda bastante.

Un tercer argumento sería el rendimiento. Los hilos no mejoran 
el rendimiento cuando todos ellos están ligados a la CPU, pero cuando 
hay una computación sustancial y también el I/O es sustancial, tener 
subprocesos permite que estas actividades se solapen, acelerando así 
la aplicación.

Finalmente, los hilos son muy útiles en sistemas con varias CPUs, donde
el real paralelismo es posible.

Por ejemplo, veamos un procesador de texto. Los procesadores de texto 
suelen mostrar el documento que se está creando en la pantalla con el 
mismo formato que aparecerá en la página impresa. Los cambios de línea y de 
página están en las posiciones correctas, por lo que el usuario puede
verlas y luego modificar el documento de texto si lo necesita(borrar
lineas que no aportan estéticamente al documento).

Imaginemos que el usuario está escribiendo un libro. El usuario puede
escribir todo en un mismo archivo, al igual que puede hacerlo separando
los archivos por capítulos, en este ultimo caso la edicion del libro
entero obligaría a tener que editar cada archivo de cada capítulo creado,
en vez de hacerlo en uno solo como sería el primer caso. Ahora, el autor
decide cambiar la primera línea de 600 página, luego decide buscar
una frase en el archivo en la página 600. El procesador de texto, 
está forzado a recargar el libro entero hasta la página 600, porque no
sabe cuál será la primera línea de la página 600 hasta que se procesen
todas las anteriores. Puede haber un retraso sustancial
antes de que pueda mostrarse la página 600, lo que provocaría 
la insatisfacción del usuario.

Los hilos pueden ayudar acá, supongamos que el procesador fue escrito
con un programa de 2 hilos. Un hilo interactúa con el usuario y el otro
ayuda recargando las páginas. Apenas se cambie la primera línea del texto, el
interactive thread le dice al thread de reinicio que reinicie el libro entero 
con los nuevos cambios. Mientras, el thread que interactue con el usuario
continua esperando alguna entrada del teclado o mouse y responde a comandos
simples como el scrolling, el otro thread está recargando las páginas siguientes
en el background. 

Algunos procesadores de textos manejan un tercer thread que se encarga de guardar
los cambios en el disco cada ciertos minutos para evitar que el usuario pierda
todo su trabajo en caso existan problemas con la CPU. Este tercer thread
maneja los backups en el disco sin interferir con los otros 2 threads.

![imagen2.7](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-7.png?raw=true)

Si solo tuvieramos un hilo, mientras se realice el backup, los comandos
del teclado y mouse serían ignorados hasta que el backup termine. 

Otra forma es que el mouse y el teclado puedan interrumpir el backup
del disco, pero esto nos llevaría a un modelo complejo de manejo de interrupciones.

Con 3 hilos, el modelo es mucho más simple.

Debe quedar claro que tener tres procesos separados no funcionaría 
aquí porque los tres hilos necesitan operar sobre el documento. Con 3 hilos
en vez de 3 procesos, se puede compartir la memoria y tener acceso a un
mismo documento mientras se edita, con 3 procesos esto no es posible.


Una situación analoga se puede dar con una hoja de cálculo, la cual
permite al usuario tener una matriz con los datos que él ha ingresado, además existen otros
elementos de la computadora que permiten al input data usar formulas complejas.
Cuando un usuario modifica una celda, otras celdas también puede modificarse, en el background
de los hilos está la recomputarización, además el interactive thread se encarga de permitir
otros cambios mientras la computadora está trabajando. De manera similar un 3er hilo
permite guardar backups en el disco. 

Otro ejemplo es un servidor para una web. Al servidor le llegan solicitudes de
páginas y este las devuelve al cliente. En las websites algunas páginas son accedidas
mediante otras páginas, por ejemplo, a la página de inicio de Sony se 
accede mucho más que a una página en lo más profundo del árbol que 
contenga las especificaciones técnicas de una cámara concreta. Para esto los servidores web
usan esto para mejorar su rendimiento, ellos guardan una colección de 
páginas concurridas en la memoria principal, para no tener que ir
al disco en cada momento, esta colección es la memoria caché.

Una forma de organizar los servidores web es la mostrada en la figura 2.8.
Acá un hilo, llamado el dispatcher, lee llamadas de trabajo de la network.
Después de examinar esta solicitudm escoge un worker thread inactivo y le
asigna la solicitud. Posiblemente escribiendo un puntero al 
mensaje en una palabra especial asociada a cada hilo. El dispatcher 
cambia el estado del worker thread de bloqued a ready.0

![imagen2.8](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-8.png?raw=true)

Cuando el worker comience a trabajar, revisará si la solicitud puede
ser resuelta con el caché asignado a las páginas web. Sino este
comienza a realizar una operación de lectura para obtener la página
del disco y se bloquea hasta que se complete la operación del disco.
Cuando se bloquea el hilo en la operación del disco, otro hilo es
escogido para ser ejecutado.

Este modelo permite al servidor ser escrito como una colección de 
hilos secuenciales. El programa de dispatch consiste en un loop infinito para
recibir solicitudes de trabajo y asignarlos a un worker. Cada código de los
workers consiste en un loop infinito de recibir las solicitudes del dispatcher
y revisar la web caché para ver si la página es presente. Si está se 
devuelve la página al cliente y el worker se blockea esperando una 
nueva solicitud. Sino se toma la página del disco, se retorna al cliente
y se bloque esperando una nueva solicitud.

En la Fig. 2-9 se muestra un esquema del código. Aquí, como en el 
resto de este libro, se asume que TRUE es la constante 1. Además, 
buf y page son estructuras apropiadas para contener una petición de 
trabajo y una página Web, respectivamente.

![imagen2.9](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-9.png?raw=true)

Consideremos como la web service pudo haber sido escrita sin hilos.
El loop principal del web server recibe la request, la examina y 
lo lleva a cabo hasta el final antes de coger el siguiente. Cuando
se realiza la espera para el disco, el servidor se encuentra inactivo
y no procesa ninguna otra request. Si el servidor está siendo ejecutado
en una sola máquina, el CPU se quedaría inactivo mientras el servidor
espera por la respuesta del disco. Estos servidores reciben muchas solicitudes
por segundo para procesar, por lo que los hilos son de gran ayuda para
el rendimiento de estos, pero cada hilo es programado secuencialmente en 
la mayoría de los casos.

Entonces hemos visto 2 diseños: una web server multihilos y una web server
con un único hilo. 

Supongamos que no se dispone de subprocesos, pero los diseñadores del 
sistema consideran inaceptable la pérdida de rendimiento debido a tener
solo un hilo. Si tenemos la posibilidad de tener una función read que
no bloquee, podríamos tener otro enfoque. Cuando llega una petición
el único hilo lo examina, si se puede solucionar con la caché, bien, sino
se inicia una operación de disco no bloqueante.

El servidor registra el estado de la petición actual en la tabla y luego
obtiene el siguiente evento, este puede ser una solicitud de nuevo
trabajo o una respuesta del disco sobre la operación anterior.
Si es un nuevo trabajo este se inicia, si es una respuesta del disco
se obtiene la información de la tabla y se procesa la respuesta.
Con I/O de disco sin bloqueo, una respuesta probablemente tendrá que
tomar la forma de una señal o interrupción. Se pierde el modelo de 
proceso secuencial que teniamos en los 2 primeros casos. El estado de
la computadora debe guardarse y recuperarse a detalle en la tabla
depues de cada cambio de trabajo por solicitudes entrantes. 
En efecto, estamos simulando los hilos y sus pilas a las malas.
Este diseño de andar guardando estados de donde se pueden realizar otros
proceso es llamado máquinas de estado finita. Las llamadas al sistema 
con bloqueo facilitan la programación y el paralelismo mejora el 
rendimiento.

El tercer enfoque logra un alto rendimiento a través del paralelismo, 
pero utiliza llamadas e interrupciones no bloqueantes y, por lo tanto,
 es difícil de programar. Estos modelos se resumen en la Fig. 2-10.

![imagen2.10](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-10.png?raw=true)


Otra solución a la que aportan los threads es en las aplicaciones que
procesan una gran cantidad de datos. Si se lee y escribe en bloques y
estas operaciones producen un bloqueo, esto dejaría a la CPU una perdida
de tiempo. Con los hilos, se pueden estructurar hilos para lectura, hilos
para procesar y hilos para escribir la información procesada.

El hilo de lectura leería la información y la pondría en un buffer, por otro lado,
el hilo de proceso tomaría la data del buffer, la procesaría y pondría el resultado
en el buffer de salida para que el hilo de output escriba este resultado
en el disco. En este punto, el input, output y proceso pueden darse al mismo tiempo.
Porsupuesto, este modelo solo funciona si la system call bloquea el 
hilo donde se está trabajando, no el proceso entero.

### 2.2.2 The Clasical Thread Model

El modelo de proceso está basados en 2 conceptos: 
- agrupación
-  ejecución de recursos

#### ¿Qué es un proceso?
Una forma de ver un proceso es como una manera de agrupar 
recursos relacionados. Un proceso tiene un espacio de direcciones que 
contiene texto y datos del programa, así como otros recursos.
Estos recursos pueden incluir archivos abiertos, procesos hijos, alarmas,
manejadores de señales, información contable, etc. Si juntamos todo esto
en forma de proceso, se puede manejar más fácilmente. El otro concepto que tiene un proceso es el de 
hilo de ejecución, normalmente abreviado como
simplemente hilo. 
#### ¿Qué es un hilo?
El hilo tiene un program counter que guarda la información
sobre qué instrucción debe ejecutarse después. Este tiene registros que
mantienen sus variables de trabajo actuales. Tiene una pila que contiene 
el historial de ejecución, con un frame por cada procedimiento llamado
pero aún no devuelto. Un thread debe ejecutarse en un proceso, no es lo
mismo un thread y un proceso. Los procesos se utilizan para agrupar 
recursos; los hilos(threads) son las entidades programadas para su ejecución 
en la CPU.

Los hilos agregan al modelo de procesos, la posibilidad de soportar
múltiples ejecuciones en el mismo ambiente de proceso, en gran medida 
independientes entre sí. Tener muchos threads ejecutándose de forma paralela en un mismo proceso
es algo análogo a tener multiples procesos siendo ejecutados de forma 
paralela en una misma computadora. En el primer caso, los procesos
comparten direcciónes de memoria y otros recursos. En el segundo caso, 
los proceso comparten memoria física, discos, impresora y otros recursos.

Como los hilos tienen algunas de las propiedades de los procesos, a 
veces se denominan procesos ligeros. El término de multithreading es usado
para decir que un proceso puede soportar varios hilos. Algunas CPU tienen
soporte directo de hardware para varios hilos y permiten cambiar de hilo en
nanosegundos.

En la figura 2-11(a) vemos 3 proceso tradicionales. Cada proceso 
tiene su propia dirección de memoria y un único hilo de control.
Por otro lado, en la figura 2-11(b) vemos un único proceso con 3 hilos de control.
En ambos casos tenemos 3 hilos, en la figura 2-11(a) cada uno de ellos
trabaja en un espacio de memoria diferente, mientras que en la figura b los 3 
comparten espacio de memoria.

![imagen2.11](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-11.png?raw=true)

Cuando un proceso de multithreading es ejecutado en una single-CPU system,
los hilos toman turnos para ejecutarse. En la figura 2-1 vemos como el proceso de 
multiprogramación funciona. Al alternar entre varios procesos se da
la sensación de tener procesos secuenciales separados ejecutandose en paralelo.
Pasa algo parecido con los multihilos. La CPU cambia entre hilos
dando la sensación de que se están ejecutando paralelamente. 
Con tres hilos de cálcula en un proceso, los hilos parecerían que se están 
ejecutando en paralelo cada uno en una CPU con un tercio de la velocidad real del CPU.

Los distintos hilos de un proceso no son tan independientes como los procesos.
Cada hilo maneja la misma dirección de memoria, por lo que también comparten
variables globales. 

Dado que cada hilo puede acceder a cualquier dirección de memoria 
dentro del espacio de direcciones del proceso, un hilo puede leer, 
escribir o incluso borrar la pila de otro hilo. No existe la protección
entre hilos, dado que, es imposible y no debe ser necesario. Dado que a diferencia
de los distintos procesos, un solo proceso solo le pertenece a un usuario, quien 
puede crear multiples hilos de tal manera que ellos copeeren y no se saboteen.

Además de compartir espacios de memoria, los hilos pueden compartir archivos
abiertos, procesos hijo, alarmas, señales como se ve en la figura 2-12. Entonces
la organización mostrada en la figura 2-11(a) se usaría cuando los 3 procesos
no están relacionados, mientras que lo mostrado en la figura 2-11(b) es
apropiada cuando los 3 hilos son parte de un mismo trabajo y están trabajando
activamente y en conjunto entre sí.

![imagen2.12](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-12.png?raw=true)

Los elementos de la primera columna son propiedades del proceso, 
no del hilo. Por ejemplo, si un hilo abre un archivo, este file es 
visible para lo otros hilos del proceso y ellos pueden leer y escribir en
él. Esto es lógico dado que el proceso sería la unidad de manejo de recurso,
no el hilo. Si cada hilo tuviera su propia dirección de memoria, archivos
abiertos, alarmas, pendiente, etc, estos serían procesos separados.
Lo que queremos lograr con el concepto de thread , es la habilidad 
para tener múltiples hilos en ejecución  para compartin un conjunto de recursos
con la finalidad de que trabajen en conjunto de manera cercana para
realizar algunas tareas.

Como un proceso tradicional, el thread puede tener varios estados:
en ejecución, bloqueado, listo o terminado. Un hilo en ejecución está usando
 la CPU y está activa. Por otro lado, un hilo bloqueado está esperando
 algún evento que o desbloquee. Por ejemplo, cuando un hilo realiza
 una system call para leer del teclado, este es bloqueado hasta que
 se reciba un input de tipeo. Un hilo puede bloquearse esperando a que
  ocurra algún evento externo o a que otro hilo lo desbloquee. Un hilo
 listo está programado para ejecutarse y lo hará en cuanto llegue su 
 turno. La transición entre estados de un hilo son las mismas que
 las que se tienen ilustradas en la figura2.2 sobre los procesos.

 Es importante entender que cada hilo tiene su propia stack, como se ve en la
 figura 2.13. Cada pila de hilo contiene un frame por cada proceso que 
 ha sido llamado pero aún no ha sido devuelto. Este frame contiene las variables
 locales del proceso y la dirección de retorno que se usará cuando el proceso
 termine. Por ejemplo, si el proceso X llama al proceso Y y este luego llama a 
 Z, cuando Z está en ejecución los frames para X, Y y Z estarán en el stack.
 Por lo general, cada hilo llamará a procedimientos diferentes y, 
 por tanto, tendrá un historial de ejecución distinto. Por ello es que 
 cada hilo necesita su propia stack.

![imagen2.13](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-13.png?raw=true)

Cuando los multihilos están presentes, los procesos usualmente con un
único hilo presente son capaces de crear a otros hilos llamando
a la libreria de procesos *thread_create*. Un parámetro a thread 
create especifica el nombre de un procedimiento para que el nuevo 
hilo se ejecute. Si no es necesario(o no es posible) especificar nada
acerca del espacio de memoria del nuevo hilo creado, este automaticamente
se ejecuta dentro de la dirección de memoria del hilo que lo creó.
Aveces los hilos tienen jerarquías con una relación padre-hijo, pero
usualmente estas relaciones no existen, todos los hilos son iguales.
Con o sin relación jerárquica, al hilo creador se le suele devolver 
un identificador de hilo que nombra al nuevo hilo. 

Cuando un hilo ha terminado su trabajo, puede salir llamando a un 
procedimiento de biblioteca, por ejemplo, thread exit. Entonces 
desaparece y deja de ser programable. En algunos sistemas de hilos, 
un hilo puede esperar la salida de otro hilo (específico) llamando a 
un procedimiento, por ejemplo, *thread_join*. Este procedimiento bloquea 
el hilo que llama hasta que un hilo (específico) haya salido. En este 
sentido, la creación y terminación de hilos es muy parecida a la 
creación y terminación de procesos.

Otra call de los hilos es thread_yield, el cual permite a un hilo dejar
la CPU voluntariamente para permitir que otro hilo se ejecute. Esta 
llamada es importante porque no existe una interrupción del reloj para 
aplicar realmente la multiprogramación, como ocurre con los procesos.
Otras llamadas permiten que un hilo espere a que otro hilo termine 
algún trabajo, que un hilo anuncie que ha terminado algún trabajo, etc.
#### Dificultades 

Si bien los hilos son muy útiles, estos también introducen un numero
de multiplicaciones en el modelo de programación. Para comenzar, consideremos
los efectos de la UNIX fork system call. Si el proceso padre tiene muchos
hilos, ¿el hijo también debería tenerlos? sino, el proceso podría no 
funcionar corretamente, dado que todos ellos deberían ser esenciales.

De todas formas, si el proceso hijo tiene tantos hilos como el 
padre, ¿qué pasaría si un hilo del padre fue bloqueado en la read 
call, desde el teclado? ¿Los 2 hilos deberían bloquear en el teclado?
¿Uno en el padre y otro en el hijo? ¿Cuándo se escribe alguna línea, 
ambos hilos deberían obtener una copia de él? ¿Sólo el padre? ¿Sólo
el hijo? El mismo problema existe con las conexiones de red abierta.
 
Otro problema existe con el hecho de que los hilos comparten varias estructuras de 
datos. ¿Qué pasa si un hilo cierra un archivo mientras otro lo está leyendo?
Supongamos que un hilo notifica que hay muy poca memoria y comienza a 
asignar más memoria. A mitad de camino, se produce un cambio de hilo, 
y el nuevo hilo también se da cuenta de que hay muy poca memoria y 
también empieza a asignar más memoria. Probablemente se asigne más
memoria 2 veces. Estos problemas pueden resolverse con algo de 
esfuerzo, pero es necesario pensar y diseñar cuidadosamente para que 
los programas multihilo funcionen correctamente.

### 2.2.3 POXIS Threads

Para que sea posible escribir programas portables con hilos, el IEEE 
ha definido una norma para los hilos en la norma IEEE 1003.1c. El paquete
de hilos es llamado Pthreads. Varios sistemas de UNIX lo soportan. El 
estándar define unas 60 llamadas al sistema, sin embargo solo vamos
a mostrar algunas de ellas en la figura 2-14.

![imagen2.14](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-14.png?raw=true)

Todas las Pthreads tienen ciertas propiedades. Cada una de ellas tiene
un identificador, un grupo de registros(incluyendo el program counter) y
un set de atributos los cuales se guardan en una estructura. Los atributos 
incluyen el tamaño de la pila, los parámetros de programación y otros 
elementos necesarios para utilizar el hilo.

#### Thread calls

Se pueden crear nuevos hilos con la llamada *pthread_call*. El identificador
del nuevo hilo creado is retornado como valor de la función. Esta 
llamada es intencionadamente muy parecida a la llamada al sistema fork 
(excepto con parámetros), con el identificador del hilo jugando el 
papel del PID, principalmente para identificar hilos referenciados en 
otras llamadas.

Cuando un hilo ha terminado el trabajo al que fue asignado, este se puede
terminar con la llamada *pthread_exit*. Esta llamada detiene el hilo y 
libera su pila.

Algunas veces un hilo necesita que otro hilo termine su trabajo y salga antes
de poder continuar. El thread que está esperando llama a *pthread_join*
para esperar que un thread específico termine. El identificador del
hilo a esperar se da como parámetro.

Aveces sucede que un hilo no está bloqueado lógicamente, pero este ya
ha sido ejecutado suficiente tiempo y queremos que otro hilo se ejecute
en vez de este. Esto se puede lograr con la call *pthread_yield*. No existe 
tal llamada para los procesos porque la suposición allí es que los 
procesos son ferozmente competitivos y cada uno quiere todo el tiempo 
de CPU que puede conseguir. De todos modos, los hilos de un proceso
trabajan juntos y su código es escrito por el mismo programador, así que
aveces el programador va a querer darle la oportunidad a un hilo de ejecutarse.

Las 2 llamadas siguientes lidian con atributos. *Pthread_attr_init* crea la
estructura de atributos asociada a un hilo y la inicializa con los valores
de default. Estos valores(como la prioridad) pueden ser cambiados manipulando
los campos en la estructura del atributo.

Finalmente, *pthread_attr_destroy* elimina una estructura de atributos de un hilo,
liberando su memoria. Esto no afecta a los hilos que la usen, estos siguen
existiendo.

#### Codigo de ejemplo

Para entender mejor el manejo de los pthreads, veamos un ejemplo en la figura
2-15. Acá el programa principal itera NUMBER_OF_THREAS veces, creando
un nuevo thread en cada iteración. Si la creación del hilo falla, este
imprime un mensaje de error y sale. Después de crear todos los hilos, el
programa principal sale.

![imagen2.15](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-15.png?raw=true)

Cuando se crea un hilo, imprime un mensaje de una línea anunciándose a 
sí mismo y luego sale. El orden en que se intercalan los distintos 
mensajes es indeterminado y puede variar en ejecuciones consecutivas 
del programa. Las llamadas a Pthreads descritas anteriormente no son 
las únicas. 

### 2.2.4 Implementing Threads in User Space

Hay 2 lugares principales para implementar lo hilos: El espacio de usuario
y el kernel. La elección es algo controversial, además la implementación
hibrida es posible. Vamos a ver estos métodos y discutiremos sobre
sus ventajas y desventajas.

#### User space

El primer método consiste en colocar el paquete de hilos enteramente 
en el espacio de usuario. El kernel no sabe nada de ellos. En lo que 
respecta al núcleo, gestiona procesos ordinarios de un solo hilo.

##### Ventajas

La primera ventaja, es que un paquete de hilos a nivel de usuario 
puede implementarse en un sistema operativo que no admita hilos.
Con este enfoque, los hilos se implementan mediante una biblioteca.

Todas estas implementaciones tiene la misma estructura general, mostradas
en la figura 2-16(a). Los hilos se ejecutan en la parte superior
del sistema de ejecución, el cual es una colección de procesos que manejan
hilos. Ya hemos visto cuatro: pthread_create, pthread_exit, pthread_join 
y pthread_yield, pero normalmente hay más.

![imagen2.16](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-16.png?raw=true)

Cuando los hilos se manejan en el user space, cada proceso necesita
tener su propia y privada thread table para seguir los hilos de ese proceso.
Esa tabla es análoga a la tabla de procesos del kernel, excepto que sólo 
mantiene un registro de las propiedades por hilo(program counter del hilo,
stack pointer, registros, estados, etc). La thread table es manejada por 
el sistema en tiempo de ejecución. Cuando un hilo cambia de estado a
listo o bloqueado, la información necesaria para reanudar el hilo, se
guarda en la tabla de hilo, de forma parecida al kernel cuando guarda
información de los procesos en la tabla de procesos.

Cuando un hilo realiza una acción que puede provocar que este sea
bloqueado localmente, por ejemplo, esperar a otro hilo a que termine
su trabajo, este llama a un procedimiento del sistema en tiempo
de ejecución. Este procedimiento comprueba si el hilo debe ponerse
en estado bloqueado. Si debe bloquearse, este guarda los registros del hilo en la thread table, busca en la tabla algún hilo que este listo para ejecutarse
y recarga los registros de la máquina con los valores guardados del nuevo hilo. Tan pronto como el puntero de pila y el contador de programa se han intercambiado,
el nuevo hilo vuelve a la vida automáticamente. En caso la máquina tenga una instrucción para guardar todos los registros y otra para cargarlos todos, el cambio
de hilo completo puede realizar con pocas instrucciones. Realizar cambios de hilos de esta forma es mucho más rápido que recurrir al núcleo y es un argumento
a favor de los paquetes de hilo a nivel de usuario.

Sin embargo, hay una diferencia clave con los procesos. Cuando un hilo finaliza momentáneamente, es decir cuando llama *thread_yield*, el código de *thread_yield*
puede guardar la información del hilo en la propia tabla de hilos. Además puede llamar al programador de hilos para elegir otro hilo que ejecutar. El 
procedimiento que guarda el estado del hilo y el planificador son solo procedimientos locales, por lo que invocarlos es mucho más eficiente que
hacer una llamada al núcleo. Entre otras cosas, no se necesita ningún trap, ningún cambio de contexto, no es necesario vaciar la caché de memoria, 
etc. Esto hace que la programación de hilos sea muy rápida.

Existen otras ventajas de trabajar con threads en el user space, estos permiten tener personalizados sus propios algoritmos de planificación. Para algunas aplicaciones
por ejemplo, aquellas con un hilo garbage-collector. No tener que preocuparse de que un hilo se detenga en un momento inoportuno es una ventaja.

##### Desventajas

Sin embargo, los paquetes de hilos en el espacio de usuario también tienen desventajas. 

El primero de ellos es el problema de cómo se implementan las llamadas al sistema de bloqueo. Supongamos que un hilo lee del teclado antes de que se haya 
pulsado ninguna tecla. Dejar que el hilo realice la llamada al sistema es inaceptable, ya que esto detendría todos los hilos. Uno de los principales objetivos de 
tener hilos en primer lugar era permitir que cada uno utilizara llamadas de bloqueo, pero evitar que un hilo bloqueado afectara a los demás. Con llamadas al 
sistema bloqueantes, es difícil ver cómo se puede lograr fácilmente este objetivo. Se podrían cambiar las llamadas al sistema para que fueran no bloqueantes,
pero cambiar el sistema operativo no es el punto.

Existe otra alternativa en caso sea posible saber si una llamada se bloqueará. En varias versiones de UNIX existe una llamada al sistema select el cual
permite saber si una posible read se bloqueará. Cuando esta llamada está presente, la llamada read puede ser reemplazada por una nueva que primero
hace select y luego hace la llamada read solo si es segura(no se bloqueará). Si la llamada read va a bloquearse, entonces no se realiza la llamada y se da paso
a otro hilo a ejecutarse. La próxima vez que el sistema en tiempo de ejecución obtenga el control, podrá comprobar denuevo si la lectura ahora es segura.
Este enfoque requiere reescribir partes de la biblioteca de llamadas al sistema, esto es ineficiente, pero no hay muchas opciones. 
El código que se coloca alrededor de la llamada al sistema para realizar la comprobación se denomina jacket o wrapper.

Algo análogo al problema con las llamadas de bloqueo al sistema, es el problema con las páginas. Por el momento, basta decir que las computadoras pueden 
configurarse de tal manera que no todo el programa esté en la memoria principal. Si el programa salta a una instrucción que no está en memoria, se produce un 
fallo de página y el sistema operativo irá a buscar la instrucción que falta (y sus vecinas) al disco. Esto es un fallo de página. El proceso se bloquea
hasta que se encuentre la instrucción requerida y esta se lea. Si un hilo causa un fallo de página, el kernel, inconsciente de la existencia de hilos, 
bloquea todo el proceso hasta que se complete el I/O del disco, aunque otros hilos puedan ejecutarse.  

Una posible solución al problema de los hilos que se ejecutan eternamente es hacer que el sistema de ejecución solicite una señal de reloj(interrupción) una vez
por segundo para darle el control, pero esto es tosco y complicado de programar. Tener interrupciones en esta frecuencia no es siempre posible, y en caso lo sea
consume demasiado. 

Otro argumento contra los user-level threads es que los programadores usualmenten buscan tener hilos en las aplicaciones que bloqueen hilos constantemente,
por ejemplo, una web server multihilos. Estos hilos están constamente realizando llamadas al sistema. Una vez se halla realizado la llamada a trap,
supone más trabajo para el núcleo, cambiar de hilo si el anterior se ha bloqueado y hacer que el núcleo haga esto elimina la necesidad de realizar constamente
llamadas al sistema select para comprobar si es seguro realizar un read. En caso las aplicaciones estén totalmente ligadas a la CPU y rara vez se bloquean,
¿qué sentido tiene tener hilos?. Nadie propondría seriamente calcular los n primeros números primos o jugar al ajedrez utilizando hilos porque no se gana nada 
haciéndolo así.

### 2.2.5 Implementing Threads in the Kernel

Ahora, imaginemos que el kernel sabe cómo manejar hilos.  No se necesita ningún sistema de ejecución en cada uno, como se muestra en la Fig. 2-16(b). Sin embargo,
no existe una tabla de hilos en cada proceso. Cuando un hilo trata de crear otro hilo o destruir un hilo existente, este realiza una llamada al kernel, donde
se realiza alguna creación o destrucción actualizando la tabla de hilos del kernel.

La tabla de hilos del kernel maneja los registros, estados y demás información de cada hilo. La información es la misma que en los user-level threads, pero
ahora se quedan en el kernel, en vez del espacio de usuario(dentro del sistema en tiempo de ejecución). Esta información es un subconjunto de información que 
los núcleos tradicionales mantiene sobre sus procesos de un solo hilo, es decir, el estado del proceso. Además el núcleo tambien mantiene la tabla de proceso
tradicional para realizar un seguimiento de los procesos. 

#### Ventajas
Todas las llamadas que podrían bloquear un hilo se implementan como llamadas al sistema, con un coste considerablemente mayor que una llamada a un procedimiento
del sistema en tiempo de ejecución. Cuando un hilo es bloqueado, el kernel, como una opción, puede ejecutar cualquier otro hilo del mismo proceso si está listo, o
algún thread de un proceso distinto. Con los hilos a nivel de usuario, el sistema en tiempo de ejecución se mantiene ejecutando hilos desde su propio proceso
hasta que el kernel tome el control para sí(no hay hilos listos para ser ejecutados).

Debido al coste relativamente mayor de crear y destruir hilos en el kernel, algunos sistemas deciden reciclar sus hilos. Cuando un hilo se destruye este se marca
como no ejecutabe, pero sus estructuras de datos del kernel no se ven afectadas. Después cuando un nuevo hilo es creado, un viejo hilo es reactivado, ahorrando
algunos gastos generales. También se pueden reciclar en el nivel de usuario, pero  debido a que su manejo de hilo es mucho menos pesado, no tiene mucho sentido
implementarlo.

Los hilos del kernel no requieren nuevas llamadas al sistema no bloqueantes. Además si un hilo en un proceso causa un page fault, el kernel puede revisar si el proceso
tiene otros hilos en ejecución y continuar ejecutandolos mientras se espera para obtener la página requerida del disco. La desventaja de esto es el costo
que se tiene para el sistema, pues las operaciones de threads(creacion, terminacion, etc), se incurrirá en muchos más gastos generales.


#### Desventajas
Aunque los hilos del núcleo pueden resolver varios problemas, no los resuelven todos. Por ejemplo, ¿qué pasa cuando un proceso multihilo realiza un fork?
¿El nuevo proceso tendrá tantos hilos como el proceso anterior, o solo tendrá uno? En muchos casos, la mejor opción depende de lo que el proceso vaya a hacer
a continuación. Si va a llamar a exec para iniciar un nuevo programa, probablemente un hilo es la opción correcta, pero si continúa ejecutando, reproducir todos 
los hilos es probablemente lo mejor.

Otro problema son las señales, recordemos que las señales se envían a los procesos, no a los hilos, como en el modelo clásico. Cuando llegue alguna señal, ¿qué
hilo debe tomarlo? Posiblemente los hilos podrían registrar su interés en determinadas señales, de modo que cuando llegara una señal se entregaría al hilo que 
dijera que la quiere. Pero, ¿qué ocurre si dos o más hilos se registran para la misma señal? Éstos son sólo dos de los problemas que plantean los hilos, 
y hay más.

### 2.2.6 Hybrid Implementations

Se han investigador varias formas para poder combinar los hilos manejados a nivel de usuario y a nivel del kernel. Una forma es utilizar hilos a nivel del kernel
y luego multiplexar hilos a nivel de usuario en algunos o en todos como lo mostrado en la figura 2-17.

Cuando esto se usa, el programador puede determinar cuandos hilo puede usar a nivel de kernel y cuantos hilos a nivel de usuario puede multiplexar. Este modelo
trae mucha flexibilidad.

![imagen2.17](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-17.png?raw=true)

Con este enfoque, el núcleo sólo conoce los subproceso a nivel del núcleo y los programa. Varios de estos hilos, tienen muchos hilos a nivel de usuario
multiplexados encima de ellos. Estos hilos a nivel de usuario pueden ser creados, destruidos y programados como hilos a nivel de usuario de un proceso que se
 ejecutan en un sistema operativo sin capacidad multihilo. En este modelo, cada hilo a nivel de núcleo tiene un conjunto de hilo a nivel de usuario 
 que se turnan para utilizarlo.

 ### 2.2.7 Scheduler Activations
----
Aunque los hilos del kernel son mejores que los hilos a nivel de usuario
estos también son mucho más lentos. Varios investigadores han buscado
formas de mejorar la situación sin perder las buenas propiedades.

A continuación vamos a describir un enfoque ideado por Anderson et al.(1992)
llamado scheduler activations. Edler et al. (1988) y Scott et al. (1990) 
analizan trabajos relacionados.

#### Objetivos
----
Los objetivos del scheduler activation(activación del programador) son 
imitar la funcionalidad de los hilos del núcleo, pero con el mejor 
rendimiento y la mayor flexibilidad que suelen asociarse a los 
paquetes de hilos implementados en el espacio de usuario. 

En particular, usar hilos a nivel de usuario, no tienen que realizar 
llamadas de bloqueos especiales o revisar si es seguro realizar 
alguna system call. Sin embargo, cuando se bloquea un hilo en una 
llamada al sistema o en un fallo de página, debería ser posible ejecutar 
otros hilos dentro del mismo proceso, si hay alguno listo. 

La eficiencia se logra al evitar transiciones necesarias entre el espacio
de usuario y el espacio del kernel. Si un hilo se bloquea esperando a que 
hilo realice algo, por ejemplo, //revisaaaa no hay motivo para incluir al kernel, sabiendo 
sobre la sobrecarga del kernel-user transition. El sistema en ejecución del
espacio de usuario puede bloquear el hilo de sincronización y programar
uno nuevo por sí mismo.

Cuando se usan scheduler activations, el kernel asigna cierto número de
procesadores virtuales para cada proceso y deja que el sistema de 
ejecución (en espacio de usuario) asigne hilos a los procesadores. 
Este mecanismo puede ser usado en un multiprocesador donde los procesadores
virtual pueden ser CPUs reales. El numero de procesadores virtuales 
asignados a un proceso al inicio es uno, pero un proceso puede solicitar
por más e incluso puede retornar procesadores si es que no los necesita.
El kernel también puede retornar procesadores virtuales recién asignados
para asignarlos a proceso más necesitados.

La idea básica que hace funcionar este esquema es que cuando el kernel 
sabe que un hilo se ha bloqueado(por ejemplo, por haber ejecutado una
llamada al sistema bloqueante o por haber tenido un fallo de página), el kernel
notifica al sistema en tiempo de ejecución del proceso, pasando como a
la pila, el número de hilos en cuestión y una descripción del evento 
ocurrido.

La notificación se produce haciendo que el núcleo active el sistema en tiempo
de ejecución en una dirección de inicio conocida, algo análogo a una señal
en UNIX. Este mecanismo se denomina upcall.

Una vez activado, el sistema en tiempo de ejecución puede reprogramar 
sus hilos, normalmente marcando el hilo actual como bloqueado y 
tomando otro hilo de la lista de hilos listos, configurando sus 
registros y reiniciándolo. Luego cuando el kernel entienda que el thread
original puede ejecutarse denuevo(por ejemplo, la tubería desde la que 
intentaba leer ahora contiene datos, o la página sobre la que falló ha 
sido traída desde el disco), este hace otra upcall para informar
al sistema en tiempo de ejecución. El sistema en tiempo de ejecución
puede o reiniciar el hilo bloqueado en cuestión o agregarlo a lista
de hilos listos en ejecución.

Cuando se realiza algún interrupt de parte del hardware mientras un
hilo está ejecutando la CPU cambia a modo kernel. Si la interrupción
es causada por un evento que no es de interés para el proceso interrumpido,
como la finalización de I/O de otro proceso, cuando el manejador de 
interrupciones termine, devuelve el hilo interrumpido al estado en el que 
se encontraba antes de la interrupción. En cambio si el proceso está 
interesado en la interrupción, como la llegada de una página por uno
de los hilos del proceso, el hilo de interrupción no es reiniciado, sino
que es suspendido y el sistema en tiempo de ejecución es iniciado en una CPU
virtual, con el estado del hilo interrumpido en la pila. Es entonces
cuando el sistema en tiempo de ejecución decido qué hilo programar de
esa CPU: la interrumpida, la recién iniciado, o una tercera opción.

Un problema con las scheduler activations es la dependencia fundamental
de las upcalls, un concepto que viola la estructura inherente a cualquier
sistema por capas. Normalmente, la capa n ofrece ciertos servicios
a los que la capa n+1 puede llamar, pero la capa n no puede llamar a 
procedimientos de la capa n+1.
Las upcalls ignoran este principio fundamental.

//PREGUNTAR POR LAS SCHEDULER ACTIVATIONS

### 2.2.8 Pop-Up Threads

Los hilos son útiles en sistemas distribuidos. Un ejemplo es
como los mensajes entrantes(como las solicitudes para un servicio)
son manejados. El enfoque principal es tener un proceso o hilo que esté 
bloqueado en el receive system call esperando por un mensaje entrante.
Cuando un mensaje llega, este lo recibe, lo desempaqueta, 
examina su contenido y lo procesa.

Otro enfoque es que el receptor de mensajes provoque que el sistema
cree un nuevo hilo para que maneje el mensaje. Como hilo,
es llamado a pop-up thread como lo mostrado en la figura 2-18. Una ventaja
clave de los pop-up threads es que apenas se tenga un hilo completamente
nuevo, este no tendra ningún historial(registros, pilas, lo que sea) 
que recuperar. Cada uno empieza de cero y cada uno es idéntico a 
todos los demás. Esto permite crear un hilo de este tipo rápidamente.

El nuevo hilo recibirá el nuevo mensaje para procesarlo. El resultado
de usar hilos emergentes es que la latencia entre la llamada del mensaje
y el inicio del procesamiento puede hacerse muy corta.

![imagen2.18](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-18.png?raw=true)

Se necesita planificar bien si se desea usar pop-up threads. 
Por ejemplo, ¿en procesos se puede implementar?. Si el sistema
soporta hilos ejecutandose en el kernel, el hilo probablemente deba
ejecutarse ahí. Tener el hilo de pop-up ejecutandose en modo kernel
es más fácil y rápido que tenerlo en espacio de usuario. Este pop-up
thread en espacio de kernel podría acceder fácilmente a las tablas
del kernel y los dispositivos I/O, los cuales probablemente vaya a necesitar
para los procesos de interrupción. 

Por otro lado, un hilo del kernel con errores puede hacer más daño que un hilo de usuario con errores. 
Por ejemplo, si se ejecuta durante demasiado tiempo y no hay forma de 
evitarlo, los datos entrantes pueden perderse permanentemente.

### 2.2.9 Making Single-Threaded Code Multithreaded

Convertir un programa hecho para un proceso single-threaded a uno multithreading es más difícil de lo que
parece.

Para comenzar, el código para un thread consiste en múltiples funciones. Acá pueden haber variables locales,
variables globales y parámetros. Las variables globales que son globales respecto a un thread, y no a todo
el programa pueden ser un problema. Estas son variables  globales en el sentido de que varias funciones sin
hilos pueden usarla, pero otro hilos no deberían interferir con ella.

Consideremos la variable errno de UNIX. Cuando un thread llama a una system call que puede fallar el codigo
de error es puesto en errno.

En la figura 2.19 el thread 1 realiza la system call acces para saber si tiene permiso para acceder a un archivo.
El sistema operativo retorna la respuesta en la variable errno. Después de retornar el control al hilo 1, pero
antes de poder leer errno, el planificador dedice que el hilo 1 tiene sufienciente espacio en CPU por
el momento y decide cambiar al hilo 2. El hilo 2 ejecuta la función open call y falla, en consecuencia,
errno va a ser sobreescrito y el acces code del hilo 1 se va a perder para siempre. Cuando el hilo 1 sen inicie
posteriormente, este va a leer el valor incorrecto.

![imagen2.19](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-19.png?raw=true)

Una solución a esto es prohibir las variables globales, sin embargo esto entra en conflictos con parte
del software existente. Otra opción es asignar variables globales privadas a cada hilo, como en la figura 2-20.
De esta forma, cada hilo tiene su propio errno y otras variables globales, entonces evitarían los conflictos.
Esto crea un nuevo nivel de alcance, las variables son visibles para todas las funciones de su propio hilo, 
además de los niveles de alcance existentes de variables visibles sólo para una función y variables 
visibles en todo el programa. No es una solución elegante, pero funciona.

![imagen2.20](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-20.png?raw=true)

Acceder a las variables globales privadas, puede ser complicado. Sin embargo, es posible asignar una parte
de la memoria para las variables globales y pasarlo a cada funcion en el hilo como un parámetro extra.
No es la mejor solución, pero funciona.

Otra opción es usar una librería que nos permite crear, setear e introducir estas variables globales
para hilos. La call sería algo asi:

    create global("bufptr");
Asigna almacenamiento para un puntero llamado bufptr en el heap o en un área de almacenamiento especial 
reservada para el hilo llamante. Independientemente de dónde se asigne el almacenamiento, sólo el hilo 
llamante tiene acceso a la variable global.

Se necesitan 2 llamdas para acceder a la variable global, una para leer y otra para escribir.
Para escribir una variable glogal se usa:

    set global("bufptr", &buf);
Esto guarda el valor de un puntero el área anteriormente creada por create_global. 
Para leer una variable global se usa:
    bufptr = read global("bufptr");
Este retorna la dirección de memoria en la variable global.


Otro problema de pasar un programa de un hilo a varios hilos es que muchos procedimientos de biblioteca 
no son reentrantes. Es decir, no se diseñaron para que se realizara una segunda llamada a un procedimiento 
determinado mientras aún no había finalizado una llamada anterior. Por ejemplo,
el envío de un mensaje via red puede ser programado para ensamblar el mensaje en un buffer fijo dentro
de la librería, luego hacer un trap al kernel para enviarlo. ¿Qué pasa si un hilo ha ensamblado su mensaje en 
el buffer, entonces una interrupción del reloj fuerza un cambio a un segundo hilo que inmediatamente 
sobrescribe el buffer con su propio mensaje?

Algo parecido sucede con malloc en UNIX, el cual mantiene tablas del uso de memoria, por ejemplo una lista
de los espacios disponibles en la memoria. Mientras malloc está ocupado actualizando esta lista, puede estar
en un estado inconsistente, con punteros que no apuntan a ninguna parte. Si se produce un cambio mientras
las tablas son insconsistentes y una nueva llamada viene de un hilo diferente, un puntero no válido puede
ser utilizado y el programa se puede crashear. Arreglar esto significaría tener que reescribir toda la librería.

Una solución diferente es darle a cada función una chaqueta que establezca un bit para marcar la biblioteca como
en uso. Todo intento de uso(proveniente de otro hilo) de un proceso de librería que está en uso se bloquea.

Aunque esto pueda funcionar, elimina en gran manera el paralelismo potencial. Consideremos señales hechas
especificamente para threads. Si un hilo llama a alarm, el resultado de la señal irá por el thread que
la llamó. Si los hilos están implementados en user-space  el kernel no sabe de ellos y es difícil enviar
la señal directamente al hilo correspondiente. Una complicación adicional se produce si un proceso puede 
tener sólo una alarma pendiente a la vez y varios hilos llaman a la alarma de forma independiente.

Otras señales como la interrupción de teclado, no son hechas específicamente para hilos. Quién debería recogerlas?
Un solo hilo? Todos los hilos? Un hilo pop up recién creado?Además, ¿qué ocurre si un hilo cambia los 
manejadores de señales sin avisar a los demás hilos? Esta situación puede darse si uno o más hilos ejecutan 
procedimientos de biblioteca estándar y otros son escritos por el usuario.

En general, las señales son bastante difíciles de gestionar en un entorno monohilo. Pasar a un entorno 
multihilo no las hace más fáciles de manejar.


Un último problema es el manejo de la pila, en algunos systemas cuando la pila del proceso se rebalsa,
el sistema asigna automáticamente más espacio a la pila. Cuando un proceso tiene muchos hilos, también debe
tener múltiples pilas. Si el kernel no está al tanto de dichas pilas, no puede hacerlas crecer automáticamente.
De hecho puede que ni siquiera sea consciente del fallo en la memoria producto producto del crecimiento de 
alguna pila del algún hilo.

Desde luego, estos problemas no son insuperables, pero demuestran que introducir hilos en un sistema existente sin 
rediseñarlo de forma sustancial no va a funcionar. 


## 2.3 INTERPROCESS COMUNNICATION

Los procesos se comunican constantemente con otros procesos. Por ejemplo, en el shell pipeline, el output
del proceso 1 debe pasarse al proceso 2 y así sucesivamente. Por ende la comunicación de procesos es 
necesaria, de preferencia en una forma bien estructurada que no utilice interrupciones.

En la seccion siguiente vamos a ver algunos problemas relacionados a la comunicación entre procesos
o IPC.

### Problemas

El primer problema es ¿cómo un proceso puede enviar información a otro?.  El segundo está relacionado a 
asegurarse que 2 procesos no se estorben, por ejemplo, 2 procesos de un sistema de aerolínea intentando
conseguir el último asiento de un avión para un cliente diferente. La tercera se refiere a la 
secuencia adecuada cuando existen dependencias. Si el proceso A produce datos y el proceso B los imprime
B debe esperar que A termine de producir los datos antes de empezar a imprimir. 2 de estos procesos
se aplican igualmente a los hilos o threads. 

El primero es fácil para los hilos que comparten espacio de memoria. Los otros 2 pueden ser resueltos con 
threads. El mismo problema existe y se aplicará la misma solución, esto relacionado con hilos.

### 2.3.1 Race Conditions

En algunos sistemas operativos, los procesos que trabajan juntos comparten un mismo almacenamiento del cual
pueden leer y escribir. El almacenamiento compartido puede estar en la memoria principal(posiblemente en
una estructura de datos del kernel) o puede estar en un archivo compartido. La ubicación de la memoria compartida
no cambia la naturaleza del comunicación el problema que genera. Veamos un ejemplo: una cola de impresión.
Cuando un proceso a va realizar una impresión ingresa el nombre del file en un spooler directory. 
Otro proceso el printer daemon, revisa periodicamente si  hay algún file en ese lugar para ver si se necesita
alguna impresión, si existe, lo imprime y luego elimina su nombre del directorio.

Imaginemos que nuestro spooler directory tiene un numero muy largo de slots, cada uno capaz de tener un nombre
de archivo. Ahora, imaginemos que tenemos 2 variables compartidas, out, la cual apunta al siguiente archivo
a imprimir, e in, el cual apunta a un lugar libre del directorio. Estas 2 variables podrían guardarse
en un archivo de 2 palabras disponible para todos los procesos. En un momento dado, las ranuras 0 a 3 están vacías (los ficheros 
ya se han impreso) y las ranuras 4 a 6 están llenas (con los nombres de los ficheros en cola de impresión). Más o menos 
simultáneamente, los procesos A y B deciden poner en cola un fichero para imprimir. Esto se ve en la figura 2-21.

![imagen2.21](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-21.png?raw=true)
En jurisdicciones donde la ley de Murphy es aplicable, podría ocurrir lo siguiente. El proceso A lee y almacena el valor, 7, 
en una variable local llamada next_free_slot. Justo en ese momento se produce una interrupción del reloj y la CPU decide que el 
proceso A ya ha funcionado lo suficiente, por lo que pasa al proceso B. El proceso B también lee y también obtiene un 7. 
También lo almacena en su variable local next_free_slot. En este instante ambos procesos piensan que la siguiente ranura 
disponible es el 7. 

El proceso B continúa ejecutándose. Almacena el nombre de su archivo en la ranura 7 y lo actualiza para que 
sea un 8. Luego se va y hace otras cosas.

Finalmente, el proceso A se ejecuta de nuevo, comenzando desde el lugar donde lo dejó. Mira la siguiente ranura libre, encuentra 
un 7 allí, y escribe su nombre de archivo en la ranura 7, borrando el nombre que el proceso B acaba de poner allí. A continuación, 
calcula la siguiente ranura libre + 1, que es 8, y la coloca en 8. El directorio del spooler es ahora internamente consistente, 
por lo que el daemon de la impresora no notará ningún error, pero el proceso B nunca recibirá ninguna salida.

Situaciones como ésta, en la que dos o más procesos están leyendo o escribiendo algunos datos compartidos y el resultado final 
depende de quién los ejecuta precisamente cuándo, se denominan race conditions. Por desgracia, con el aumento del paralelismo 
debido al incremento del número de núcleos, los race condition son cada vez más comunes. Además los resultados de las 
depuraciones en programas con race condition pueden ser correctos en su mayoría, pero de vez en cuando suceden cosas raras,
difíciles de explicar.


### 2.3.2 Critical Regions

## APUNTES DE CLASE

En el archivo se relacionado nombre con un nodo-i. 

Todas las variables locales de funcion, parametros y punto de retorno.

Todos los hilos se encuentran dentro de segmento de texto de un mismo proceso.

cuando algunos procesos son concurrentes, esto significa que comparten recursos