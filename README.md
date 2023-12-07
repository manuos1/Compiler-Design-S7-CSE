# Compiler-Design-S7-CSE

<div align="center">
  <h2>Will be updated in time</h2>
</div>

### Compile Lex files
1. Compile lex
2. Compile c
```
lex main.l
```
Now compile the `lex.yy.c` file generated, with -lfl flag
```
gcc lex.yy.c -o main.out -lfl
```


### Compile yacc files
1. Compile lex
2. Compile yacc
3. Compile c
```
lex main.l
```
`lex.yy.c` file will be generated
Compile yacc file
```
yacc -d main.y
```
Now `y.tab.c` and `y.tab.h` files will be generated
```
gcc y.tab.c -o main.out -lfl -ly
```
  
