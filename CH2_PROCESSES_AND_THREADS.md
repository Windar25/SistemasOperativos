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

¿Cómo evitamos las race condition? La regla para prevenir problemas acá y en otras situaciones que tengan que ver con memoria, archivos y todo loo que sea compartido es prohibir a uno o mas procesos la lectura y escritura de datos simultanea. En otras palabras, necesitamos **exclusión mutua**, esto es una forma de asegurar de que mientras un proceso está usando una variable o archivo compartido, los demás procesos van a ser excluidos de usar el mismo file o variable. El problema anterior surgió dado que el proceso B comenzó a usar una variable compartida antes de que el proceso A termine de usarla. La elección de las operaciones primitivas apropiadas para lograr la exclusión mutua es una cuestión de diseño importante en cualquier sistema operativo, y un tema que examinaremos con gran detalle en las siguientes secciones.

El problema de evitar las race condition puede ser formulada de forma abstracta. Parte del tiempo, un proceso está ocupado realizando cálculos  u operaciones internas que no nos llevan a race condition. De todos modos, el proceso pued acceder a memoria o archivos compartidos, o algún lugar crítico que nos lleve a la condición de carrera. Esa parte del programa donde la memoria compartida es accedida es llamada **critical region** o **critical section**. Si pudiéramos organizar las cosas de forma que nunca hubiera dos procesos en sus regiones críticas al mismo tiempo, podríamos evitar las carreras.

Aunque este requisito evita las condiciones de carrera, no es suficiente para que los procesos paralelos cooperen correcta y eficientemente utilizando datos compartidos. Necesitamos que se cumplan cuatro condiciones para tener una buena solución: 
1.  No deben haber 2 procesos simultáneamente en sus regiones críticas.
2.  No se pueden hacer suposiciones sobre las velocidades o el número de CPU.
3.  Ningún proceso que esté afuera de su sección crítica debe poder bloquear algún proceso.
4.  Ningún proceso debería tener que esperar eternamente para entrar en su región crítica.

Este comportamiento es el que queremos mostrar en la figura 2-22. Acá el proceso A entra a la región crítica en el momento T1. Tiempo después en un tiempo B, el proceso B trata de entrar a la región crítica, pero falla porque otro proceso ya está en la región crítica y solo vamos a permitir que solo uno acceda a la vez. Consecuentemente, B es suspendido temporalmente, hasta un tiempo T3, donde A deje su región crítica, permitiendo a B entrar inmediatamente. Eventualmente, B deja la sección crítica en un tiempo T4 y nos encontramos en la situación inicial de no tener proceso en la región crítica.

![figura2.22](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-22.png?raw=true)

### 2.3.3 Mutual Exclusion with Busy Waiting

En esta sección vamos a examinar varias propuestas para lograr la exclusión mutua de tal modo que 
cuando un proceso se encuente en su región crítica, otro proceso entre y cause problemas.

#### Deshabilitar interruptores
En un sistema de un solo procesador, la solución más simple es tener deshabilitado los interruptores de los
demás procesos, mientras nuestro proceso se encuentre en su zona crítica, al finalizar nuestro proceso, se volverán
a habilitar los interruptores. Con las interrupciones deshabilitadas no existirán interrupciones de clock.
La CPU solo cambia de proceso en proceso como resultado del clock o de interrupciones, con las interrupciones 
desactivadas la CPU no se cambiará a otro proceso. Entonces, un proceso que deshabilita las interrupciones puede
puede examinar y actualizar la memoria compartida sin miedo a que otro proceso intervenga.
Este enfoque es generalmente poco atractivo porque no es prudente dar a los procesos de usuario el poder de desactivar 
las interrupciones. ¿Qué pasaría si alguno de ellos nunca las reactiva? Esto sería el fin del sistema.

Además, si el sistema es un multiprocesador (con dos o más CPUs) desactivar las interrupciones afecta sólo a 
la CPU que ejecutó la instrucción de desactivación. Las demás seguirán funcionando y podrán acceder a la 
memoria compartida.

Por otro lado, con frecuencia es conveniente que el propio núcleo desactive las interrupciones durante unas 
pocas instrucciones mientras actualiza variables o especialmente listas. Si se produce una interrupción 
mientras la lista de procesos listos, por ejemplo, está en un estado inconsistente, podrían producirse 
*race condition*.

En conclusión, deshabilitar interrupciones puede ser útil pero no es apropiado como una exclusión general mutua
de mecanismos para los procesos de usuario.

Además, la posibilidad de deshabilitar interrupciones para responder a la race condition es cada vez menos eficiente, pues
las computadoras cada vez cuentan con más núcleos. Esto significa que si un núcleo desactiva sus interrupciones, esto no impide
que los demás núcleos puedan acceder a su espacio de memoria compartido, es decir, no evitan la race condition.


#### Lock Variables

Una solución de software sería tener una única variable compartida (de bloqueo) iniciada en 0.
Si un proceso desea entrar a su critical region primero revisa el lock. Si el lock es 0, el proceso asigna 1
al lock y entra al critical region. Si el lock es 1, el proceso espera hasta que sea 0. Es decir, el 0 significa
que ningun proceso está en el critical region y 1 significa que algún proceso está en el critical region.

Desafortunadamente, esta idea contiene el mismo problema que en el spooler directory. Supongamos que un proceso
lee el lock y ve que es 0, antes de que setee el lock como 1, otro proceso comienza a ejecutarse y lee el lock en 0
y lo setea en 1. Cuando el primer proceso se reanude y setee el lock en 1, tendremos 2 procesos en la misma critical
region.

Ahora podrías pensar que podríamos evitar este problema leyendo primero el valor del bloqueo, y comprobándolo 
de nuevo justo antes de almacenarlo, pero eso realmente no ayuda. La carrera ocurre ahora si el segundo 
proceso modifica el bloqueo justo después de que el primer proceso haya terminado su segunda comprobación.

#### Strict Alternation

Veamos un ejemplo en lenguaje C. En la figura 2-23 la variable tipo int turn, inicialmente puesta en 0, lleva 
la cuenta de a quién le toca entrar en la critical region y examina o actualiza la memoria compartida.
Inicialmente, el proceso 0 lee turn, ve que es 0 y entra a la región crítica. El proceso 1 ve que turn es 0 y
entra cíclicamente en un loop testeando turn para cuando este sea 1. Probar continuamente una variable hasta 
que aparezca algún valor se denomina *busy waiting*. Esto debe tratar de evitarse, dado que desperdicia tiempo
en la CPU. Solo es bueno usarlo cuando es necesario. El lock que produce el busy waiting es llamado spin lock.
Cuando el proceso 0 deja la critical region, este cambia el turn a 1, lo que permite al proceso 1 entrar al critical
region. Supongamos que el proceso 1 entra sale del critical region rápidamente, entonces ambos procesos
estarían en su zona no crítica, y se cambiaría el turn 0, evitando nuevamente que ambos procesos estén en la critical
region simultáneamente.

De repente, el proceso 0 termina su región no crítica y vuelve a la parte superior de su bucle. 
Desafortunadamente, no se le permite entrar en su región crítica ahora, porque el turno es 1 y el proceso 1 
está ocupado con su región no crítica. Se cuelga en su bucle while hasta que el proceso 1 pone turn a 0. 
Dicho de otra manera, tomar turnos no es una buena idea cuando uno de los procesos es mucho más lento que el 
otro.

![figura2.23](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-23.png?raw=true)

Esta situación viola la condición 3 expuesta anteriormente: el proceso 0 está siendo bloqueado por un proceso que no se encuentra 
en su región crítica.De hecho, esta solución requiere que los dos procesos se alternen estrictamente a la hora de entrar en sus 
regiones críticas, por ejemplo, en la cola de impresión de archivos. A ninguno de los dos se le permitiría 
poner en cola dos archivos seguidos. Aunque este algoritmo evita todas las carreras, no es realmente un 
candidato serio como solución porque viola la condición 3.

#### Peterson Solution

Peterson descubrió una forma mucho más sencilla de lograr la exclusión mutua, con lo que la solución de 
Dekker quedó obsoleta. El algoritmon de Peterson es mostrado en la figura 2-24.

![imagen2.24](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-24.png?raw=true)

Antes de usar las variables compartidas, cada proceso llama a *enter_region* con su propio numero de proceso
0 o 1 como parámetro. Esta llamada puede causar una espera hasta que sea seguro entrar. Después de finalizar
con la variable compartida, el proceso llama al *leave_region* para indicar que ya terminó y así permitir
al otro proceso entrar si es que este lo desea.

Veamos un ejemplo, al inicio ningún proceso está en la critical region. Ahora el proceso 0 llama a 
*enter_region*. Este indica que está interesado y setea el array element a TRUE y coloca turno en 0.
Si el proceso 1 no está interesado *enter_region* retorna inmediatamente, en caso contrario, este proceso
también llama al *enter_region* y se quedará ahí hasta que interested[0] se torne a FALSE.
Y el evento solo puede suceder cuando el proceso 0 llame a *leave_region* para salir
de la region crítica.

Ahora veamos que pasa si ambos procesos llaman a *enter_region* simultáneamente.
Ambos van a setear su número de proceso en turn. El último que guarde su turno es el
que se va a contar, el primero se va a sobreescribir y se va a perder. Supongamos
que el proceso 1 guardó al último, entonces su turno es 1. Luego ambos procesos entrarán al while
statement, process 0 ejecuta el while 0 veces y entra a la región crítica.
El proceso 1 se queda en el loop y no entra a la región crítica hasta que
el proceso 0 salga de la región crítica.

#### The TSL Intruction

Ahora veamos una propuesta que necesita una pequeña ayuda del hardware. Algunas
computadoras, especialmente las diseñadas con multiples procesadores en mente
tienen una instrucción como: 

        TSL RX,LOCK

(Test and Set Lock) que funciona de la siguiente manera:
Se lee el contenido en el memory word *lock* en el registro RX y se guarda un valor distinto
a 0 en la dirección de memoria *lock*. Se garantiza que las 
operaciones de lectura de la palabra y de almacenamiento en 
ella son indivisibles(ningun otro procesador puede acceder a la memory word hasta
que la instrucción finalice). La CPU ejecuta la instrucción TSL y bloquea el memory bus
para evitar que otras CPUs accedan a la direción de memoria hasta que se haya realizado la instrucción.

Cabe destacar que bloquear la memoria del bus es distinto a deshabilitar las interupciones.
Deshabilitar interrupciones para realizar un read en la memoria de una palabra seguido de un
write no previene que otro procesador en el bus puede acceder a la dirección de la palabra
entre la lectura y escritura. Es decir, deshabilitar interrupciones en un procesador
no las deshabilita en los demás procesadores. La única forma de evitar que los demás
procesadores accedan a la memoria de la palabra es cerrando el bus, el cual requiere
una facilidad de hardware(básicamente, una línea de bus que 
afirma que el bus está bloqueado y no está disponible para 
procesadores distintos del que lo bloqueó).

Para usar el TSL vamos a usar una variable compartida llamada *lock* para coordinar el acceso 
a la memoria compartida. Cuando el lock es 0, cualquier 
proceso puede ponerlo a 1 utilizando la instrucción TSL y 
luego leer o escribir en la memoria compartida. Cuando 
termina, el proceso vuelve a poner el bloqueo a 0 
utilizando una instrucción move normal.

Ahora, ¿cómo esta solución previene el race condition evitando el ingreso de 2
procesos a la misma región crítica?. La solución está en la figura 2-25.

![imagen2.25](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-25.png?raw=true)

Acá hay 4 instrucciones de subrutina en un lenguaje ensamblador ficticio.
La primera instrucción copia el antiguo valor de lock al registro y setea 1 al lock.
Luego, el antiguo valor es comparado con 0. Si no es 0, el lock se acaba de setear entonces
el programa vuelve al inicio y vuelve a testearlo. Tarde o 
temprano este será 0(cuando el proceso actualmente en su 
región crítica ha terminado con su región crítica), y la 
subrutina regresa, con el bloqueo establecido.

Limpiar el lock es simple, el programa solo guarda 0 en lock. No se necesita ninguna 
instrucción especial de sincronización. 

La solución al problema de la región crítica ahora es más fácil. Antes de entrar a la región crítica el proceso
llama a enter_region, el cual realiza busy waiting hasta que el lock se libere, luego adquiere el lock y retorna.
Después de dejar la región crítica el proceso llama a *leaves_region* y guarda el lock en 0.
Como todas las soluciones basadas en regiones críticas, los procesos deben llamar
*enter_region* y *leave_region* en los momentos correctos para que el método funcione.
Si un proceso hace trampa, la exclusión mutua va a fallar. En otras palabras las regiones
críticas funcionan solo si los procesos cooperan.

Una solución alternativa al STL es el XCHG el cual intercambia 
atómicamente el contenido de dos posiciones, por ejemplo, 
un registro y una palabra de memoria. El código se muestra 
en la Fig. 2-26, y, como puede verse, es esencialmente el 
mismo que la solución con TSL.

![imagen2.26](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-26.png?raw=true)

### 2.3.4 Sleep and Wakeup

