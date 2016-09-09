#ifndef TOKENINDEX_H
#define TOKENINDEX_H

//tokenIndex.h


typedef struct TokenizerT_ TokenizerT;

struct TokenizerT_ {

    int position;
    char *inputString;
};

char *subString(char *str, int start, int end);

TokenizerT *TKCreate(FILE * fd);

void TKDestroy(TokenizerT *tk);

char *TKGetNextToken(TokenizerT * tk);

#endif
