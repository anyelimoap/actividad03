### Historial de cambios

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
