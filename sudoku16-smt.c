#include <stdio.h>
#include <ctype.h>

const char *const smtHeader =
    "(set-info :smt-lib-version 2.6)\n"
    "(set-logic QF_LIA)\n"
    "(set-info :status sat)\n"
    "\0";

const char *const smtFooter =
    "(check-sat)\n"
    "(get-value (board11 board12 board13 board14 board15 board16 board17 board18 board19))\n"
    "(get-value (board21 board22 board23 board24 board25 board26 board27 board28 board29))\n"
    "(get-value (board31 board32 board33 board34 board35 board36 board37 board38 board39))\n"
    "(get-value (board41 board42 board43 board44 board45 board46 board47 board48 board49))\n"
    "(get-value (board51 board52 board53 board54 board55 board56 board57 board58 board59))\n"
    "(get-value (board61 board62 board63 board64 board65 board66 board67 board68 board69))\n"
    "(get-value (board71 board72 board73 board74 board75 board76 board77 board78 board79))\n"
    "(get-value (board81 board82 board83 board84 board85 board86 board87 board88 board89))\n"
    "(get-value (board91 board92 board93 board94 board95 board96 board97 board98 board99))\n"
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
                    c = tolower(c);
                    c -= 'a';
                    c += 10;
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
            if (isNumber(board[y][x])) {
                printf("(declare-const board%X%X Int)(assert (= %d board%X%X))\n", x,y,board[y][x],x,y);
            } else {
                printf("(declare-const board%X%X Int)(assert (and (<= 0 board%X%X)(< board%X%X 16)))\n", x,y,x,y,x,y);
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