Las soluciones mostradas anteriormente son correctas, pero tienen el problema del busy waiting.
Es decir, las soluciones proponen la siguiente estructura: Si un proceso desea entrar
a su critical region debe revisar si está permitido. En caso no esté el proceso se mantiene en un loop
hasta que se le dé el permiso.

Esto no solo desperdicia el tiempo del CPU, sino que puede tener efectos inesperados.
Consideremos una CPU con 2 procesos, H, con prioridad alta y L con menor prioridad.
Las reglas de programación son tales que H se ejecuta siempre que esté en estado listo.
En un cierto momento, cuando L está en la región crítica, H se encuentra listo para
ejecutarse(se completó una operacion I/O). H ahora se encuentra en busy waiting, pero 
como L nunca se programa mientras H se está ejecutando, L nunca tiene la oportunidad 
de salir de su región crítica, por lo que H hace un bucle eterno. Esta situación se 
denomina a veces problema de inversión de prioridad.

Veamos ahora algunos procesos de intercomunicación primitivos que bloquean en lugar de malgastar
tiempo en la CPU cuando no se les permite entrar a las regiones críticas.

Una de las más sencillas es el par de sleep y wakeup. Sleep es una llamada al sistema que 
hace que la llamada se bloquee, es decir, se suspenda hasta que otro proceso la despierte.
La llamada wakeup tiene un parámetro, proceso a ser despertado.
Alternativamente, tanto sleep como wakeup tiene cada uno un parámetro, una dirección de memoria
usada para emparejar sleeps con wakeups.

#### The Producer-Consumer problem
----
Para ver como usar estos interprocesos veamos el ejemplo del productor y consumidor.
2 procesos comparten un buffer común. Uno de ellos, el productor, pone información
en el buffer y el otro, el consumidor, la toma(también se puede tomar el ejemplo con m productores
y n consumidores pero para facilitar la solución, veamos el caso de 1 a 1) .

El problema comienza cuando el productor quiere poner un nuevo item en el buffer, pero
este ya está lleno. La solución para el productor es ir a dormir, para luego despertarse
cuando el consumidor haya tomado uno o más items. De manera similar, si el consumidor quiere
remover un item del buffer y ve que este está lleno, este debe ir a dormir hasta que el productor
ponga algo en el buffer y así luego él se despierte.
Este enfoque suena simple, pero lleva al mismo caso de race conditions que vimos con el
spooler directory. Para mantener la cuenta de número de items en el buffer, necesitamos la variable
count. Si el número máximo de items en el buffer es N, el codigo del productor debe verificar
si el contador está en N. Si lo está, el productor se va a dormir, sino, el productor ingresa
otro item y actualiza el contador.

El código del consumidor es similar: primero revisa si el contador es 0, si lo es este se va a dormir, sino
remueve el item y disminuye el contador. Cada proceso revisa si el otro debe despertarse y si debe, lo despierta.
EL código para el productor y consumidor se encuentra en la figura 2-27.

Para expresar system calls como *sleep* o *wakeup* en C, las mostraremos como llamadas a rutinas de biblioteca.
No existen en la librería standar de C, pero se pueden usar en cualquier sistema que tenga estas systems calls.
Las funciones *insert_item* y *remove_item*, las cuales no se muestran 
, se encargan de la contabilidad de poner y sacar elementos de la memoria intermedia.



![imagen2.27](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-27.png?raw=true)

Ahora, respecto a la race condition, este puede ocurrir si el acceso a la variable count es sin restricciones.
En consecuencia podría pasar lo siguiente: El buffer está vacío y el consumidor acaba de leer
que el contador está en 0. En ese momento, el planificador de trabajos decide parar la ejecución del consumidor 
y comenzar a ejecutar al productor. El productor inserta un item en el buffer, incrementa el contador y se da cuenta que 
ahora es 1. Si el contador fue 0 hace unos momentos, entonces el consumidor va a hacer *sleep*, el productor llama
*wakeup* y "despierta" al consumidor.

Sin embargo, el consumidor no estaba durmiendo lógicamente aún, entonces
la señal de *wakeup* se pierde. Cuando sea el turno del consumidor, él va a leer valor del contador anteriormente
leído, va a encontrar que es 0 y se jecuta *sleep*. Ambos se irán a dormir para siempre.

La esencia de este problema es que se envía la señal de *wakeup* a una función que aún no duerme y por ende
esta señal se va a perder. Si esta no se perdiera, todo andaría bien en el programa. Una forma de arreglar esto
es modificar las reglas para añadir un *wakeup waiting bit*. Cuando se envía una señal
de wakeup a un proceso que sigue despierto, se setea este bit. Después cuando el proceso
intente ir a dormir, si el wakeup bit está en activo, este se apagará, pero el proceso
seguirá despierto. El wakeup waiting bit es una alcancía para guardar wakeup signals.
El consumidor limpia el waiting bit en cada iteración del loop.

Si bien el wakeup waiting bit funciona en este caso, esta solución no es útil para
3 o más procesos. Podríamos hacer otro parche y añadir un segundo bit de espera de 
despertar, o tal vez 8 o 32 de ellos, pero en principio el problema sigue ahí.

### 2.3.5 Semaphores

Esta era la situación en 1965, cuando E. W. Dijkstra (1965) sugirió utilizar una variable entera para contar el número de 
wakeups guardados para uso futuro. En su propuesta, se introdujo un nuevo tipo de variable, que denominó semáforo. Un 
semáforo podía tener el valor 0, indicando que no se había guardado ningún wakeup, o algún valor positivo si había uno 
o más wakeups pendientes.

Dijsktra propuso tener 2 operaciones para el semáforo: *down* and *up*(generalizacions de sleep y wakeup respectivamente).
La operación *down* en el semáforo, revisa si el valor es mayor a 0. Si lo es disminuye el valor(utiliza una activación almacenada)
y luego continua. Si el valor es 0, el proceso es puesto a dormir sin completar el down por el momento. Revisar el valor, cambiarlo
y posiblemente mandándolo a dormir, es hecho como una simple y única **atomic action**. Se garantiza que una vez que la operación
semaforo haya empezado, ningun otro proceso puede acceder al semáforo hasta que la operación se haya completado
o bloqueado. Esta atomicidad es muy esencial para solucionar problemas de sincronización y evitar race conditions.
Acciones atómicas, en las que un grupo de operaciones relacionadas se realizan todas sin interrupción o no se realizan en absoluto, 
son extremadamente importantes también en muchas otras áreas de la informática.

La operación *up* incrementa el valor del semáforo. Si uno más procesos estaban durmiendo en el semáforo, inhabilidatos para completar
su operación *down* iniciada anteriormente, uno de ellos, escogido por el sistema (aleatoriamente) es permitida para completar su función
down. Por lo tanto, después de usar un up en un semáforo con procesos durmiendo en él, el semáforo seguirá estando en 0, pero
habrá un proceso menos durmiendo en él. La operación de incrementar el semáforo y despertar algún proceso es indivisible.
Ningún proceso se bloquea al hacer un up, al igual que ningún proceso se bloquea al hacer un wakeup en el modelo anterior.

Estos términos se introdujeron por primera vez en el lenguaje de programación Algol 68.

#### **Solving the Producer-Consumer Problem Using Semaphores**

Los semáforos solucionan la pérdida de wakeup mostrada en la figura 2-28. Para que esto funcione correctamente es necesario que
el semáforo sea implementado de una forma indivisible. La forma normal es implementar *up* y *down* como system calls, donde el sistema
operativo desactiva brevemente todas las interrupciones mientras comprueba el semáforo, lo actualiza y pone el proceso en reposo, 
si es necesario. Todas estas acciones toman solo pocas instrucciones, no se produce ningún daño al desactivar las interrupciones.
Si se están usando múltiples CPUs, cada semáforo debe ser protegido con una variable *lock*, con las
instrucciones TSL o XCHG usadas para asegurarse de que solo una CPU esté examinando el semáforo en un mismo momento.

Debemos entender que usar TSL o XCHG para evitar que varias CPUs accedan a un mismo semáforo es muy diferente de que el productor o el 
estén ocupados(busy waiting) esperando a que el otro vacíe o llene el búfer. Las operaciones de semáforo tomo solo pocos microsegundos, mientras que
el productor o consumidor pueden tomar mucho más.

![imagen2.28](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-28.png?raw=true)

Esta solución emplea 3 semáforos: uno llamado *full* para contar el número de slots que están llenos, otro llamado *empty* para contar el número
de slots que están vacíos y otro llamado *mutex* para asegurarse de que el productor y el consumidor no acceden al
mismo tiempo. *Full* es inicialmente 0, *empty* es inicialmente el número de slots del buffer y *mutex* es inicialmente 1. Los semáforos que se 
inicializan a 1 y son utilizados por dos o más procesos para garantizar que sólo uno de ellos puede entrar en su región crítica al mismo tiempo se denominan **binary semaphores**.

Si cada procesos realiza un down justo antes de entrar a su región crítica y realiza un up justo después de dejarla,
la exclusión mutua es garantizada.

Ahora que disponemos de una buena comunicación entre procesos, veamos la secuencia de interrupcion de la figura 2-5.
En un sistema con semáforos, el camino natural para ocultar interrupciones es tener un semáforo inicializado en 0 y asociado con
cada dispositivo I/O. Justo después de comenzar con el dispositivo I/O, el manejador de procesos realiza un down en el semáforo asociado
bloqueandolo inmediatamente. Cuando la interrupción retorne, el manejador de interrupciones realizará un up en el semáforo asociado, el cual permitirá
que el proceso relevante esté listo para ejecutarse nuevamente. En este modelo, el paso 5 en la figura 2-5 consiste en hacer up
en el semáforo correspondiente, para que en el paso 6 el planificador pueda ejecutar el administrador de dispositivos.
Por supuesto, si hay varios procesos listos, el planificador probablemente vaya a ejecutar el más importante. Vamos a ver algunos de estos
algoritmos más tarde en este capítulo.

En el ejemplo de la figura 2-28, estamos usando semáforos en 2 distintas formas. Es importante hacer explícita esta diferencia. El semaforo *mutex* es usado para exclusión
mutua. Está diseñado para garantizar que solo un proceso a la vez va a estar leyendo o escribiendo en el buffer y las variables asociadas.
Esta exclusión mutua es necesaria para evitar problemas. Vamos a estudiar exclusión mutua y como lograrla en la siguiente sección.

El otro uso de semáforos es para la **sincronización**. Los semáforos *full* y *empty* son necesarios para garantizar que ciertos eventos secuenciales
no ocurran. En este caso, ellos garantizan que el productor tendrá su ejecución cuando el buffer esté lleno y que el consumidor detendrá su ejecución cuando el buffer esté
vacío. Su uso es distinto para exclusión mutua.

### 2.3.6 Mutexes

Cuando la capacidad del semáforo para contar no es necesaria, a veces se utiliza una versión simplificada del semáforo, llamada mutex.
Los mutex solo son útiles para manejar la exclusión mutua para algunos recursos compartidos o partes de código.
Son fáciles y eficientes de implementar, lo que los hace especialmente útiles en paquetes de hilos que se implementan completamente en el espacio de usuario.

Un **mutex** es una variable compartida que puede encontrarse en 2 estados: bloqueado o desbloqueado.
En consecuencia, solo necesitamos un bit para representarlo, pero en la práctica un entero es más usado,
0 significa desbloqueado y todos los demás valores significan bloqueado.

Se usan 2 procesos con los mutex. Cuando un hilo o proceso necesita acceder a un región crítica, este llama al 
*mutex_lock*. Si el mutex esta desbloqueado(osea que la región crítica está disponible), la llamada tiene éxito y 
el hio llamante está libre para entrar a la región crítica. 

De otra forma, si el mutex se encuentra bloqueado, el hilo llamante is bloqueado hasta que el hilo en la región crítica termine y
ejecute la función *mutex_unlock*. Si múltiples hilos están bloqueados en el mútex, uno de ellos es escogido aleatoriamente y 
son permitidos para adquirir el lock.

Como los mutex son simples, pueden implementarse fácilmente en el espacio de usuario siempre que se disponga de una instrucción TSL o XCHG.
El código para *mutex_lock* y *mutex_unlock* para su uso con un paquete de hilos a nivel de usuario se muestran en la Fig. 2-29.
La solución con XCHG es esencialmente la misma.

![imagen2.29](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-29.png?raw=true)

El código para *mutex_lock* es muy similar al código de *enter_region* en la figura 2-25, pero con una diferencia
crucial. Cuando *enter_region* falla a la hora de entrar a la región crítica, este se mantiene consultando el lock repetidas veces
(busy waiting). Con el tiempo, el reloj se agota y algún otro proceso está programado para ejecutarse. Tarde o temprano, el proceso 
que tiene el bloqueo consigue ejecutarse y lo libera.

Con user threads la situación es distinta pues no existe un clock que detenga el hilo que ya no deba ejecutarse más. En consecuencia, 
un hilo que intenta adquirir un bloqueo mediante la espera ocupada hará un bucle eterno y nunca adquirirá el bloqueo porque nunca permite 
que ningún otro hilo se ejecute y libere el bloqueo.

Acá llega la diferencia entre *enter_region* y *mutex_lock*. Cuando se falle al adquirir el lock, este debe llamar
a la llamada thread_yield para dejar el CPU a otro hilo. De esta forma no hay busy waiting. Cuando el hilo se ejecute 
nuevamente esté revisará nuevamente el lock.

