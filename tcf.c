#include "tcf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define l_    LIT ), (cell) (
#define _     ), (cell) (2 +
#define __    ), 0 }
#define cw(p,cn,fn) const cell cn[] = { (cell) (p), (cell) fn, (cell) &cn##_ }
#define fw(p,cn,fn) const cell cn[] = { (cell) (p), (cell) fn, ((cell) &do_colon _
#define C(x) ((cell) (x))
#define CP(x) ((cell*) (x))

typedef struct sys_s {
    int     (*key)(void);
    void    (*emit)(int c);
} sys_t;

typedef struct forth_s {
    const cell   *ip;
    cell *psp, *rsp, *mem, mem_cells;
    sys_t   sys;
} forth_t;

#define PSP_BASE CP(f->mem + 100)
#define RSP_BASE CP(f->mem +  50)

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

void forth_dump(const forth_t *f);

void error(const char *s) {
    fputs(s, stderr);
    exit(1);
}


static void mem     (forth_t *f) { --PSP; TOP = (cell) f->mem; RETURN; }
static void memsiz  (forth_t *f) {
    --PSP;
    TOP = sizeof f->mem_cells * sizeof (cell);
    RETURN;
}
static void pspa    (forth_t *f) { --PSP; TOP = (cell) &PSP; RETURN; }

static void dup     (forth_t *f) { --PSP; TOP = PSP[1]; RETURN; }
static void drop    (forth_t *f) { ++PSP; RETURN; }
static void swap    (forth_t *f) { cell c = TOP; TOP = PSP[1]; PSP[1] = c; RETURN; }
static void over    (forth_t *f) { --PSP; TOP = PSP[2]; RETURN; }
static void rot     (forth_t *f) { /* ( x1 x2 x3 -- x2 x3 x1 ) */
    cell tmp = PSP[2];
    PSP[2] = PSP[1];
    PSP[1] = TOP;
    TOP = tmp;
    RETURN;
}
static void nrot    (forth_t *f) { /* ( x1 x2 x3 -- x3 x1 x2 ) */
    cell tmp = TOP;
    TOP = PSP[1];
    PSP[1] = PSP[2];
    PSP[2] = tmp;
    RETURN;
}
static void pick    (forth_t *f) { TOP = PSP[TOP]; RETURN; }
static void roll    (forth_t *f) {
    cell tmp = PSP[TOP];
    for (; TOP; --TOP) {
        PSP[TOP] = PSP[TOP-1];
    }
    TOP = tmp;
}

static void literal (forth_t *f) { IP = (cell *) RPOP; PUSH(*IP++); }

static void branch  (forth_t *f) {
    IP = (cell *) RPOP;
    IP += *IP;
}

static void zbranch (forth_t *f) {
    IP = (cell *) RPOP;
    IP += POP ? 1 : *IP;
}

static void add     (forth_t *f) { PSP[1] += TOP; ++PSP; RETURN; }
static void sub     (forth_t *f) { PSP[1] -= TOP; ++PSP; RETURN; }
static void mul     (forth_t *f) { PSP[1] *= TOP; ++PSP; RETURN; }
static void divmod  (forth_t *f) {
    cell tmp = PSP[1];
    PSP[1] = tmp % TOP;
    TOP    = tmp / TOP;
    RETURN;
}
static void muldivmod  (forth_t *f) {
    dcell num = (dcell) PSP[2] * PSP[1];
    PSP[2] = num / TOP;
    PSP[1] = num % TOP;
    ++PSP;
    RETURN;
}

static void isnot0  (forth_t *f) { TOP = TOP ? -1 : 0; RETURN; }
static void lt      (forth_t *f) {
    PSP[1] = PSP[1] < TOP ? -1 : 0;
    ++PSP;
    RETURN;
}

static void invert  (forth_t *f) { TOP = ~TOP; RETURN; }
static void and     (forth_t *f) { PSP[1] &= TOP; ++PSP; RETURN; }
static void or      (forth_t *f) { PSP[1] |= TOP; ++PSP; RETURN; }
static void xor     (forth_t *f) { PSP[1] ^= TOP; ++PSP; RETURN; }

