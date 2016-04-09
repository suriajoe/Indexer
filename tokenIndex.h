#ifndef TOKENINDEX_H
#define TOKENINDEX_H

//tokenIndex.h


typedef struct TokenizerT_ TokenizerT;

struct TokenizerT_ {

    int position;
    int tkType;
    char *inputString;
};

char *subString(char *str, int start, int end);

Tokenizer *TkCreate(char *ts);

void TKDestroy(TokenizerT *tk);

char *TKGetNextToken(TokenizerT * tk);

#endif
