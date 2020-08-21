#include "Scanner.h"
#include <stdbool.h>

/*
* Structure declarations here, definitions below
*/
#define SIZE 12
typedef struct program_node program_node;
typedef struct decl_seq_node decl_seq_node;
typedef struct stmt_seq_node stmt_seq_node;
typedef struct decl_node decl_node;
typedef struct id_list_node id_list_node;
typedef struct stmt_node stmt_node;
typedef struct assign_node assign_node;
typedef struct in_node in_node;
typedef struct out_node out_node;
typedef struct if_node if_node;
typedef struct loop_node loop_node;
typedef struct cond_node cond_node;
typedef struct cmpr_node cmpr_node;
typedef struct expr_node expr_node;
typedef struct term_node term_node;
typedef struct factor_node factor_node;
typedef struct const_node const_node;
typedef struct id_node id_node;
typedef struct decl_func_node decl_func_node;
typedef struct func_node func_node;
typedef struct stackFrame stackFrame;
typedef struct table table;
/*
* struct definitions below
* Each struct represents a type of node in the parse tree
* Each nonterminals of the grammar should have a type of node
*/

// program_node represents the root of the parse tree
struct program_node {
	decl_seq_node *dsn; // Link to the decl_seq child or root
	stmt_seq_node *ssn; // Link to the stmt_seq child of root
};

// decl_seq_node represents decl_seq nodes in the parse tree
struct decl_seq_node{
	decl_node *decl;
	decl_seq_node *decl_seq;
	int option;
};

// stmt_seq_node represents stmt_seq nodes in the parse tree
struct stmt_seq_node{
	stmt_node *stmt;
	stmt_seq_node *stmt_seq;
	int option;
};

struct decl_node{
	id_list_node *id_list;
    decl_func_node *decl_func;
	int option;
};

struct id_list_node{
	id_node *id;
	id_list_node *id_list;
	int option;
};

struct stmt_node{
	assign_node *assign;
	if_node *ifthen;
	loop_node *loop;
	in_node *in;
	out_node *out;
	func_node *funcNode;
	int option;
};

struct assign_node{
	id_node *id;
	expr_node *expr;
};

struct in_node{
	id_node *id;
};

struct out_node{
	expr_node *expr;
};

struct if_node{
	cond_node *cond;
	stmt_seq_node *stmt_seq1;
	stmt_seq_node *stmt_seq2;
	int option;
};

struct loop_node{
	cond_node *cond;
	stmt_seq_node *stmt_seq;
};

struct cond_node{
	cmpr_node *cmpr;
	cond_node *cond;
	int option;
};

struct cmpr_node{
	expr_node *expr1;
	expr_node *expr2;
	int option;
};

struct expr_node{
	term_node *term;
	expr_node *expr;
	int option;
};

struct term_node{
	factor_node *factor;
	term_node *term;
	int option;
};

struct factor_node{
	const_node *constant;
	id_node *id;
	expr_node *expr;
	int option;
};

struct const_node{
	int value;
};

struct id_node{
	char *value;
};

struct decl_func_node{
    id_node *id;
    id_list_node *id_list;
    stmt_seq_node *stmt_seq;
    int lookUp;
};

struct func_node{
    id_node *id;
    id_list_node *id_list;
};

struct stackFrame{
    int FP;
    int SP;
};

struct table{
    id_node *id;
    id_list_node *pra;
    stmt_seq_node *stmtSeqNode;
    char identifiers[SIZE][20];
    int count;
};

/*
* Function declarations here, definitions below
*/

void parser_program(program_node *prog, char* codeFileName);
void printer_program(program_node *prog);
void executor_program(program_node *prog, char* dataFileName);
void delete_program(program_node *prog);

void parser_decl_seq(decl_seq_node *dsn);
void printer_decl_seq(decl_seq_node *dsn, int tabbing);
void executor_decl_seq(decl_seq_node *dsn);

void parser_decl_func(decl_func_node *dfn);
void printer_decl_func(decl_func_node *dfn);
void executor_decl_func(decl_func_node *dfn);

void parser_func(func_node *fn);
void printer_func(func_node *fn, int tabbing);
void executor_func(func_node *fn);

void parser_decl(decl_node *dn);
void printer_decl(decl_node *dn, int tabbing);
void executor_decl(decl_node *dn);

void parser_id_list(id_list_node *idl);
void parser_func_id_list(id_list_node *idl, int lookup);
void printer_id_list(id_list_node *idl);
void executor_id_list(id_list_node *idl);

void parser_id_add(id_node *id);
int parser_func_id_add(id_node *id);
void parser_id(id_node *id);
void parser_pram_id(id_node *id,int lookup);
void parser_func_id(id_node *id);
void printer_id(id_node *id);
int executor_id_store(id_node *id);
int executor_id(id_node *id);

