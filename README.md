# Compiler-Design-S7-CSE

Will be updated in time

## Compile Lex files
1. Compile lex
2. Compile c
  lex sample.l 
Now `lex.yy.c` file will be generated
  gcc lex.yy.c -o sample.out -lfl


## Compile yacc files
1. Compile lex
2. Compile yacc
3. Compile c
  lex sample.l
Now `lex.yy.c` file will be generated
  yacc -d sample.y
Now `y.tab.c` and `y.tab.h` files will be generated
  gcc y.tab.c -o sample.out -lfl -ly
  
