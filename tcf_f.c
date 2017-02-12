#include "tcf_f.h"


fw(LAST_C_WORD, DOUBLE,     "DOUBLE"    ) /* A -- 2*A */
    DUP _ ADD __;

/* ARITHMETIC */

/* Single-length */

fw(DOUBLE,      DIVMOD,     "/MOD"      ) DIV __;
fw(DIVMOD,      MULDIV,     "*/"        ) ROT _ ROT _ MUL _ DIV __;
fw(MULDIV,      MULDIVMOD,  "*/MOD"     ) ROT _ ROT _ MUL _ DIVMOD __;
fw(MULDIVMOD,   UMUL,       "U*"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "U/MOD"     ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "1+"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "1-"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "2+"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "2-"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "2*"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "2/"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "ABS"       ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "NEGATE"    ) ROT _ ROT _ MUL _ DIVMOD __;

/* Double-length */

fw(UMUL,        UDIVMOD,    "D+"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "D-"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "DNEGATE"   ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "DABS"      ) ROT _ ROT _ MUL _ DIVMOD __;

/* Mixed-length */

fw(UMUL,        UDIVMOD,    "M+"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "M/"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "M*"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "M*/"       ) ROT _ ROT _ MUL _ DIVMOD __;

/* CHARACTER INPUT */

fw(UMUL,        UDIVMOD,    "EXPECT"    ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "WORD"      ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "TEXT"      ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "COUNT"     ) ROT _ ROT _ MUL _ DIVMOD __;

/* CHARACTER OUTPUT */

fw(UMUL,        UDIVMOD,    "CR"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "SPACE"     ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "SPACES"    ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "EMIT"      ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    ".\""       ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "PAGE"      ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "TYPE"      ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    ">TYPE"     ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "-TRAILING" ) ROT _ ROT _ MUL _ DIVMOD __;

/* COMPARISONS */

/* Single-length */

fw(UMUL,        UDIVMOD,    "="         ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "-"         ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "<"         ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "U<"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    ">"         ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "0="        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "0<"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "0>"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "MIN"       ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "MAX"       ) ROT _ ROT _ MUL _ DIVMOD __;

/* Double-length */

fw(UMUL,        UDIVMOD,    "D="        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "D0="        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "D<"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "DU<"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "DMIN"        ) ROT _ ROT _ MUL _ DIVMOD __;
fw(UMUL,        UDIVMOD,    "DMAX"        ) ROT _ ROT _ MUL _ DIVMOD __;

/* String */

fw(UMUL,        UDIVMOD,    "-TEXT"        ) ROT _ ROT _ MUL _ DIVMOD __;

/* COMPILATION */

/* CONSTANTS */

/* DEFINING WORDS */

/* DICTIONARY MANAGEMENT */

/* EDITOR COMMANDS */

/* INTERPRETATION */

/* LOGIC */

/* MEMORY */

/* NUMBER INPUT CONVERSION */

/* NUMBER OUTÙT */

/* NUMBER FORMATTING */

/* OPERATING SYSTEM */

/* Commands */

/* User variables */

/* RETURN STACK */

/* STACK MANIPULATION */

/* Single-length */

/* Double-length */

/* STRUCTURE CONTROL */

/* VIRTUAL MEMORY */
