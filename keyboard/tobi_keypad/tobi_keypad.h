
#ifndef ACTIONMAP_COMMON_H
#define ACTIONMAP_COMMON_H


#define ACTIONMAP( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23, \
    K30, K31, K32, K33, \
    K40, K41, K42, K43  \
) { \
    { AC_##K00, AC_##K01, AC_##K02, AC_##K03 }, \
    { AC_##K10, AC_##K11, AC_##K12, AC_##K13 }, \
    { AC_##K20, AC_##K21, AC_##K22, AC_##K23 }, \
    { AC_##K30, AC_##K31, AC_##K32, AC_##K33 }, \
    { AC_##K40, AC_##K41, AC_##K42, AC_##K43 }  \
}

#define ACTIONMAP_tobi_keypad( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23, \
    K30, K31, K32, K33, \
    K40, K41, K42, K43  \
) ACTIONMAP( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23, \
    K30, K31, K32, K33, \
    K40, K41, K42, K43  \
)

#endif

