//
// Created by young on 02/01/2021.
//
#include <string.h>

// States Table
enum State {
    STATE_INITIAL,
    STATE_INT_SIGN,
    STATE_INTEGER,
    STATE_POINT,
    STATE_POINT_WITHOUT_INT,
    STATE_FRACTION,
    STATE_EXP,
    STATE_EXP_SIGN,
    STATE_EXP_NUMBER,
    STATE_END,
    STATE_ILLEGAL
};

enum CharType {
    CHAR_NUMBER,
    CHAR_EXP,
    CHAR_POINT,
    CHAR_SIGN,
    CHAR_SPACE,
    CHAR_ILLEGAL
};

enum CharType toCharType(char ch) {
    if (ch >= '0' && ch <= '9') return CHAR_NUMBER;
    else if (ch == 'e' || ch == 'E') return CHAR_EXP;
    else if (ch == '.') return CHAR_POINT;
    else if (ch == '+' || ch == '-') return CHAR_SIGN;
    else if (ch == ' ') return CHAR_SPACE;
    else return CHAR_ILLEGAL;
}

enum State transfer(enum State st, enum CharType typ) {
    switch (st) {
        case STATE_INITIAL: {
            switch (typ) {
                case CHAR_SPACE:
                    return STATE_INITIAL;
                case CHAR_NUMBER:
                    return STATE_INTEGER;
                case CHAR_POINT:
                    return STATE_POINT_WITHOUT_INT;
                case CHAR_SIGN:
                    return STATE_INT_SIGN;
                default:
                    return STATE_ILLEGAL;
            }
        }
        case STATE_INT_SIGN: {
            switch (typ) {
                case CHAR_NUMBER:
                    return STATE_INTEGER;
                case CHAR_POINT:
                    return STATE_POINT_WITHOUT_INT;
                default:
                    return STATE_ILLEGAL;
            }
        }
        case STATE_INTEGER: {
            switch (typ) {
                case CHAR_NUMBER:
                    return STATE_INTEGER;
                case CHAR_EXP:
                    return STATE_EXP;
                case CHAR_POINT:
                    return STATE_POINT;
                case CHAR_SPACE:
                    return STATE_END;
                default:
                    return STATE_ILLEGAL;
            }
        }
        case STATE_POINT: {
            switch (typ) {
                case CHAR_NUMBER:
                    return STATE_FRACTION;
                case CHAR_EXP:
                    return STATE_EXP;
                case CHAR_SPACE:
                    return STATE_END;
                default:
                    return STATE_ILLEGAL;
            }
        }
        case STATE_POINT_WITHOUT_INT: {
            switch (typ) {
                case CHAR_NUMBER:
                    return STATE_FRACTION;
                default:
                    return STATE_ILLEGAL;
            }
        }
        case STATE_FRACTION: {
            switch (typ) {
                case CHAR_NUMBER:
                    return STATE_FRACTION;
                case CHAR_EXP:
                    return STATE_EXP;
                case CHAR_SPACE:
                    return STATE_END;
                default:
                    return STATE_ILLEGAL;
            }
        }
        case STATE_EXP: {
            switch (typ) {
                case CHAR_NUMBER:
                    return STATE_EXP_NUMBER;
                case CHAR_SIGN:
                    return STATE_EXP_SIGN;
                default:
                    return STATE_ILLEGAL;
            }
        }
        case STATE_EXP_SIGN: {
            switch (typ) {
                case CHAR_NUMBER:
                    return STATE_EXP_NUMBER;
                default:
                    return STATE_ILLEGAL;
            }
        }
        case STATE_EXP_NUMBER: {
            switch (typ) {
                case CHAR_NUMBER:
                    return STATE_EXP_NUMBER;
                case CHAR_SPACE:
                    return STATE_END;
                default:
                    return STATE_ILLEGAL;
            }
        }
        case STATE_END: {
            switch (typ) {
                case CHAR_SPACE:
                    return STATE_END;
                default:
                    return STATE_ILLEGAL;
            }
        }
        default:
            return STATE_ILLEGAL;
    }
}

bool isNumber(char *s) {
    int len = strlen(s);
    enum State st = STATE_INITIAL;

    for (int i = 0; i < len; ++i) {
        enum CharType type = toCharType(s[i]);
        enum State nextState = transfer(st, type);

        if (nextState == STATE_ILLEGAL) return false;
        st = nextState;
    }

    return st == STATE_INTEGER \
 || st == STATE_POINT \
 || st == STATE_FRACTION \
 || st == STATE_EXP_NUMBER \
 || st == STATE_END;
}