Comenzando que *thread_yield* es una llamada para el planificador de hilos en espacio de usuario, este es 
bastante rápido. En consecuencia ni *mutex_lock* ni *mutex_unlock* requieren alguna
llamada al kernel. Con ellas, los subprocesos de nivel de usuario pueden sincronizarse por completo en el espacio de usuario utilizando 
procedimientos que sólo requieren un puñado de instrucciones.

El sistema de mutex mostrado anteriormente es un conjunto básico de llamadas. Con todo software, siempre hay demanda de más funciones, y las 
primitivas de sincronización no son una excepción. Por ejemplo, aveces un packete de hilos ofrece la llamada *mutex_trylock* adquiere el 
bloqueo o devuelve un código en caso de fallo, pero no bloquea. Esta llamada da al hilo la flexibilidad de decidir qué hacer a continuación si 
hay alternativas para simplemente esperar.

Hay una cuestión sutil que hasta ahora hemos pasado por alto, pero vale la pena explicar.  Con un paquete de hilos en espacio de usuario 
no hay problema con que varios hilos tengan acceso al mismo mutex, ya que todos los hilos operan en un espacio de direcciones común.
Sin embargo, con la mayoría de las soluciones anteriores, como el algoritmo de Peterson y los semáforos, hay una suposición tácita de que múltiples 
procesos tienen acceso al menos a algo de memoria compartida, quizás sólo una palabra, pero algo. Si los procesos tienen espacios de direcciones disjuntos, 
como hemos dicho sistemáticamente, ¿cómo pueden compartir la variable de turno en el algoritmo de Peterson, o los semáforos o un buffer común? 

Hay 2 respuesta. Primero, alguna de las estructuras de datos comunes como los semáforos, pueden estar guardados en el kernel y solo son accedidas mediante
system calls. Este enfoque elimina el problema. Segundo, la mayoria de sistemas operativos modernos, ofrecen formas de compartir algunas porciones de espacio
de memoria con otros procesos. De esta forma, los buffers y otras estructuras de datos pueden ser compartidas. En otro caso, tomando el peor de todos, 
un archivo compartido puede ser usado. Si 2 o más procesos comparten la mayoría o todo su espacio de memoria, no habría mucha diferencia entre los hilos y 
los procesos. 2 procesos que compartan el mismo espacio de memoria siguen teniendo diferentes archivos abiertos, timers de alarma y otras propiedades, mientras 
que los hilos en un mismo proceso las comparten. Y siempre es cierto que los procesos múltiples que comparten un espacio de direcciones común nunca tienen la 
eficiencia de los hilos a nivel de usuario, ya que el núcleo está profundamente implicado en su gestión.

#### Futexes

Con el crecimiento del paralelismo, la eficiencia de sincronización y el locking es bastante importante para el rendimiento. Los spin locks son rápidos si 
la espera es corta, pero desperdician ciclos de CPU si no lo son. Si hay mucha espera, es más eficiente bloquear el proceso y permitir al kernel desbloquearlo
solo cuando el lock esté libre.  Desafortunadamente esto tiene el problema inverso: funciona bien bajo una fuerte espera, pero cambiar continuamente al 
kernel es costoso si hay muy poca espera para empezar. Para hacer esto peor, puede no ser fácil predecir la cantidad de espera de bloqueos.

Una solución interesante a este problema es el **futex** o el "fast user space mutex". Un futex es una caracteristica de Linux que implementa el bloqueo 
básico(mutex) pero evita caer en el kernel a menos que este realmente lo necesite. Dado que cambiar entre el kernel es bastante caro, usar el futex es 
considerablemente rentable. Un futex consiste en 2 partes: en un servicio de kernel y una librería de usuario. El servicio de kernel provee una "wait queue"
que permite a múltiples procesos esperar en un lock. Ellos no se van a ejecutar, hasta que el kernel los desbloquee. Para poner un proceso en la cola de espera 
se requiere una llamada al sistema (costosa) y debe evitarse. En la ausencia de espera, los futex trabajan completamente en los user space. Los procesos comparten
una misma variable lock(32-bit integer).Supongamos que el bloqueo es inicialmente 1, lo que suponemos que significa que el bloqueo está libre. Un hilo toma 
el lock realizando un atomic "decremente and test" (Las funciones atómicas en Linux consisten en ensamblaje en línea envuelto en funciones C y se definen en 
archivos de cabecera). Luego, el hilo inspecciona el resultado para ver si el lock está libre o no. Si está libre, todo está bien y nuestro hilo ha tomado satisfactoriamente
el lock. Si el lock le pertenece a otro hilo, nuestro hilo se queda esperando. En este caso, la librería de futex no entra en spin, pero usa una llamada al sistema 
para poner al hilo en la cola de espera del kernel. Esperemos que el costo de cambiar al kernel, esté justificado, dado que el hilo fue bloqueado de todos modos.
Cuando un hilo termina con el lock, libera el lock con un atomic "increment and test" y revisa el resultado para ver si algún proceso continua bloqueado en la
cola de espera del kernel. Si es así, hará saber al kernel que puede desbloquear uno o más de estos procesos. Si no hay contención, el kernel no interviene en absoluto.

#### Mutexes in Pthreads
Pthreads proporciona una serie de funciones que se pueden utilizar para sincronizar hilos.
Los mecanismos básicos usados en una variable mutex son para bloquear o desbloquear, es decir, cuidar la región crítica.
Un thread que quiere entrar a la zona crítica primero debe lockear el mutex asociado. Si el mutex no está bloqueado el hilo puede
entrar y el lock es atomicamente seteado, evitando que otros hilos entren. Si el mutex ya está bloqueado, el hilo llamado es bloqueado
hasta que este sea desbloqueado. Si varios hilos esperan en un mismo mutex, cuando este se desbloquee
uno de ellos es permitido para tomarlo y volver a bloquearlo. Estos locks no son mandatorios, está en manos del programador
asegurarse de usar los hilos correctamente.

La mayor llamada relacionada a los mutexes se encuentra en la figura 2-30. Como vemos, los mutex pueden ser creados y destruidos.
Las llamadas para realizar estas operaciones son:
- phtread_mutex_init
- pthread_mutex_destroy

Los hilos tambien pueden ser bloqueados con *pthread_mutex_lock* el cual trata de adquirir el lock y bloquea el hilo si ya estaba
lockeado. También existe la opción de tratar de lockear un mutex y fallar con un codigo de error, en vez de bloquear el hilo si es que 
el lock ya estaba seteado. Esta llamada es *pthread_mutex_trylock*. Esta llamada permite a los hilos realizar efectivamente el busy waiting
si es necesario. Finalmente, *pthread_mutex_unlock* desbloquea un mutex y libera exactamente un hilo si uno o más están en espera de él. Los mutex
también pueden tener atributos, pero estos son usados solo para propósitos especiales.

![imagen2.30](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-30.png?raw=true)

En adición a los mutex, Pthreads ofrece un segudo mecanismo de sincronización: **condition variables**. Los mutex son buenos para permitir o restringir accesos 
a las regiones críticas. Las variables de condición permiten que los hilos se bloqueen si no se cumple alguna condición. Casi siempre los dos métodos se utilizan 
juntos. Veamos ahora la interacción de hilos, mutexes y variables de condición con un poco más de detalle.

Como un ejemplo simple, consideremos el problema del productor-consumidor nuevamente: un hilo comienza a poner cosas en el buffer y otro comienza a tomar cosas del 
buffer. Si el productor descubre que no hay más slots disponibles en el buffer, este debe bloquearse hasta que un slot esté disponible. Los mutex permiten hacer la 
comprobación atómicamente sin interferencia de otros hilos, pero habiendo descubierto que el buffer está lleno, el productor necesita una forma de bloquearse y ser 
despertado más tarde. Esto es lo que permiten las variables de condición. 

Las llamadas más importantes relacionadas a las variables de condición se encuentran en la figura 2-31.
Como probablemente esperabas, existen llamadas para crear y destruir variables de condition. Pueden tener atributos y existen varias llamadas para gestionarlos (no se muestran).
Las operaciones primarias de las variables de condition son *pthread_con_wait* y *pthread_cond_signal*. La primera bloquea el hilo que realiza la llamada hasta que otro hilo le 
envía una señal (utilizando la segunda llamada).Los motivos de bloqueo y espera no forman parte del protocolo de espera y señalización, por supuesto. El hilo bloqueado suele estar esperando
la señal de un hilo para poder realizar algún trabajo, liberar algún recurso o realizar alguna otra actividad. Solo así podrá continuar el hilo bloqueado. Las variables de condición permiten que 
este waiting y blocking se realicen atómicamente. La llamada *pthread_cond_broadcast* se utiliza cuando hay varios hilos potencialmente todos bloqueados y esperando la misma señal.

Las variables de condición y los mutex siempre son usados juntos. El patrón es para un hilo que lockea un mutex, luego espera en una variable condicional si es que no obtiene lo que quiere.
Eventualmente otro hilo le envía una señal y él puede continuar. La llamada *pthread_cond_wait* desbloquea atómicamente el mutex que está reteniendo. 
Por esta razón, el mutex es uno de los parámetros.

También vale la pena señalar que las variables de condición (a diferencia de los semáforos) no tienen memoria. Si una señal es enviada a una variable de condición en el cual no hay un hilo esperando,
se pierde la señal. Los programadores deben ser cuidadosos para no perder señales. 

![imagen2.31](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-31.png?raw=true)

Como ejemplo de como los mutexes y variables de condición usadas, la figura 2-32 muestra un ejemplo simple del problema del productor-consumidor con un solo buffer.
Cuando el productor ha llenado el buffer, este debe esperar a que el consumidor la vacíe antes de producir el siguiente artículo. Similarmente, cuando el consumidor ha removido 
un ítem, debe esperar a que el consumidor produzca otro . Esto es bastante simple, este ejemplo muestra los mecanismos básicos. 
La sentencia que pone un hilo a dormir siempre debe comprobar la condición para asegurarse de que se cumple antes de continuar, ya que el hilo podría haber sido despertado debido a una señal UNIX o alguna otra razón.

![imagen2.32](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-32.png?raw=true)

### 2.3.7 Monitors

Con semaforos y mutex los interprocesos de comunicación se pueden ver fáciles, verdad?
Miremos cuidadosamente el orden de los downs antes de insertar o remover items del buffer en la figura 2-28. Supongamos que 2 downs en el código del productor
fueran cambiados en orden, entonces el mutex fue decrementado antes de que esté vacío en vez de realizarlo después. Entonces, la siguiente vez que el consumidor
quiera acceder al buffer, realizará un down en el mutex, ahora 0 y se bloqueará. Ambos proceso estarán bloqueados por siempre y no podrán terminar. Esto se llama deadlock
y lo veremos en el capítulo 6. 

Este problema apunta a mostrar la importancia de ser cuidadoso al usar semáforos. Un error sútil y todo se paraliza. Es como programar en lenguaje ensamblador, solo que peor, 
porque los errores son race condition, deadlock y otras formas de comportamiento impredecible e irreproducible.

Para facilitar la escritura de programas correctos, Brinch Hansen y Hoare propusieron una sincronización primitiva de alto nivel llamada **monitor**. Sus propósitos son se diferencian sutilmente,
como veremos. Un monitor es una colección de funciones, variables, y estructuras de datos que son agrupadas juntas en una especie de módulo o package. Los procesos pueden llamar a las funciones de un monitor
cuando ellas lo requieran, pero no pueden acceder a la estructura interna del monitor desde funciones declaradas afuera del monitor. La figura 2-33 muestra un monitor escrito
en un lenguaje imaginario, Pidgin Pascal. No se puede usar C dado que los monitores son un *language concept*.

![imagen2.33](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-33.png?raw=true)

Los monitores tienen una propiedad importante que la hace útil para lograr la exclusión mutua: solo un proceso puede estar activo en un monitor en cualquier instante. 
Los monitores son una construcción del lenguaje de programación, por lo que el compilador sabe que son especiales y puede manejar las llamadas a procedimientos de monitorización de forma diferente a otras llamadas a procedimientos.
Tipicamente, cuando un proceso llama a una función del monitor, las primeras intrucciones de la función revisa si otro proceso se encuentra activo con el monitor.
Si lo está, el proceso que realizó la llamada será suspendido hasya que el otro deje el monitor, en caso no haya otro proceso en el monitor, el proceso llamante podrá entrar.
Depende del compilador implementar la exclusión mutua en las entradas del monitor, pero una forma común es utilizar un mutex o un semáforo binario. Dado que el compilador, y no el programador, se encarga de la exclusión mutua, 
es mucho menos probable que algo salga mal. En cualquier caso, la persona que escribe el monitor no tiene por qué ser consciente de cómo el compilador organiza la exclusión mutua. Es suficiente saber que al convertir todas las 
regiones críticas en procedimientos de monitorización, nunca dos procesos ejecutarán sus regiones críticas al mismo tiempo. 

