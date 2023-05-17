# Cap 2

-   aging



1. **Pseudoparallelism**: Se refiere a la ilusión de ejecución paralela que se da en los sistemas con un solo procesador. Aunque solo un proceso puede ejecutarse a la vez, el cambio rápido entre procesos puede dar la apariencia de paralelismo.

2. **Multiprocessor**: Un sistema multiprocesador tiene más de un procesador físico. Esto permite la ejecución real de procesos en paralelo, mejorando el rendimiento y la eficiencia.

3. **Sequential processes**: Los procesos secuenciales se ejecutan uno después del otro, en contraste con los procesos paralelos o concurrentes que pueden ejecutarse simultáneamente.

4. **Processes**: Un proceso es una instancia de un programa en ejecución, incluyendo el estado actual de la ejecución y los recursos asignados.

5. **Multiprogramming**: Es una técnica que permite a varios procesos residir en memoria al mismo tiempo, aumentando la utilización del CPU al permitir el cambio de contexto cuando un proceso no puede continuar.

6. **Copy-on-write**: Es una técnica de optimización que retrasa la copia de un objeto hasta que es modificado. Es útil para ahorrar memoria en operaciones como la duplicación de procesos.(Cuando usamos un fork)

7. **Handle**: Es una referencia a un recurso que está gestionado por el sistema, como un archivo o un proceso. Los programas utilizan manejadores para interactuar con estos recursos. En el caso de windows el padre tiene un token especial llamado handle el cual se usa para controlar al hijo, pero de todas formas este token se puede pasar a otro proceso.

8. **Process table**: Una tabla de procesos es una estructura de datos en el sistema operativo que guarda el estado de todos los procesos. Cada entrada contiene información como el ID del proceso, el estado, los recursos asignados y otros detalles del proceso.

9. **Process control blocks (PCB)**: Un PCB es una estructura de datos que contiene la información necesaria para gestionar un proceso, incluyendo el estado del proceso, los registros del CPU, la dirección de memoria, la prioridad, los propietarios y los identificadores.

10. **Interrupt vector**: Es una estructura de datos que contiene las direcciones de las rutinas de servicio de interrupción. Cuando ocurre una interrupción, el CPU utiliza el vector de interrupciones para determinar qué función debe ejecutar.

11. **Cache**: En informática, una caché es un tipo de almacenamiento temporal y rápido que guarda datos para futuras solicitudes. Se utiliza para reducir el tiempo de acceso a datos que se utilizan con frecuencia.

12. **Dispatcher**: Es la parte del sistema operativo que da control del CPU a los procesos. Es responsable de la conmutación de contexto, cambiando el proceso que se está ejecutando.

13. **Worker thread**: En un modelo de programación multihilo, un hilo de trabajo es un hilo que se utiliza para realizar tareas en segundo plano o tareas que no requieren interacción con el usuario.(Es el hilo q)

14. **Finite-state machine**: Es un modelo de computación que tiene un número finito de estados. Puede estar en exactamente un estado en un momento dado, y los cambios de estado se disparan por eventos o condiciones.

15. **Thread**: Un hilo es la unidad más pequeña de procesamiento que puede ser gestionada por un sistema operativo. Los hilos dentro de un proceso comparten el espacio de direcciones y los recursos del proceso, pero pueden ejecutarse de forma independiente.

16. **Lightweight processes**: Es una forma de concurrencia a nivel de usuario que se utiliza para
mejorar la eficiencia en comparación con los procesos pesados. Los procesos ligeros son más eficientes porque tienen menos sobrecarga y pueden compartir recursos más fácilmente.(hilos)

1.  **Multithreading**: Es una técnica que permite la ejecución concurrente de varias partes de un programa para mejorar la eficiencia y el rendimiento.

2.  **Pthreads**: Es una biblioteca en el lenguaje C que permite la programación multihilo. Proporciona funciones para crear y gestionar hilos, así como para la sincronización y la comunicación entre hilos.

3.  **Thread table**: Es una estructura de datos que mantiene un seguimiento de todos los hilos en un proceso o en todo el sistema. Cada entrada en la tabla contiene información sobre un hilo, como su estado, su ID y la información de su contexto.

