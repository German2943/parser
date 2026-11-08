#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"

char *transicion_getter(char caracter, char *estado)
{

    FILE *f = fopen("dfa_datos.txt", "r");
    char linea[100];

    while (fgets(linea, sizeof(linea), f) != NULL)
    {

        char estado_origen[strcspn(linea, ",") + 1];
        estado_origen[0] = linea[0];
        int i = 1;
        for (i; i <= strcspn(linea, ",") + 1; i++)
        {
            if (linea[i] == ',')
            {
                estado_origen[i] = '\0';
                break;
            }
            estado_origen[i] = linea[i];
        }
        char caracter_leido[strcspn(linea + i + 1, ",") + 1];
        caracter_leido[0] = linea[i + 1];
        int j = 1;
        for (j; j <= strcspn(linea + i + 1, ",") + 1; j++)
        {
            if (linea[i + 1 + j] == ',')
            {
                caracter_leido[j] = '\0';
                break;
            }
            caracter_leido[j] = linea[i + 1 + j];
        }
        char estado_destino[strcspn(linea + i + 1 + j + 1, "\n") + 1];
        estado_destino[0] = linea[i + 1 + j + 1];
        int k = 1;
        for (k; k <= strcspn(linea + i + 1 + j + 1, "\n") + 1; k++)
        {
            if (linea[i + 1 + j + 1 + k] == '\n')
            {
                estado_destino[k] = '\0';
                break;
            }
            estado_destino[k] = linea[i + 1 + j + 1 + k];
        }

        if (atoi(estado) == atoi(estado_origen) && caracter == caracter_leido[0])
        {

            char *result = malloc(strlen(estado_destino) + 1);
            strcpy(result, estado_destino);
            fclose(f);
            return result;
        }
    }

    return "253";
}

char *lexem_identifier(char *lexem) // given a str, gives what is its state
{
    char *estado = (char *)malloc((strlen(lexem) + 1) * sizeof(char));
    estado[0] = '0';
    estado[1] = '\0';

    for (int i = 0; i < strlen(lexem) + 1; i++)
    {
        if (lexem[i] == '\0')
        {
            break;
        }
        if (transicion_getter(lexem[i], estado) == NULL)
        {
            return NULL;
        }

        strcpy(estado, transicion_getter(lexem[i], estado));
        estado[strlen(lexem) + 1] = '\0';
    }
    return estado;
}

char *token_assigner(int estado)
{
    FILE *f = fopen("tokens.txt", "r");
    char linea[100];
    while (fgets(linea, sizeof(linea), f) != NULL)
    {
        char estado_origen[strcspn(linea, ",") + 1];
        estado_origen[0] = linea[0];
        int i = 1;
        for (i; i <= strcspn(linea, ",") + 1; i++)
        {
            if (linea[i] == ',')
            {
                estado_origen[i] = '\0';
                break;
            }
            estado_origen[i] = linea[i];
        }
        char token[strcspn(linea + i + 1, "\n") + 1];
        token[0] = linea[i + 1];
        int j = 1;
        for (j; j <= strcspn(linea + i + 1, "\n") + 1; j++)
        {
            if (linea[i + 1 + j] == '\n')
            {
                token[j] = '\0';
                break;
            }
            token[j] = linea[i + 1 + j];
        }
        if (atoi(estado_origen) == estado)
        {

            char *s = malloc(strlen(token) + 1);
            strcpy(s, token);
            fclose(f);
            return s;
        }
    }
    fclose(f);
    return "INVALID_TOKEN";
}
int es_aceptacion(int valor)
{
    int aceptacion[238] = {1, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 155, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 243, 247, 249, 248, 251};
    for (int i = 0; i < 238; i++)
    {
        if (valor == aceptacion[i])
        {
            return 0;
        }
    }
    return 1;
}