Aunque los monitores provean una manera fácil de lograr exclusion mutua, como hemos visto anteriomente, esto no es suficiente. También necesitamos una forma de que los procesos se bloqueen cuando no puedan continuar.
En el problema productor-consumidor, es bastante fácil poner todas las pruebas para buffer-full y buffer-empty en procedimientos de monitorización, pero ¿cómo debería bloquear el productor cuando encuentra el buffer lleno?
La solución reside en la introducción de variables de condición, junto con dos operaciones sobre ellas, wait y signal. Cuando una función del monitor descubra que ya no puede continuar(buffer lleno para el productor), este realiza
un wait en alguna variable de condición, dice, full. Esta acción causa que el proceso llamante se bloquee. Esto permite a otros procesos que anteriormente estaban prohibidos de entrar al monitor que entren. 
Hemos visto variables de condición y estas operaciones en el contexto del Pthread.

Para el otro proceso, por ejemplo, el consumidor, puede despertar a la parte durmiente realizando una señal en la variable de condición en la que espera su compañero.
Para evitar tener 2 procesos activos en el monitor al mismo tiempo, necesitamos una regla que diga qué sucede después de una señal. Hoare propuso dejar funcionar el proceso recién despertado, suspendiendo el otro.
Brinch Hansen propuso solucionar el problema exigiendo que un proceso que emita una señal salga inmediatamente del monitor. En otras palabras, una sentencia de señal sólo puede aparecer como sentencia final en un procedimiento de monitorización. 
Utilizaremos la propuesta de Brinch Hansen porque es conceptualmente más sencilla y también más fácil de implementar. Si se realiza una señal sobre una variable de condición en la que hay varios procesos en espera, sólo se reactivará uno de ellos, 
determinado por el planificador del sistema.

Existe una tercera solución que no fue propuesta ni por Hoare o Brinch Hansen. Esto es para permitir que el señalador continúe ejecutándose y que el proceso en espera comience a ejecutarse sólo después de que el señalador haya salido del monitor.
Las variables de condición no son contadores. Ellas no acumulan señales para su uso posterior como lo hacen los semáforos. Entonces, si una variable de condición es señalada sin nadie que lo espere, la señal se pierde para siempre.
En otras palabras, el wait debe estar antes de la señal. Esta regla hace la implementación mucho más simple. En la práctica esto no es un problema dado que es fácil llevar un registro del estado de cada proceso con variables si es que 
lo necesitamos. Un proceso que de otro modo podría hacer una señal puede ver que esta operación no es necesaria mirando las variables.

Un esqueleto del problema del productor-consumidor con monitores es mostrado en la figura 2-34 con el lenguaje imaginario, Pidgin Pascal. 

Puedes estar pensando que las operaciones *wait* y *signal* pueden parecer similares a sleep y wakeup, las cuales dijimos anteriormente que tenía un pésimo problema con los race condition. Bueno, estas instrucciones son similares, pero no son iguales.
Wait y sleep fallan, porque cuando un proceso intentaba dormirse, el otro intentaba despertarlo. Con los monitores, esto no puede suceder. La exclusión mutua está garantizada, es decir, si el productor en el monitor descubre que el buffer está lleno, podrá completar la operación wait sin tener que preocuparse por la posibilidad de que el planificador cambie al consumidor justo antes de que se complete la espera. El consumidor ni siquiera entrará en el monitor hasta que el wait haya terminado y el productor haya sido marcado como no ejecutable.

Como Pidgin Pascal es un lenguaje imaginario, algunos lenguajes de programación reales soportan el uso de monitores. Uno de ellos es Java. Si agregamos la keyword synchronized a un método de declaración, Java garantiza que una vez se ejecute ese hilo, ningún otro hilo va a poder ejecutar otro método synchronized de ese objeto. Sin synchronized, no existe garantía de esa inclusión.

![imagen2.34](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-34.png?raw=true)

Una solución al problema del productor-consumidor es mostrada en la figura 2-35. La solución tiene 4 clases. La clase externa ProducerConsumer crea e inicia 2 hilos, p y c. La segunda y tercera clase, productor y consumidor, respectivamente tienen el codigo para el productor y el consumidor. Finalmente la clase, *our_monitor* es el monitor. Esta clase contiene 2  hilos synchronized que son usados para insertar valores en el buffer y sacarlos. A diferencia de los ejemplos anteriores, aquí tenemos el código completo de inserción y eliminación.

![imagen2.35](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-35.png?raw=true)


Los hilos del productor y del consumidor son funcionalente idénticos a los mostrados en los ejemplos pasados. El consumidor tiene un loop infinito creando items y poniéndolos en el buffer, mientras que el consumidor tiene otro loop infinito consumiendo items y sacandolos del buffer.

La parte interesante del código es la de la clase *our_monitor*, donde se maneja el buffer, las variables de admistración y los 2 métodos sincronizados. Cuando el productor está activo en el insert, este sabe que el consumidor no puede estar activo en el remove, dando la seguridad de actualizar las variables en el buffer sin miedo a las race condition. La variable count lleva la cuenta de cuántos items hay en el buffer. Este puede tener cualquier valor desde 0 hasta N-1. La variable lo es el indice del buffer donde se va a recoger el siguiente item, mientras que la variable hi es el indice del buffer donde se va a poner el siguiente item. Está permitido el lo=hi, el cual significa que hay 0 elementos o N elementos en el búfer. El valor de
count indica qué caso se cumple. 

Los métodos sincronizados en Java se diferencian de los monitores clásicos ya que Java no incorpora variables de condición. En vez de eso, este tiene 2 procesos, wait y notify, los cuales son equivalentes a sleep y wakeup excepto por el hecho de que se usan en métodos sincronizados, no pueden tener race condition. En teoría el método wait no puede ser interrumpido,  de eso trata el código que lo rodea.Java requiere que el manejo de excepciones se haga explícito. Para nuestros propósitos, imagina que go to sleep es la forma de ir a dormir.

Realizando la exclusión mutua de las regiones críticas, los monitores permiten programar paralelamente con muchos menos errores que con los semáforos. De todos modos, igual presenta inconvenientes. Los monitores son un concepto de lenguaje de programación.El compilador debe reconocerlos y realizar la exclusión mutua de una manera u otra. Lenguajes como C, Pascal y otros no tiene monitores, entonces no tiene sentido esperar que sus compiladores puedan realizar la exclusión mutua. Entonces, ¿cómo el compilador puede saber qué funciones están en un monitor y cuales no?

Estos 2 lenguajes de programación tampoco tiene incluidos semáforos, pero añadirlos es fácil: Solo debes agregar 2 pequeñas instrucciones en lenguaje ensamblador a la librería para poder realizar las llamadas a up y down. Los compiladores no tiene porque saber que existen. Por supuesto, los sistemas operativos deben saber de los semáforos pero a menos que tengas un sistema operativo basado en semáforos, tu puedes escribir programas de usuario para ellos en C o C++. Para los monitores tú necesitas un lenguaje de programación escrito para ellos.

Otro problema con los monitores, al igual que con los semáforos es que están diseñados para resolver la exclusión mutua para una o más CPUs que tiene acceso a una memoria común. Colocando los semáforos en la memoria compartida y protegiéndolos con instrucciones TSL o XCHG, podemos evitar las race condition. Cuando pasamos a un sistema distribuido que consta de diferentes CPUs, cada una de ellas tiene su memoria privada conectada a una local network, estas primitivas se vuelven inaplicables.

La conclusión es que los semáforos son de muy bajo nivel y los monitores no pueden ser usados excepto en pocos lenguajes de programación. De todas formas, ninguna de las primitivas permite el intercambio de información entre máquinas. Se necesita algo más.

### 2.3.8 Message Passing

Este método de comunicación entre procesos utiliza dos primitivas, **send** y **recieve**, que, al igual que los semáforos y a diferencia de los monitores, son llamadas al sistema y no construcciones del lenguaje. Como tales, pueden incluirse fácilmente en procedimientos de biblioteca, tales como:

        send(destination,&message)
y

        receive(source,&message)

La primera llamada envía un mensaje a un destino determinado y la segunda recibe un mensaje de un origen determinado(o cualquiera si al receptor no le importa). Si no hay ningun mensaje disponible, el receptor puede bloquearse hasta que un mensaje llegue. De otra forma, este puede retornar inmediatamente con un código de error. 



#### Design Issues for Message-Passing Systems

Los sistemas de mesagee-passing presentan varios problemas que los semáforos o monitores no tienen, especialmente si el proceso de comunicación se realiza entre diferentes máquinas conectadas a una network. Por ejemplo, los mensajes pueden perderse en la network. Para evitar la pérdida de mensajes, el emisor y el receptor pueden acordar que, en cuanto se reciba un mensaje, el receptor envíe de vuelta un mensaje especial de acuse de **mensaje de recibo**. Si el emisor no ha recibido el mensaje de recibo en un cierto intervalo de tiempo, este retransmite el mensaje.

Ahora consideremos que pasa si el mensaje ha sido recibido correctamente, pero el mensaje de confirmación enviado al emisor se pierde. El emisor retransmitirá el mensaje, entonces el receptor lo tendrá 2 veces. Es importante que el receptor sepa diferenciar un mensaje nuevo a uno retransmitido. Usualmente este problema es resuelto colocando números consecutivos en el mensaje original. Si el receptor recibe un mensaje con el mismo número de secuencia que el mensaje anterior, sabe que se trata de un duplicado que puede ignorar. 

Los sistemas de mensajes también tienen que abordar la cuestión de cómo se nombran los procesos, para que el proceso especificado en una llamada de envío o recepción no sea ambiguo. La **autenticación** es otro problema en el sistema de mensajes: ¿cómo puede el cliente decir que está comunicándose de un archivo real de servidor y no está siendo un intruso?

En el otro extremo del espectro, también hay cuestiones de diseño que son importantes cuando el emisor y el receptor están en la misma máquina. Uno de ellos es el rendimiento. Copiar mensajes de un proceso a otro es siempre más lento que hacer una operación semáforo o entrar en un monitor. Se ha trabajado mucho para que el paso de mensajes sea eficiente.

#### The Producer-Consumer Problem with Message Passing

Ahora veamos como el problema del productor-consumidor puede ser resuelto con message passing y sin memoria compartida. La solución es mostrada en la figura 2-36. Nosotros asumimos que los mensajes tienen el mismo tamaño y que los mensajes enviados y no recibidos son guardados en el buffer automaticamente por el sistema operativo. En esta solución, se usa un total de N mensajes, análogo a los N slots en el buffer compartido. El consumidor comienza enviando N mensajes vacíos al productor. Cuando el productor tiene un item para enviarle al consumidor, toma un mensaje vacío y devuelve uno completo. De esta forma, el numero total de mensajes en el sistema se mantiene constante en el tiempo, para que puedan almacenarse en una determinada cantidad de memoria conocida de antemano.

Si el productor trabaja más rápido que el consumidor, todos los mensajes acabarán llenos, esperando al consumidor, el productor se encontrará bloqueado, esperando un mensaje vacío. Si el consumidor trabaja más rápido, ocurre lo contrario, todos los mensajes estarán vacíos a la espera de que el productor los llene; el consumidor estará bloqueado, a la espera de un mensaje lleno. 

Se pueden tener muchas variantes para los message passsing. Para empezar, veamos cómo se dirigen los mensajes. Una forma es asignar a cada proceso, una única dirección y tener mensajes que se envíen a los procesos. Otra forma es inventar una nueva estructura de datos, llamada **mailbox**. Un mailbox es un lugar donde se almanena cierto numero de mensajes, esto se especifica cuando se crea el mailbox. Cuando los mailbox son usados, los parámetros de dirección en las llamadas de send y receive son buzones, no procesos. Cuando un proceso trata de enviar algo a un mailbox que está lleno, este se suspende hasta que un mensaje sea removido del mailbox, para dejar espacio para uno nuevo.

Para el problema del productor-consumidor, ambos deben crear mailbox de un tamaño N para N mensajes. El productor debe enviar mensajes conteniendo el dato actual para el mailbox del consumidor y el consumidor debe enviar mensajes vacíos para el mailbox del productor. Cuando se usan mailbox, el mecanismo de almacenamiento en el buffer es claro: el mailbox de destino contiene mensajes que han sido enviados al proceso de destino pero que aún no han sido aceptados.

El otro extremo de tener mailbox es eliminar todo el almacenamiento del buffer. Cuando se adopta este enfoque, si el envío se realiza antes de la recepción, el proceso de envío se bloquea hasta que se produce la recepción, momento en el que el mensaje puede copiarse directamente del emisor al receptor, sin almacenamiento en el buffer. Del mismo modo, si la recepción se realiza en primer lugar, el receptor se bloquea hasta que se produce un envío. Esta estrategia se conoce a menudo como "rendezvous". Es más fácil de implementar que un esquema de mensajes en buffer pero es menos flexible, ya que el emisor y el receptor se ven obligados a funcionar al mismo tiempo.

![imagen2.36](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-36.png?raw=true)

Los message passing son usados sistemas de programación paralela. Un message passing system muy conocido es MPI(Message-Passing Interface)

### 2.3.9 Barriers

