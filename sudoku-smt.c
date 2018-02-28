#include <stdio.h>

const char *const smtHeader =
    "(set-info :smt-lib-version 2.6)\n"
    "(set-logic QF_IDL)\n"
    "(set-info :status sat)\n"
    "\0";

const char *const smtFooter =
    "(assert (distinct board11 board12 board13 board14 board15 board16 board17 board18 board19))\n"
    "(assert (distinct board11 board21 board31 board41 board51 board61 board71 board81 board91))\n"
    "(assert (distinct board21 board22 board23 board24 board25 board26 board27 board28 board29))\n"
    "(assert (distinct board12 board22 board32 board42 board52 board62 board72 board82 board92))\n"
    "(assert (distinct board31 board32 board33 board34 board35 board36 board37 board38 board39))\n"
    "(assert (distinct board13 board23 board33 board43 board53 board63 board73 board83 board93))\n"
    "(assert (distinct board41 board42 board43 board44 board45 board46 board47 board48 board49))\n"
    "(assert (distinct board14 board24 board34 board44 board54 board64 board74 board84 board94))\n"
    "(assert (distinct board51 board52 board53 board54 board55 board56 board57 board58 board59))\n"
    "(assert (distinct board15 board25 board35 board45 board55 board65 board75 board85 board95))\n"
    "(assert (distinct board61 board62 board63 board64 board65 board66 board67 board68 board69))\n"
    "(assert (distinct board16 board26 board36 board46 board56 board66 board76 board86 board96))\n"
    "(assert (distinct board71 board72 board73 board74 board75 board76 board77 board78 board79))\n"
    "(assert (distinct board17 board27 board37 board47 board57 board67 board77 board87 board97))\n"
    "(assert (distinct board81 board82 board83 board84 board85 board86 board87 board88 board89))\n"
    "(assert (distinct board18 board28 board38 board48 board58 board68 board78 board88 board98))\n"
    "(assert (distinct board91 board92 board93 board94 board95 board96 board97 board98 board99))\n"
    "(assert (distinct board19 board29 board39 board49 board59 board69 board79 board89 board99))\n"
    "(assert (distinct board11 board12 board13 board21 board22 board23 board31 board32 board33))\n"
    "(assert (distinct board14 board15 board16 board24 board25 board26 board34 board35 board36))\n"
    "(assert (distinct board17 board18 board19 board27 board28 board29 board37 board38 board39))\n"
    "(assert (distinct board41 board42 board43 board51 board52 board53 board61 board62 board63))\n"
    "(assert (distinct board44 board45 board46 board54 board55 board56 board64 board65 board66))\n"
    "(assert (distinct board47 board48 board49 board57 board58 board59 board67 board68 board69))\n"
    "(assert (distinct board71 board72 board73 board81 board82 board83 board91 board92 board93))\n"
    "(assert (distinct board74 board75 board76 board84 board85 board86 board94 board95 board96))\n"
    "(assert (distinct board77 board78 board79 board87 board88 board89 board97 board98 board99))\n"
    "(check-sat)\n"
    "(exit)\n"
    "\0";

const int height = 9;
const int width  = 9;

int isNumber(char c) {
    return ('1' <= c && c <= '9');
}

int isUnknown(char c) {
    return (c == '_') || (c == '.');
}

int main(void) {
    int board[height][width];
    int unknowns = 0;
    for (int x=0; x<width; ++x) {
        for (int y=0; y<height; ++y) {
            for(;;) {
                board[y][x] = getchar();
                if (isUnknown(board[y][x])) {
                    ++unknowns;
                    break;
                } else if (isNumber(board[y][x])) {
                    break;
                }
            }
        }
    }

    fputs(smtHeader, stdout);
    printf("(set-info :unknowns %d)\n", unknowns);

    for (int x=0; x<width; ++x) {
        for (int y=0; y<height; ++y) {
            char xpos = x+'1';
            char ypos = y+'1';
            if (isNumber(board[y][x])) {
                printf("(declare-const board%c%c Int)(assert (= %c board%c%c))\n", xpos,ypos,board[y][x],xpos,ypos);
            } else {
                printf("(declare-const board%c%c Int)(assert (and (<= 1 board%c%c)(<= board%c%c 9)))\n", xpos,ypos,xpos,ypos,xpos,ypos);
            }
        }
    }
    fputs(smtFooter, stdout);
}
