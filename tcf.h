#ifndef TCF_F_H__
#define TCF_F_H__

#include <stdint.h>

typedef intptr_t cell;
typedef long long int dcell;    /* Double precission cell */

struct forth_s;
typedef void (forth_fn)(struct forth_s *);

#endif                         /* TCF_F_H__ */
