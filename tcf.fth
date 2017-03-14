c: DUP      dup ;       ( x -- x x )
c: DROP     drop ;      ( x -- )
c: SWAP     swap ;      ( x1 x2 -- x2 x1 )
c: OVER     over ;      ( x1 x2 -- x1 x2 x1 )

c: LITERAL  literal ;

c: +        add ;       ( n1|u1 n2|u2 -- n3|u3 )
c: -        sub ;       ( n1|u1 n2|u2 -- n3|u3 )
c: *        mul ;       ( n1|u1 n2|u2 -- n3|u3 )
c: /        div_ ;      ( n1 n2 -- n3 )
c: MOD      mod ;       ( n1 n2 -- n3 )

c: EMIT     emit ;      ( x -- )
c: KEY      key ;       ( -- char )

c: =        eq ;        ( x1 x2 -- flag )

c: CELLS    cells ;     ( n1 -- n2 )

: 2* 3 DUP + ;

: CR 10 EMIT ;
: STAR 42 EMIT ;

: STARS STAR STAR STAR CR ;