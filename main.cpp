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

bool esNumero(const std::string& palabra) {
    if (palabra.empty()) return false;
    for (size_t i = 0; i < palabra.size(); ++i) {
        if (!std::isdigit(palabra[i])) return false;
    }
    return true;
}

bool esPalabraValida(const std::string& palabra) {
    return esTipo(palabra) || esPalabraClave(palabra) || esOperador(palabra) || esIdentificador(palabra) || esNumero(palabra);
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
    bool estructuraCorrecta = true;
    int palabraNum = 1;

    while (archivo.get(c)) {
        if (std::isspace(c) || c == ';' || c == '(' || c == ')' || c == '{' || c == '}') {
            if (!palabra.empty()) {
                if (esPalabraValida(palabra)) {
                    std::cout << "Palabra válida detectada (" << palabraNum << "): " << palabra << std::endl;
                } else {
                    std::cout << "Palabra NO válida (" << palabraNum << "): " << palabra << std::endl;
                    estructuraCorrecta = false;
                }
                if (esOperador(palabra)) hayOperacion = true;
                palabra.clear();
                palabraNum++;
            }
            if (esOperador(std::string(1, c))) {
                std::cout << "Operador detectado (" << palabraNum << "): " << c << std::endl;
                hayOperacion = true;
                palabraNum++;
            }
        } else {
            palabra += c;
        }
    }
    // Última palabra
    if (!palabra.empty()) {
        if (esPalabraValida(palabra)) {
            std::cout << "Palabra válida detectada (" << palabraNum << "): " << palabra << std::endl;
        } else {
            std::cout << "Palabra NO válida (" << palabraNum << "): " << palabra << std::endl;
            estructuraCorrecta = false;
        }
        if (esOperador(palabra)) hayOperacion = true;
    }

    if (estructuraCorrecta && hayOperacion) {
        std::cout << "\n¡La estructura de la gramática está correcta!" << std::endl;
    } else {
        std::cout << "\nLa estructura de la gramática NO es correcta." << std::endl;
    }

    archivo.close();
    return 0;
}
