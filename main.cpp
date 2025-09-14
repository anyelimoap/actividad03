// Código base entregado al inicio de la clase 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

bool esTipo(const std::string& palabra) {
    return palabra == "int" || palabra == "float" || palabra == "char";
}

bool esPalabraClave(const std::string& palabra) {
    return palabra == "if" || palabra == "else";
}

bool esOperador(const std::string& palabra) {
    return palabra == "+" || palabra == "-" || palabra == "*" || palabra == "/" ||
           palabra == ">" || palabra == "<" || palabra == "==" || palabra == "!=" || palabra == "=";
}

bool esIdentificador(const std::string& palabra) {
    if (palabra.empty() || !std::isalpha(palabra[0])) return false;
    for (size_t i = 0; i < palabra.size(); ++i) {
        if (!std::isalnum(palabra[i])) return false;
    }
    return true;
}

int main() {
    std::ifstream archivo("archivo.txt");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    std::string palabra;
    char c;
    bool hayOperacion = false;

    while (archivo.get(c)) {
        if (std::isspace(c) || c == ';' || c == '(' || c == ')' || c == '{' || c == '}') {
            if (!palabra.empty()) {
                if (esTipo(palabra)) {
                    std::cout << "Tipo detectado: " << palabra << std::endl;
                } else if (esPalabraClave(palabra)) {
                    std::cout << "Palabra clave detectada: " << palabra << std::endl;
                } else if (esOperador(palabra)) {
                    std::cout << "Operador detectado: " << palabra << std::endl;
                    hayOperacion = true;
                } else if (esIdentificador(palabra)) {
                    std::cout << "Identificador detectado: " << palabra << std::endl;
                }
                palabra.clear();
            }
            if (esOperador(std::string(1, c))) {
                std::cout << "Operador detectado: " << c << std::endl;
                hayOperacion = true;
            }
        } else {
            palabra += c;
        }
    }
    // Última palabra
    if (!palabra.empty()) {
        if (esTipo(palabra)) {
            std::cout << "Tipo detectado: " << palabra << std::endl;
        } else if (esPalabraClave(palabra)) {
            std::cout << "Palabra clave detectada: " << palabra << std::endl;
        } else if (esOperador(palabra)) {
            std::cout << "Operador detectado: " << palabra << std::endl;
            hayOperacion = true;
        } else if (esIdentificador(palabra)) {
            std::cout << "Identificador detectado: " << palabra << std::endl;
        }
    }

    if (hayOperacion) {
        std::cout << "¡Se detectó gramática de operaciones en el archivo!" << std::endl;
    } else {
        std::cout << "No se detectó gramática de operaciones en el archivo." << std::endl;
    }

    archivo.close();
    return 0;
}
