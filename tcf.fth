c: _MEM     mem ;       ( -- a-addr ) \ Return address of RAM start
c: _#MEM    memsiz ;    ( -- u )      \ Return size of RAM memory

c: DOCOL    do_colon ;

\ Return the address of the top of the stack before SP@ is executed.
c: PSP      pspa ;      ( -- a-addr )

c: DUP      dup ;       ( x -- x x )
c: DROP     drop ;      ( x -- )
c: SWAP     swap ;      ( x1 x2 -- x2 x1 )
c: OVER     over ;      ( x1 x2 -- x1 x2 x1 )
c: ROT      rot ;       ( x1 x2 x3 -- x2 x3 x1 )
c: -ROT     nrot ;      ( x1 x2 x3 -- x3 x1 x2 )
c: PICK     pick ;      ( xu ... x1 x0 u -- xu ... x1 x0 xu )
c: ROLL     roll ;      ( xu xu-1 ... x0 u -- xu-1 ... x0 xu )

c: +        add ;       ( n1|u1 n2|u2 -- n3|u3 )
c: -        sub ;       ( n1|u1 n2|u2 -- n3|u3 )
c: *        mul ;       ( n1|u1 n2|u2 -- n3|u3 )
c: /MOD     divmod ;    ( n1 n2 -- n1%n2 n1/n2 )

\ Multiply n1 and n2, divide the product by n3. Return both the
\ remainder and quotient
c: */MOD    muldivmod ; ( n1 n2 n3 -- n4 )

c: 0<>      isnot0 ;    ( x1 -- flag )
c: <        lt ;        ( n1 n2 -- flag )
c: INVERT   invert ;    ( n1 -- ~n1 )   \ Bitwise negate
c: AND      and ;       ( x1 x2 -- x3 ) \ Bitwise AND
c: OR       or ;        ( x1 x2 -- x3 ) \ Bitwise OR
c: XOR      xor ;       ( x1 x2 -- x3 ) \ Bitwise XOR

c: !        store ;     ( x a-address -- )
c: @        fetch ;     ( a-adress -- x )

c: C!       cstore ;    ( x a-address -- )
c: C@       cfetch ;    ( a-adress -- x )

c: EMIT     emit ;      ( x -- )
c: KEY      key ;       ( -- char )

c: CELLS    cells ;     ( n1 -- n2 )

c: LITERAL  literal ;
c: BRANCH   branch ;
c: 0BRANCH  zbranch ;

\ *****************************************************************************


\ *****************************************************************************
\   SYSTEM & USER VARIABLES
\ *****************************************************************************

: CP    _MEM 0 + ;
: SP0   _MEM 1 + ;

: HERE CP @ ;           ( -- addr )
\ : PAD HERE 20 CELLS + ;
: TIB ;
: LATEST ;


\ *****************************************************************************
\   STACK MANIPULATION
\ *****************************************************************************

: SP@   PSP  @ ;        ( -- a-addr )
: SP!   PSP  ! ;        ( a-addr -- )

\ Duplicate top of stack if non zero
: ?DUP  DUP IF DUP THEN ; ( x -- x (x) )
: R> ;
: R@ ;
: DEPTH SP@ SP0 - ;

: 2DROP DROP DROP ;     ( x1 x2 -- )
: 2DUP  OVER OVER ;     ( x1 x2 -- x1 x2 x1 x2 )
: 2SWAP 4 ROLL 4 ROLL ; ( x1 x2 x3 x4 -- x3 x4 x1 x2 )

\ *****************************************************************************
\   COMPARISON
\ *****************************************************************************

