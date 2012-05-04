LEX=flex
YACC=yacc
CC=g++

sql_parser: sql_y.o sql_l.o sql.o
	$(CC) sql_y.o sql_l.o sql.o  -o $@ -lfl

sql_y.o: y.tab.c 
	$(CC) -c $< -o $@

sql_l.o: lex.yy.c
	$(CC) -c $< -o $@

sql.o: sql.c
	$(CC) -c $< -o $@

y.tab.c: sql.y
	$(YACC) -vdt sql.y

lex.yy.c: sql.l
	$(LEX) sql.l

clean:
	rm lex.yy.c y.tab.c y.tab.h y.output *.o sql_parser
