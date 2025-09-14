# Actividad de Aprendizaje 

Este proyecto tiene como objetivo **implementar y analizar gramáticas libres de contexto (GLC)** a través de un programa en c++ que lee un archivo de texto y separa su contenido en palabras o tokens. El propósito es reconocer instrucciones de un lenguaje sencillo a través de un programa en C++ que actúa como un **analizador léxico y sintáctico básico**.   En particular, se trabajan cuatro tipos de gramáticas: **expresiones aritméticas**, **identificadores**, **declaraciones** y **condicionales**. 

---
## Estructura del proyecto

- **`main.cpp`** → Código en C++ encargado de leer y procesar los archivos de entrada.  
- **`gramatica.txt`** → Contiene la gramática que se desea implementar y analizar.  
- **`archivo.txt`** → Archivo de entrada que incluye el bloque de código fuente a evaluar.  

El programa lee el archivo `archivo.txt`, separa las palabras y símbolos en tokens, y los compara con las reglas definidas en `gramatica.txt` para verificar su validez según las gramáticas planteadas.

---
## Historial de cambios

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

**refactor(tokenizer):** ajustar flujo de impresión
- Antes de imprimir un símbolo, se vacía primero la palabra acumulada.
- Limpieza de la lógica de acumulación de tokens.
- Tokens impresos de forma más clara y ordenada.
- Mejoras:
  - Mayor precisión en la separación de tokens.
  - Reconocimiento de operadores y delimitadores como entidades independientes.
  - Código más cercano al funcionamiento de un analizador léxico básico.

**feat(parser):** agregar tokenizador y soporte para detectar declaraciones (DECL) y estructura IF (IF)
- Separar la lógica de tokenización en una función `tokenizar()`.
- Añadir validadores (`esTipo`, `esID`, `esLetra`, `esDigito`) para diferenciar tipos, identificadores y números.
- Implementar funciones de parsing:
  - `parseDECL`: detectar declaraciones con asignación y `;`.
  - `parseIF`: detectar estructuras `if` con condición, bloque `{}` y soporte de `else`.
- Mostrar tokens extraídos antes del análisis sintáctico.
- Manejo explícito de errores en declaraciones e instrucciones `if`.
- Ampliar reconocimiento de operadores de dos caracteres (==, !=, <=, >=).

**feat(parser):** detección de identificadores (ID) en declaraciones y estructuras de control
- `parseDECL`:
  - Imprime `ID detectado` al reconocer identificadores (ID) en declaraciones (DECL).
  - Reconoce IDs cuando se usan como valores asignados.
- `parseIF`:
  - Detecta identificadores (ID) dentro de condiciones `if`.
  - Detecta identificadores (ID) en los bloques `{}` de `if` y `else`.
  - Salida más clara, ya que los tokens se imprimen con espacios y cada ID reconocido se reporta.
- Mejoras generales:
  - Salida de consola más detallada para depuración.
  - Mensajes consistentes para identificación de tokens.
- Problemas:
  - Reconoce la asignación y expresiones aritméticas como identificadores (ID).

**feat(parser):** agregar soporte para expresiones aritméticas (ART) y condiciones (COND)
- Tokenizador:
  - Se añadieron símbolos `-` y `/` para reconocer más operadores.
- Validadores:
  - Nuevo validador `esNumero` para reconocer enteros y decimales.
  - Nuevas funciones `esRelop` (operadores relacionales) y `esOp` (operadores aritméticos).
- Parser:
  - `parseExpr`: reconoce identificadores (ID) y números como expresiones válidas.
  - `parseCOND`: analiza condiciones con formato <expr> <relop> <expr>.
  - `parseArt`: analiza operaciones aritméticas <expr> <op> <expr>.
  - `parseInstr`: añade soporte para asignaciones con expresiones aritméticas.
  - `parseDECL`: valida asignación inicial usando `parseExpr`.
  - `parseIF`: estructura mejorada, ahora soporta condiciones más formales y bloques de instrucciones con asignaciones aritméticas.
