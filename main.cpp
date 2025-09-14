#include <iostream>
#include <fstream>
#include <string>
#include <cctype> // para isspace , isalpha, isdigit

bool esSimbolo(char c) {
    return c == ';' || c == '(' || c == ')' ||
           c == '{' || c == '}' || c == '+' ||
           c == '*' || c == '=' || c == '<' ||
           c == '>' || c == '!';
}

int main() {
    std::ifstream archivo("archivo.txt"); 
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    char c;
    std::string palabra = "";

    while (archivo.get(c)) {
        if (c == '\n' || c == '\r') {
            continue; // Ignorar saltos de línea
        }

        if (isspace(c)) {
            if (!palabra.empty()) {
                std::cout << "Palabra: " << palabra << std::endl;
                palabra.clear();
            }
        }
        else if (esSimbolo(c)) {
            if (!palabra.empty()) {
                std::cout << "Palabra: " << palabra << std::endl;
                palabra.clear();
            }
            std::cout << "Palabra: " << c << std::endl; // símbolo como token independiente
        }
        else {
            palabra += c; // construir palabra normal
        }
    }

    if (!palabra.empty()) {
        std::cout << "Palabra: " << palabra << std::endl;
    }

    archivo.close();
    return 0;
}