char *keyword_identifier(char *lexem)
{

    char lexemas_posibles[44][15] = {
        "auto",
        "double",
        "int",
        "struct",
        "break",
        "else",
        "long",
        "switch",
        "case",
        "enum",
        "register",
        "typedef",
        "char",
        "extern",
        "return",
        "union",
        "const",
        "float",
        "short",
        "unsigned",
        "continue",
        "for",
        "signed",
        "void",
        "default",
        "goto",
        "sizeof",
        "volatile",
        "do",
        "if",
        "static",
        "while",
        "scanf",
        "print",
        "define",
        "elif",
        "endif",
        "error",
        "if",
        "ifdef",
        "ifndef",
        "include",
        "message",
        "undef"};
    char keyword_token[44][15] = {"AUTO", "DOUBLE", "INT", "STRUCT", "BREAK", "ELSE", "LONG", "SWITCH", "CASE", "ENUM", "REGISTER", "TYPEDEF", "CHAR", "EXTERN", "RETURN", "UNION", "CONST", "FLOAT", "SHORT", "UNSIGNED", "CONTINUE", "FOR", "SIGNED", "VOID", "DEFAULT", "GOTO", "SIZEOF", "VOLATILE", "DO", "IF", "STATIC", "WHILE", "READ", "WRITE", "DEFINE", "ELIF", "ENDIF", "ERROR", "IF", "IFDEF", "IFNDEF", "INCLUDE", "MESSAGE", "UNDEF"};

    /*
    char lexemas_posibles[4][15] = {"SELECT", "WHERE", "AND", "OR"};
    char keyword_token[4][15] = {"SELECT", "WHERE", "AND", "OR"};
    */
    char *match;
    int length = sizeof(lexemas_posibles) / sizeof(lexemas_posibles[0]);
    int i = 0;
    while (i < length)
    {

        if (strcmp(lexem, lexemas_posibles[i]) == 0)
        {

            match = (char *)malloc(sizeof(char) * strlen(keyword_token[i]));
            match = strcpy(match, keyword_token[i]);

            return match;
        }

        i++;
    }

    match = (char *)malloc(sizeof(char) * 3);
    match = strcpy(match, "ID");
    return match;
}
int maximalMunch(char *str, TOKEN **tokens, int *capacidad_tokens, int *token_counter)
{

    int inicio = 0;

    while (inicio < strlen(str))
    {
        int estado = 0;
        int ultima_pos_aceptora = -1;
        int ultimo_token_aceptado = -1;
        int pos = inicio;
        while (pos < strlen(str))
        {
            char buffer[12];
            sprintf(buffer, "%d", estado);
            int siguiente = atoi(transicion_getter(str[pos], buffer));
            if (siguiente == 253)
                break;
            estado = siguiente;
            pos++;
            if (es_aceptacion(estado) == 0)
            {
                ultima_pos_aceptora = pos;
                ultimo_token_aceptado = estado;
            }
        }

        if (ultima_pos_aceptora == -1)
        {
            inicio++;
        }
        else
        {
            int len = ultima_pos_aceptora - inicio;
            char *lexema = strndup(str + inicio, len);

            char *label = token_assigner(ultimo_token_aceptado);
            if (strcmp(label, "ID") == 0)
            {
                free(label);
                label = keyword_identifier(lexema);
            }

            if (*token_counter >= *capacidad_tokens)
            {
                *capacidad_tokens *= 2;
                *tokens = realloc(*tokens, sizeof(TOKEN) * (*capacidad_tokens));
            }

            (*tokens)[*token_counter].label = label;
            (*tokens)[*token_counter].lexem = lexema;
            (*token_counter)++;

            inicio = ultima_pos_aceptora;
        }
    }

    return 0;
}

void reader(FILE *f, TOKEN **tokens, int *capacidad_tokens, int *token_counter)
{
    char *raw_chars = string_divider(f);

    int index_buffer = 0;
    int capacidad_buffer = 100;
    char *buffer = (char *)malloc(sizeof(char) * capacidad_buffer);
    for (int i = 0; i <= strlen(raw_chars); i++)
    {
        if (isspace(raw_chars[i]) || i >= strlen(raw_chars))
        {
            if (strlen(buffer) == 0)
            {
                continue;
            }
            if (index_buffer >= capacidad_buffer)
            {
                capacidad_buffer = capacidad_buffer * 2;
                buffer = realloc(buffer, capacidad_buffer);
            }

            buffer[index_buffer] = '\0';
            index_buffer = 0;
            maximalMunch(buffer, tokens, capacidad_tokens, token_counter);

            continue;
        }
        if (index_buffer >= capacidad_buffer)
        {
            capacidad_buffer = capacidad_buffer * 2;
            buffer = realloc(buffer, capacidad_buffer);
        }

        buffer[index_buffer] = raw_chars[i];
        index_buffer++;
    }

    free(buffer);
    free(raw_chars);
}

char no_terminales[] = {'Q', 'L', 'l', 'W', 'E', 'e', 'T', 't', 'F', 'C', 'O', 'V'};

char simbolo_inicial = 'Q';

char terminales[][15] = {"SELECT", "WHERE", "AND", "OR", "EQ", "NOT_EQ", "GT", "LT",
                         "GTEQ", "LTEQ", "ID", "INT_NUM", "STRING", "COMMA",
                         "SEMICOLON", "LPAR", "RPAR", "$"};

static void expresion(void), asignacion(void), binaria(int), unaria(void),
    potencia(void), primario(void), programa(void), decl_funcion(void),
    bloque(void), sentencia(void), sentencia_simple(void);

static TOKEN *toks;
static size_t pos;
static void error_esperaba(const char *esperado)
{
    fprintf(stderr, "Error sintactico: se esperaba '%s' pero se encontro '%s' (\"%s\") en el token #%zu\n",
            esperado, toks[pos].label, toks[pos].lexem, pos);
    exit(1);
}
static int check(const char *t) { return strcmp(toks[pos].label, t) == 0; }
static int match(const char *t)
{
    if (check(t))
    {
        pos++;
        return 1;
    }
    return 0;
}
static void expect(const char *t)
{
    if (!match(t))
        error_esperaba(t);
}

