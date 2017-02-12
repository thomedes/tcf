#ifndef TCF_F_H__
#define TCF_F_H__

#include <stdint.h>

typedef intptr_t cell;

struct forth_s;
typedef void (forth_fn)(struct forth_s *);

forth_fn do_colon;

extern const cell
    ADD[],
    DUP[],
    LAST_C_WORD[],
    LAST_FTH_WORD[];

#define l_    LIT ), (cell) (
#define _     ), (cell) (2 +
#define __    ), 0 }
#define cw(p,cn,fn) const cell cn[] = { (cell) (p), (cell) fn, (cell) &cn##_ }
#define fw(p,cn,fn) static const cell cn[] = { (cell) (p), (cell) fn, ((cell) &do_colon _

#endif                         /* TCF_F_H__ */