- Main:
  - El flujo principal ahora reconoce y procesa declaraciones, instrucciones aritméticas y estructuras `if-else`.

**refactor:** mejorar mensajes de validación y simplificar flujo de parseo
- Mensajes de salida más claros:
  - `parseCOND`, `parseArt`, `parseInstr`, `parseDECL`, `parseIF` ahora imprimen “válido / inválido” en lugar de solo mostrar estructuras detectadas.
  - Esto mejora la depuración y permite identificar rápidamente si la gramática analizada es correcta o no.
- Uniformidad en la nomenclatura:
  - Se reemplazaron frases como `Fin de instrucción` o `Fin de declaración` por `INSTR válida` y `DECLARACION válida`, unificando la semántica.
- Control de errores más explícito:
  - En lugar de depender solo de `cerr << "Error ..."`, ahora cada función imprime su propio estado de validez.
  - Ejemplo: `ESTRUCTURA IF inválida` en caso de fallo.
- Simplificación en el main:
  - Ya no se muestran errores genéricos, pues las funciones de parseo se encargan de imprimir el resultado detallado.
  - El bucle principal ahora se detiene simplemente cuando un `parseX` devuelve `false`.
- Problemas:
  - Imprime `Token inesperado` dentro de la estructura IF (IF) y las instrucciones (INSTR).

**feat:** agregar soporte para if con else opcional
- Ampliación de `parseIF`:
  - Ahora la estructura `if` admite tanto la forma clásica `if (...) { ... } else { ... }` como la versión simplificada `if (...) { ... }` sin bloque `else`.
  - Se agregó lógica para validar correctamente la ausencia o presencia del else.
- Validaciones más estrictas:
  - Se añadió verificación de cierre correcto de llaves (`}`) antes de continuar con el análisis.
  - Si no se encuentra la llave de cierre, se marca explícitamente como "ESTRUCTURA IF inválida".
- Mensajes de depuración:
  - En caso de `if` con `else`, se imprime `ESTRUCTURA IF válida` solo después de procesar ambos bloques correctamente.
  - En caso de `if` sin `else`, también se confirma con `ESTRUCTURA IF válida`.

**feat(parser):** agregar validaciones de expresiones y condiciones
- Implementar funciones de parsing adicionales:
  - `parseExpr()`: valida si un token es identificador o número.
  - `parseCOND()`: valida condiciones con operadores relacionales (`<`, `>`, `==`, `!=`).
  - `parseArt()`: valida expresiones aritméticas simples con operadores (`+`, `-`, `*`, `/`).
- Añadir mensajes de validación más detallados:
  - `COND válido`, `ART válido`, `INSTR válida`, `DECLARACION válida`, `ESTRUCTURA IF válida`.
- Diferenciar en `main` entre declaraciones (`parseDECL`) y estructuras de control (`parseIF`).
- Si no coincide con ninguna, mostrar **DECLARACION inválida** y detener el análisis.

**feat(parser):** nuevas estructuras de parsing
- `parseInstr()`: reconoce instrucciones de asignación (`x = a + b;`).
- `parseDECL()`: amplía reconocimiento de declaraciones con asignación inicial (`int x = 10;`).
- `parseIF()`: soporte para la estructura `if-else`, con validación de condiciones y múltiples instrucciones dentro de `{}`.

**feat**: Se agregaron nuevas funciones al parser y se mejoró la validación de estructuras.
- Implementación de validadores:
  - `parseExpr()`: reconoce identificadores y números.
  - `parseCOND()`: valida condiciones con operadores relacionales (`<`, `>`, `==`, `!=`).
  - `parseArt()`: valida expresiones aritméticas simples (`+`, `-`, `*`, `/`).
- Nuevas estructuras en el parser:
  - `parseInstr()`: instrucciones de asignación (`x = a + b;`).
  - `parseDECL()`: declaraciones con asignación inicial (`int x = 10;`).
  - `parseIF()`: soporte para estructuras de control `if-else` con bloques `{}`.
- Se añadieron mensajes de validación detallados (`COND válido`, `ART válido`, `INSTR válida`, etc.) para mejorar el debugging.

---











