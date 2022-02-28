director=$(pwd);
cd main;
flex lex.l;
bison -d yacc.y;
gcc lex.yy.c yacc.tab.c ../aux/symbol_tabler.c ../aux/stacker.c ../aux/hash_tabler.c -o ../Pretor;
cd $director;