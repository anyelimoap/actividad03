## Historial de cambios

feat(parser): agregar tokenizador y soporte para detectar declaraciones (DECL) y estructura IF (IF)
- Separar la lógica de tokenización en una función `tokenizar()`.
- Añadir validadores (`esTipo`, `esID`, `esLetra`, `esDigito`) para diferenciar tipos, identificadores y números.
- Implementar funciones de parsing:
  - `parseDECL`: detectar declaraciones con asignación y `;`.
  - `parseIF`: detectar estructuras `if` con condición, bloque `{}` y soporte de `else`.
- Mostrar tokens extraídos antes del análisis sintáctico.
- Manejo explícito de errores en declaraciones e instrucciones `if`.
- Ampliar reconocimiento de operadores de dos caracteres (==, !=, <=, >=).