4.  **Jacket or wrapper**: En el contexto de los sistemas operativos, una chaqueta o envoltorio es una función o rutina que proporciona una interfaz uniforme para una operación subyacente que puede variar entre sistemas o entornos. Por ejemplo, un envoltorio puede proporcionar una interfaz de sistema de archivos uniforme que puede utilizarse con varios sistemas de archivos subyacentes.
El código que se coloca alrededor de la llamada al sistema para realizar la comprobación(ejemplo del read) se denomina cubierta o envoltura.


21. **Scheduler activations**: Es un mecanismo que permite al núcleo del sistema operativo y a la biblioteca de hilos a nivel de usuario cooperar en la programación de hilos. Esto permite una programación más eficiente y un mejor rendimiento en sistemas multihilo. 

Cuando se utilizan Scheduler activations, el núcleo asigna un determinado número de procesadores virtuales a cada proceso y deja que el sistema de ejecución (espacio de usuario) asigne hilos a los procesadores. Este mecanismo también puede utilizarse en un multiprocesador en el que los procesadores virtuales pueden ser CPU reales. El número de procesadores virtuales asignados a un proceso es inicialmente uno, pero el proceso puede pedir más y también puede devolver los procesadores que ya no necesita.

22. **Upcall**: Es una técnica de comunicación entre el núcleo del sistema operativo y el espacio de usuario. Un upcall es una llamada de procedimiento desde el núcleo a una función específica en el espacio de usuario.

23. **Pop-up thread**: Es un hilo creado por el núcleo del sistema operativo en respuesta a un evento, como una interrupción de hardware. Los hilos emergentes permiten al sistema operativo manejar eventos de forma asincrónica.

24. **InterProcess Communication (IPC)**: Es un conjunto de técnicas que permiten a los procesos intercambiar datos y señales. Los mecanismos de IPC incluyen tuberías, sockets, semáforos, memoria compartida y colas de mensajes.

25. **Spooler directory**: En los sistemas operativos, un directorio de spooler es un lugar en el sistema de archivos donde los trabajos de impresión o correo electrónico se almacenan temporalmente antes de ser procesados.

26. **Race conditions**: Es una situación en la que el comportamiento de un sistema depende del orden relativo o la temporización de los eventos. Las condiciones de carrera pueden causar errores o comportamientos inesperados si no se manejan correctamente.

27. **Mutual exclusion**: Es una propiedad de los sistemas concurrentes que garantiza que solo un proceso o hilo puede acceder a un recurso compartido a la vez. La exclusión mutua se utiliza para prevenir condiciones de carrera.

28. **Critical region**: Es una sección de código que accede a recursos compartidos y que debe ejecutarse de manera atómica para prevenir condiciones de carrera. La exclusión mutua se utiliza para proteger las regiones críticas.

29. **Busy waiting**: Es una técnica en la que un proceso en un sistema multiprocesador verifica continuamente una condición en lugar de proceder de inmediato. Esto se considera ineficiente ya que el proceso consume tiempo de CPU que podría utilizarse para otros procesos.

30. **Spin lock**: Es un tipo de bloqueo que utiliza la espera ocupada. Cuando un proceso no puede adquirir un bloqueo de giro, sigue intentándolo hasta que tiene éxito, en lugar de cambiar a otro trabajo.

31. **Priority inversion problem**: Es un escenario en el que un proceso de alta prioridad se ve obligado a esperar a un proceso de baja prioridad debido al uso de un recurso compartido. Esto puede llevar a problemas de rendimiento y a la violación de los plazos de tiempo real.

32. **Bounded-buffer**: Es una región de memoria utilizada para el intercambio de datos entre procesos. El buffer tiene un tamaño fijo y se utiliza un mecanismo de sincronización para garantizar que los datos no se sobrescriban o se consuman antes de que estén listos.(como para el problema del productor-consumidor)

33. **Wakeup waiting bit**: Es una técnica utilizada en algunos sistemas operativos para evitar la espera ocupada. Cuando un proceso no puede continuar, establece un bit de espera y se pone en un estado de espera, liberando así el CPU para otros procesos.
    