void parser_stmt_seq(stmt_seq_node *ssn);
void printer_stmt_seq(stmt_seq_node *ssn, int tabbing);
void executor_stmt_seq(stmt_seq_node *ssn);
void executor_stmt_seq(stmt_seq_node *ssn);

void parser_stmt(stmt_node *sn);
void printer_stmt(stmt_node *sn, int tabbing);
void executor_stmt(stmt_node *sn);

void parser_assign(assign_node *assign);
void printer_assign(assign_node *assign, int tabbing);
void executor_assign(assign_node *assign);

void parser_if(if_node *ifthen);
void printer_if(if_node *ifthen, int tabbing);
void executor_if(if_node *ifthen);

void parser_loop(loop_node *loop);
void printer_loop(loop_node *loop, int tabbing);
void executor_loop(loop_node *loop);

void parser_in(in_node *input);
void printer_in(in_node *input, int tabbing);
void executor_in(in_node *input);

void parser_out(out_node *output);
void printer_out(out_node *output, int tabbing);
void executor_out(out_node *output);

void parser_cond(cond_node *cond);
void printer_cond(cond_node *cond);
bool executor_cond(cond_node *cond);

void parser_cmpr(cmpr_node *cmpr);
void printer_cmpr(cmpr_node *cmpr);
bool executor_cmpr(cmpr_node *cmpr);

void parser_expr(expr_node *expr);
void printer_expr(expr_node *expr);
int executor_expr(expr_node *expr);

void parser_term(term_node *term);
void printer_term(term_node *term);
int executor_term(term_node *term);

void parser_factor(factor_node *factor);
void printer_factor(factor_node *factor);
int executor_factor(factor_node *factor);

void parser_const(const_node *constant);
void printer_const(const_node *constant);
int executor_const(const_node *constant);


/*
* Helper function and global variable to handle .data file
*/
FILE* input_file;
int get_input() {
	int read = 0;
	if (!feof (input_file))
	{
		fscanf(input_file, "%d", &read);
	}
	return read;
}



/*
* Symbol table things here
* Variables are added to the "identifiers" array
* The values are put at the same index in the "stored" array
* The "initialized" array keeps track of which variables have been initialized
*/
int id_count;
int FP;
int SP;
int func;//1 for func mode
int stored[1000];
int initialized[1000];
char identifiers[1000][20];
struct stackFrame stack[SIZE];
int stackState[SIZE];//0 for unused frame
struct table lookupTable[SIZE];//function lookup table
int luTable[SIZE];

void add_func_identifier(char *id, int lookup){
    int i = 0;
    while (i < lookupTable[lookup].count) {
        if (strcmp(id, lookupTable[lookup].identifiers[i]) == 0) {
            printf("ERROR: Duplicate ID detected in func decl\n");
            exit(0);
        }
        i++;
    }
    strcpy(lookupTable[lookup].identifiers[i], id);
    lookupTable[lookup].count++;
}

