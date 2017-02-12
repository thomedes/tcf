#include "tcf_f.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sys_s {
    int     (*key)(void);
    void    (*emit)(int c);
} sys_t;

typedef struct forth_s {
    const cell   *ip;
    cell *psp, *rsp, *mem, mem_cells;
    sys_t   sys;
} forth_t;

#define WPREV(p)    ((p)[0])
#define WNAME(p)    ((p)[1])
#define WCODE(p)    ((p)[2])
#define WPARAMS(p)  ((p)[3])

#define IP          f->ip

#define PSP         f->psp
#define PUSH(x)     (*(--PSP) = (x))
#define POP         (*(PSP++))
#define TOP         PSP[0]

#define RSP         f->rsp
#define RPUSH(x)    (*(--RSP) = (cell) (x))
#define RPOP        (*(RSP++))
#define RTOP        RSP[0]

#define RETURN      { IP = (cell *) RPOP; return; }

static void forth_dump(const forth_t *f);

static void DUP_ (forth_t *f) { --PSP; TOP = PSP[1]; RETURN }
static void DROP_(forth_t *f) { ++PSP; RETURN }
static void SWAP_(forth_t *f) { cell c = TOP; TOP = PSP[1]; PSP[1] = c; RETURN }
static void OVER_(forth_t *f) { --PSP; TOP = PSP[2]; RETURN }

static void LIT_ (forth_t *f) { IP = (cell *) RPOP; PUSH(*IP++); }

static void ADD_ (forth_t *f) { PSP[1] += TOP; ++PSP; RETURN }
static void SUB_ (forth_t *f) { PSP[1] -= TOP; ++PSP; RETURN }
static void MUL_ (forth_t *f) { PSP[1] *= TOP; ++PSP; RETURN }
static void DIV_ (forth_t *f) { PSP[1] /= TOP; ++PSP; RETURN }
static void MOD_ (forth_t *f) { PSP[1] %= TOP; ++PSP; RETURN }

static void EMIT_(forth_t *f) { (*f->sys.emit)(POP); RETURN }
static void KEY_ (forth_t *f) { PUSH((*f->sys.key)()); RETURN }

static const char *word_name(cell *code) { return (const char *) (code[-1]); }

void do_colon(forth_t *f)
{
//     printf("do_colon %s\n", word_name(IP - 1));
    while (*IP) {
        RPUSH(IP + 1);
        IP = (cell *) *IP;
//         printf("--> %s\n", word_name(IP));

        (**(forth_fn *) *IP++)(f);
    }
}

static void word_dump(cell *code)
{
    int i;

    printf(": %s ", word_name(code));

    if (*code == (cell) &do_colon) {
        for (i = 1; code[i] != 0; ++i) {
            if (*(cell *) code[i] == (cell) &LIT_) {
                printf("%d ", (int) code[++i]);
            } else {
                printf("%s ", word_name((cell *) code[i]));
            }
        }
    }
    printf(";\n");
}

static void forth_dump(const forth_t *f)
{
    printf("f: { IP: %p - %20ld, PSP: %20ld, RSP: %20ld }\n",
           (void *) f->ip, (long) (f->ip  - f->mem),
           (long) (f->psp - f->mem),
           (long) (f->rsp - f->mem));
//     word_dump(f->ip);
}

/* ARITHMETIC */

/* Single-length */

cw(0,       ADD,    "+"   );/* A B -- A+B */
cw(ADD,     SUB,    "-"   );/* A B -- A+B */
cw(SUB,     MUL,    "*"   );/* A B -- A+B */
cw(MUL,     DIV,    "/"   );/* A B -- A+B */
cw(DIV,     MOD,    "MOD" );/* A B -- A/B A%B */

cw(0,       DUP,    "DUP"   );/* A -- A A */
cw(DUP,     DROP,   "DROP"  );/* A -- */
cw(DROP,    SWAP,   "SWAP"  );/* A B -- B A */
cw(SWAP,    OVER,   "OVER"  );/* A B -- A B A */

cw(OVER,    LIT,    "LIT"   );/* -- [IP] */


cw(ADD,     EMIT,   "EMIT"   );/* A -- */
cw(EMIT,    KEY,    "KEY"    );/* -- A */

const cell LAST_C_WORD[] = { KEY, (cell) "" };

const cell * const last_c_word = KEY;

fw(0, STAR, "STAR") l_ 42 _ EMIT __;

static void emit(int c) { putchar(c); }

int main(int arc, char *argv[])
{
    sys_t   sys = { &getchar, &emit };
    cell    mem[100];
    forth_t f = { STAR + 3, mem + 100, mem + 50, mem, 100, sys };

//     word_dump(STAR + 2);
    do_colon(&f);

    return EXIT_SUCCESS;
}