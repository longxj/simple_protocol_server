%{
	#include <stdlib.h>
	#include "sql.h"

	extern "C" {
		
	void yyerror(const char *s);
	extern int yylex(void);
		
	}
%}	


%union {
	SqlNodeType* pNode;
}

%token STMT
%token OP ST NSPLIT ST_LIST
%token FM NAME FM_LIST NAME_LIST
%token WH WHSPLIT WH_LIST WHNAME_LIST WHNAME
%token OPERATOR LBORDER RBORDER
%token TERMINATOR
%token NUMBER

%type<pNode> STMT
%type<pNode> OP ST NSPLIT ST_LIST
%type<pNode> FM NAME FM_LIST NAME_LIST
%type<pNode> WH WHSPLIT WH_LIST WHNAME_LIST WHNAME
%type<pNode> OPERATOR LBORDER RBORDER
%type<pNode> TERMINATOR
%type<pNode> NUMBER

%type<pNode> program stmt st_list fm_list wh_list name_list whname_list whname whvalue

%%

program:
stmt TERMINATOR {ProcessTree($1);}
;    

stmt:
st_list fm_list                                {$$ = NewFatherAddSon(STMT, $1, $2);}
|st_list fm_list wh_list           {$$ = NewFatherAddSon(STMT, $1, $2, $3);}
;

st_list:
ST name_list                    {$$ = NewFatherAddSon(ST_LIST, $1, $2);}
;

fm_list:
FM NAME                         {$$ = NewFatherAddSon(FM_LIST, $1, $2);}
;

wh_list:
WH whname_list                  {$$ = NewFatherAddSon(WH_LIST, $1, $2);}
;

name_list:
NAME                           {$$ = NewFatherAddSon(NAME_LIST, $1);}
|name_list NAME          {$$ = FatherAddSon($1, $2);}
;

whname_list:
whname                          {$$ = NewFatherAddSon(WHNAME_LIST, $1);}
|whname_list WHSPLIT whname     {FatherAddSon($1, $2); $$ = FatherAddSon($1, $3);}
;

whname:
NAME OPERATOR whvalue          {$$ = NewFatherAddSon(WHNAME, $1, $2, $3);}

whvalue:
NAME                             {$$ = $1;}
|NUMBER                          {$$ = $1;}
;

%%

void yyerror(const char *s)
{
	printf("Error: %s\n", s);
}
