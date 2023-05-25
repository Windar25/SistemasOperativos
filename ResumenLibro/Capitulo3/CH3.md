# MEMORY MANAGEMENT

La memoria principal (RAM) es un importante recurso que debe ser manejada cuidadosamente. Mientras el promedio de computadoras de estos días tiene 10 000 veces más memoria que el IBM 7094, la computadora más grande del mundo en 1960, los programas están creciendo más que las memorias. Para parafrasear la ley de Parkinson "Los programas crecen para llenar la memoria disponible para albergarlos". En este capítulo vamos a estudiar como los sistemas operativos crean abstracciones de la memoria y como los manejan. 

Lo que todos los programadores buscan es una memoria privada, infinitamente larga e infinitamente larga que sea no volatil, que no pierda su contenido si se va la luz. Si estamos así, porqué no hacerla barata también? Desafortunadamente, la tecnología no provee estas memorias en el presente. Quizás descubras como hacerlo.

¿Cuál es la segunda opción? A lo largo de los años, las personas han descubierto el concepto de **memory hierarchy**, en el cual la computadora tiene algunos megabytes que son múy rápidos, caros, con memoria caché volatil, unos pocos gigabytes de velocidad media, precio medio, memoria principal volatil, unos con pocos terabytes lentos, baratos, no volatiles magneticos o almacenamiento de estado sólido, sin mencionar el almacenamiento removible, como los DVDs o USBs. Esta es el trabajo del sistema operativo para abstraer esta arquitectura en modelo útil y luego manejar la abstracción.

La parte del sistema operativo que maneja(parte de ) la arquitectura de memoria es el **memory manager**. Su trabajo es manejar la memoria eficientemente: llevar un registro de qué partes de la memoria se están usando, asignar memoria a los procesos cuando lo necesiten, y desasignar su memoria cuando hayan acabado.

En este capítulo vamos a investigar varios modelos de manejo de memoria, yendo desde los más simples hasta los más sofisticados. Comenzando con el manejo de los niveles bajos de la memoria caché los cuales son realizados por el hardware, el tema de este capítulo estpa en el modelo de programación de la memoria prncipal y como esta puede manejarse. Las abstracciones para el manejo del almacenamiento permanente(el disco), son sujeto del siguiente capítulo. Vamos a ver primero los esquemas más simples y luego avanzaremos gradualmente a los más elaborados.

