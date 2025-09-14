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
<<<<<<< HEAD
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
    if (!esLetra(tok[0])) return false;
    for (size_t j = 1; j < tok.size(); j++) {
        if (!(esLetra(tok[j]) || esDigito(tok[j]))) return false;
    }
    return true;
}

bool esNumero(const string &tok) {
    bool punto = false;
    for (size_t j = 0; j < tok.size(); j++) {
        if (tok[j] == '.') {
            if (punto) return false;
            punto = true;
        } else if (!esDigito(tok[j])) {
            return false;
        }
    }
    return !tok.empty();
}

bool esRelop(const string &tok) {
    return tok == "<" || tok == ">" || tok == "==" || tok == "!=";
}

bool esOp(const string &tok) {
    return tok == "+" || tok == "-" || tok == "*" || tok == "/";
}

// ------------------- ARITMÉTICA: IDENTIFICADOR DE TOKENS -------------------
void mostrarTipoToken(const string &tok) {
    if (esTipo(tok)) cout << "Tipo detectado: " << tok << endl;
    else if (esID(tok)) cout << "Identificador detectado: " << tok << endl;
    else if (esNumero(tok)) cout << "Número detectado: " << tok << endl;
    else if (esOp(tok)) cout << "Operador aritmético detectado: " << tok << endl;
    else if (tok == "(") cout << "Paréntesis izquierdo detectado: (" << endl;
    else if (tok == ")") cout << "Paréntesis derecho detectado: )" << endl;
    else if (tok == "{") cout << "Llave izquierda detectada: {" << endl;
    else if (tok == "}") cout << "Llave derecha detectada: }" << endl;
    else if (tok == ";") cout << "Punto y coma detectado: ;" << endl;
    else if (esRelop(tok)) cout << "Operador relacional detectado: " << tok << endl;
    else if (tok == "=") cout << "Asignación detectada: =" << endl;
    else if (tok == "if" || tok == "else") cout << "Palabra clave detectada: " << tok << endl;
    else cout << "Token desconocido: " << tok << endl;
}

// ------------------- PARSER -------------------
bool parseExpr(const string &tok) {
    return esID(tok) || esNumero(tok);
}

bool parseCOND(const vector<string> &tokens, int &i) {
    if (i + 2 < tokens.size() && parseExpr(tokens[i]) && esRelop(tokens[i+1]) && parseExpr(tokens[i+2])) {
        cout << "COND válido" << endl;
        mostrarTipoToken(tokens[i]);
        mostrarTipoToken(tokens[i+1]);
        mostrarTipoToken(tokens[i+2]);
        i += 3;
        return true;
    }
    cout << "COND inválido" << endl;
    return false;
}

bool parseArt(const vector<string> &tokens, int &i) {
    if (i + 2 < tokens.size() && parseExpr(tokens[i]) && esOp(tokens[i+1]) && parseExpr(tokens[i+2])) {
        cout << "ART válido" << endl;
        mostrarTipoToken(tokens[i]);
        mostrarTipoToken(tokens[i+1]);
        mostrarTipoToken(tokens[i+2]);
        i += 3;
        return true;
    }
    cout << "ART inválido" << endl;
    return false;
}

bool parseInstr(const vector<string> &tokens, int &i) {
    if (i + 3 < tokens.size() && esID(tokens[i]) && tokens[i+1] == "=") {
        mostrarTipoToken(tokens[i]);
        mostrarTipoToken(tokens[i+1]);
        i += 2;
        if (parseArt(tokens, i)) {
            if (i < tokens.size() && tokens[i] == ";") {
                mostrarTipoToken(tokens[i]);
                cout << "INSTR válida" << endl;
                i++;
                return true;
            }
        }
    }
    cout << "INSTR inválida" << endl;
    return false;
}

bool parseDECL(const vector<string> &tokens, int &i) {
    if (i < tokens.size() && esTipo(tokens[i])) {
        mostrarTipoToken(tokens[i]);
        i++;
        if (i < tokens.size() && esID(tokens[i])) {
            mostrarTipoToken(tokens[i]);
            i++;
            if (i < tokens.size() && tokens[i] == "=") {
                mostrarTipoToken(tokens[i]);
                i++;
                if (i < tokens.size() && parseExpr(tokens[i])) {
                    mostrarTipoToken(tokens[i]);
                    i++;
                    if (i < tokens.size() && tokens[i] == ";") {
                        mostrarTipoToken(tokens[i]);
                        cout << "DECLARACION válida" << endl;
                        i++;
                        return true;
                    }
                }
            }
        }
    }
    cout << "DECLARACION inválida" << endl;
    return false;
}

bool parseIF(const vector<string> &tokens, int &i) {
    if (i < tokens.size() && tokens[i] == "if") {
        mostrarTipoToken(tokens[i]);
        i++;
        if (i >= tokens.size() || tokens[i] != "(") {
            cout << "ESTRUCTURA IF inválida" << endl;
            return false;
        }
        mostrarTipoToken(tokens[i]);
        i++;
        if (!parseCOND(tokens, i)) {
            cout << "ESTRUCTURA IF inválida" << endl;
            return false;
        }
        if (i >= tokens.size() || tokens[i] != ")") {
            cout << "ESTRUCTURA IF inválida" << endl;
            return false;
        }
        mostrarTipoToken(tokens[i]);
        i++;
        if (i >= tokens.size() || tokens[i] != "{") {
            cout << "ESTRUCTURA IF inválida" << endl;
            return false;
        }
        mostrarTipoToken(tokens[i]);
        i++;
        while (i < tokens.size() && tokens[i] != "}") {
            if (!parseInstr(tokens, i)) {
                cout << "ESTRUCTURA IF inválida" << endl;
                return false;
            }
        }
        if (i >= tokens.size() || tokens[i] != "}") {
            cout << "ESTRUCTURA IF inválida" << endl;
            return false;
        }
        mostrarTipoToken(tokens[i]);
        i++;
        if (i < tokens.size() && tokens[i] == "else") {
            mostrarTipoToken(tokens[i]);
            i++;
            if (i >= tokens.size() || tokens[i] != "{") {
                cout << "ESTRUCTURA IF inválida" << endl;
                return false;
            }
            mostrarTipoToken(tokens[i]);
            i++;
            while (i < tokens.size() && tokens[i] != "}") {
                if (!parseInstr(tokens, i)) {
                    cout << "ESTRUCTURA IF inválida" << endl;
                    return false;
                }
            }
            if (i >= tokens.size() || tokens[i] != "}") {
                cout << "ESTRUCTURA IF inválida" << endl;
                return false;
            }
            mostrarTipoToken(tokens[i]);
            i++;
        }
        cout << "ESTRUCTURA IF válida" << endl;
        return true;
    }
    return false;
}

// ------------------- MAIN -------------------
int main() {
    vector<string> tokens = tokenizar("archivo.txt");

    int i = 0;
    while (i < tokens.size()) {
        if (esTipo(tokens[i])) {
            if (!parseDECL(tokens, i)) break;
        }
        else if (tokens[i] == "if") {
            if (!parseIF(tokens, i)) break;
        }
        else {
            mostrarTipoToken(tokens[i]);
            cout << "DECLARACION inválida" << endl;
            break;
        }
    }
=======
>>>>>>> aade1f38fbc81993c52a837b022f75c17e746680
    return 0;
}

