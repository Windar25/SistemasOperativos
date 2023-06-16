Todas las aplicaciones de computadora necesitan almacenar y recuperar información. Mientras se ejecuta un proceso , puede guardarse una cantidad limitada de información con nuestro propio espacio de direcciones. De todos modos, la capacidad esta restringida por el tamaño del espacio de direcciones. Para algunas aplicaciones el tamaño es adecuado, pero para otras, como las reservaciones de aerolineas, bancos o registros de corporaciones este es muy pequeño. 

Un segundo problema de guardar información con un espacio de direcciones de un proceso es que cuando un proceso termina, se pierde la información. Para muchas aplicaciones(por ejemplo, bases de datos), la información debe guardarse por semanas, meses o incluso para siempre. Es inaceptable que desaparezca cuando finaliza el proceso que lo utiliza. Además, no debe desaparecer cuando un fallo del ordenador mate el proceso.

Un tercer problema es que a menudo es necesario que varios procesos accedan a (partes de) la información al mismo tiempo. Si tenemos un directorio telefónico en línea almacenado en el espacio de direcciones de un único proceso, sólo ese proceso podrá acceder a él. La forma de resolver este problema es hacer que la información en sí sea independiente de cualquier proceso. Así, tenemos tres requisitos esenciales para el almacenamiento de información a largo plazo:

1. Debe ser posible guardar una gran cantidad de información.
2. La información debe sobrevivir a la terminación del proceso que la está usando.
3. Múltiples procesos deben poder acceder a la información a la vez.

Los discos magnéticos han sido usados por años para el almacenamiento a largo plazo. En años recientes, las unidades de estado sólido son cada vez más populares,  ya que no tienen partes móviles que puedan romperse. De todos modos, ellos ofrecen rápido acceso aleatorio. Las cintas y los discos ópticos también se han utilizado mucho, pero tienen un rendimiento mucho menor y suelen emplearse para copias de seguridad. Estudiaremos más a fondo los discos en el Cap. 5, pero por el momento basta con pensar en un disco como una secuencia lineal de bloques de tamaño fijo y que admite dos operaciones.

1. Leer el block k
2. Escribir en el block k

En realidad hay más, pero con estas 2 operaciones uno puede resolver en principio, el problema del almacenamiento a largo plazo.

Sin embargo, se trata de operaciones muy incómodas, sobre todo en sistemas grandes utilizados por muchas aplicaciones y posiblemente varios usuarios (por ejemplo, en un servidor).  Algunas de las preguntas que surgen rápidamente son: 

1. ¿Cómo encontrar la información? 
2. ¿Cómo evitar que un usuario lea los datos de otro? 
3. ¿Cómo saber qué bloques están libres?

y hay muchas más.

Al igual que vimos cómo el sistema operativo abstrajo el concepto de procesador para crear la abstracción de proceso y cómo abstrajo el concepto de memoria física para ofrecer a los procesos espacios de direcciones (virtuales), podemos resolver este problema con una nueva abstracción: el file. Juntas, las abstracciones de procesos (e hilos), espacios de direcciones y ficheros son los conceptos más importantes relacionados con los sistemas operativos. Si realmente entiendes estos tres conceptos de principio a fin, estás bien encaminado para convertirte en un experto en sistemas operativos.

**Files** son unidades lógicas de información creadas por los procesos. Un disco tiene miles o incluso millones de estas, cada uno es independiente del otro. De hecho, si tú si piensas como cada uno de los files como una especie de espacios de direcciones, no estás tan lejos, salvo que se utilizan para modelar el disco en lugar de modelar la RAM. 

Los procesos pueden leer files existentes y crear nuevos si es que los necesitan. La información almacenada en files debe ser **persistent**, esto es, no debe ser afectada por la creación y eliminación de procesos. Un file debe desaparecer solo cuando su propietario lo remueve explícitamente. 

Aunque las operaciones de lectura y escritura de archivos son las más comunes, existen muchas otras, algunas de las cuales examinaremos a continuación. Los files son gestionados por el sistema operativo. Cómo se estructuran, nombran, acceden, utilizan, protegen, implementan y gestionan son temas importantes en el diseño de sistemas operativos. En conjunto, la parte del sistema operativo que se ocupa de los ficheros se conoce como **file system** y es el tema de este capítulo.

Desde el punto de vista del usuario, el aspecto más importante de un **file system** es cómo aparece, es decir, qué constituye un archivo, cómo se nombran y protegen los archivos, qué operaciones se permiten en los archivos, etc. Los detalles de si se utilizan listas enlazadas o mapas de bits para llevar la cuenta del almacenamiento libre y cuántos sectores hay en un bloque lógico de disco no tienen ningún interés, aunque son de gran importancia para los diseñadores del sistema de ficheros. Por este motivo, hemos estructurado el capítulo en varias secciones. Las dos primeras tratan de la interfaz de usuario para files y directorios, respectivamente. Luego viene una discusión detallada de cómo se implementa y gestiona el **file system**. Por último, damos algunos ejemplos de sistemas de ficheros reales.