static const char *NIVELES[][5] = {
    {"or"}, {"and"}, {"==", "~="}, {"<", "<=", ">", ">="}, {"+", "-"}, {"*", "/"}, {"%"}};
#define N_NIVELES 7

static int en(const char **ops)
{
    for (; *ops; ops++)
        if (check(*ops))
            return 1;
    return 0;
}

static void expresion(void) { asignacion(); }

static void asignacion(void)
{
    binaria(0);
    if (match(":="))
        asignacion();
}

static void binaria(int nivel)
{
    if (nivel == N_NIVELES)
    {
        unaria();
        return;
    }
    binaria(nivel + 1);
    while (en(NIVELES[nivel]))
    {
        pos++;
        binaria(nivel + 1);
    }
}

static void unaria(void)
{
    if (match("-") || match("~"))
        unaria();
    else
        potencia();
}

static void potencia(void)
{
    primario();
    if (match("^"))
        unaria();
}

static void primario(void)
{
    if (match("INT_NUM") || match("STRING") || match("true") || match("false"))
        return;
    if (match("("))
    {
        expresion();
        expect(")");
        return;
    }
    if (match("ID"))
    {
        if (match("("))
        {
            if (!check(")"))
            {
                expresion();
                while (match(","))
                    expresion();
            }
            expect(")");
        }
        return;
    }
    error_esperaba("expresion");
}

static void programa(void)
{
    while (!check("EOF"))
    {
        if (check("func"))
            decl_funcion();
        else
            sentencia();
    }
    printf("la cadena pertenece a la gramática");
}

static void decl_funcion(void)
{
    expect("func");
    expect("ID");
    expect("(");
    if (match("ID"))
    {
        while (match(","))
            expect("ID");
    }
    expect(")");
    bloque();
    expect("end");
}

static void bloque(void)
{
    while (!check("end") && !check("else") && !check("EOF"))
        sentencia();
}

static void sentencia(void)
{
    if (match("if"))
    {
        expresion();
        expect("then");
        bloque();
        if (match("else"))
            bloque();
        expect("end");
    }
    else if (match("while"))
    {
        expresion();
        expect("do");
        bloque();
        expect("end");
    }
    else if (match("for"))
    {
        expect("ID");
        expect(":=");
        expresion();
        expect(",");
        expresion();
        if (match(","))
            expresion();
        expect("do");
        bloque();
        expect("end");
    }
    else
    {
        sentencia_simple();
        expect(";");
    }
}

static void sentencia_simple(void)
{
    if (match("print") || match("println") || match("ret"))
        expresion();
    else if (match("local"))
    {
        expect("ID");
        expect(":=");
        expresion();
    }
    else
        expresion();
}

static const char *KEYWORDS[] = {
    "func", "end", "if", "then", "else", "while", "do", "for",
    "print", "println", "ret", "local", "and", "or", "true", "false", NULL};

static int es_keyword(const char *s)
{
    for (int i = 0; KEYWORDS[i]; i++)
        if (strcmp(KEYWORDS[i], s) == 0)
            return 1;
    return 0;
}

static void set_label(TOKEN *t, const char *nuevo)
{
    free(t->label);
    t->label = strdup(nuevo);
}

static void normalizar(TOKEN *t, int n)
{
    for (int i = 0; i < n; i++)
    {
        const char *l = t[i].label;
        if (strcmp(l, "ID") == 0)
        {
            if (es_keyword(t[i].lexem))
                set_label(&t[i], t[i].lexem);
        }
        else if (strcmp(l, "INT_NUM") == 0 || strcmp(l, "FLOAT_NUM") == 0)
        {
            set_label(&t[i], "INT_NUM");
        }
        else if (strcmp(l, "STRING") != 0 && strcmp(l, "EOF") != 0)
        {
            set_label(&t[i], t[i].lexem);
        }
    }
}

int main(void)
{
    int capacidad_tokens = 100;
    int token_counter = 0;
    TOKEN(*tokens);
    tokens = (TOKEN *)malloc(sizeof(TOKEN) * capacidad_tokens);

    reader(fopen("testing.txt", "r"), &tokens, &capacidad_tokens, &token_counter);
    if (token_counter >= capacidad_tokens)
    {
        capacidad_tokens++;
        tokens = (TOKEN *)realloc(tokens, sizeof(TOKEN) * capacidad_tokens);
    }

    tokens[token_counter].label = strdup("EOF");
    tokens[token_counter].lexem = strdup("");
    token_counter++;
    normalizar(tokens, token_counter);
    toks = tokens;
    pos = 0;

    printf("\ntokens generados\n");

    for (int i = 0; i < token_counter; i++)
    {
        printf("#%d label=\"%s\" lexem=\"%s\"\n", i, tokens[i].label, tokens[i].lexem);
    }
    programa();
    for (int i = 0; i < token_counter; i++)
    {
        free((tokens[i]).label);
        free((tokens[i]).lexem);
    }

    free(tokens);

    return 0;
}