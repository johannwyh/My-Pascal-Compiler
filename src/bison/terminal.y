int tok;
int num;
double real;
char chr;
char str[MAX_STR_LEN];

#union

%token PAS_AND PAS_ARRAY PAS_BEGIN PAS_BREAK PAS_CASE PAS_CONST PAS_CONTINUE PAS_DEFAULT PAS_DIV PAS_DO PAS_DOWNTO
%token PAS_ELSE PAS_END PAS_EXIT  PAS_FILE PAS_FOR PAS_FORWARD PAS_FUNCTION PAS_GOTO PAS_IF PAS_IN PAS_LABEL PAS_MOD
%token PAS_NIL PAS_NOT PAS_OF PAS_OR PAS_PACKED PAS_PROCEDURE PAS_PROGRAM PAS_RECORD PAS_REPEAT PAS_SET
%token PAS_THEN PAS_TO PAS_TYPE PAS_UNTIL PAS_VAR PAS_WHILE PAS_WITH PAS_XOR

%token SYS_WRITE SYS_WRITELN SYS_READ

%token SYM_ADD SYM_SUB SYM_MUL SYM_DIV SYM_EQ SYM_LT SYM_GT SYM_LBRAC SYM_RBRAC SYM_PERIOD SYM_COMMA SYM_COLON
%token SYM_SEMICOLON SYM_CARET SYM_LPAREN SYM_RPAREN SYM_NE SYM_LE SYM_GE SYM_ASSIGN SYM_RANGE

%token TYPE_INT TYPE_REAL TYPE_CHAR TYPE_BOOL

%token BOOL_TRUE BOOL_FALSE

%token ID INT REAL CHAR STR

%type <tok> PAS_AND PAS_ARRAY PAS_BEGIN PAS_BREAK PAS_CASE PAS_CONST PAS_CONTINUE PAS_DEFAULT PAS_DIV PAS_DO PAS_DOWNTO
%type <tok> PAS_ELSE PAS_END PAS_EXIT PAS_FILE PAS_FOR PAS_FORWARD PAS_FUNCTION PAS_GOTO PAS_IF PAS_IN PAS_LABEL PAS_MOD
%type <tok> PAS_NIL PAS_NOT PAS_OF PAS_OR PAS_PACKED PAS_PROCEDURE PAS_PROGRAM PAS_RECORD PAS_REPEAT PAS_SET
%type <tok> PAS_THEN PAS_TO PAS_TYPE PAS_UNTIL PAS_VAR PAS_WHILE PAS_WITH PAS_XOR

%type <tok> SYS_WRITE SYS_WRITELN SYS_READ

%type <tok> SYM_ADD SYM_SUB SYM_MUL SYM_DIV SYM_EQ SYM_LT SYM_GT SYM_LBRAC SYM_RBRAC SYM_PERIOD SYM_COMMA SYM_COLON
%type <tok> SYM_SEMICOLON SYM_CARET SYM_LPAREN SYM_RPAREN SYM_NE SYM_LE SYM_GE SYM_ASSIGN SYM_RANGE

%type <tok> TYPE_INT TYPE_REAL TYPE_CHAR TYPE_BOOL
%type <tok> BOOL_TRUE BOOL_FALSE

%type <str> ID STR
%type <num> INT
%type <real> REAL
%type <chr> CHAR
