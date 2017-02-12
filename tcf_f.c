#include "tcf_f.h"

/* ARITHMETIC */

/* Single-length */

fw(LAST_C_WORD, DIVMOD,     "/MOD"      ) 0 __;
fw(DIVMOD,      MULDIV,     "*/"        ) 0 __;
fw(MULDIV,      MULDIVMOD,  "*/MOD"     ) 0 __;
fw(MULDIVMOD,   UMUL,       "U*"        ) 0 __;
fw(UMUL,        UDIVMOD,    "U/MOD"     ) 0 __;
fw(UDIVMOD,     INC1,       "1+"        ) 0 __;
fw(INC1,        DEC1,       "1-"        ) 0 __;
fw(DEC1,        INC2,       "2+"        ) 0 __;
fw(INC2,        DEC2,       "2-"        ) 0 __;
fw(DEC2,        DOUBLE,     "2*"        ) /* A -- 2*A */
    DUP _ ADD __;
fw(DOUBLE,      HALF,       "2/"        ) 0 __;
fw(HALF,        ABS,        "ABS"       ) 0 __;
fw(ABS,         NEGATE,     "NEGATE"    ) 0 __;

/* Double-length */

fw(NEGATE,      DADD,       "D+"        ) 0 __;
fw(DADD,        DSUB,       "D-"        ) 0 __;
fw(DSUB,        DNEGATE,    "DNEGATE"   ) 0 __;
fw(DNEGATE,     DABS,       "DABS"      ) 0 __;

/* Mixed-length */

fw(DABS,        MADD,       "M+"        ) 0 __;
fw(MADD,        MDIV,       "M/"        ) 0 __;
fw(MDIV,        MMUL,       "M*"        ) 0 __;
fw(MMUL,        MMULDIV,    "M*/"       ) 0 __;

/* CHARACTER INPUT */

fw(MMULDIV,     EXPECT,     "EXPECT"    ) 0 __;
fw(EXPECT,      WORD,       "WORD"      ) 0 __;
fw(WORD,        TEXT,       "TEXT"      ) 0 __;
fw(TEXT,        COUNT,      "COUNT"     ) 0 __;

/* CHARACTER OUTPUT */

fw(COUNT,       CR,         "CR"        ) 0 __;
fw(CR,          SPACE,      "SPACE"     ) 0 __;
fw(SPACE,       SPACES,     "SPACES"    ) 0 __;
//fw(UMUL,        UDIVMOD,    "EMIT"      ) 0 __;
fw(SPACES,      DOTDQUOTE,  ".\""       ) 0 __;
fw(DOTDQUOTE,   PAGE,       "PAGE"      ) 0 __;
fw(PAGE,        TYPE,       "TYPE"      ) 0 __;
fw(TYPE,        GTTYPE,     ">TYPE"     ) 0 __;
fw(GTTYPE,      DTRAILING,  "-TRAILING" ) 0 __;

/* COMPARISONS */

/* Single-length */

fw(DTRAILING,   EQ,         "="         ) 0 __;
fw(EQ,          MINUS,      "-"         ) 0 __;
fw(MINUS,       LT,         "<"         ) 0 __;
fw(LT,          ULT,        "U<"        ) 0 __;
fw(ULT,         GT,         ">"         ) 0 __;
fw(GT,          IS_ZERO,    "0="        ) 0 __;
fw(IS_ZERO,     IS_NEGATIVE,"0<"        ) 0 __;
fw(IS_NEGATIVE, IS_POSITIVE,"0>"        ) 0 __;
fw(IS_POSITIVE, MIN,        "MIN"       ) 0 __;
fw(MIN,         MAX,        "MAX"       ) 0 __;

/* Double-length */

fw(MAX,         DEQ,        "D="        ) 0 __;
fw(DEQ,         DIS_ZERO,   "D0="        ) 0 __;
fw(DIS_ZERO,    DLT,        "D<"        ) 0 __;
fw(DLT,         DULT,       "DU<"        ) 0 __;
fw(DULT,        DMIN,       "DMIN"        ) 0 __;
fw(DMIN,        DMAX,       "DMAX"        ) 0 __;

/* String */

fw(DMAX,        DTEXT,      "-TEXT"        ) 0 __;
fw(DTEXT,       LAST_FTH_WORD, ""          ) 0 __;

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