Nuestro último mecanismo de sincronización está orientado a un grupo de procesos, en vez del caso de 2 procesos como puede ser para el productor-consumidor. Algunas aplicaciones se dividen en fases y tienen la regla de que no deben tener procesos en la siguiente fase hasta que todos los procesos estén listo para avanzar de fase. Este comportamiento puede ser logrado poniendo una **barrier** al final de cada fase. Cuando un proceso llega a la barrera, este se bloquea hasta que todos los demás procesos hayan llegado a la barrera. Esto permite sincronizar grupos de procesos. La operación de barrera está ilustrada en la figura 2-37.

![imagen2.37](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-37.png?raw=true)

En la figura 2-37(a) vamos a ver 4 procesos que se acercan a una barrera. Esto significa que aún no alcanzan el final de su fase actual. Al cabo de un rato, el primer proceso termina toda la computación que se le había exigido durante la primera fase. Entonces ejecuta la **barrier primitive**, generalmente llamando a un procedimiento de biblioteca. A continuación el proceso se suspende. Poco tiempo después, el segundo y tercer proceso finalizan(figure 2-37b). Finalmente el último proceso C llega a la barrera y todos los procesos son liberos, como en la figura 2-37(b).

Como un ejemplo de un problema que requiere barreras, consideremos un problema in física o ingeniería. Usualmente existe una matriz que contiene valores iniciales, el valor puede representar la temperatura en varios puntos de una lámina de metal. La idea es calcular qué tanto le tomaría a una llama propagarse de una esquina hacia toda la lámina.

Comenzando con los valores iniciales, se aplica una aplicación a la matriz para obtener una segunda versión de la matriz, por ejemplo, aplicando las leyes de la termodinámica para ver todas las temperaturas después. Luego el proceso se repite una y otra vez, dando la temperatura de distintos puntos de la hoja como una función de tiempo mientras la hoja se quema. El algoritmo produce una secuencia de matrices a lo largo del tiempo, cada una para un momento dado.

Ahora, imaginemos que la matriz es bastante larga(1 millon x 1 millon), entonces se necesitan procesos paralelos de cálculo para acelerar el cálculo. Diferentes procesos trabajan en distintas partes de la matriz, calculando los nuevos elementos de la matriz a partir de los antiguos según las leyes de la física.
De todos modos, ningún proceso debe comenzar con la iteración n+1 hasta que la iteración n se complete, es decir, hasta que todos los procesos hayan terminado su trabajo actual. La forma de lograr este objetivo es programar cada proceso para ejecutar una operación barrier después de terminar su parte en la iteración actual. Cuando todos hayan acabado, la matriz nueva(el input para la nueva iteración) estará lista y todos los procesos van a ser liberados simultáneamente para comenzar la nueva iteración.

### 2.3.10 Avoiding Locks: Read-Copy-Update

Los locks rápidos no son locks del todo. La cuestión es si podemos permitir accesos concurrentes de lectura
y escritura a estructuras de datos compartidas sin bloqueo. En el caso general la respuesta es claramente no. Imaginemos un proceso A ordenando un array de números, mientras que el proceso B calcula el promedio. Debido a que A mueve los valores entre el array, B puede encontrar un valor varias veces o incluso no encontrarlo. El resultado puede ser cualquier cosa, por lo que probablemente sea erróneo.

En algunos casos, podemos permitir a un writer actualizar una estructura de datos mientrras otros procesos la están usando. El truco es de asegurarse de que cada reader lea la versión anterior del dato, o la nueva, pero no una combinación rara de ambas.  A modo de ilustración consideremos el arbol mostrado en la figura 2-38.

![imagen2.38](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-38.png?raw=true)

Los lectores recorren el árbol desde la raíz hasta las hojas. En la media mitad del arbol se agrega un nodo X. Para ello hacemos que el nodo sea "perfecto" antes de hacerlo visible en el árbol: inicializamos todos los valores del nodo X, incluidos los punteros a sus hijos.Luego con una escritura atómica hacemos que X sea hijo de A. Ningún lector leerá nunca una versión inconsistente. En la mitad inferior del arbol, eliminamos B y D. Primero, hacemos que el puntero izquierdo de A apunte a C. Todos los lectores que estaban en A continuarán en el nodo C y nunca verán B o D. En otras palabras sólo verán la nueva versión.
Del mismo modo, los lectores que se encuentren en B o D continuarán siguiendo los punteros de la estructura de datos original y verán la versión antigua. Todo va bien y nunca necesitaremos bloquear nada. La razón principal por la que la eliminación de B y D funciona sin bloquear la estructura de datos, es que RCU (Read-Copy-Update), desacopla las fases de eliminación y reclamación de la actualización.

Sin embargo, hay un problema, mientras no estemos seguros que no hay más lectores para B o D, no podemos liberarlos realmente.¿Pero cuánto debemos esperar?¿Un minuto?¿Diez? Tenemos que esperar hasta que el último lector deje los nodos. RCU detemina el tiempo máximo que un lector puede mantener una referencia a la estructura de datos. Transcurrido ese tiempo, puede recuperar la memoria de forma segura. En concreto, los lectores accceden a la escritura de datos en lo que se conoce como **read-side critical section**, que puede contener cualquier código siempre y cuando no se bloquee o duerma. En ese caso, sabemos el tiempo máximo que debemos esperar. Específicamente, definimos un **grace period** como cualquier periodo de tiempo en el que sabemos que cada hilo estará fuera de la sección crítica del lado de lectura al menos una vez. Todo irá bien si esperamos una duración que sea al menos igual al periodo de gracia antes de reclamar. Como el código de una sección crítica de lectura no puede bloquearse ni dormir, un criterio sencillo es esperar a que todos los hilos hayan ejecutado un cambio de contexto.

## 2.4 SCHEDULING

Cuando un ordenador está multiprogramado, suele tener varios procesos o hilos compitiendo por la CPU al mismo tiempo. Esta situación ocurre cuando por lo menos 2 de ellos se encuentran en estado ready. Si solo hay una CPU disponible, se debe realizar una decisión para escoger el siguiente proceso a ejecutar. La parte del sistema operativo que realiza está decisión llamada el **scheduler** y el algoritmo utilizado para es llamado **scheduling algorithm**. Estos temas constituyen el objeto de las siguientes secciones.

Muchas de las mismas cuestiones que se aplican a la programación de procesos también se aplican a la programación de hilos, aunque algunas son diferentes. Cuando el kernel maneja hilos, la planificación se realiza por un hilo, sin tener en cuenta a qué proceso pertenece el hilo. Inicialmente vamos a concentrarnos en los errores de planificación aplicados a procesos  y a hilos. Más adelante veremos explícitamente la planificación de hilos y algunos de los problemas específicos que plantea. Nos ocuparemos de los chips multinúcleo en el cap 8.

### 2.4.1 Introduction to Scheduling

En los tiempos de sistemas por lotes con entradas en forma de imágenes de tarjetas en una cinta magnética, el algoritmo de programación era sencillo: solo había que ejecutar el siguiente trabajo en la cinta. Con los sistemas de multiprogramación, el algoritmo de planificación se volvió más complejo dado que habían multiples usuarios esperando por el mismo servicio. Algunos mainframes se mantuvieron combinando el batch y el timesharing service, lo que requiere que el planificador decida si el siguiente paso debe ser un trabajo por lotes o un usuario interactivo en un terminal(Como inciso, un trabajo por lotes puede ser una solicitud para ejecutar varios programas en sucesión, pero para esta sección, sólo asumiremos que es una solicitud para ejecutar un solo programa). Dado que el tiempo de CPU es un recurso escaso en estas máquinas, un buen planificador puede marcar una gran diferencia en el rendimiento percibido y la satisfacción del usuario. Por ello se ha dedicado mucho trabajo a idear algoritos de planificación inteligentes y eficientes.

Con la llegada de las computadoras personales, la situación cambió en 2 sentidos. 

Primero, la mayor parte del tiempo solo hay un proceso activo. Es poco probable que un usuario que introduce un documento en un procesador de textos, esté compilando simúltaneamente en segundo plano. Cuando el usuario escribe una orden en el procesador de textos, el planificador no tiene porque hacer mucho trabajo par averiguar qué proceso debe ejecutarse: el procesador de textos es el único candidato.

Segundo, las computadoras se han vuelto mucho más rápidas con el paso de los años, por lo que la CPU ya casi nunca es un recurso escaso. La mayoría de los programas para ordenadores personales están limitados por la velocidad a la que el usuario puede introducir datos(tecleando o haciendo click), no por la velocidad a que la CPU puede procesarlos. Incluso las compilaciones que antes consumían muchos ciclos de CPU, hoy en día solo tardan segundos. Además, cuando se ejecutan 2 programas a la vez, como un procesador de textos y una hoja de cálculo, apenas importa cuál va primero, ya que el usuario probablemente está esperando que terminen los 2. En consecuencia, la planificación no tiene mucha importancia en las PCs sencillas. Por supuesto, hay aplicaciones que prácticamente se comen viva a la CPU. Por ejemplo, renderizar una hora de video en alta resolución mientras se ajustan los colores de cada uno de los 107892 frames en NTSC o 90 000 frames en PAL, esto requiere una potencia de cálculo industrial. Aplicaciones similares a esta son excepciones.

Cuando vamos a los servidores network, vemos que múltiples procesos compiten continuamente por el CPU, entonces la planificación es importante nuevamente. Por ejemplo, cuando la CPU escoge entre ejecutar un proceso que recoja las estadísticas diarias y otra que atienda las peticiones de los usuarios, éstos estarán mucho más contentos si esta última se queda con la CPU en primer lugar.

El argumento de "abundancia de recursos" no es igual de sustentable en CPUs como en los smartphones (excepto quizás los modelos más potentes) y nodos en redes de sensores. En los smartphones, la CPU puede ser más débil y la memoria más pequeña. Otro punto a tomar en cuenta es la batería, cuyo tiempo de vida es más importante en estos dispositivos por lo que los planificadores tratan de optimizar el consumo de esta.
Además de escoger el proceso correcto para ejecutar, el planificador debe preocuparse de realizar un uso eficiente de la CPU, dado que el cambio entre procesos es caro. Para comenzar, debe producirse un cambio del modo de usuario al modo kernel. A continuación, se debe guardar el estado del proceso actual, incluyendo el almacenamiento de sus registros en la tabla de proceso para que puedan ser recargados más tarde. En algunos sistemas, el memory map también debe guardarse. Luego, un nuevo proceso debe ser seleccionado por el algoritmo del planificador para que se ejecute. Además de todo esto, el cambio de proceso puede invalidar la memoria cache y las tablas relacionadas, obligando a recargarla dinámicamente desde la memoria principal 2 veces(al entrar en el kernel y al salir de él). En definitiva, realizar demasiados cambios de proceso por segundo puede consumir una cantidad sustancial de tiempo en CPU, por lo que se recomienda precaución.

#### Process Behavior

Casi todos los procesos alternan ráfagas de computación con peticiones de I/O (disco o red), como se muestra en la Fig. 2-39. A menudo, la CPU funciona durante un tiempo sin detenerse y a continuación realiza una llamada al sistema para leer de un archivo o escribir en un archivo. Cuando la llamada se completa, la CPU computa denuevo hasta que necesite más datos o tenga que escribir más datos y así sucesivamente. Nótese que algunas actividades de I/O cuentan como computación. Por ejemplo, cuando la CPU copia bits a una RAM de video para actualizar la pantalla, está computando, no haciendo I/O, porque la CPU está en uso. Los I/O en este sentido es cuando un proceso entra al estado de bloqueo esperando a que un dispositivo externo complete su trabajo.

![imagen2.39](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-39.png?raw=true)

Es importante notar que en el proceso mostrado en la figura 2-39(a), este se encuentra gran parte del tiempo computando, mientras que en el ejemplo, este se encuentra esperando por un dispositivo I/O.

El primero es llamado **compute-bound** o **CPU-bound**, el segundo es llamado **I/O bound**. 

Los procesos ligados a la computación suelen tener ráfagas largas de CPU, y por tanto, la espera de I/O es poco frecuente. Por otro lado, los procesos ligados a los I/O tienen ráfagas cortas de CPU y por tanto, esperas de I/O frecuentes. Tenga en cuenta que el factor clave es la duración de la ráfaga de CPU, no la duración de la ráfaga de I/O. Los procesos I/O bound son I/O bound porque no computan mucho entre peticiones I/O, no porque tengan peticiones I/O especialmente largas. Se tarda el mismo tiempo en emitir la petición de hardware para leer un bloque de disco, independientemente de lo mucho o poco que se tarde en procesar los datos después de que lleguen. 

Cabe destacar que a medida que las CPUs se hacen más rápidas, los procesos tienden a estar más ligados a los I/O. Este efecto ocurre porque las CPUs mejoran mucho más rápido que los discos. Como consecuencia es probable que la planificación de procesos ligados a I/O se convierta en un tema más importante en el futuro. La idea básica aquí es que si un proceso ligado a I/O quiere ejecutarse, debe tener una oportunidad rápidamente para que pueda emitir su petición de disco y mantener al disco ocupado.

Como vimos en la Fig. 2-6, cuando los procesos están ligados a la E/S, se necesitan bastantes de ellos para mantener la CPU totalmente ocupada.

#### When to Schedule

