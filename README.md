Contribuciones de Jose Manuel Mariaca



Desarrollé una primera versión del analizador léxico que ayudo a ver bien el camino para donde iba el codigo.


```cpp

// Función original para detección de símbolos

bool esSimbolo(char c) {

;   return c == ';' || c == '(' || c == ')' || 

;          c == '{' || c == '}' || c == '+' || 

;          c == '\*' || c == '=' || c == '<' || 

;          c == '>' || c == '!';

}



// Primera validación de identificadores con guión bajo

bool esIdentificador(const std::string\& palabra) {

   if (palabra.empty()) return false;

   if (!isalpha(palabra\[0]) \&\& palabra\[0] != '\_') return false;

   for (size\_t i = 1; i < palabra.length(); i++) {

      if (!isalnum(palabra\[i]) \&\& palabra\[i] != '\_') {

           return false;

       }

   }

   return true;
}

```

Mejoras implementadas:



1 Soporte para identificadores con \_



\_variable, var\_1, \_temp\_var ahora son válidos



Cumple con estándares C/C++ de naming



2 Ampliación de palabras reservadas



Añadidos: void, double, while, for, return, main



Mejor cobertura del lenguaje



3 Lógica de tokenización robusta



Separación precisa por espacios y símbolos



Detección de operadores compuestos (==, !=, etc.)