: 0=    0<> INVERT ;    ( x1 -- flag )   \ Corresponds to logical negation
: =     - 0= ;          ( x1 x2 -- flag )
: <>    - 0<> ;         ( x1 x2 -- flag )
: >     SWAP < ;        ( x1 x2 -- flag )
: <=    > 0= ;          ( x1 x2 -- flag )
: >=    < 0= ;          ( x1 x2 -- flag )
: 0<    0 < ;           ( x1 -- flag )
: 0>    0 > ;           ( x1 -- flag )
: 0<=   0 <= ;          ( x1 -- flag )
: 0>=   0 >= ;          ( x1 -- flag )
: U< ;
\ : NOT 0= ;              ( flag -- ¬flag )

\ *****************************************************************************
\   ARITHMETICAL AND LOGICAL
\ *****************************************************************************

: MOD /MOD DROP ;       ( n1 n2 -- n1%n2 )
: /   /MOD SWAP DROP ;  ( n1 n2 -- n1/n2 )

\ Multiply n1 and n2, divide the product by n3
: */ */MOD DROP ;       ( n1 n2 n3 -- n4 )

: 1+    1 + ;
: 1-    1 - ;
\: 4+    4 + ;
\: 4-    4 - ;

: 2* DUP + ;

: NEGATE -1 * ;

: MAX 2DUP > IF SWAP THEN DROP ;
: MIN 2DUP < IF SWAP THEN DROP ;
: ABS DUP 0< IF NEGATE THEN ;

\ *****************************************************************************
\   MEMORY
\ *****************************************************************************

\ add operand to cell at address
: +! SWAP OVER @ + SWAP ! ; ( n|u a-address -- )
\ subtract operand to cell at address
: -! SWAP OVER @ - SWAP ! ; ( n|u a-address -- )

\ *****************************************************************************
\   CONTROL STRUCTURES
\ *****************************************************************************


\ *****************************************************************************
\   TERMINAL INPUT-OUTPUT
\ *****************************************************************************

: BL   32 ;
: CR   10 EMIT ;
: SPACE BL EMIT ;
\ : SPACES  ;
\ : TYPE ;
\ : COUNT ;
\ : -TRAILING ;
\ : EXPECT ;
\ : QUERY ;

\ *****************************************************************************
\   NUMERIC CONVERSION
\ *****************************************************************************

\ : BASE ;
\ : DECIMAL 10 BASE ! ;
\ : . ;
\ : U. ;
\ : CONVERT ;
\ : <# ;
\ : #
\ : #S
\ : HOLD ;
\ : SIGN ;
\ : #> ;

\ *****************************************************************************
\   MASS STORAGE INPUT-OUTPUT
\ *****************************************************************************


\ *****************************************************************************
\   COMPILER
\ *****************************************************************************

: ALLOT CP +! ;         ( n -- )
: ,     HERE 1 CELLS ALLOT ! ; ( x -- )
: IMMEDIATE ;
: STATE ;
: [  0 STATE ! ;
: ] -1 STATE ! ;
\ : COMPILE
\ : [COMPILE]

\ *****************************************************************************
\   DEFINING WORDS
\ *****************************************************************************

: ' ;
: HIDDEN ;
: WORD ;
: CREATE ;
: : WORD CREATE ' DOCOL , LATEST @ HIDDEN [ ;
: ; 0 , LATEST @ HIDDEN ] ;
: VARIABLE ;
; CONSTANT ;

\ *****************************************************************************
\   MISCELLANEOUS
\ *****************************************************************************

\ : (
\ : >IN
\ : BLK
\ : ABORT

: IF IMMEDIATE ;
: ELSE IMMEDIATE ;
: THEN IMMEDIATE ;

: STAR 42 EMIT ;
: STARS STAR STAR STAR STAR STAR STAR STAR STAR CR ;

: INTERPRET
    STAR
    \ WORD
    \ ' IF
    \ ELSE
    \  \   _NUMBER IF
    \     ELSE
    \     THEN
    \ THEN
;

\ This MUST be the last word as this is the word that will be executed
\ when Forth starts.
: QUIT ( R0 RSP! ) BEGIN INTERPRET 0 UNTIL ;
