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
