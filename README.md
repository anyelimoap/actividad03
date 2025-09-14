### Historial de cambios

---
**feat(tokenizer):** implementar lectura básica y separación de palabras
- Lectura del archivo `archivo.txt` carácter por carácter con `ifstream`.
- Ignorar saltos de línea (`\n`, `\r`).
- Separar palabras únicamente con el espacio `' '`.
- Imprimir cada palabra encontrada en consola.
- Manejo básico de acumulación de caracteres en la variable `palabra`.

**known issues:**
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

