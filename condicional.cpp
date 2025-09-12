#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

struct Token {
    std::string valor;
    std::string tipo;
};

// Palabras clave
std::string tipos[] = {"int", "float", "char"};
std::string reservadas[] = {"if", "else"};

// -------------------------------
// Clasificación de caracteres
// -------------------------------
bool esSeparador(char c) {
    return c == ';' || c == '(' || c == ')' || c == '{' || c == '}';
}

bool esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' ||
           c == '=' || c == '<' || c == '>' || c == '!';
}

// -------------------------------
// Clasificación de tokens
// -------------------------------
std::string clasificarToken(const std::string &token) {
    if (token.empty()) return "";

    // tipo
    for (size_t i = 0; i < sizeof(tipos)/sizeof(tipos[0]); i++) {
        if (token == tipos[i]) return "TIPO";
    }

    // palabras reservadas
    for (size_t i = 0; i < sizeof(reservadas)/sizeof(reservadas[0]); i++) {
        if (token == reservadas[i]) return "RESERVADA";
    }

    // número
    bool esNumero = true;
    for (size_t i = 0; i < token.size(); i++) {
        if (!isdigit(token[i])) { esNumero = false; break; }
    }
    if (esNumero) return "EXPR";

    // operador (relop + aritméticos juntos)
    if (token == "=" || token == "+" || token == "-" || token == "*" || token == "/" ||
        token == "<" || token == ">" || token == "==" || token == "!=") {
        return "RELOP";
    }

    // identificador
    if (isalpha(token[0])) {
        bool valido = true;
        for (size_t i = 1; i < token.size(); i++) {
            if (!isalnum(token[i])) { valido = false; break; }
        }
        if (valido) return "EXPR";
    }

    return "DESCONOCIDO";
}

// -------------------------------
// Imprimir tokens en formato gramática
// -------------------------------
void imprimirToken(const Token &tok) {
    if (tok.tipo == "EXPR") {
        std::cout << "expr -> " << tok.valor << std::endl;
    }
    else if (tok.tipo == "RELOP") {
        std::cout << "relop -> " << tok.valor << std::endl;
    }
    else if (tok.tipo == "TIPO") {
        std::cout << "tipo -> " << tok.valor << std::endl;
    }
    else if (tok.tipo == "RESERVADA") {
        std::cout << "PALABRA RESERVADA -> " << tok.valor << std::endl;
    }
    else if (tok.tipo == "SEPARADOR") {
        std::cout << "separador -> " << tok.valor << std::endl;
    }
    else {
        std::cout << tok.tipo << " -> " << tok.valor << std::endl;
    }
}

// -------------------------------
// Verificar estructura IF (múltiples if)
// -------------------------------
bool verificarIf(const std::vector<Token> &tokens, size_t &i) {
    if (i >= tokens.size() || tokens[i].valor != "if") return false;
    i++;

    if (i >= tokens.size() || tokens[i].valor != "(") return false;
    i++;

    if (i >= tokens.size() || tokens[i].tipo != "EXPR") return false;
    std::string expr1 = tokens[i].valor;
    i++;

    if (i >= tokens.size() || tokens[i].tipo != "RELOP") return false;
    std::string relop = tokens[i].valor;
    i++;

    if (i >= tokens.size() || tokens[i].tipo != "EXPR") return false;
    std::string expr2 = tokens[i].valor;
    i++;

    if (i >= tokens.size() || tokens[i].valor != ")") return false;
    i++;

    if (i >= tokens.size() || tokens[i].valor != "{") return false;
    while (i < tokens.size() && tokens[i].valor != "}") { i++; }
    if (i >= tokens.size() || tokens[i].valor != "}") return false;
    i++;

    if (i >= tokens.size() || tokens[i].valor != "else") return false;
    i++;

    if (i >= tokens.size() || tokens[i].valor != "{") return false;
    while (i < tokens.size() && tokens[i].valor != "}") { i++; }
    if (i >= tokens.size() || tokens[i].valor != "}") return false;
    i++;

    // Imprimir la condición según la gramática
    std::cout << "\nIF -> if (COND) { INSTRUCCIONES } else { INSTRUCCIONES }" << std::endl;
    std::cout << "COND -> expr relop expr" << std::endl;
    std::cout << "expr -> " << expr1 << std::endl;
    std::cout << "relop -> " << relop << std::endl;
    std::cout << "expr -> " << expr2 << std::endl;

    return true;
}

// -------------------------------
// Main
// -------------------------------
int main() {
    std::ifstream archivo("archivo.txt"); 
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    char c;
    std::string palabra = "";
    std::vector<Token> tokens;

    while (archivo.get(c)) {
        if (c == '\n' || c == '\r') continue;

        if (isspace(c)) {
            if (!palabra.empty()) {
                tokens.push_back({palabra, clasificarToken(palabra)});
                palabra.clear();
            }
        }
        else if (esSeparador(c)) {
            if (!palabra.empty()) {
                tokens.push_back({palabra, clasificarToken(palabra)});
                palabra.clear();
            }
            std::string sep(1, c);
            tokens.push_back({sep, "SEPARADOR"});
        }
        else if (esOperador(c)) {
            if (!palabra.empty()) {
                tokens.push_back({palabra, clasificarToken(palabra)});
                palabra.clear();
            }
            char siguiente;
            if (archivo.peek() == '=' && (c == '=' || c == '!' || c == '<' || c == '>')) {
                archivo.get(siguiente);
                std::string op; op += c; op += siguiente;
                tokens.push_back({op, clasificarToken(op)});
            } else {
                std::string op(1, c);
                tokens.push_back({op, clasificarToken(op)});
            }
        }
        else {
            palabra += c;
        }
    }
    if (!palabra.empty()) {
        tokens.push_back({palabra, clasificarToken(palabra)});
    }
    archivo.close();

    // Mostrar tokens en formato de gramática
    for (size_t i = 0; i < tokens.size(); i++) {
        imprimirToken(tokens[i]);
    }

    // Validar múltiples IF
    bool ifEncontrado = false;
    size_t i = 0;
    while (i < tokens.size()) {
        if (tokens[i].valor == "if") {
            if (verificarIf(tokens, i)) {
                ifEncontrado = true;
            } else {
                std::cout << "\nError: estructura IF invalida" << std::endl;
                i++; // avanzar para evitar bucle infinito
            }
        } else {
            i++;
        }
    }

    if (!ifEncontrado) {
        std::cout << "\nNo se encontró ninguna estructura IF válida" << std::endl;
    }

    return 0;
}