Esto es para casos análogos al siguiente: un proceso manda una señal wake a otro proceso, sin embargo este proceso no se encontraba dormido, por lo que la señal se pierde, en consecuencia, cuando este vaya a dormir dormirá para siempre. Con el wakeup waiting bit, si el proceso recibe la señal y estaba despierto, la señal se "guarda" en el bit para despertarse cuando vaya a dormir.

34. **Semaphore**: Es una variable especial utilizada para la sincronización entre procesos. Los semáforos pueden utilizarse para proteger una región crítica, para coordinar la cooperación entre procesos, o para evitar condiciones de carrera.

35. **Atomic action**: Es una operación que se completa en su totalidad sin ser interrumpida. Las acciones atómicas son importantes en los sistemas concurrentes para prevenir condiciones de carrera.

36. **Binary semaphores**: Son semáforos que solo pueden tener los valores 0 o 1. Se utilizan para implementar la exclusión mutua en la sincronización de procesos.

37. **Synchronization**: En el contexto de los sistemas operativos, la sincronización se refiere a la coordinación de la ejecución de múltiples procesos para garantizar un comportamiento correcto.

38. **Mutex**: Es un objeto de sincronización que permite la exclusión mutua. Solo un hilo puede poseer un mutex a la vez, y cualquier otro hilo que intente adquirir el mutex será bloqueado hasta que el hilo propietario lo libere.

39. **Futex**: Es un mecanismo de sincronización en el kernel de Linux que proporciona bloqueos rápidos en el espacio de usuario cuando no hay contención, y se degrada a bloqueos en el espacio del kernel cuando hay contención.
Si no se trata de cerrar un futex cerrado, no se realiza la llamada al kernel, esta llamada solo se da para encolar o desencolar procesos de la cola de espera de procesos.

40. **Condition variables**: Son objetos de sincronización utilizados para bloquear un hilo hasta que se cumpla una determinada condición. Se utilizan en combinación con mutex para sincronizar la ejecución de varios hilos.

41. **Monitor**: En la concurrencia, un monitor es un objeto de sincronización que permite a múltiples hilos cooperar en la ejecución de un programa. Un monitor tiene un bloqueo interno y variables de condición que permiten a los hilos esperar hasta que se cumpla una determinada condición.

42. **Message passing**: Es un mecanismo de comunicación entre procesos que permite el intercambio de datos y señales a través de mensajes. El paso de mensajes puede ser síncrono o asíncrono.

43. **Acknowledgement**: En los sistemas de comunicación, un reconocimiento es una señal enviada por el receptor para indicar que un mensaje o un paquete de datos ha sido recibido correctamente.

44. **Authentication**: Es el proceso de verificar la identidad de un usuario, proceso o dispositivo. La autenticación es crucial para la seguridad de los sistemas informáticos.

45. **Mailbox**: En los sistemas operativos, un buzón es una ubicación en memoria utilizada para almacenar mensajes entre procesos. Un proceso puede enviar un mensaje a un buzón, y otro proceso puede leer el mensaje en un momento posterior.

46. **Rendezvous**: Es un método de sincronización en el que dos procesos coordinan su ejecución para encontrarse en un punto específico. Se utiliza para el intercambio seguro de información entre procesos.

47. **MPI (Message-Passing Interface)**: Es una especificación para el paso de mensajes en programas paralelos. MPI proporciona una interfaz estándar para la comunicación entre procesos en un sistema de computación paralela.

48. **Barrier**: En programación paralela, una barrera es un tipo de sincronización que hace que un grupo de hilos o procesos se detenga en un punto específico hasta que todos los miembros del grupo hayan alcanzado ese punto.

49. **RCU (Read-Copy-Update)**: Es un mecanismo de sincronización en el kernel de Linux que permite a las operaciones de lectura y escritura en estructuras de datos compartidas proceder en paralelo para mejorar el rendimiento.

50. **Read-side critical section**: En el contexto de RCU, es una sección de código que puede ser ejecutada por múltiples lectores al mismo tiempo, pero que es protegida de las modificaciones concurrentes mediante el uso de RCU.

