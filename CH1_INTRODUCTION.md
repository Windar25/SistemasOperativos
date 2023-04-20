# INTRODUCTION
//Falta leer

## 1.1 WHAT IS AN OPERATING SYSTEM?

Los sistemas operativos realizan 2 funciones:
-   Proveer a los programadores un conjunto abstracto y limpio de recursos en lugar de los desordenados
recursos de hardware.
-   Permitir el manejo de estos recursos de hardware.

### 1.1.1 The Operating System as an Extended Machine

### 1.1.2 The Operating System as a Resource Manager

Multiplexing:
Time multiplexing: diferentes programas se turnan para usar un recurso, por ejemplo, la CPU o una impresora.
Space multiplexing: En vez de tomar turnos, cada uno toma parte del recurso, por la memoria principal se divide 
normalmente entre varios programas en ejecución, de modo que cada uno de ellos puede ser residente al mismo tiempo.
es más eficiente mantener varios programas a la vez en memoria que dársela toda a uno de ellos, sobre todo si sólo 
necesita una pequeña fracción del total.
## 1.3 COMPUTER HARDWARE REVIEW
//Esto es OAC

### 1.7.3 Microkernels
Con el enfoque por capas, los diseñadores pueden elegir dónde trazar el límite entre el núcleo y el usuario.  
De hecho, se puede argumentar a favor de poner lo menos posible en modo kernel porque los fallos en el kernel pueden hacer caer 
el sistema al instante. Por el contrario, los procesos de usuario pueden configurarse para que tengan menos potencia, de modo que }
un fallo en ellos no sea fatal. Una cifra aproximada de bugs para los sistemas industriales es de 2 y 10 fallos por cada
1000 lineas de código.

No obstante, los sistemas operativos tienen tantos fallos que los fabricantes de ordenadores les ponen botones de reinicio 
(a menudo en el panel frontal), algo que no hacen los fabricantes de televisores, equipos de música y coches, a pesar de la gran 
cantidad de software que contienen estos aparatos.

La idea básica que subyace al diseño del **microkernel** es lograr una alta fiabilidad dividiendo el sistema operativo en módulos 
pequeños y bien definidos, de los cuales sólo uno -el micronúcleo- se ejecuta en modo núcleo y el resto se ejecuta como procesos 
de usuario ordinarios relativamente desprovistos de energía.En concreto, al ejecutar cada controlador de dispositivo y sistema de 
archivos como un proceso de usuario independiente, un fallo en uno de ellos puede bloquear ese componente, pero no todo el sistema.
De tal modo un fallo en el audio puede hacer que el sonido se distorsione o detenga, pero que no se bloquee todo el ordenador. 
La arquitectura monolítia no contempla esta facilidad. A pesar que las computadores de escritorio no las usen,predominan en 
aplicaciones en tiempo real, industriales, de aviónica y militares que son críticas para la misión y tienen requisitos de 
fiabilidad muy elevados.