Un problema clave relacionado a la planificación es cuando se deben tomar decisiones de planificación. 
Resulta que cuando hay una gran variedad de situaciones en las que es necesario planificar. Primero, cuando un proceso es creado, se necesita decidir si se va a ejecutar el proceso padre o el hijo. Desde que ambos procesos se encuentran en estado listo, es una decisión normal de planificación y puede ir en cualquier dirección, es decir, el planificador puede elegir ejecutar el programa padre o el hijo.

Segundo, una decisión de planificación debe darse cuando se termine un programa. Este proceso ya no podrá ejecutarse, entonces otro proceso que se encuentre listo debe escogerse. Si no se encuentra algún proceso, normalmente se ejecuta un proceso inactivo suministrado por el sistema.

Tercero, cuando un proceso se bloquea en I/O, en un semáforo, o por alguna otra razón, debe escogerse otro programa para ejecutarse. Aveces el motivo del bloqueo puede influir en la elección. Por ejemplo, si A es un proceso importante y está esperando a que B salga de la región crítica, dejar que B se ejecute a continuación le permitirá salir de su región crítica y así dejar que A continúe. El problema, es que el planificador generalmente no tiene la información necesaria para tener estas dependencias en cuenta.

Cuarto, cuando una interrupcion I/O ocurre, se debe tomar una decisión de planificación. Si una interrupción viene de un I/O que ahora ha completado su trabajo, algún proceso que estaba bloqueado esperando la I/O puede estar ahora listo para ejecutarse. Es decisión del planificador quien va a ser el nuevo proceso a ejecturase, el proceso que se estaba ejecutando antes de la interrupción u otro proceso.

Si un clock en el hardware provee interrupciones periódicas en los 50 o 60 Hz o en alguna otra frecuencia, una decisión de planificación puede realizarse en cada interrupción de clock o cada *k* interrupciones de clock. Los algoritmos de planificación pueden dividirse en 2 categorías respecto a como lidiar con las interrupciones de clock. Un **nonpreemptive** algoritmo de planificación toma un proceso para ejecutar y luego simplemente lo deja correr hasta que se bloquea(ya sea por I/O o esperando otro proceso) o libera voluntariamente la CPU. Incluso si este es ejecutado por muchas horas, este no puede ser suspendido forzosamente. En efecto, no se realizan decisiones de planificación durante las interrupciones de clock. Una vez finalizado el procesamiento de la interrupción de reloj, se reanuda el proceso que se estaba ejecutando antes de la interrupción, a menos que un proceso de mayor prioridad estuviera esperando un tiempo de espera ya cumplido.

Por otro lado, un **preemptive** algoritmo de planificación toma un proceso y lo deja ejecutando por un máximo de tiempo determinado. Si dicho proceso se mantiene ejecutando hasta el final de este tiempo, este es suspendido y el planificador escoge otro proceso para ejecutarse(si alguno está disponible). Realizar este tipo de planificación preferente requiere tener una interrupcion de reloj al final de cada intervalo de tiempo para devolverle el control de la CPU al planificador. Si no hay reloj disponible, la programación no preferente es la única opción.

#### Categorías de algoritmos de planificación

No es de sorprender el hecho de que distintos casos requieren distintos algoritmos de planificación. Esta situación surge debido a las distintas areas de aplicación(y diferentes tipos de sistemas operativos)
requieren distintos objetivos. En otras palabras, lo que el algoritmo de planificación debe optimizar no es siempre lo mismo para todos los sistemas. Se distinguen 3 entornos:

-   Lote
-   Interactivo
-   Tiempo real

Los sistemas por lotes se siguen utilizando mucho en el mundo empresarial para hacer payroll, inventarios, cuentas por cobrar, cuentas por pagar, cálculo de intereses(en los bancos), tramitación de siniestros(en las aseguradoras) y otras tareas periódicas. En los sistemas por lotes, no hay usuarios impacientes esperando las respuestas rápidas a solicitudes breves. En consecuencia, los algoritmos no preferentes, o preferentes con largos periodos de tiempo para cada proceso, suelen ser aceptables. Este enfoque reduce los cambios de proceso y por tanto mejorará el rendimiento. Los algoritmos por lotes son en realidad bastante generales y a menudo aplicables también a otras situaciónes, lo que hace que merezca la pena estudiarlos.

En un entorno con usuarios interactivos, la preferencia es importante para mantener un proceso  acaparando la CPU y negar el servicio a los demás. Incluso si no hay procesos ejecutandose para siempre, un proceso podría dejar afuera a todos los demás indefinidamente debido a un bug del programa. La preferencia es necesaria para evitar este comportamiento. Los servidores también entran en esta categoría, ya que normalmente sirven a múltiples usuarios(remotos), todos ellos con mucha prisa. Los usuarios de ordenadores siempre tienen mucha prisa.

En los sistema con restricciones de tiempo real, curiosamente aveces no es necesaria la preferencia dado que los procesos saben que no pueden ejecutarse durante largos periodos de tiempo y suelen hacer su trabajo y bloquearse rápidamente. La diferencia con los sistemas interactivos es que los sistemas en tiempo real sólo ejecutan programas destinados a hacer avanzar la aplicación en cuestión. Los sistemas interactivos son de propósito general y pueden ejecutar programas arbitrarios que no son cooperativos e incluso que pueden ser maliciosos.

#### Scheduling Algorithm Goals

Con el fin de diseñar un algoritmo de planificación, es necesario tener idea de que tan bueno debe ser un algoritmo. Algunos objetivos dependen del entorno(lote, interactivo o tiempo real), pero algunos son deseables en todos los casos. Algunos objetivos son listados en la figura 2-40.

![imagen2.40](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-40.png?raw=true)

En cualquier caso, la equidad es importante. Los procesos comparabalbes deben recibir un servicio comparable. Dar a un proceso mucho más tiempo que a otro equivalente no es justo. Por supuesto, distintas categorías de procesos pueden ser tratados de manera diferente. Piense en el control de seguridad y en hacer las nóminas(payroll) en el centro informático de un reactor nuclear. Algo relacionado con la equidad es la aplicación de las políticas del sistema. Si la política local es que los procesos de control de seguridad se ejecuten cuando quieran, incluso si esto significa que la nómina se retrasa 30 segundos, el programador tiene que asegurarse que esta política se cumpla.

Otro objetivo general es mantener todas las partes del sistema ocupadas siempre que sea posible. Si la CPU y todos los dispositivos I/O pueden mantenerse en funcionamiento todo el tiempo, se realiza más trabajo por segundo que si algunos de los componentes están inactivos. En un sistema por lotes, por ejemplo, el programador tiene el control de qué trabajos se traen a memoria para ejecutarse.

Tener algunos procesos ligados a la CPU y algunos procesos ligados a los I/O en la misma memoria es una mejor idea que primero cargar y ejecutar todos los trabajos ligados a la CPU y cuando terminan, cargar y ejecutar todos los trabajos ligados a los I/O. Si se utiliza esta última estrategia, cuando los proceso ligados a la CPU se estén ejecutando, lucharán por la CPU y el disco estará inactivo. Más tarde cuando lleguen los trabajos ligados al I/O, lucharán por el disco y la CPU estará ociosa. Es mejor mantener todo el sistema funcionando a la vez mediante una cuidadosa mezcla de procesos.

Los responsables de grandes centros informáticos que ejecutan muchos trabajos por lotes suelen fijarse en 3 parámetros para comprobar el rendimiento de sus sistemas: rendimiento, tiempo de respuesta y utilización de CPU. **Throughput** es el número de trabajos por hora completados por el sistema. **Turnaround time** es el tiempo medio estadístico desde el momento en que se envía un trabajo por lotes hasta el momento en que se completa. Mide cuanto tiempo tiene que esperar un usuario promedio para obtener la salida.

Un algoritmo de planificación que trate de maximizar el rendimiento no necesariamente debe reducir el tiempo de respuesta. Por ejemplo, dado un conjunto de trabajos cortos y largos, un planificador que siempre ejecute trabajos cortos y nunca ejecute trabajos largos podría lograr un rendimiento excelente(muchos trabajos cortos por hora), pero a costa de un tiempo de respuesta terrible para los trabajos largos. Si los trabajos cortos siguieran llegando a un ritmo bastante constante, los trabajos largos podrían no ejecutarse nnunca, con lo que el tiempo de ejecución sería infinito y se lograría un alto throughput.

La utilización de la CPU se utiliza a menudo como métrica en los sistemas por lotes. Sin embargo, no es una buena métrica. Lo que realmente importa es cuántos trabajos por hora salen del sistema(rendimiento) y cuánto tiempo se tarde en recuperar un trabajo(tiempo de respuesta). Utilizar el uso de CPU como métrica es como clasificar los autos en función de cuántas veces por hora gira el motor. Sin embargo, saber cuándo la utilización de la CPU es casi del 100% es útil para saber cuándo es el momento de conseguir más potencia de cálculo.

En el caso de los sistemas interactivos , los objetivos son distintos. El más importante es minimizar el tiempo de respuesta, es decir, el tiempo que transcurre entre la emisión de un comando y la obtención del resultado. En un ordenador personal en el que se esté ejecutando un proceso en segundo plano(por ejemplo, leyendo y almacenando correo electrónico de la red) una petición del usuario para iniciar un programa o abrir un archivo debe tener prioridad sobre el trabajo en segundo plano. Hacer que todas las peticiones interactivas vayan primero se percibirá como un buen servicio.

Un problema relacionado es **proportionality**. Los usuarios tiene una idea a menudo incorrecta del tiempo que deben tardar las cosas. Cuando una solicitud que el usuario percibe como compleja tarda mucho, los usuarios lo aceptan, pero cuando una solicitud que se percibe como sencilla tarda mucho, los usuarios se irritan. Por ejemplo, si hacer click en un icono que inicia la carga de un video de 500 MB a un servidor en la nube tarda 60 segudos, el usuario probablemente lo aceptará como un hecho porque no espera la carga tarde 5 segundos. El sabe que toma tiempo.

Por otro lado, cuando un usuario hace click en el icono que interrumpe la conexión con el servidor en la nube después de cargar el video, sus expectativas son diferentes. Si no se ha completado después de 30 segundos, el usuario probablemente se enojará y después de 60 segundos será peor. Este comportamiento se debe a la percepción común del usuario de que se supone que enviar muchos datos lleva mucho más tiempo que interrumpir la conexión. En algunos casos(como éste), el planificador no puede hacer nada sobre el tiempo de respuesta, pero en otros sí, especialmente cuando el retraso se debe a una mala elección del orden de los procesos.

Los sistemas en tiempo real tienen propiedades distintas que los sistemas interactivos, y por ende, diferentes objetivos de planificación. Están caracterizados por tener deadlines que deben o almenos deberían cumplirse. Por ejemplo, si un ordenador controla un dispositivo que produce datos a un ritmo regular, si no se ejecuta el proceso de recogida de datos a tiempo pueden perderse datos. Por tanto, la principal necesidad de un sistema en tiempo real es cumplir todos o la mayoría de los deadlines.

En algunos sistemas de tiempo real, especificamente en aquellos relacionados al mutimedia, la predictabilidad es importante. Perder algún deadline no es fatal, pero si el proceso de audio se ejecuta inadecuadamente, la calidad del sonido puede deteriorarse rápidamente. El video también es un problema, pero el oido es mucho más sensible a las fluctuaciones que el ojo. Para evitar este problema, la planificación de los procesos debe ser muy previsible y regular. En este capítulo estudiaremos los algoritmos de planificacion por lotes e interactivos.

### 2.4.2 Scheduling in Batch Systems

Es hora de pasar de las cuestiones generales de planificación a los algoritmos de planificación específicos. En esta sección analizaremos los algoritmos utilizados en los sistemas por lotes. Luego examinaremos sistemas interactivos y en tiempo real. Cabe señalar que algunos algoritmos se utilizan tanto en sistemas por lotes como interactivos.

#### First-Come, First-Served

Probablemente, el más sencillo de todos los algoritmos de planificación es el de orden de llegada no preferente. Con este algoritmo, a los procesos se les asigna la CPU en el orden que la solicitan. Básicamente, hay una única cola de procesos listos.
Cuando el primer trabajo entra en el sistema desde el inicio de la mañana, se inicia inmediatamente y se le permite funcionar el tiempo que quiera. No se interrumpe porque haya durado demasiado. A medida que entran los otros trabajos, se ponen al final de la cola. Cuando el proceso en ejecución se bloquea, se ejecuta a continuación el primer proceso de la cola. Cuando un proceso bloqueado está listo, como un trabajo recién llegado, se coloca al final de la cola, detrás de todos los procesos en espera.

Lo bueno de este algoritmo es que es fácil de entender y fácil de programa. También es justo en el mismo sentido en el que es justo asignar las escasas entradas para un concierto o los Iphones a las personas que están dispuestas a hacer la cola desde temprano. Con este algoritmo, una única lista enlazada lleva la cuenta de todos los procesos listos. Elegir un proceso para ejecutarlo sólo requiere retirar uno de la parte delantera de la cola. Añadir un nuevo trabajo o proceso desbloqueado solo requiere agregarlo al final de la cola.