51. **Grace period**: En el contexto de RCU, es un período de tiempo durante el cual todas las secciones críticas de lectura que estaban en ejecución cuando comenzó el período de gracia deben haberse completado. Después de un período de gracia, las actualizaciones pueden ser seguramente liberadas.

52. **Scheduler**: Es la parte del sistema operativo que decide qué proceso debe ejecutarse en el CPU en un momento dado. El programador utiliza un algoritmo de programación para tomar esta decisión.

53. **Scheduling algorithm**: Es el algoritmo utilizado por el programador para decidir qué proceso debe ejecutarse en el CPU. Los algoritmos de programación pueden basarse en la prioridad, el tiempo de CPU utilizado, el tiempo de espera, la llegada de trabajos, entre otros factores.

54. **Compute-bound**: Se refiere a los procesos o sistemas que están limitados por la velocidad de la CPU. Estos procesos pasan la mayor parte de su tiempo realizando cálculos en lugar de esperar a las operaciones de I/O.

55. **I/O-bound**: Se refiere a los procesos o sistemas que están limitados por la velocidad de las operaciones de entrada/salida. Estos procesos pasan la mayor parte de su tiempo esperando a las operaciones de I/O en lugar de realizar cálculos.

56. **Nonpreemptive**: En la programación no preventiva, una vez que un proceso ha sido asignado al CPU, continúa ejecutándose hasta que se completa o hasta que se bloquea por una operación de I/O.

57. **Preemptive**: En la programación preventiva, el sistema operativo puede interrumpir un proceso en ejecución y reasignar el CPU a otro proceso. Esto se hace para asegurar un reparto equitativo del CPU entre los procesos y para mejorar la respuesta y la utilización del sistema.

58. **Throughput**: Se refiere a la cantidad de trabajo que un sistema puede procesar en un período de tiempo dado. En el contexto de los sistemas operativos, esto podría referirse a la cantidad de procesos que pueden completarse en un período de tiempo.

59. **Turnaround time**: Es el tiempo total que tarda un proceso desde que se envía hasta que se completa. Incluye el tiempo que el proceso pasa en la cola de espera, en la CPU y realizando operaciones de I/O.

60. **Response time**: Es el tiempo que transcurre desde que se envía una solicitud hasta que se recibe la primera respuesta. En el contexto de los sistemas operativos, esto podría referirse al tiempo que tarda un proceso en comenzar a ejecutarse después de que ha sido programado.

61. **Proportionality**: En el contexto de la programación, la proporcionalidad es un objetivo de los algoritmos de programación que buscan equilibrar el tiempo de CPU entre los procesos en función de su prioridad o de algún otro factor.

62. **First-come, first-served**: Es un algoritmo de programación simple que asigna el CPU a los procesos en el orden en que llegan. Este algoritmo es fácil de implementar, pero puede llevar a una mala utilización del CPU y a largos tiempos de espera para los procesos.

63. **Shortest job first**: Es un algoritmo de programación que asigna el CPU al proceso con el menor tiempo de ejecución estimado. Este algoritmo puede mejorar el rendimiento, pero requiere que el sistema operativo tenga información sobre el tiempo de ejecución de los procesos.

64. **Shortest remaining time next**: Es una variante preemptiva del algoritmo de programación de trabajos más cortos primero. Asigna el CPU al proceso con el menor tiempo de ejecución restante.

65. **Round robin**: Es un algoritmo de programación que asigna el CPU a los procesos en un orden circular, asignando a cada proceso un intervalo de tiempo fijo, o quantum, antes de pasar al siguiente proceso.

66. **Quantum**: Es el intervalo de tiempo durante el cual un proceso puede ejecutarse en un sistema de programación de round robin. Después de que el quantum ha expirado, el proceso actual es interrumpido y el CPU es asignado al siguiente proceso.

67. **Process switch**: Es el acto de guardar el estado de un proceso en ejecución, llamado contexto, y luego cargar el contexto de otro proceso para que pueda ejecutarse. El cambio de proceso es necesario para la programación preventiva, pero tiene un costo en términos de tiempo y recursos del sistema.