int lookup_func_identifier(char *id, int lookup){
    int i=0;
    while (i < lookupTable[lookup].count){
        if (strcmp(id, lookupTable[lookup].identifiers[i]) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

void add_identifier(char *id) {
	int i = FP;
	while (i < SP) {
		if (strcmp(id, identifiers[i]) == 0) {
			printf("ERROR: Duplicate ID detected\n");
			exit(0);
		}
		i++;
	}
	strcpy(identifiers[i], id);
	id_count++;
	SP++;
}

int lookup_identifier(char *id) {
	int i = FP;
	while (i < SP) {
		if (strcmp(id, identifiers[i]) == 0) {
			return i;
		}
		i++;
	}
	return -1;
}

int lookup_func(char *id) {
    int i = 0;
    while (i < SIZE) {
        if (strcmp(id, lookupTable[i].id->value) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

/*
* Function definitions below
* Each struct should have 4 functions associated with it:
* parser_* - this handles the recursive descent parsing, and builds the parse tree
* printer_* - this nicely prints the program from the parse tree, to verify the tree
* executor_* - this walks over the tree and executes the statements of the program
* delete_* - this recursively dismantles the tree, releasing allocated memory
*/

void parser_program(program_node *prog, char* codeFileName) {
	// Initialize the scanner
	Scanner(codeFileName);
    FP=0;
    SP=0;
    func=0;
	// This will keep track of how large the symbol table is
	id_count = 0;
    for (int i = 0; i < SIZE; ++i) {
        stackState[i]=0;
    }
    for (int i = 0; i < SIZE; ++i) {
        luTable[i]=0;
    }
	nextToken();
	if (currentToken() != PROGRAM) {
		printf("ERROR: Expected PROGRAM token\n");
		exit(0);
	}
	nextToken(); // Consume the PROGRAM token

	// Scanner should be at the begining of the declaration sequence
	(*prog).dsn = (decl_seq_node*)malloc(sizeof(decl_seq_node));
	parser_decl_seq((*prog).dsn);

	// After parsing the declaration sequence, should have BEGIN token
	if (currentToken() != BEGIN) {
		printf("ERROR: Expected BEGIN token\n");
		exit(0);
	}
	nextToken(); // Consume the BEGIN token

	// Scanner should be at the start of the statement sequence
	(*prog).ssn = (stmt_seq_node*)malloc(sizeof(stmt_seq_node));
	parser_stmt_seq((*prog).ssn);

	// After parsing the declaration sequence, should have END token, then EOS
	if (currentToken() != END) {
		printf("ERROR: Expected BEGIN token\n");
		exit(0);
	}
	nextToken(); // Consume the END token
	if (currentToken() != EOS) {
		printf("ERROR: Unexpected token after END\n");
		exit(0);
	}
}

void printer_program(program_node *prog) {
	printf("program\n");
	printer_decl_seq((*prog).dsn, 1);
	printf("begin\n");
	printer_stmt_seq((*prog).ssn, 1);
	printf("end\n");
}

void executor_program(program_node *prog, char* dataFileName) {
	input_file = fopen(dataFileName, "r");
	executor_decl_seq((*prog).dsn);
	executor_stmt_seq((*prog).ssn);
	fclose (input_file);
}

void delete_program(program_node *prog) {
	free((*prog).dsn);
	free((*prog).ssn);
}


void parser_decl_seq(decl_seq_node *dsn) {
	(*dsn).option = 0;
	(*dsn).decl = (decl_node*)malloc(sizeof(decl_node));
	parser_decl((*dsn).decl);
	if (currentToken() != BEGIN) {
		(*dsn).option = 1;
		(*dsn).decl_seq = (decl_seq_node*)malloc(sizeof(decl_seq_node));
		parser_decl_seq((*dsn).decl_seq);
	}
}

void printer_decl_seq(decl_seq_node *dsn, int tabbing) {
	printer_decl((*dsn).decl, tabbing);
	if ((*dsn).option == 1) {
		printer_decl_seq((*dsn).decl_seq, tabbing);
	}
}

void executor_decl_seq(decl_seq_node *dsn) {
	executor_decl((*dsn).decl);
	if ((*dsn).option == 1) {
		executor_decl_seq((*dsn).decl_seq);
	}
}

void parser_decl(decl_node *dn) {
    int t=currentToken();
	if (currentToken() != INT && currentToken() != ID) {
		printf("ERROR: Expected INT or ID token\n");
		exit(0);
	}
	if (currentToken()==INT) {
        (*dn).option=1;
        nextToken();
        (*dn).id_list = (id_list_node *) malloc(sizeof(id_list_node));
        parser_id_list((*dn).id_list);
        if (currentToken() != SEMICOLON) {
            printf("ERROR: Expected SEMICOLON token after decl\n");
            exit(0);
        }
        nextToken();
    }else{
        (*dn).option=2;
        (*dn).decl_func = (decl_func_node *)malloc(sizeof(decl_func_node));
	    parser_decl_func((*dn).decl_func);
	}
}

void printer_decl(decl_node *dn, int tabbing) {
    for (int i=0; i<tabbing; i++) {
        printf("\t");
    }
    if ((*dn).option==1){
        printf("int ");
        printer_id_list((*dn).id_list);
        printf(";\n");
    } else{
        printer_decl_func((*dn).decl_func);
    }
}

void executor_decl(decl_node *dn) {
	executor_id_list((*dn).id_list);
}

void parser_id_list(id_list_node *idl) {
    int t=currentToken();
	(*idl).option = 0;
	if (currentToken() != ID) {
		printf("ERROR: Expected ID token in id_list\n");
		exit(0);
	}
	(*idl).id = (id_node*)malloc(sizeof(id_node));
	parser_id_add((*idl).id);
	if (currentToken() == COMMA) {
		(*idl).option = 1;
		nextToken();
		(*idl).id_list = (id_list_node*)malloc(sizeof(id_list_node));
		parser_id_list((*idl).id_list);
	}
}

void parser_func_id_list(id_list_node *idl, int lookup) {
    int t=currentToken();
    (*idl).option = 0;
    if (currentToken() != ID) {
        printf("ERROR: Expected ID token in id_list\n");
        exit(0);
    }
    (*idl).id = (id_node*)malloc(sizeof(id_node));
    parser_pram_id((*idl).id,lookup);
    if (currentToken() == COMMA) {
        (*idl).option = 1;
        nextToken();
        (*idl).id_list = (id_list_node*)malloc(sizeof(id_list_node));
        parser_func_id_list((*idl).id_list,lookup);
    }
}

void printer_id_list(id_list_node *idl) {
	printer_id((*idl).id);
	if ((*idl).option == 1) {
		printf(",");
		printer_id_list((*idl).id_list);
	}
}

void executor_id_list(id_list_node *idl) {
	// Set init to 0 to indicate the variable is uninitialized
	initialized[lookup_identifier((*(*idl).id).value)] = 0;
	if ((*idl).option == 1) {
		executor_id_list((*idl).id_list);
	}
}

// Parser for ID when appearing in decl_seq, add the ID to the Identifiers array
void parser_id_add(id_node *id) {
    int t=currentToken();
	(*id).value = (char*)malloc(20);
	getID((*id).value);
	nextToken();
	add_identifier((*id).value);
}

int parser_func_id_add(id_node *id){
    int t=currentToken();
    (*id).value = (char*)malloc(20);
    getID((*id).value);
    int i=0;
    for(i=0;i<SIZE;i++){
        if (luTable[i]==0){
            luTable[i]=1;
            break;
        }
        if (strcmp(lookupTable[i].id->value,id->value)==0){
            printf("ERROR: Function name has already been used\n");
            exit(0);
        }
    }
    lookupTable[i].id=id;
    nextToken();
    return i;
}

// Parser for ID when appearing in the stmt_seq, verifies the ID is declared
void parser_id(id_node *id) {
    int t=currentToken();
        (*id).value = (char*)malloc(20);
        getID((*id).value);
        nextToken();
    if (func==0){
        if (lookup_identifier((*id).value) == -1) {
            printf("ERROR: An ID in the stmt_seq was not declared\n");
            exit(0);
        }
    }else{
        int j=SIZE-1;
        while (luTable[j]==0){
            j--;
        }//find current func
        //printf("%s",lookupTable[j].identifiers[0]); Debug
        if (lookup_func_identifier((*id).value,j) == -1) {
            printf("ERROR: An ID in the func stmt_seq was not declared\n");
            exit(0);
        }
    }
}

void parser_pram_id(id_node *id, int lookup){
    int t=currentToken();
    (*id).value = (char*)malloc(20);
    getID((*id).value);
    nextToken();
    add_func_identifier((*id).value,lookup);
}

void parser_func_id(id_node *id){
    int t=currentToken();
    (*id).value = (char*)malloc(20);
    getID((*id).value);
    nextToken();
    int i=0;
    for (i = 0; i < SIZE; ++i) {
        if (strcmp((*id).value,lookupTable[i].id->value)==0){
            break;
        }
    }
    if (i==SIZE){
        printf("ERROR: An ID in the func was not declared\n");
        exit(0);
    }
}

void printer_id(id_node *id) {
	printf("%s", (*id).value);
}

// Executor when storing to a variable
int executor_id_store(id_node *id) {
	int index = lookup_identifier((*id).value);
	initialized[index] = 1;
	return index;
}

// Executor when retrieving from a variable
int executor_id(id_node *id) {
	int index = lookup_identifier((*id).value);
	if (initialized[index] == 0) {
		printf("ERROR: Trying to use an uninitialized variable\n");
		exit(0);
	}
	return index;
}


void parser_stmt_seq(stmt_seq_node *ssn) {
    int t=currentToken();
	(*ssn).option = 0;
	(*ssn).stmt = (stmt_node*)malloc(sizeof(stmt_node));
	parser_stmt((*ssn).stmt);
	if (currentToken() != END && currentToken() != ENDWHILE && currentToken() != ELSE && currentToken() != ENDIF && currentToken() !=ENDFUNC) {
		(*ssn).option = 1;
		(*ssn).stmt_seq = (stmt_seq_node*)malloc(sizeof(stmt_seq_node));
		parser_stmt_seq((*ssn).stmt_seq);
	}
}

void printer_stmt_seq(stmt_seq_node *ssn, int tabbing) {
	printer_stmt((*ssn).stmt, tabbing);
	if ((*ssn).option == 1) {
		printer_stmt_seq((*ssn).stmt_seq, tabbing);
	}
}

void executor_stmt_seq(stmt_seq_node *ssn) {
	executor_stmt((*ssn).stmt);
	if ((*ssn).option == 1) {
		executor_stmt_seq((*ssn).stmt_seq);
	}
}

void parser_stmt(stmt_node *sn) {
    int t=currentToken();
	if (currentToken() == ID) {
		(*sn).option = 1;
		(*sn).assign = (assign_node*)malloc(sizeof(assign_node));
		parser_assign((*sn).assign);
	} else if (currentToken() == IF) {
		(*sn).option = 2;
		(*sn).ifthen = (if_node*)malloc(sizeof(if_node));
		parser_if((*sn).ifthen);
	} else if (currentToken() == WHILE) {
		(*sn).option = 3;
		(*sn).loop = (loop_node*)malloc(sizeof(loop_node));
		parser_loop((*sn).loop);
	} else if (currentToken() == INPUT) {
		(*sn).option = 4;
		(*sn).in = (in_node*)malloc(sizeof(in_node));
		parser_in((*sn).in);
	} else if (currentToken() == OUTPUT) {
		(*sn).option = 5;
		(*sn).out = (out_node*)malloc(sizeof(out_node));
		parser_out((*sn).out);
	} else if (currentToken() == BEGIN){
        (*sn).option = 6;
        (*sn).funcNode = (func_node*)malloc(sizeof(func_node));
        parser_func((*sn).funcNode);
    } else {
		printf("ERROR: Expected a statement\n");
		exit(0);
	}
}

void printer_stmt(stmt_node *sn, int tabbing) {
	if ((*sn).option == 1) {
		printer_assign((*sn).assign, tabbing);
	} else if ((*sn).option == 2) {
		printer_if((*sn).ifthen, tabbing);
	} else if ((*sn).option == 3) {
		printer_loop((*sn).loop, tabbing);
	} else if ((*sn).option == 4) {
		printer_in((*sn).in, tabbing);
	} else if ((*sn).option == 5) {
		printer_out((*sn).out, tabbing);
	} else if ((*sn).option == 6) {
	    printer_func((*sn).funcNode, tabbing);
	}
}

void executor_stmt(stmt_node *sn) {
	if ((*sn).option == 1) {
		executor_assign((*sn).assign);
	} else if ((*sn).option == 2) {
		executor_if((*sn).ifthen);
	} else if ((*sn).option == 3) {
		executor_loop((*sn).loop);
	} else if ((*sn).option == 4) {
		executor_in((*sn).in);
	} else if ((*sn).option == 5) {
		executor_out((*sn).out);
	} else if ((*sn).option == 6) {
        executor_func((*sn).funcNode);
    }
}

void parser_assign(assign_node *assign) {
    int t=currentToken();
	(*assign).id = (id_node*)malloc(sizeof(id_node));
	parser_id((*assign).id);
	if (currentToken() != ASSIGN) {
		printf("ERROR: Expected ASSIGN token\n");
		exit(0);
	}
	nextToken();
	(*assign).expr = (expr_node*)malloc(sizeof(expr_node));
	parser_expr((*assign).expr);
	if (currentToken() != SEMICOLON) {
		printf("ERROR: Expected SEMICOLON token after assign\n");
		exit(0);
	}
	nextToken();
}

void printer_assign(assign_node *assign, int tabbing) {
	for (int i=0; i<tabbing; i++) {
		printf("\t");
	}
	printer_id((*assign).id);
	printf("=");
	printer_expr((*assign).expr);
	printf(";\n");
}

void executor_assign(assign_node *assign) {
	int result = executor_expr((*assign).expr);
	int index = executor_id_store((*assign).id);
	stored[index] = result;
}

void parser_if(if_node *ifthen) {
    int t=currentToken();
	(*ifthen).option = 0;
	nextToken();
	(*ifthen).cond = (cond_node*)malloc(sizeof(cond_node));
	parser_cond((*ifthen).cond);
	if (currentToken() != THEN) {
		printf("ERROR: Expected THEN token\n");
		exit(0);
	}
	nextToken();
	(*ifthen).stmt_seq1 = (stmt_seq_node*)malloc(sizeof(stmt_seq_node));
	parser_stmt_seq((*ifthen).stmt_seq1);
	if (currentToken() == ELSE) {
		(*ifthen).option = 1;
		nextToken();
		(*ifthen).stmt_seq2 = (stmt_seq_node*)malloc(sizeof(stmt_seq_node));
		parser_stmt_seq((*ifthen).stmt_seq2);
	}
	if (currentToken() != ENDIF) {
		printf("ERROR: Expected ENDIF token\n");
		exit(0);
	}
	nextToken();
	if (currentToken() != SEMICOLON) {
		printf("ERROR: Expected SEMICOLON token after ENDIF token\n");
		exit(0);
	}
	nextToken();
}

void printer_if(if_node *ifthen, int tabbing) {
	for (int i=0; i<tabbing; i++) {
		printf("\t");
	}
	printf("if ");
	printer_cond((*ifthen).cond);
	printf(" then\n");
	printer_stmt_seq((*ifthen).stmt_seq1, tabbing+1);
	if ((*ifthen).option == 1) {
		for (int i=0; i<tabbing; i++) {
			printf("\t");
		}
		printf("else\n");
		printer_stmt_seq((*ifthen).stmt_seq2, tabbing+1);
	}
	for (int i=0; i<tabbing; i++) {
		printf("\t");
	}
	printf("endif;\n");
}

void executor_if(if_node *ifthen) {
	if (executor_cond((*ifthen).cond)) {
		executor_stmt_seq((*ifthen).stmt_seq1);
	} else if ((*ifthen).option == 1) {
		executor_stmt_seq((*ifthen).stmt_seq2);
	}
}

void parser_loop(loop_node *loop) {
    int t=currentToken();
	nextToken();
	(*loop).cond = (cond_node*)malloc(sizeof(cond_node));
	parser_cond((*loop).cond);
	if (currentToken() != BEGIN) {
		printf("ERROR: Expected BEGIN token in loop\n");
		exit(0);
	}
	nextToken();
	(*loop).stmt_seq = (stmt_seq_node*)malloc(sizeof(stmt_seq_node));
	parser_stmt_seq((*loop).stmt_seq);
	if (currentToken() != ENDWHILE) {
		printf("ERROR: Expected ENDWHILE token\n");
		exit(0);
	}
	nextToken();
	if (currentToken() != SEMICOLON) {
		printf("ERROR: Expected SEMICOLON token after ENDWHILE token\n");
		exit(0);
	}
	nextToken();
}

void printer_loop(loop_node *loop, int tabbing) {
	for (int i=0; i<tabbing; i++) {
		printf("\t");
	}
	printf("while ");
	printer_cond((*loop).cond);
	printf(" begin\n");
	printer_stmt_seq((*loop).stmt_seq, tabbing+1);
	for (int i=0; i<tabbing; i++) {
		printf("\t");
	}
	printf("endwhile;\n");
}

void executor_loop(loop_node *loop) {
	while (executor_cond((*loop).cond)) {
		executor_stmt_seq((*loop).stmt_seq);
	}
}

void parser_in(in_node *input) {
    int t=currentToken();
	nextToken();
	(*input).id = (id_node*)malloc(sizeof(id_node));
	parser_id((*input).id);
	if (currentToken() != SEMICOLON) {
		printf("ERROR: Expected SEMICOLON token after input statement\n");
		exit(0);
	}
	nextToken();
}

void printer_in(in_node *input, int tabbing) {
	for (int i=0; i<tabbing; i++) {
		printf("\t");
	}
	printf("input ");
	printer_id((*input).id);
	printf(";\n");
}

void executor_in(in_node *input) {
	stored[executor_id_store((*input).id)] = get_input();
}

void parser_out(out_node *output) {
    int t=currentToken();
	nextToken();
	(*output).expr = (expr_node*)malloc(sizeof(expr_node));
	parser_expr((*output).expr);
	if (currentToken() != SEMICOLON) {
		printf("ERROR: Expected SEMICOLON token after output statement\n");
		exit(0);
	}
	nextToken();
}

void printer_out(out_node *output, int tabbing) {
	for (int i=0; i<tabbing; i++) {
		printf("\t");
	}
	printf("output ");
	printer_expr((*output).expr);
	printf(";\n");
}

void executor_out(out_node *output) {
	int result = executor_expr((*output).expr);
	printf("%d\n", result);
}

void parser_cond(cond_node *cond) {
    int t=currentToken();
	if (currentToken() == NEGATION) {
		(*cond).option = 2;
		nextToken();
		if (currentToken() != LPAREN) {
			printf("ERROR: Expected LPAREN token\n");
			exit(0);
		}
		nextToken();
		(*cond).cond = (cond_node*)malloc(sizeof(cond_node));
		parser_cond((*cond).cond);
		if (currentToken() != RPAREN) {
			printf("ERROR: Expected RPAREN token after cond\n");
			exit(0);
		}
		nextToken();
	} else {
		(*cond).option = 1;
		(*cond).cmpr = (cmpr_node*)malloc(sizeof(cmpr_node));
		parser_cmpr((*cond).cmpr);
		if (currentToken() == OR) {
			(*cond).option = 3;
			nextToken();
			(*cond).cond = (cond_node*)malloc(sizeof(cond_node));
			parser_cond((*cond).cond);
		}
	}
}

void printer_cond(cond_node *cond) {
	if ((*cond).option == 2) {
		printf("!(");
		printer_cond((*cond).cond);
		printf(")");
	} else {
		printer_cmpr((*cond).cmpr);
		if ((*cond).option == 3) {
			printf(" or ");
			printer_cond((*cond).cond);
		}
	}
}

bool executor_cond(cond_node *cond) {
	bool lhs, rhs;
	if ((*cond).option == 2) {
		lhs = !executor_cond((*cond).cond);
	} else {
		lhs = executor_cmpr((*cond).cmpr);
		if ((*cond).option == 3) {
			rhs = executor_cond((*cond).cond);
			lhs = lhs || rhs;
		}
	}
	return lhs;
}

void parser_cmpr(cmpr_node *cmpr) {
    int t=currentToken();
	(*cmpr).expr1 = (expr_node*)malloc(sizeof(expr_node));
	parser_expr((*cmpr).expr1);
	if (currentToken() == EQUAL) {
		(*cmpr).option = 1;
	} else if (currentToken() == LESS) {
		(*cmpr).option = 2;
	} else if (currentToken() == LESSEQUAL) {
		(*cmpr).option = 3;
	} else {
		printf("ERROR: Invalid operation in cmpr\n");
		exit(0);
	}
	nextToken();
	(*cmpr).expr2 = (expr_node*)malloc(sizeof(expr_node));
	parser_expr((*cmpr).expr2);
}

void printer_cmpr(cmpr_node *cmpr) {
	printer_expr((*cmpr).expr1);
	if ((*cmpr).option == 1) {
		printf("==");
	} else if ((*cmpr).option == 2) {
		printf("<");
	} else {
		printf("<=");
	}
	printer_expr((*cmpr).expr2);
}

bool executor_cmpr(cmpr_node *cmpr) {
	int lhs, rhs;
	bool result;
	lhs = executor_expr((*cmpr).expr1);
	rhs = executor_expr((*cmpr).expr2);
	if ((*cmpr).option == 1) {
		result = lhs==rhs;
	} else if ((*cmpr).option == 2) {
		result = lhs<rhs;
	} else {
		result = lhs<=rhs;
	}
	return result;
}

void parser_expr(expr_node *expr) {
    int t=currentToken();
	(*expr).term = (term_node*)malloc(sizeof(term_node));
	parser_term((*expr).term);
	(*expr).option = 1;
	if (currentToken() == ADD) {
		(*expr).option = 2;
		nextToken();
		(*expr).expr = (expr_node*)malloc(sizeof(expr_node));
		parser_expr((*expr).expr);
	} else if (currentToken() == SUB) {
		(*expr).option = 3;
		nextToken();
		(*expr).expr = (expr_node*)malloc(sizeof(expr_node));
		parser_expr((*expr).expr);
	}
}

void printer_expr(expr_node *expr) {
	printer_term((*expr).term);
	if ((*expr).option == 2) {
		printf("+");
		printer_expr((*expr).expr);
	} else if ((*expr).option == 3) {
		printf("-");
		printer_expr((*expr).expr);
	}
}

int executor_expr(expr_node *expr) {
	int lhs, rhs;
	lhs = executor_term((*expr).term);
	if ((*expr).option == 2) {
		rhs = executor_expr((*expr).expr);
		lhs = lhs + rhs;
	} else if ((*expr).option == 3) {
		rhs = executor_expr((*expr).expr);
		lhs = lhs - rhs;
	}
	return lhs;
}

void parser_term(term_node *term) {
    int t=currentToken();
	(*term).factor = (factor_node*)malloc(sizeof(factor_node));
	parser_factor((*term).factor);
	(*term).option = 1;
	if (currentToken() == MULT) {
		(*term).option = 2;
		nextToken();
		(*term).term = (term_node*)malloc(sizeof(term_node));
		parser_term((*term).term);
	}
}

void printer_term(term_node *term) {
	printer_factor((*term).factor);
	if ((*term).option == 2) {
		printf("*");
		printer_term((*term).term);
	}
}

int executor_term(term_node *term) {
	int lhs, rhs;
	lhs = executor_factor((*term).factor);
	if ((*term).option == 2) {
		rhs = executor_term((*term).term);
		lhs = lhs*rhs;
	}
	return lhs;
}

void parser_factor(factor_node *factor) {
    int t=currentToken();
	if (currentToken() == CONST) {
		(*factor).option = 1;
		(*factor).constant = (const_node*)malloc(sizeof(const_node));
		parser_const((*factor).constant);
	} else if (currentToken() == ID) {
		(*factor).option = 2;
		(*factor).id = (id_node*)malloc(sizeof(id_node));
		parser_id((*factor).id);
	} else if (currentToken() == LPAREN) {
		(*factor).option = 3;
		nextToken();
		(*factor).expr = (expr_node*)malloc(sizeof(expr_node));
		parser_expr((*factor).expr);
		if (currentToken() != RPAREN) {
			printf("ERROR: Expected RPAREN after expr in factor\n");
			exit(0);
		}
		nextToken();
	} else {
		printf("ERROR: Invalid option in factor\n");
		exit(0);
	}
}

void printer_factor(factor_node *factor) {
	if ((*factor).option == 1) {
		printer_const((*factor).constant);
	} else if ((*factor).option == 2) {
		printer_id((*factor).id);
	} else if ((*factor).option == 3) {
		printf("(");
		printer_expr((*factor).expr);
		printf(")");
	}
}

int executor_factor(factor_node *factor) {
	int result;
	if ((*factor).option == 1) {
		result = executor_const((*factor).constant);
	} else if ((*factor).option == 2) {
		result = stored[executor_id((*factor).id)];
	} else if ((*factor).option == 3) {
		result = executor_expr((*factor).expr);
	}
	return result;
}

void parser_const(const_node *constant) {
	(*constant).value = getCONST();
	nextToken();
}

void printer_const(const_node *constant) {
	printf("%d", (*constant).value);
}

int executor_const(const_node *constant) {
	return (*constant).value;
}

void parser_decl_func(decl_func_node *dfn){
    int t=currentToken();
    func=1;
    (*dfn).id=(id_node*)malloc(sizeof(id_node));
    int lookUp=parser_func_id_add((*dfn).id);
    (*dfn).lookUp=lookUp;
    if (currentToken() != LPAREN) {
        printf("ERROR: Expected LPAREN after id in decl_func\n");
        exit(0);
    }
    nextToken();
    lookupTable[lookUp].count=0;
    (*dfn).id_list=(id_list_node*)malloc(sizeof(id_list_node));
    parser_func_id_list((*dfn).id_list,lookUp);
    lookupTable[lookUp].pra=(*dfn).id_list;
    //
    if (currentToken() != RPAREN) {
        printf("ERROR: Expected RPAREN after id_list in decl_func\n");
        exit(0);
    }
    nextToken();
    if (currentToken() != BEGIN) {
        printf("ERROR: Expected BEGIN token in decl_func\n");
        exit(0);
    }
    nextToken();
    (*dfn).stmt_seq=(stmt_seq_node*)malloc(sizeof(stmt_seq_node));
    parser_stmt_seq((*dfn).stmt_seq);
    lookupTable[lookUp].stmtSeqNode=(*dfn).stmt_seq;
    if (currentToken() != ENDFUNC) {
        printf("ERROR: Expected ENDFUNC token in decl_func\n");
        exit(0);
    }
    nextToken();
    if (currentToken() != SEMICOLON) {
        printf("ERROR: Expected SEMICOLON token after decl_func\n");
        exit(0);
    }
    nextToken();
    func=0;
}

void printer_decl_func(decl_func_node *dfn){
    printer_id((*dfn).id);
    printf("(");
    printer_id_list((*dfn).id_list);
    printf(")");
    printf("begin");
    printer_stmt_seq((*dfn).stmt_seq,0);
    printf("endfunc;");
}

void executor_decl_func(decl_func_node *dfn){
// no need for executor
}

void parser_func(func_node *fn){
    int t=currentToken();
    if (currentToken() != BEGIN) {
        printf("ERROR: Expected BEGIN token in func\n");
        exit(0);
    }
    nextToken();
    (*fn).id=(id_node*)malloc(sizeof(id_node));
    parser_func_id((*fn).id);
    if (currentToken() != LPAREN) {
        printf("ERROR: Expected LPAREN after id in func\n");
        exit(0);
    }
    nextToken();
    (*fn).id_list=(id_list_node*)malloc(sizeof(id_list_node));
    parser_id_list((*fn).id_list);
    if (currentToken() != RPAREN) {
        printf("ERROR: Expected RPAREN after id_list in func\n");
        exit(0);
    }
    nextToken();
    if (currentToken() != SEMICOLON) {
        printf("ERROR: Expected SEMICOLON token after func\n");
        exit(0);
    }
    nextToken();
}

void printer_func(func_node *fn, int tabbing){
    for (int i=0; i<tabbing; i++) {
        printf("\t");
    }
    printf("begin");
    printer_id((*fn).id);
    printf("(");
    printer_id_list((*fn).id_list);
    printf(");");
}

void lookup_id_list(id_list_node *idl, int pram[], int id[]) {
    int lookup=lookup_identifier((*(*idl).id).value);
    for (int i = 0; i < SIZE; ++i) {
        if (id[i]!=-1){
            id[i]=lookup;
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        if (pram[i]!=-1){
            pram[i]=stored[lookup];
        }
    }
    if ((*idl).option == 1) {
        lookup_id_list((*idl).id_list,pram,id);
    }
}

void executor_func(func_node *fn){
    int lookupfunc=lookup_func((*fn).id->value);
    int pram[SIZE]={-1};//value of prameter passed by caller
    int id[SIZE]={-1};//position in the stack of prameter passed by caller
    lookup_id_list((*fn).id_list,pram,id);
    int i=0;
    for (i = 0; i < SIZE; ++i) {
        if(stackState[i]==0){
            stack[i].FP=FP;
            stack[i].SP=SP;
            FP=SP;//record FP and SP of caller in a stackframe and point FP to SP
            break;
        }
    }
    for (int j = 0; j < lookupTable[lookupfunc].count; ++j) {
        add_identifier(lookupTable[lookupfunc].identifiers[j]);
        stored[lookup_identifier(lookupTable[lookupfunc].identifiers[j])]=pram[j];
    }
    executor_id_list(lookupTable[lookupfunc].pra);
    executor_stmt_seq(lookupTable[lookupfunc].stmtSeqNode);
    for (int j = 0; j < lookupTable[lookupfunc].count; ++j) {
        int newPos=lookup_identifier(lookupTable[lookupfunc].identifiers[j]);
        stored[id[j]]=stored[newPos];// Copy back value to caller
    }
    FP=stack[i].FP;
    SP=stack[i].SP;//restore calling stack
}

