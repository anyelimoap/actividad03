# Comparación entre la versión del Código 1 y Código 2

Este proyecto presenta el avance de un programa en C++ que lee un archivo de texto y separa su contenido en palabras.  
La segunda versión constituye una mejora de la primera al ampliar los delimitadores reconocidos y tratar ciertos símbolos como tokens independientes.

---

## Código 1: Versión inicial (brindada en clase)

En la primera versión, el archivo se procesa **carácter por carácter** y se van construyendo palabras únicamente cuando se detecta un espacio simple (`' '`).  
Esto significa que **solo el espacio** funciona como delimitador. Otros caracteres de separación, como tabulaciones o saltos de línea, no son tenidos en cuenta.  

Además, los **símbolos especiales** como `;`, `+`, `(` o `)` no se reconocen de forma independiente, sino que se mantienen concatenados a las palabras.  
Como consecuencia, esta versión es más limitada y menos precisa para identificar elementos del texto.

---

## Primera modificación

La segunda versión introduce cambios como:
En lugar de usar solo el espacio como delimitador, emplea la función `isspace(c)`, lo que permite reconocer **cualquier tipo de espacio en blanco**: espacios, tabulaciones y saltos de línea.  

Otra mejora fundamental es la incorporación de la función `esSimbolo(c)`, que identifica un conjunto de **símbolos especiales** (`; ( ) { } + * = < > !`) y los trata como **tokens individuales**.  
De esta manera, los símbolos dejan de estar pegados a las palabras y pasan a ser reconocidos de forma separada, para simular el comportamiento de un analizador léxico básico.

---

## Diferencias principales

- **Delimitadores:**  
  - Versión 1: solo detecta el espacio simple (`' '`).  
  - Versión 2: reconoce cualquier espacio en blanco (`isspace`).  

- **Símbolos:**  
  - Versión 1: los símbolos quedan pegados a las palabras.  
  - Versión 2: los símbolos se separan como tokens independientes.  

- **Robustez:**  
  - Versión 1: limitado y menos flexible.  
  - Versión 2: más general, preciso y cercano a un tokenizador.  


En resumen, mientras que la **primera versión del código** únicamente permite separar palabras por espacios y no distingue símbolos, la **segunda versión** amplía el manejo de delimitadores y clasifica los símbolos como tokens separados.  
Esta modificación hace que la segunda versión sea más flexible y adecuada como base para un **análisis léxico** o procesamiento de texto más avanzado.