68. **Priority scheduling**: Es un algoritmo de programación que asigna el CPU a los procesos en función de su prioridad. Los procesos con mayor prioridad se ejecutan antes que los procesos con menor prioridad.

69. **Multiple Queues**: Es una técnica de programación en la que los procesos se dividen en varias colas, cada una con su propio algoritmo de programación. Esto puede utilizarse para dar prioridad a ciertos tipos de procesos o para gestionar diferentes clases de servicio.

70. **Shortest Process Next**: Es un algoritmo de programación que selecciona para ejecución el proceso con el menor tiempo de servicio estimado aún por cumplir. Este algoritmo es óptimo para minimizar el tiempo de espera de los procesos, pero puede ser difícil de implementar en la práctica debido a la dificultad de estimar el tiempo de servicio de un proceso.

71. **Aging**: Es una técnica utilizada para prevenir la inanición en los sistemas de programación por prioridades. La técnica implica incrementar gradualmente la prioridad de los procesos que han estado esperando durante mucho tiempo.  

La técnica de estimar el siguiente valor de una serie tomando la media ponderada del valor medido actual y la estimación anterior se denomina a veces *aging*. Es aplicable a muchas situaciones en las que debe hacerse una predicción basada en valores anteriores. El *aging* es especialmente fácil de aplicar cuando a = 1/2. Basta con sumar el nuevo valor a la estimación actual y dividir la suma por 2 (desplazándola 1 bit a la derecha).

72. **Lottery scheduling**: Es un algoritmo de programación que asigna a los procesos "billetes de lotería" y luego selecciona aleatoriamente un "billete" para decidir qué proceso debe ejecutarse a continuación. Esto permite un equilibrio flexible del tiempo de CPU entre los procesos.

73. **Real-time system**: Es un sistema en el que las tareas tienen que completarse dentro de un plazo específico. Los sistemas de tiempo real son comunes en entornos como el control de procesos industriales, los sistemas de vuelo y las telecomunicaciones.

74. **Hard real time**: En un sistema de tiempo real duro, es crítico que las tareas se completen dentro de su plazo. Si una tarea no se completa a tiempo, puede tener consecuencias graves, como la falla del sistema.

75. **Soft real time**: En un sistema de tiempo real suave, es deseable pero no crítico que las tareas se completen dentro de su plazo. Si una tarea no se completa a tiempo, el sistema puede continuar funcionando, aunque con un rendimiento degradado.

76. **Periodic**: En el contexto de los sistemas de tiempo real, una tarea periódica es una que debe ejecutarse a intervalos regulares. Por ejemplo, un sistema de control puede necesitar leer los sensores y ajustar los actuadores a una frecuencia fija.

77. **Aperiodic**: Una tarea aperiódica es una que no tiene un patrón de llegada regular. Estas tareas pueden producirse en respuesta a eventos externos, como las interrupciones de hardware.

78. **Schedulable**: En el contexto de la programación de tiempo real, una tarea o conjunto de tareas es programable si existe una programación que permite que todas las tareas cumplan sus plazos.

79. **Scheduling mechanism**: Es la parte del sistema operativo que implementa el algoritmo de programación. El mecanismo de programación incluye las rutinas que seleccionan el próximo proceso a ejecutar, que realizan el cambio de proceso y que gestionan las colas de procesos.

80. **Scheduling policy**: Es el conjunto de reglas y algoritmos que el sistema operativo utiliza para decidir qué proceso debe ejecutarse a continuación. Las políticas de programación pueden estar diseñadas para optimizar el rendimiento, el tiempo de respuesta, la utilización del sistema u otros factores. Con el scheduling policy, un proceso de usuario puede controlar las políticas de planificicación.

81. **Starvation**: En el contexto de los sistemas operativos, la inanición se produce cuando un proceso no obtiene los recursos que necesita para progresar. La inanición puede producirse debido a la competencia por los recursos o a las políticas de programación.

Una situación como ésta, en la que todos los programas siguen ejecutándose indefinidamente pero no logran ningún avance, se denomina **Starvation**.