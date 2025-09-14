### Historial de cambios

---
**feat(tokenizer):** implementar lectura básica y separación de palabras
- Lectura del archivo `archivo.txt` carácter por carácter con `ifstream`.
- Ignorar saltos de línea (`\n`, `\r`).
- Separar palabras únicamente con el espacio `' '`.
- Imprimir cada palabra encontrada en consola.
- Manejo básico de acumulación de caracteres en la variable `palabra`.
- Problemas
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

**feat(tokenizer):** clasificación avanzada de tokens
- Se agregó la estructura `Token` con campos `valor` y `tipo`.
- Implementación de `clasificarToken()`:
  - Reconoce **tipos** (`int`, `float`, `char`).
  - Reconoce **palabras reservadas** (`if`, `else`).
  - Diferencia **números enteros** (`EXPR`).
  - Soporte para **operadores relacionales** (`=`, `<`, `>`, `==`, `!=`) y aritméticos (`+`, `-`, `*`, `/`) bajo el tipo `RELOP`.
  - Reconoce **identificadores válidos** (`EXPR`) que empiezan con letra y pueden contener alfanuméricos.
  - Retorna `DESCONOCIDO` para tokens inválidos.

**feat(tokenizer):** manejo de separadores y operadores múltiples
- Función `esSeparador()` para `; ( ) { }`.
- Función `esOperador()` para `+ - * / = < > !`.
- Detección de operadores de dos caracteres (`==`, `!=`, `<=`, `>=`) mediante `peek()` en el stream.
- Almacena separadores con tipo `SEPARADOR`.

**feat(parser):** impresión en formato de gramática
- Nueva función `imprimirToken()` que traduce los tokens a producciones:
  - `expr -> valor`
  - `relop -> valor`
  - `tipo -> int/float/char`
  - `PALABRA RESERVADA -> if/else`
  - `separador -> ; ( ) { }`
- Salida alineada con las gramáticas libres de contexto definidas en la práctica.

**feat(parser):** validación de estructuras `if-else`
- Implementación de `verificarIf()`:
  - Valida la estructura `if (expr relop expr) { INSTRUCCIONES } else { INSTRUCCIONES }`.
  - Imprime la derivación según la gramática:
    - `IF -> if (COND) { INSTRUCCIONES } else { INSTRUCCIONES }`
    - `COND -> expr relop expr`.
- Recorre el bloque `{}` del `if` y del `else` hasta encontrar `}`.
- Manejo de múltiples estructuras `if` en el mismo archivo de entrada.
- Reporta error explícito si la estructura no es válida.

**feat(main):** integración completa de análisis léxico y sintáctico
- Tokenización en un vector `tokens` con tipo y valor.
- Impresión de tokens en formato de gramática.
- Bucle que detecta múltiples `if` en el código fuente.
- Mensaje de error `Error: estructura IF invalida` si la validación falla.
- Mensaje final si no se encuentra ningún `if`.

**improvements:**
- Flujo principal más robusto: ya no se limita a tokenizar, también valida gramáticas.
- Salida más clara y alineada con las producciones formales.
- Soporte para múltiples bloques `if-else` en un mismo archivo de entrada.

**known issues:**
- La validación de `if` es rígida: exige siempre la estructura completa con `else`. No reconoce `if` sin `else`.
- Los bloques `{}` se recorren de forma lineal, sin analizar instrucciones internas.
- No diferencia entre operadores aritméticos (`+`, `-`, `*`, `/`) y relacionales (`<`, `>`, `==`, `!=`) en el etiquetado, todos caen en `RELOP`.
- Los números decimales no son reconocidos (solo enteros).
- No existe aún soporte para declaraciones (`DECL`) ni asignaciones (`INSTR`).