static int a_addr(cell c) { return 0 == (c % sizeof (cell)); }

static void store   (forth_t *f) {
    if (!a_addr(TOP)) {
        error("!: missaligned store");
    }
    *(cell *) TOP = PSP[1];
    PSP += 2;
    RETURN;
}
static void fetch   (forth_t *f) {
    if (!a_addr(TOP)) {
        error("@: missaligned read");
    }
    TOP = * (cell *) TOP; RETURN;
}
static void cstore  (forth_t *f) {
    *(unsigned char *) TOP = (unsigned char) PSP[1];
    PSP += 2;
    RETURN;
}
static void cfetch  (forth_t *f) {
    TOP = (cell) *((unsigned char *) TOP);
    RETURN;
}

static void emit    (forth_t *f) { (*f->sys.emit)(POP); RETURN; }
static void key     (forth_t *f) { PUSH((*f->sys.key)()); RETURN; }

static void cells   (forth_t *f) { TOP *= sizeof (cell); RETURN; }


static const char *word_name(const cell *code) {
    return code ? (const char *) (code[-1]) : "(nil)";
}

void do_colon(forth_t *f);

void word_dump(const cell *code)
{
    int i;

    /* printf(": %s\n", (const char *) code[-1]); fflush(stdout); */
    printf(": %s ", word_name(code));

    if (*code == (cell) &do_colon) {
        for (i = 1; code[i] != 0; ++i) {
            /* printf("%d - %ld, %ld\n", i, code[i], (long unsigned) literal); */

            if (*(cell *) code[i] == (cell) &literal) {
                /* printf("LIT "); fflush(stdout); */
                printf("%d ", (int) code[++i]);
            } else {
                printf("%s ", word_name((cell *) code[i]));
            }
        }
    }
    printf(";\n");
}

const cell forth_rom[];

void forth_dump(const forth_t *f)
{
    printf("f: { IP: %s, PSP: %4ld, RSP: %4ld }\n",
           word_name(IP),
           /* (void *) f->ip, (long) (f->ip  - forth_rom), */
           (long) (f->psp - f->mem),
           (long) (f->rsp - f->mem));
    /* word_dump(f->ip); */
}

void do_colon(forth_t *f)
{
    /* printf("do_colon(%s)\n", word_name(IP - 1)); */
#if 1
    while (*IP) {
        cell * const callee = (cell *) *IP;
        forth_fn * const callee_fn = (forth_fn *) callee[0];
        cell * const callee_data = (cell *) callee + 1;
        const cell * const next_ip = IP + 1;

        /* printf("IP: %ld\n", IP - forth_rom); */
        /* printf("{ calling %s\n", word_name(callee)); */

        RPUSH(next_ip);
        IP = callee_data;
        /* printf("--> %s\n", word_name(IP)); */

        (*callee_fn)(f);

        /* printf("} next is %s\n", word_name((cell *) *IP)); */
    }
    RETURN;
#endif
}

#include "output/tcf-rom.c"

static void myemit(int c) { putchar(c); }

static void check(void) {
#if 0
    int i;

    for (i = 0; i < 6; ++i) {
        printf("%ld.%d: ",
               CP(last_forth_rom_word) + i - forth_rom,
               i);
        switch (i) {
        case 0:
            printf("%ld", CP(CP(last_forth_rom_word)[i]) - forth_rom);
            break;
        case 1:
            printf("%s", (char *) (CP(last_forth_rom_word)[i]));
            break;
        case 2:
            printf("%p", (void *) (CP(last_forth_rom_word)[i]));
            break;
        default:
            printf(" %ld", CP(last_forth_rom_word)[i]);
        }
        printf("\n");
    }
#endif
}

int main(/* int args, char *argv[] */)
{
    sys_t   sys = { &getchar, &myemit };
    cell    mem[100];
    cell    *LATEST = CP(forth_rom_latest);

    forth_t f = { LATEST + 3, CP(mem + 100), CP(mem + 50), CP(mem), 100, sys };

    check();

    /* printf("Hi Forth!\n"); */
    /* word_dump(LATEST + 2); */
    do_colon(&f);

    return EXIT_SUCCESS;
}
