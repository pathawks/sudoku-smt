#include <stdio.h>
#include <ctype.h>

const char *const smtHeader =
    "(set-info :smt-lib-version 2.6)\n"
    "(set-logic QF_NIA)\n"
    "(set-info :status sat)\n"
    "\0";

const int height = 16;
const int width  = 16;
int produceModels = 0;

void footer(void);

int isNumber(char c) {
    return (0 <= c && c <= 15);
}

int isValid(char c) {
    return isNumber(c) || (c == '_'-'A') || (c == '.'-'0');
}

int main(void) {
    int board[height][width];
    for (int x=0; x<width; ++x) {
        for (int y=0; y<height; ++y) {
            do {
                int c;
                c = getchar();
                if (c >= 'A') {
                    c = tolower(c) - 'a' + 10;
                } else {
                    c -= '0';
                }
                board[y][x] = c;
            } while (!isValid(board[y][x]));
        }
    }

    fputs(smtHeader, stdout);
    if (produceModels) {
        puts("(set-option :produce-models true)");
    }

    for (int x=0; x<width; ++x) {
        for (int y=0; y<height; ++y) {
            char xpos = x < 10 ? x + '0' : x + 'A' - 10;
            char ypos = y < 10 ? y + '0' : y + 'A' - 10;
            if (isNumber(board[y][x])) {
                printf("(declare-const board%c%c Int)(assert (= %d board%c%c))\n", xpos,ypos,board[y][x],xpos,ypos);
            } else {
                printf("(declare-const board%c%c Int)(assert (and (<= 0 board%c%c)(< board%c%c 16)))\n", xpos,ypos,xpos,ypos,xpos,ypos);
            }
        }
    }
    footer();
}

void footer(void) {
    for (int x=0; x<16; ++x) {
        fputs("(assert (distinct", stdout);
        for (int y=0; y<16; ++y) {
            printf(" board%X%X", x, y);
        }
        fputs("))\n", stdout);
    }
    for (int x=0; x<16; ++x) {
        fputs("(assert (distinct", stdout);
        for (int y=0; y<16; ++y) {
            printf(" board%X%X", y, x);
        }
        fputs("))\n", stdout);
    }
    for (int xx=0; xx<16; xx+=4)
        for (int yy=0; yy<16; yy+=4) {
            fputs("(assert (distinct", stdout);
            for (int x=xx; x<xx+4; ++x)
                for (int y=yy; y<yy+4; ++y) {
                    printf(" board%X%X", y, x);
                }
            fputs("))\n", stdout);
        }
    puts("(check-sat)");
    if (produceModels) {
        for (int x=0; x<16; ++x) {
            fputs("(get-value (", stdout);
            for (int y=0; y<16; ++y) {
                if (y) fputs(" ", stdout);
                printf("board%X%X", x, y);
            }
            fputs("))\n", stdout);
        }
    }
    puts("(exit)");
}
