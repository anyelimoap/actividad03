#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <unordered_set>

bool esSimbolo(char c) {
    return c == ';' || c == '(' || c == ')' ||
           c == '{' || c == '}' || c == '+' ||
           c == '*' || c == '=' || c == '<' ||
           c == '>' || c == '!';
}

std::string clasificarToken(const std::string &tok) {
    static std::unordered_set<std::string> palabrasClave = {
        "if", "else", "int", "float", "char"
    };

    if (palabrasClave.count(tok)) {
        if (tok == "if") return "IF";
        if (tok == "else") return "ELSE";
        if (tok == "int") return "INT";
        if (tok == "float") return "FLOAT";
        if (tok == "char") return "CHAR";
    }

    // números ? expr
    if (std::isdigit(tok[0])) return "expr";

    // identificadores ? expr
    if (std::isalpha(tok[0])) return "expr";

    // operadores relacionales
    if (tok == "=" || tok == "==" || tok == "!=" || tok == "<" || tok == ">")
        return "relop";

    // símbolos que se mantienen tal cual
    if (tok == ";" || tok == "(" || tok == ")" || tok == "{" || tok == "}")
        return tok;

    // fallback
    return "desconocido";
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
        if (c == '\n' || c == '\r') continue;

        if (isspace(c)) {
            if (!palabra.empty()) {
                std::cout << clasificarToken(palabra) << std::endl;
                palabra.clear();
            }
        }
        else if (esSimbolo(c)) {
            if (!palabra.empty()) {
                std::cout << clasificarToken(palabra) << std::endl;
                palabra.clear();
            }

            // chequeo de operadores de dos caracteres (==, !=)
            if ((c == '=' || c == '!') && archivo.peek() == '=') {
                char siguiente = archivo.get();
                std::string op;
                op += c;
                op += siguiente;
                std::cout << clasificarToken(op) << std::endl;
            } else {
                std::string op(1, c);
                std::cout << clasificarToken(op) << std::endl;
            }
        }
        else {
            palabra += c;
        }
    }

    if (!palabra.empty()) {
        std::cout << clasificarToken(palabra) << std::endl;
    }

    archivo.close();
    return 0;
}
