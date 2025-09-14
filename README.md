# Compiladores Actividad 02 

Este proyecto tiene como objetivo **implementar y analizar gramáticas libres de contexto (GLC)** a través de un programa en c++ que lee un archivo de texto y separa su contenido en palabras o tokens. El propósito es reconocer instrucciones de un lenguaje sencillo a través de un programa en C++ que actúa como un **analizador léxico y sintáctico básico**.   En particular, se trabajan cuatro tipos de gramáticas: **expresiones aritméticas**, **identificadores**, **declaraciones** y **condicionales**. 

---
## Estructura del proyecto

- **`main.cpp`** → Código en C++ encargado de leer y procesar los archivos de entrada.  
- **`gramatica.txt`** → Contiene la gramática que se desea implementar y analizar.  
- **`archivo.txt`** → Archivo de entrada que incluye el bloque de código fuente a evaluar.  

El programa lee el archivo `archivo.txt`, separa las palabras y símbolos en tokens, y los compara con las reglas definidas en `gramatica.txt` para verificar su validez según las gramáticas planteadas.

### Historial de cambios
---
**feat(tokenizer):** implementar lectura básica y separación de palabras
- Lectura del archivo `archivo.txt` carácter por carácter con `ifstream`.
- Ignorar saltos de línea (`\n`, `\r`).
- Separar palabras únicamente con el espacio `' '`.
- Imprimir cada palabra encontrada en consola.
- Manejo básico de acumulación de caracteres en la variable `palabra`.
- Problemas:
  - No reconoce tabulaciones ni otros tipos de espacio.
  - Los símbolos (`;`, `+`, `=`, `(`, `)`, `{`, `}`) permanecen pegados a las palabras.
  - Funcionalidad limitada como analizador de tokens.

**feat(tokenizer):** ampliar reconocimiento de espacios en blanco
- Inclusión de la librería `<cctype>` para usar `isspace()`.
- Reemplazo de la condición `c == ' '` por `isspace(c)`.
- Ahora se reconocen espacios, tabulaciones y saltos de línea como delimitadores.

**feat(tokenizer):** agregar reconocimiento de símbolos como tokens
- Creación de la función `esSimbolo(char c)`.
- Identificación de símbolos comunes: `; ( ) { } + * = < > !`.
- Símbolos impresos como tokens separados en consola.
---








