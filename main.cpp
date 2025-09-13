// Código base entregado al inicio de la clase 

#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Abre el archivo "archivo.txt" para lectura
    std::ifstream archivo("archivo.txt"); 
    if (!archivo.is_open()) {
        // Si no se puede abrir el archivo, muestra un mensaje de error y termina el programa
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    char c;
    std::string palabra = "";

    // Lee el archivo carácter por carácter
    while (archivo.get(c)) {
        // Ignora los saltos de línea
        if (c == '\n' || c == '\r') {
            continue;
        }

        // Si encuentra un espacio, imprime la palabra construida y la limpia
        if (c == ' ') {
            if (!palabra.empty()) {
                std::cout << "Palabra: " << palabra << std::endl;
                palabra.clear(); // limpia la cadena
            }
        } else {
            // Si no es espacio, agrega el carácter a la palabra
            palabra += c;
        }
    }

    // Imprime la última palabra si existe
    if (!palabra.empty()) {
        std::cout << "Palabra: " << palabra << std::endl;
    }

    // Cierra el archivo
    archivo.close();
    return 0;
}