Sin embargo, el orden de llegada tambien tiene una gran desventaja. Supongamos que hay un proceso de cálculo que se ejecuta durante 1 segundo cada vez y muchos procesos de I/O que utilizan poco tiempo de CPU, pero cada uno tiene que realizar 1000 lecturas de disco para completar. El proceso de cálculo se ejecuta durante un segundo, luego lee un bloque del disco. Todos los procesos de I/O se ejecutan y comienzan a leer el disco.
Cuando el proceso de cálculo obtiene su bloque de disco, se ejecuta durante otro segundo, seguido por todos los procesos de I/O en rápida sucesión.

<<<<<<< HEAD
El resultado neto es que cada proceso de I/O puede leer un bloque por segundo y tardará 1000 segundos en terminar. Con un algoritmo de planificación que se adelantara al proceso de cálculo cada 10 mseg, los procesos de I/O terminarían en 10 seg en lugar de 1000 seg y sin ralentizar mucho el proceso de cálculo.
=======
El resultado neto es que cada proceso de I/O puede leer un bloque por segundo y tardará 1000 segundos en terminar. Con un algoritmo de planificación que se adelantara al proceso de cálculo cada 10 mseg, los procesos de I/O terminarían en 10 seg en lugar de 1000 seg y sin ralentizar mucho el proceso de cálculo. 
>>>>>>> 9bf386f (update L3)

#### Shortest Job First

Veamos ahora otro algoritmo por lotes no preventivo que asume que los tiempos de ejecución se conocen de antemano. En una compañía de seguros, por ejemplo, la gente puede predecir con bastante exactitud cuánto tardará en tramitarse un lote de 1000 reclamaciones, dado que se realiza un trabajo similar todos los días. Cuando hay varios trabajos igual de importantes en la cola de entrada esperando a ser iniciados, el planificador escoge primero el **shortest job first**. Veamos la figura 2-41, acá podemos encontrar 4 trabajos A, B , C y D con tiempos de ejecución de 8, 4, 4 y 4 minutos respectivamente. Si ejecutamos estos procesos en dicho orden, el tiempo de respuesta para A es de 8 minutos, para B es de 12 minutos, para C es de 16 minutos y para D es de 20 minutor con un promedio de 14 minutos.

![imagen2.41](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-41.png?raw=true)


Ahora consideremos ejecutar estos 4 procesos usando el shortest job first, como se ve en la figura 2-41(b). Los tiempos de respuesta ahora son de 4, 8, 12 y 20 minutos con un promedio de 11 minutos. Shortest job first es probablemente óptimo. Consideremos el caso de 4 trabajos coin tiempos de ejecución de a, b, c y d respectivamente. El primer trabajo termina con un tiempo a, el segundo con a +b y así sucesivamente. El promedio de tiempo de espera es de (4a + 3b + 2c +d)/4. Es claro que a contribuye más al promedio  que los otros tiempos, entonces tiene que ser el trabajo más corto, seguido de b, luego c y finalmente d como el más largo dado que este afectá más al tiempo promedio. Los mismos argumentos aplican para cualquier número de trabajos.

Cabe señalar que el trabajo más corto primero solo es óptimo cuando todos los trabajos están disponibles simultáneamente. Veamos un contraejemplo, consideremos 5 trabajos de A hasta E con tiempos de trabajo 2, 4, 1, 1 y 1 respectivamente. Sus tiempos de llegada con 0,0,3,3 y 3. Inicialmente solo A y B pueden ser reprogramados, dado que los otros trabajos todavía no están disponibles. Usando el trabajo más corto primero, vamos a ejecutar los trabajos en el orden A,B, C, D, E con un promedio de 4.6. De todos modos, ejecutar en el orden B, C, D, E, A tiene un promedio de 4.4.

#### Shortest Remaining Time Next

Una versión preferente del shortest time first es el **shortest remaining time next**. Con este algoritmo, el planificador siempre va a escoger al proceso cuyo tiempo de ejecución restante es el más corto. También en este caso, el tiempo de ejecución debe conocerse de antemano. Cuando llega un nuevo trabajo, su tiempo total se compara con el tiempo restante del proceso actual. Si el nuevo trabajo necesita menos tiempo para terminar que el proceso actual, se suspende el proceso actual y se inicia el nuevo trabajo. Este esquema permite que los nuevos trabajos cortos obtengan un buen servicio.

### 2.4.3 Scheduling in Interactive Systems

Vamos a ver algunos algoritmos que pueden ser usados en sistemas interactivos. Estos son comunes en computadoras personales, servidores y otros tipos de sistemas.

#### Round-Robin Scheduling

Uno de los algoritmos más antiguos, sencillos, justos y utilizados es el **round robin**. A cada proceso se le asigna un intervalo de tiempo, llamado **quantum**, durante el cual puede ejecutarse. Si el proceso sigue en marcha al final del quantum, la CPU se adelanta y se da a otro proceso. Si el proceso es bloqueado o es finalizado antes de que el quantum haya pasado, el cambio de CPU se da cuando el procesose haya bloqueado o finalizado. Round robin es fácil de implementar. Todo lo que el planificador necesita hacer es mantener una lista de procesos ejecutables, como se muestra en la Fig. 2-42(a). Cuando el proceso agota su quantum, se coloca al final de la lista, como se muestra en la Fig. 2-42(b). El único problema realmente interesante del round robin es la duración del quantum. Pasar de un proceso a otro requiere cierto tiempo para realizar toda la administración- guardar y cargar registros y mapas de memoria, actualizar varias tablas y listas, vaciar y recargar la memoria caché, etc.

![imagen2.42](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-42.png?raw=true)

Supongamos que este **process switch** o **context switch**, como es llamado aveces, toma 1 msec, incluyendo cambiar los mapas de memoria, vaciar y recargar la caché, etc. También supongamos que un quantum es de 4msec. Con estos parámetros, después de realizar 4msec de arduo trabajo, la CPU tendrá que gastar(es decir, desperdiciar) 1 mse en el cambio de proceso. Entonces 20% del tiempo en CPU se tomará como overhead administrativo. Esto es demasiado.

Para mejorar la eficiencia, cambiemos el quantum a 100 msec. Ahora el tiempo de desperdicio es del 1%. Pero piense en lo que ocurre en un sistema servidor si entran 50 peticiones en un intervalo de tiempo muy corto y con requisitos de CPU muy variables. Si la CPU está inactiva, la primera va a comenzar inmediatamente, la segunda no va a comenzar hasta 100 msec después. El desafortunado último puede tener que esperar 5 segundos antes de tener una oportunidad, suponiendo que todos los demás utilicen todos sus quantums. La mayoría de usuarios percibirán como lenta una solicitud de 5 segundos a una orden corta. Esta situación es especiamente mala si algunas de las peticions cercanas al final tienen solo unos milisegundos de tiempo de CPU. Con un quantum corto, habrían obtenido un mejor servicio.

Otro factor es que si el quantum se fija más largo que la ráfaga media de la CPU, el adelantamiento no ocurrirá muy a menudo. En su lugar, la mayoría de los procesos realizarán una operación de bloqueo antes de que se agote el quantum, provocando un cambio de proceso. La eliminación del adelantamiento mejora el rendimiento porque los cambios de proceso sólo se producen cuando son lógicamente necesarios, es decir, cuando un proceso se bloquea y no puede continuar.

La conclusión se puede formular como: tener un quantum muy corto puede causar muchos cambios de procesos, los cuales pueden disminuir la eficiencia de la CPU, pero tener quantums muy largos pueden causar una pobre respuesta a solicitudes de procesos interactivos cortos. Un quantum alrededor de 20-50 msec es una opción razonable.

#### Priority scheduling

Round-robin scheduling asume implícitamente que todos los procesos son igual de importantes. Con frecuencia, las personas que poseen y manejan ordenadores multiusuario tienen ideas muy distintas al respecto. En una universidad, por ejemplo, el orden jerárquico puede ser primero el presidente, luego los decanos de la facultad, después los profesores, las secretarias, los conserjes y por último, los estudiantes. La necesidad de tener en cuenta factores externos conduce a la programación prioritaria. La idea básica es sencilla: a cada proceso se le asigna una prioridad, y el proceso ejecutable con la prioridad más alta puede ejecutarse. 

Incluso en una PC con un único propietario, pueden haber múltiples procesos, algunos de ellos más importantes que otros. Por ejemplo, a un proceso daemon que envía correo electrónico en segundo plano se le debe asignar una prioridad menor que a un proceso que muestra una película de video en la pantalla en tiempo real.

Para prevenir que los procesos de alta prioridad se ejecuten indefinidamente, el planificador puede reducir la prioridad del proceso actual en cada tick de clock(por ejemplo clada clock interrupt). Alternativamente, a cada proceso se le puede asignar un quantum de tiempo máximo que se le permite ejecutar. Cuando este quantum se agota, el siguiente proceso de mayor prioridad tiene la oportunidad de ejecutarse.

Las prioridades pueden ser asignadas a los procesos de forma estática o dinámica. En una computadora militar, los procesos iniciados por los generales podrían comenzar en prioridad 100, los procesos iniciados por los coroneles podrían comenzar en prioridad 90, mayores en 80, capitanes con 70, tenientes con 60 y así sucesivamente. Alternativamente, un centro comercial computacional puede tener procesos de alta prioridad con un costo de 100$ la hora, prioridad media 75$ la hora, y la baja prioridad 50$ la hora.  

El sistema UNIX tiene un comando, nice, que permite a un usuario reducir voluntariamente la prioridad de su proceso, para ser amable con los demás usuarios. Nadie
lo utiliza nunca.

Las prioridades pueden ser asignadas dinámicamente por el sistema para lograr ciertos objetivos del sistema. Por ejemplo, algunos procesos están muy ligados al I/O y pasan la mayor parte de su tiempo esperando a que se complete el I/O. Siempre que un proceso de este tipo quiera la CPU, se le debe dar la CPU inmediatamente, para permitirle iniciar su siguiente petición de I/O, que puede entonces proceder en paralelo con otro proceso que esté realmente computando. Hacer que el proceso de I/O espere mucho tiempo por la CPU, solo significa tenerlo ocupando memoria durante un tiempo innecesariamente largo. Un algoritmo simple para dar un buen servicio a los procesos vinculados a los I/O es setear la prioridad en 1/f donde f es la fracción del último quantum que utilizó un proceso. Un proceso que solo usó 1 msec de los 50 msec de quantum, tendrá una prioridad de 50, mientras que un proceso que usó 25 msec antes de bloquearse obtendrá una prioridad 2 y el proceso que usó todo el quantum tendrá una prioridad 1.

A menudo es conveniente agrupar los procesos en clases prioritarias y utilizar la programación prioritaria entre las clases, pero la programación round-robin dentro de cada clase. La figura 2-43 muestra un sistema con 4 clases de prioridad. 

