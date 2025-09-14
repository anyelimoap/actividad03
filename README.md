# Compiladores Actividad 02 

Este proyecto tiene como objetivo **implementar y analizar gramáticas libres de contexto (GLC)** a través de un programa en c++ que lee un archivo de texto y separa su contenido en palabras o tokens. El propósito es reconocer instrucciones de un lenguaje sencillo a través de un programa en C++ que actúa como un **analizador léxico y sintáctico básico**.   En particular, se trabajan cuatro tipos de gramáticas: **expresiones aritméticas**, **identificadores**, **declaraciones** y **condicionales**. 

---
## Estructura del proyecto

- **`main.cpp`** → Código en C++ encargado de leer y procesar los archivos de entrada.  
- **`gramatica.txt`** → Contiene la gramática que se desea implementar y analizar.  
- **`archivo.txt`** → Archivo de entrada que incluye el bloque de código fuente a evaluar.  

El programa lee el archivo `archivo.txt`, separa las palabras y símbolos en tokens, y los compara con las reglas definidas en `gramatica.txt` para verificar su validez según las gramáticas planteadas.

Esta actividad fue desarrollada en equipo a partir de varias versiones. A continuación, se documentan los commits principales:
---

## Versión 1 (commit inicial brindado en clase)
**Descripción:**  
Se implementó la primera versión del programa que lee un archivo de texto (`archivo.txt`) carácter por carácter y separa las palabras utilizando únicamente el espacio `' '` como delimitador.  
Se imprimen todas las palabras encontradas, ignorando saltos de línea.

**Cambios realizados:**
- Lectura de archivo con `ifstream`.
- Iteración carácter por carácter con `archivo.get(c)`.
- Ignorar saltos de línea (`\n` y `\r`).
- Uso de espacio simple `' '` como único delimitador.
- Impresión de palabras en consola.

**Limitaciones identificadas:**
- No reconoce tabulaciones ni otros tipos de espacio.
- Los símbolos (`; + = ( ) { }`, etc.) quedan pegados a las palabras.
- Funcionalidad limitada como analizador de tokens.

---

## Versión 2 (corrección de las limitaciones)
**Descripción:**  
Se mejoró la robustez del programa al permitir la detección de cualquier tipo de espacio en blanco y al reconocer símbolos como tokens independientes.

**Cambios realizados:**
- Inclusión de la librería `<cctype>` para usar funciones de clasificación de caracteres.
- Reemplazo de la condición `c == ' '` por `isspace(c)`, lo que permite reconocer espacios, tabulaciones y saltos de línea.
- Creación de la función `esSimbolo(c)` para identificar símbolos comunes en código fuente:  
  `; ( ) { } + * = < > !`.
- Modificación del flujo de lectura:
  - Antes de imprimir un símbolo, se asegura imprimir primero la palabra acumulada.
  - Los símbolos se imprimen como tokens separados.
- Limpieza del código y mejor manejo de casos límite.

**Mejoras obtenidas:**
- Mayor precisión en la separación de tokens.
- Reconocimiento de símbolos como entidades independientes.
- Código más cercano al funcionamiento de un **analizador léxico básico**.

---




