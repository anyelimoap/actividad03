#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// ------------------- TOKENIZADOR -------------------
bool esSimbolo(char c) {
    return c == ';' || c == '(' || c == ')' ||
           c == '{' || c == '}' || c == '+' ||
           c == '*' || c == '=' || c == '<' ||
           c == '>' || c == '!';
}

vector<string> tokenizar(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<string> tokens;
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return tokens;
    }

    char c;
    string palabra = "";
    while (archivo.get(c)) {
        if (c == '\n' || c == '\r') continue;

        if (isspace(c)) {
            if (!palabra.empty()) {
                tokens.push_back(palabra);
                palabra.clear();
            }
        }
        else if (esSimbolo(c)) {
            if (!palabra.empty()) {
                tokens.push_back(palabra);
                palabra.clear();
            }
            // verificar operadores de dos caracteres (==, !=, <=, >=)
            if ((c == '=' || c == '!' || c == '<' || c == '>') && archivo.peek() == '=') {
                char next;
                archivo.get(next);
                string op;
                op += c;
                op += next;
                tokens.push_back(op);
            } else {
                tokens.push_back(string(1, c));
            }
        }
        else {
            palabra += c;
        }
    }
    if (!palabra.empty()) tokens.push_back(palabra);

    archivo.close();
    return tokens;
}

// ------------------- VALIDADORES -------------------
bool esTipo(const string &tok) {
    return tok == "int" || tok == "float" || tok == "char";
}

bool esLetra(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool esDigito(char c) {
    return (c >= '0' && c <= '9');
}

bool esID(const string &tok) {
    if (tok.empty()) return false;
    if (!esLetra(tok[0])) return false;  // primera debe ser letra
    for (size_t j = 1; j < tok.size(); j++) {
        if (!(esLetra(tok[j]) || esDigito(tok[j]))) return false;
    }
    return true;
}

// ------------------- PARSER -------------------
bool parseDECL(const vector<string> &tokens, int &i) {
    if (i < tokens.size() && esTipo(tokens[i])) {
        cout << "DECLARACION detectada:" << endl;
        cout << "  Tipo: " << tokens[i] << endl;
        i++;
        if (i < tokens.size() && esID(tokens[i])) {
            cout << "  ID: " << tokens[i] << endl;
            cout << "ID detectado: " << tokens[i] << endl;
            i++;
            if (i < tokens.size() && tokens[i] == "=") {
                i++;
                if (i < tokens.size() && (isdigit(tokens[i][0]) || esID(tokens[i]))) {
                    if (esID(tokens[i])) {
                        cout << "ID detectado: " << tokens[i] << endl;
                    }
                    cout << "  Valor: " << tokens[i] << endl;
                    i++;
                    if (i < tokens.size() && tokens[i] == ";") {
                        cout << "  Fin de declaracion" << endl;
                        i++;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool parseIF(const vector<string> &tokens, int &i) {
    if (i < tokens.size() && tokens[i] == "if") {
        cout << "ESTRUCTURA IF detectada:" << endl;
        i++;
        if (i < tokens.size() && tokens[i] == "(") {
            i++;
            cout << "  COND: ";
            while (i < tokens.size() && tokens[i] != ")") {
                cout << tokens[i] << " ";
                if (esID(tokens[i])) {
                    cout << "\nID detectado: " << tokens[i];
                }
                i++;
            }
            cout << endl;
            if (i < tokens.size() && tokens[i] == ")") i++;

            if (i < tokens.size() && tokens[i] == "{") {
                i++;
                cout << "  INSTRUCCIONES (if): ";
                while (i < tokens.size() && tokens[i] != "}") {
                    cout << tokens[i] << " ";
                    if (esID(tokens[i])) {
                        cout << "\nID detectado: " << tokens[i];
                    }
                    i++;
                }
                cout << endl;
                if (i < tokens.size() && tokens[i] == "}") i++;

                if (i < tokens.size() && tokens[i] == "else") {
                    i++;
                    if (i < tokens.size() && tokens[i] == "{") {
                        i++;
                        cout << "  INSTRUCCIONES (else): ";
                        while (i < tokens.size() && tokens[i] != "}") {
                            cout << tokens[i] << " ";
                            if (esID(tokens[i])) {
                                cout << "\nID detectado: " << tokens[i];
                            }
                            i++;
                        }
                        cout << endl;
                        if (i < tokens.size() && tokens[i] == "}") {
                            i++;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// ------------------- MAIN -------------------
int main() {
    vector<string> tokens = tokenizar("archivo.txt");

    cout << "=== TOKENS ===" << endl;
    for (auto &t : tokens) cout << t << " ";
    cout << endl << endl;

    int i = 0;
    while (i < tokens.size()) {
        if (esTipo(tokens[i])) {
            if (!parseDECL(tokens, i)) {
                cerr << "Error en declaracion" << endl;
                break;
            }
        }
        else if (tokens[i] == "if") {
            if (!parseIF(tokens, i)) {
                cerr << "Error en if" << endl;
                break;
            }
        }
        else if (esID(tokens[i])) {
            cout << "ID detectado: " << tokens[i] << endl;
            i++;
        }
        else {
            cout << "Token inesperado: " << tokens[i] << endl;
            i++;
        }
    }

    return 0;
}