![imagen2.43](https://github.com/gabo52/SistemasOperativos/blob/main/figures/Chapter2/figure2-43.png?raw=true)

El algoritmo de programación es el siguiente: mientras haya procesos ejecutables en la clase de prioridad 4, ejecute cada uno de ellos durante un quantum, de forma round-robin y no se moleste nunca con las clases de prioridad inferior. Si la clase de prioridad 4 está vacía, ejecute los procesos de la clase 3 con round robin. Si las clases 4 y 3 están vacías, entonces ejecute la clase 2 en round robin y así sucesivamente. Si las prioridades no se ajustan de vez en cuando, las clases de prioridad pueden morir de hambre.

#### Multiple Queues
<<<<<<< HEAD

Uno de los primeros planificadores de prioridades fue el CTSS, el M.I.T. Compatible TimeSharing System que funcionaba en el IBM 7094 (Corbato'et al., 1962). CTSS tenía el problema de que la conmutación entre procesos era lenta porque el 7094 sólo podía contener un proceso en memoria. Cada cambio significaba intercambiar el proceso actual al disco y leer uno nuevo del disco. Los diseñadores de CTSS se dieron cuenta rápidamente que era más eficiente dar a los procesos ligados a la CPU un quantum más grande de vez en cuando, en lugar de darles quantums pequeños frecuentemente(para reducir el intercambio). Por otro lado, dar a todos los procesos un quantum grande puede significar tener un tiempo de respuesta pobre, como acabamos de ver. Su solución fue implementar clases de prioridad. Procesos en la prioridad más alta tendrán todo un quantum para ejecutarse. Procesos en el siguiente nivel más alto tendrán un tiempo de ejecución de hasta 2 quantums, los siguiente procesos tendrán un tiempo máximo de 4 quantums y así sucesivamente. Cuando un proceso usa todo el quantum asignado, este desciende de clase. A modo de ejemplo, consideremos un proceso el cual necesita usar la CPU continuamente por 100 quanta. Inicialmente se le daría un quantum y luego cambiaría. La siguiente vez recibiría 2 quantums antes de ser intercambiado. En las siguientes obtendría 4, 8, 32 y 64 quantums, aunque solo hubiera utilizado 37 de los 64 quantums finales para completar su trabajo. Solo se necesitarían 7 cambios (incluyendo la carga inicial) en vez de 100 con un algoritmo puro de round-robin. Además, a medida que el proceso se hundiera más y más en las colas de prioridad, se ejecutaría cada vez con menos frecuencia, ahorrando a la CPU, procesos cortos e interactivos. 

Dicha política fue adoptada para evitar castigar a los procesos que tengan que ejecutarse por un tiempo muy largo cuando se iniciaron por primera vez, peor que se volvió interactivo más tarde. Siempre que se de un return(Enter) en la terminal, el proceso perteneciente a ese terminal fue movido a la clase de mayor prioridad, asumiendo que estaba a punto de convertirse en interactivo. Un día un usuario con un proceso que consumía mucha CPU descubrió que sentarse en la terminal y teclear carriage returns al azar cada pocos segundos, hacía maravillas con su tiempo de respuesta. Se lo contó a todos sus amigos. Ellos se lo contaron a todos sus amigos. Moraleja de la historia: hacerlo bien en la práctica es mucho más difícil que hacerlo al principio.

#### Shortest Process Next

Dado que los trabajos cortos siempre producen el menor tiempo de respuesta promedio para los sistemas de lotes, estaría poder usarlos en los procesos interactivos. Hasta cierto punto, es posible. Los procesos interactivos suelen seguir el patrón de esperar comando, ejecutar comandos, esperar comando, etc. Si consideramos la ejecución de cada comando como un "trabajo" independiente, podemos minimizar el tiempo de respuestas total ejecutando primero el más corto. El problema es averiguar cual de los procesos actualmente ejecutables es el más corto.

Un enfoque consiste en hacer estimaciones basadas en el comportamiento pasado y ejecutar el proceso con el tiempo de ejecución estimado más corto. Supongamos que el tiempo estimado por comando para un proceso es T0. Luego supongamos que su siguiente instrucción es T1. Podríamos actualizar nuestra estimación tomando una suma ponderada de estos 2 números, es decir a*T0 + (1 - a)T1. Mediante la elección de a podemos decidir que el proceso de estimación olvide rápidamente las ejecuciones antiguas o que las recuerde por mucho tiempo. Con a = 1/2 obtenemos la siguiente sucesión

    T0, T0/2 + T1/2, T0/4 + T1/4 + T2/2, T0/8 + T1/8 + T2/4 + T3/2

Después de 3 neuvos turnos, el peso de T0 ha disminuido a 1/8. La técnica de estimar el siguiente valor de una serie tomando la media ponderada del valor medido actual y la estimación anterior se denomina aveces envejecimiento. Es aplicable a muchas situaciones en las que debe hacerse una predicción basada en valores anteriores. El envejecimiento es especialmente fácil de aplicar cuando a= 1/2. Basta con sumar el nuevo valor a la estimación actual y dividir la suma por 2(desplazamiento de un bita la derecha).

#### Guaranteed Scheduling

Un enfoque completamente distinto a la planificación consiste en hacer promesas reales a los usuarios sobre rendimiento y luego cumplirlas. Una promesa realista y fácil de cumplir es la siguiente: Si hay n usuarios conectados mientras estás trabajando, recibirás aproximadamente 1/n de la potencia de la CPU. De forma similar, en un sistema de single-user con n procesos ejecutándose, debería ser igual, cada proceso obtendría 1/n ciclos de CPU. Parece justo.

Para ser buenos en esta promesa, el sistema debe mantener la cuenta de cuanto CPU debe tener cada proceso desde que se crea. A continuación, calcula la cantidad de CPU a la que cada uno tiene derecho, es decir, el tiempo transcurrido desde la creación divido entre n. Dado que también se conoce la cantidad de tiempo de CPU que cada proceso ha tenido realmente, es bastante sencillo calcular la relación entre el tiempo de CPU real consumido y el tiempo de CPU al que tiene derecho. Un ratio de 0,5 significa que un proceso solo ha tenido la mitad de lo que debería haber tenido, y un ratio de 2,0 significa que un proceso ha tenido el doble de lo que le correspondía. El algoritmo consiste en ejecutar el proceso con el ratio más bajo hasta que su ratio supere al de su competidor más cercano. A continuación este es escogido para ejecutarse.

#### Lottery scheduling 

Mientras que algunos hacen promesas a los usuarios y luego cumplirlas es buena idea, es difícil de implementar. Sin embargo, se puede usar otro algoritmo para dar de manera resultados predecibles similares con una implementación mucho más simple. Esta es llamada **lottery scheduling**.

La idea básica es dar a los procesos tickets de lotería para varios recursos del sistema como el tiempo del CPU. Cuando una decisión de planificación es tomada, se toma un ticket de lotería de forma aleatoria, y el proceso que tiene el ticket es el que accede al recurso. Luego, hablando del planificador del CPU, este puede tener 50 tickets de lotería por segundo, con cada ganador con 20msec de tiempo en el CPU como premio.

Parafraseando a George Orwell: "Todos los procesos son iguales, pero algunos procesos son más iguales". Los procesos más importantes tendrán tickets extra, para incrementar sus posibilidades de ganar. Si hay 100 tickets pendientes y un proceso tiene 20 de esos, este tiene 20% de probabilidades de anar cada lotería. A largo plazo, este tiene 20% del tiempo en CPU. En contraste con el priority scheduler, donde es bastante dificil tener una prioridad de 40, aquí la regla es clara: un proceso que contiene una fracción f de los tickets, obtendrá aproximadamente una fracción f del recurso en cuestión.

Lottery scheduling tiene varias propiedades interesantes. Por ejemplo, si aparece un nuevo proceso y se le otorgan nuevos boletos, en la próxima lotería tendrá una posibilidad de ganar en proporción al número de entradas que posee. En otras palabras, la programación de lotería es altamente receptiva.

Los proces que cooperan pueden intercambiar tickets si ellos desean. Por ejemplo, cuando un proceso de cliente envia un mensaje a un proceso de servidor y luego se bloquea, este probablemente le haya dado todos sus tickets a dicho proceso para aumentar las posibilidades de que el servidor se ejecute después. Cuando el servidor finalice, este retorna los tickets al cliente  para que esta pueda continuar ejecutándose. En ausencia de los clientes, los servidores no necesitan tickets en absolutos.

Lottery scheduling puede ser usado para resolver problemas que son difíciles de manejar con otros métodos. Un ejemplo es un servidor de videos en el cual varios procesos  están alimentando secuencias de video a sus clientes, pero a diferentes velocidades de fotogramas. Supongamos que los procesos necesitan fotogramas a 10, 20, 35 fotogramas/seg. Mediante la asignación a estos procesos con 10, 20, 25 tickets respectivamente, ellos automáticamente dividirán a la CPU en la proporción correcta, la cual es: 10, 20 y 25.

#### Fair-Share Scheduling

Hasta ahora hemos asumido está planificado por su cuenta, sin importar quien sea su propietario. Como resultado si un usuario 1 comienza 9 procesos y un usuario 2 comienza un proceso, con round-robin o prioridads iguales el usuario 1 tiene 90% de la CPU y el usuario 2 solo el 10%.

Para evitar esta situación, algunos sistemas, tienen en cuenta qué usuario posee un proceso antes de planificarlo. En este modelo, cada usuario esta asignado con una fracción de la CPU y el planificador toma procesos de tal manera que se cumplan. Entonces si a 2 usuarios se les ha prometido el 50% de la CPU, cada uno obtendrá eso, no importa cuantos procesos tengan en existencia.

A modo de ejemplo, consideremos un sistema con 2 usuarios, a cada uno se le ha prometido el 50% de la CPU. El usuario 1 tiene 4 procesos, A, B, C y D, el usuario 2 tiene solo un proceso E. Si se usa el round robin, una posible secuencia de planificacion que cumple con todas las restricciones esta:

A E B E C E D E A E B E C E D E...

Por otro lado, si el usuario 1 tiene derecho al doble de tiempo de CPU que el usuario 2:

A B E C D E A B E C D E ..

Existen numerosas posibilidades, y pueden ser exploradas según la noción de equidad que se tenga.

### 2.4.4 Scheduling in Real-Time Systems

Un sistema **real-time** es uno en el cual el tiempo juega un rol esencial. Normalmente, uno o varios dispositivos físicos externos al ordenador generán estímulos y el ordenador debe reaccionar adecuadamente a ellos en un tiempo determinado. Por ejemplo, la computadora de un reproductor de discos compactos recibe los bits a medida que salen de la unidad y debe convertirlos en música en un intervalo de tiempo muy cerrado. Si el cálculo toma mucho tiempo, la música puede sonar peculiar. Otros sistemas de tiempo real son los monitores de los pacientes en la unidad de cuidados intensivos de un hospital, el piloto automático de un avión y el control de robots en una fábrica automatizada. En todos estos casos, tener la respuesta correcta, pero tenerla en un tiempo muy prolongado puede ser tan malo como no tenerla en absoluto.

Los sistemas en tiempo real se suelen clasificar en **hard real time**, es decir, que hay plazos absolutos que deben cumplirse y **soft real time**, es decir, que el incumplimiento ocasional de un plazo no es deseable, pero sí tolerable. En ambos casos, el comportamiento en tiempo real se consigue dividiendo el programa en varios procesos, cada uno de los cuales tiene un comportamiento predecible y conocido de antemano. Estos procesos suelen ser de corta duración y pueden completarse en menos de un segundo. Cuando se detecta un evento externo, la tarea del planificador consiste en planificar los procesos de forma en que se cumplan todos los plazos.

Los eventos a los que debe responder un sistema en tiempo real pueden clasificarse en **periódicos** (es decir, que se producen a intervalos regulares) o **aperiódicos**(es decir, que se producen de forma impredecible). Un sistema puede tener que responder a múltiples flujos de eventos periódicos. Dependiendo del tiempo que requiera el procesamiento de cada evento, puede que ni siquiera sea posible gestionarlos todos.Por ejemplo, si hay m eventos periódicos y el evento i ocurre con un periodo Pi y requiere Ci segundos de CPU para manejar cada evento, entonces la carga sólo se puede manejar si.

 m
 Σ Ci/Pi ≤ 1
i=1

Un sistema en tiempo real que tenga este criterio es llamado **planificable**. Esto significa que puede ser implementado. Un proceso que falla ante este test no puede ser programable dado que el tiempo total de CPU que el proceso busca colectivamente es mayor que el que el CPU puede brindar.

Como ejemplo, consideremos un soft real-time system con 3 eventos periódicos, con periodos de 100, 200 y 500 msec, respectivamente. Si este sistema necesitara 50, 30 y 100 msec de tiempo en CPU por evento. El sistema es planificable dado que 0.5 + 0.15 + 0.2 < 1. Si un cuarto evento de un periodo de 1 sec es añadido, el sistema va a seguir siendo planificable hasta que este evento no necesite más de 150 msec de tiempo en CPU por evento. Se asume implícitamente que la sobrecarga de cambio de contexto es tan pequeña que se puede ignorar.

Los algoritmos de planificación real-time pueden ser estáticos o dinámicos. Estos últimos toman sus decisiones de planificación en tiempo de ejecución, una vez iniciada la ejecución. La planificación estática solo funciona cuando se dispone de información perfecta de antemano sobre el trabajo que hay que hacer y los plazos que hay que cumplir. Los algoritmos de programación dinámica no tienen estas restricciones.

Hasta ahora, hemos asumido tácticamente que todos los proceso del sistema pertenecen a distintos usuarios y, por tanto, compiten por la CPU. Aunque esto suele ser cierto, a veces ocurre que un proceso tiene muchos hijos ejecutándose bajo su control. Por ejemplo, un proceso de sistema de gestión de base de datos puede tener muchos hijos. Cada hijo puede estar trabajando en una solicitud diferente, o cada uno puede tener alguna función específica que realizar(análisis de consulta de datos, acceso a disco, etc.).
### 2.4.5 Policy Versus Mechanism
=======
-------
Uno de los primeros planificadores de prioridad se encontraban en CTSS, en M.I.T. Compatible TimeSharing System que funcionaba en el IBM 7094 (Corbató et al., 1962). CTSS tenía el problema de que el cambio de proceso era lento debido a que 7094 podía tener solo un proceso en memoria. Cada cambio significaba intercambiar el proceso actual al disco y leer uno nuevo del disco. Los diseñadores del CTSS rápidamente se dieron cuenta que era más eficiente dar a los procesos ligados a CPU un quantum más grande de vez en cuando, en lugar de darles quantus pequeños frecuentemente (para reducir el intercambio). Por otro lado, dar a todos los procesos un quantum grande significaría un tiempo de respuesta deficiente, como ya hemos visto. Su solución fue establecer clases de prioridad. Los procesos de la clase inmediatamente superior se ejecutaban durante 4 quantums, etc. Cuando un proceso agotaba todos los quantums que tenía asignado, descendía de clase.


>>>>>>> 9bf386f (update L3)


## APUNTES DE CLASE

En el archivo se relacionado nombre con un nodo-i. 

Todas las variables locales de funcion, parametros y punto de retorno.

Todos los hilos se encuentran dentro de segmento de texto de un mismo proceso.

cuando algunos procesos son concurrentes, esto significa que comparten recursos

Posible pregunta: 
En UNIX o en algún sistema operativo se ha usado el Strict Alternation o el Peterson's Solution
para poder evitar el race condition? En caso UNIX no lo use actualmente, qué metodo utiliza para evitar
que 2 procesos entre en race condition?

Existe alguna forma de generalizar el Peterson Solution para varios procesos? dado que este solo se muestra para 2 procesos ejecutados sim

planificador de trabajos -> scheduler
estudiar la imagen 2-28

preguntar semáforo.