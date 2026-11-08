#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef struct TOKEN
{
    char *label;
    char *lexem;
} TOKEN;

extern int capacidad_tokens;
extern int token_counter;
extern TOKEN *tokens;

#endif