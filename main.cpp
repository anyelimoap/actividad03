// Código base entregado al inicio de la clase 

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

// Variables globales para el parser
std::string expr;
size_t pos = 0;

// Prototipos
bool EXPR();
bool TERM();
bool FACTOR();
void saltarEspacios();

void saltarEspacios() {
    while (pos < expr.size() && std::isspace(expr[pos])) pos++;
}

bool NUM() {
    saltarEspacios();
    size_t start = pos;
    while (pos < expr.size() && std::isdigit(expr[pos])) pos++;
    if (pos > start) {
        std::cout << "Número detectado: " << expr.substr(start, pos - start) << std::endl;
        return true;
    }
    return false;
}

bool ID() {
    saltarEspacios();
    size_t start = pos;
    if (pos < expr.size() && std::isalpha(expr[pos])) {
        pos++;
        while (pos < expr.size() && std::isalnum(expr[pos])) pos++;
        std::cout << "Identificador detectado: " << expr.substr(start, pos - start) << std::endl;
        return true;
    }
    return false;
}

bool FACTOR() {
    saltarEspacios();
    if (pos < expr.size() && expr[pos] == '(') {
        std::cout << "Paréntesis izquierdo detectado: (" << std::endl;
        pos++;
        if (!EXPR()) return false;
        saltarEspacios();
        if (pos < expr.size() && expr[pos] == ')') {
            std::cout << "Paréntesis derecho detectado: )" << std::endl;
            pos++;
            return true;
        }
        return false;
    }
    return ID() || NUM();
}

bool TERM() {
    if (!FACTOR()) return false;
    while (true) {
        saltarEspacios();
        if (pos < expr.size() && (expr[pos] == '*' || expr[pos] == '/')) {
            std::cout << "Operador detectado: " << expr[pos] << std::endl;
            pos++;
            if (!FACTOR()) return false;
        } else {
            break;
        }
    }
    return true;
}

bool EXPR() {
    if (!TERM()) return false;
    while (true) {
        saltarEspacios();
        if (pos < expr.size() && (expr[pos] == '+' || expr[pos] == '-')) {
            std::cout << "Operador detectado: " << expr[pos] << std::endl;
            pos++;
            if (!TERM()) return false;
        } else {
            break;
        }
    }
    return true;
}

int main() {
    std::ifstream archivo("archivo.txt");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }
    std::getline(archivo, expr);
    archivo.close();

    pos = 0;
    bool valido = EXPR();
    saltarEspacios();

    if (valido && pos == expr.size()) {
        std::cout << "\n¡La expresión es válida según la gramática!" << std::endl;
        std::cout << "Expresión: " << expr << std::endl;
    } else {
        std::cout << "\nLa expresión NO es válida según la gramática." << std::endl;
        std::cout << "Error cerca de: " << expr.substr(pos) << std::endl;
    }
    return 0;
}
