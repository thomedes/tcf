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

static void dup     (forth_t *f) { --PSP; TOP = PSP[1]; RETURN }
static void drop    (forth_t *f) { ++PSP; RETURN }
static void swap    (forth_t *f) { cell c = TOP; TOP = PSP[1]; PSP[1] = c; RETURN }
static void over    (forth_t *f) { --PSP; TOP = PSP[2]; RETURN }

static void literal (forth_t *f) { IP = (cell *) RPOP; PUSH(*IP++); }

static void add     (forth_t *f) { PSP[1] += TOP; ++PSP; RETURN }
static void sub     (forth_t *f) { PSP[1] -= TOP; ++PSP; RETURN }
static void mul     (forth_t *f) { PSP[1] *= TOP; ++PSP; RETURN }
static void div_    (forth_t *f) { PSP[1] /= TOP; ++PSP; RETURN }
static void mod     (forth_t *f) { PSP[1] %= TOP; ++PSP; RETURN }

static void emit    (forth_t *f) { (*f->sys.emit)(POP); RETURN }
static void key     (forth_t *f) { PUSH((*f->sys.key)()); RETURN }

static void eq      (forth_t *f) { PSP[1] = PSP[1] == TOP ? -1 : 0; RETURN }

static void cells   (forth_t *f) { TOP *= sizeof (cell); RETURN }


static const char *word_name(const cell *code) {
    return (const char *) (code[-1]);
}

void do_colon(forth_t *f)
{
    /* printf("do_colon(%p)\n", f); */
    /* fflush(stdout); */
#if 1
    /* printf("do_colon %s\n", word_name(IP - 1)); */
    while (*IP) {
        RPUSH(IP + 1);
        IP = (cell *) *IP;
        /* printf("--> %s\n", word_name(IP)); */

        (**(forth_fn *) *IP++)(f);
    }
#endif
}

#include "output/tcf-rom.c"


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

void forth_dump(const forth_t *f)
{
    printf("f: { IP: %p - %20ld, PSP: %20ld, RSP: %20ld }\n",
           (void *) f->ip, (long) (f->ip  - f->mem),
           (long) (f->psp - f->mem),
           (long) (f->rsp - f->mem));
    /* word_dump(f->ip); */
}

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
    cell    *STAR = CP(last_forth_rom_word);

    forth_t f = { STAR + 3, CP(mem + 100), CP(mem + 50), CP(mem), 100, sys };

    check();

    /* printf("Hi Forth!\n"); */
    word_dump(STAR + 2);
    do_colon(&f);

    return EXIT_SUCCESS;
}
