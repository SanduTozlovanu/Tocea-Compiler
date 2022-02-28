%{
#include <stdio.h>
#include <stdbool.h>
#include "../aux/symbol_tabler.h"
#include "../aux/stacker.h"

void yyerror(const char*, ...);
int yylex();
void interpret(Node* root);

//tell the interpreter to enter a new scope
void enterScope();
//tell te interpreter to exit the current scope
void exitScope();
//tell the interpreter to enter a new block
void enterBlock();
//tell the interpreter to exit the current block
void exitBlock();
//tell the interpreter to enter a declaration
void enterDeclaration();
//tell the interpreter to enter a function call
void enterCall();
//tell the interpreter to exit the current function call
void exitCall();

//returns a pointer to an element of an array
void* getPointerToArrayElement(Node* root, int print_errors);

//prints from prinqueue variable
void fprintQueue();
//add to the printqueue variable
void addPrintQueue(const char* format, ...);


//this is the stack for the stack machiene
CallStack* callStack;
//this is the symbol table
CallStackUnit* symbolTable;
//true if we are inside a function, else false
bool callingFunction=false;
//true if return exists, else false
int returnExists=0;
//true if the program is running, else false
bool running=false;
//true if an error occured, else false
bool errorOccured=false;
//true if we consider declaration errors
bool printDeclarationErrors=true;
//stuff that will be printed is stored here
char* printQueue;
//true if in global scope
bool inGlobalScope = false;
//true if assigning
bool assigning = false;
//node that will be returned
Node* returnNodePointer=NULL;
//node that stores global declarations
NodeDeclarationBlock globalDeclarations;
//node that stores declarations in the current scope
NodeDeclarationBlock* currentDeclarations;
//node that stores the current function call
NodeBlock currentFunctionCall;
//the stack with nodes
Stack stack;
//the stack with array size
Stack currentArraySize;

extern int line_number;

FILE* sym_file;
extern FILE* yyin;

%}

%union
{
    int intValue;
    char* stringValue;
    float floatValue;
    int boolValue;
    char charValue;
    int typeValue;
    struct Node* node;
}

%token BLOB MAIN CONST INT FLOAT CHAR STRING BOOL VOID IF THEN ELSE ELIF WHILE FUNCDEF EVAL PRINT RETURN LESSEQUAL GREATEREQUAL NOTEQUAL EQUAL ANDL ORL VARDEF LIST FUNCALL
%token <intValue> CONSTANT_INT
%token <stringValue> VAR CONSTANT_STRING
%token <charValue> CONSTANT_CHAR 
%token <floatValue>  CONSTANT_FLOAT
%token <boolValue> CONSTANT_BOOL
%start app
%left ORL
%left ANDL
%left GREATEREQUAL LESSEQUAL EQUAL NOTEQUAL '>' '<'
%left '-' '+'
%left '*' '/' '%'

%type <node> block compound_statement statement expression if while condition elif print function_call declaration function parameters return blob array_size array_access eval
%type <typeValue> type_name type
%type <stringValue> variable

%%

app:
    globalDeclarations MAIN block   { 
                                            exitScope(); 
                                            enterScope(); 
                                            Node* glob_decl = declarationBlockNode(&globalDeclarations);
                                            running = 1;
                                            interpret(glob_decl);
                                            interpret($3); 
                                            inGlobalScope = true;
                                            exitScope(); 
                                            inGlobalScope = false;
                                            if (!errorOccured){
                                                printf("\n");
                                                fprintQueue();
                                            }
                                        }
    ;

globalDeclarations:
    globalDeclarations declaration { addDeclarationToBlock(&globalDeclarations,$2); }
    | globalDeclarations function  { addDeclarationToBlock(&globalDeclarations,$2); }
    | globalDeclarations blob   { addDeclarationToBlock(&globalDeclarations,$2); }
    |
    ;

declaration:
    var_declaration CONST type_name variable_list  ';' { $$ = declarationBlockNode(currentDeclarations); setVariableType($3,$$,1); interpret($$); }
    | var_declaration type_name variable_list  ';' { $$ = declarationBlockNode(currentDeclarations); setVariableType($2,$$,0); interpret($$); }
    ;

var_declaration:
    VARDEF { enterDeclaration(); }
    ;

variable_list:
    variable_list ',' VAR   {
                                Node* decl_node = declarationNode(INVALID_T,$3,NULL);
                                addDeclarationToBlock(currentDeclarations,decl_node);
                            }
    | VAR                   {
                                Node* decl_node = declarationNode(INVALID_T,$1,NULL);
                                addDeclarationToBlock(currentDeclarations,decl_node);

                            }
    | variable_list ',' VAR '=' expression  
                            {
                                Node* decl_node = declarationNode(INVALID_T,$3,$5);
                                addDeclarationToBlock(currentDeclarations,decl_node);
                            }
    | VAR '=' expression    {
                                Node* decl_node = declarationNode(INVALID_T,$1,$3);
                                addDeclarationToBlock(currentDeclarations,decl_node);
                            }
    | variable_list ',' LIST VAR lsquare array_size ']' {
                                                                    Node* decl_node = declarationNode(INVALID_T, $4, blockNode(topStack(&currentArraySize)));
                                                                    addDeclarationToBlock(currentDeclarations,decl_node);
                                                                    popStack(&currentArraySize); 
                                                                }
    | LIST VAR lsquare array_size ']'                   { 
                                                                    Node* decl_node = declarationNode(INVALID_T, $2, blockNode(topStack(&currentArraySize)));
                                                                    addDeclarationToBlock(currentDeclarations,decl_node);
                                                                    popStack(&currentArraySize); 
                                                                }
    ;

type_name:
    INT { $$ = INT_T;}
    | FLOAT { $$ = FLOAT_T; }
    | CHAR { $$ = CHAR_T; }
    | STRING { $$ = STRING_T; }
    | BOOL { $$ = BOOL_T; }
    | VOID { $$ = STATEMENT_T; }
    ;

type:
    CONST type_name { $$ = $2; }
    | type_name { $$ = $1; }
    ;

function:
    funcdef type VAR parameters block                     {
                                                                        exitScope();
                                                                        exitCall();
                                                                        callingFunction = 0;
                                                                        if (returnExists && $2 == STATEMENT_T)
                                                                        {
                                                                            $$ = NULL;
                                                                            yyerror("Cannot return from void function.");
                                                                        }
                                                                        else if (!returnExists && $2 != STATEMENT_T)
                                                                        {
                                                                            $$ = NULL;
                                                                            yyerror("No return from non-void function");
                                                                        }
                                                                        else if (returnExists - 1 != $2)
                                                                        {
                                                                            $$ = NULL;
                                                                            yyerror("Incompatible return type %s expected %s",getTypeName(returnExists-1),getTypeName($2));
                                                                        }
                                                                        else
                                                                        {
                                                                            $$ = functionNode($2,$3,$4,$5);
                                                                            interpret($$);
                                                                        }
                                                                        returnExists = 0;
                                                                    }
    | funcdef type VAR '(' ')' block                      {
                                                                        exitScope();
                                                                        exitCall();callingFunction = 0;
                                                                        if (returnExists && $2 == STATEMENT_T)
                                                                        {
                                                                            $$ = NULL;
                                                                            yyerror("Cannot return from void function.");
                                                                        }
                                                                        else if (!returnExists && $2 != STATEMENT_T)
                                                                        {
                                                                            $$ = NULL;
                                                                            yyerror("No return from non-void function");
                                                                        }
                                                                        else if (returnExists - 1 != $2)
                                                                        {
                                                                            $$ = NULL;
                                                                            yyerror("Incompatible return type %s expected %s",getTypeName(returnExists-1),getTypeName($2));
                                                                        }
                                                                        else
                                                                        {
                                                                            Node* parameters = declarationBlockNode(currentDeclarations);
                                                                            parameters->node.decl_block_node.size=0;
                                                                            $$ = functionNode($2,$3,parameters,$6);
                                                                            interpret($$);
                                                                        }
                                                                        returnExists = 0;
                                                                    }
    ;

funcdef: 
    FUNCDEF { enterCall(); enterScope(); enterDeclaration(); callingFunction=1; returnExists=0; }
    ;

parameters:
    '(' function_parameters ')' {
                                    Node* parameters = declarationBlockNode(currentDeclarations); 
                                    interpret(parameters);
                                    $$ = parameters;
                                }
    ;

function_parameters:
    function_parameters ',' type VAR            { 
                                                    Node* decl_node = declarationNode($3,$4,NULL);
                                                    addDeclarationToBlock(currentDeclarations,decl_node);
                                                }
    | type VAR                                  { 
                                                    Node* decl_node = declarationNode($1,$2,NULL);
                                                    addDeclarationToBlock(currentDeclarations,decl_node);
                                                }
    ;

blob_declarations:
    blob_declarations declaration 
    | blob_declarations function  
    | declaration 
    | function  
    ;

blob:
    BLOB VAR '{' blob_declarations '}' ';'        { $$ = NULL; }
    ;


block:
    lbrace compound_statement rbrace { $$ = $2; }
    ;

lbrace:
    '{' { enterBlock(); }
    ;

rbrace:
    '}' { exitBlock(); }
    ;

compound_statement:
    compound_statement statement { 
                                    addStatementToBlock(topStack(&stack),$2);
                                    $$ = blockNode(topStack(&stack));
                                 }
    |
    ;

statement:
    expression ';'                  { $$ = $1; }
    | variable '=' expression ';'       { 
                                            Node* var = varNode($1,getSymbolFromCallstackUnit(symbolTable,$1));
                                            Node* expression = $3;
                                            $$ = assignmentNode(var,expression);
                                        }
    | array_access '=' expression ';'   {
                                            $$ = assignmentNode($1, $3);
                                        }
    | if                            { $$ = $1; }
    | while                         { $$ = $1; }
    | print ';'                     { $$ = $1; }
    | eval ';'                      { $$ = $1; }
    | declaration                   { $$ = $1; }
    | return ';'                    { $$ = $1; }
    ;

variable:
    VAR { 
            $$ = $1;
            Symbol* sym = getSymbolFromCallstackUnit(symbolTable,$1);
            if (sym == NULL)
                yyerror("Undeclared variable %s",$1);
        }
    ;

array_access:
    variable lsquare array_size_access ']'                  {
                                                                Symbol *sym = getSymbolFromCallstackUnit(symbolTable, $1);
                                                                $$ = arrayAccessNode($1, topStack(&currentArraySize), sym->value.array_v.type);
                                                                popStack(&currentArraySize); 
                                                            }
    ;

lsquare:
    '['                                                     { 
                                                                NodeBlock *new_block = (NodeBlock*)malloc(sizeof(NodeBlock));
                                                                initializeBlock(new_block);
                                                                pushStack(&currentArraySize, new_block); 
                                                            }
    ;


array_size:
    array_size ',' CONSTANT_INT                                {   
                                                                Symbol sym;
                                                                sym.type = INT_T;
                                                                sym.value.int_v = $3;
                                                                Node* size = constNode(&sym);
                                                                addStatementToBlock(topStack(&currentArraySize), size);
                                                            }
    | CONSTANT_INT                                             {
                                                                Symbol sym;
                                                                sym.type = INT_T;
                                                                sym.value.int_v = $1;
                                                                Node* size = constNode(&sym);
                                                                addStatementToBlock(topStack(&currentArraySize), size);
                                                            }
    ;

array_size_access:
    array_size ',' expression                               {   
                                                                addStatementToBlock(topStack(&currentArraySize), $3);
                                                            }
    | expression                                            {
                                                                addStatementToBlock(topStack(&currentArraySize), $1);
                                                            }
    ;

function_call:
    funcall VAR '(' actual_parameters ')'            {
                                                        char* signature = createFuncCallSignature($2,blockNode(&currentFunctionCall));
                                                        Symbol* sym = getSymbolFromCallstackUnit(symbolTable,signature);
                                                        if (sym == NULL)
                                                        {
                                                            yyerror("No function with signature %s declared",signature);
                                                            $$ = NULL;
                                                        }
                                                        else
                                                            $$ = functionCallNode(signature,blockNode(&currentFunctionCall),sym->value.function_v->node.function_node.type);
                                                    }
    | funcall VAR '(' ')'                            {
                                                        char* signature = createFuncCallSignature($2,blockNode(&currentFunctionCall));
                                                        Symbol* sym = getSymbolFromCallstackUnit(symbolTable,signature);
                                                        if (sym == NULL)
                                                        {
                                                            yyerror("No function with signature %s declared",signature);
                                                            $$ = NULL;
                                                        }
                                                        else
                                                            $$ = functionCallNode(signature,blockNode(&currentFunctionCall),sym->value.function_v->node.function_node.type);
                                                    }
    ;

funcall:
    FUNCALL                                          { initializeBlock(&currentFunctionCall); }
    ;

actual_parameters:
    actual_parameters ',' expression                { addStatementToBlock(&currentFunctionCall, $3); }
    | expression                                    { addStatementToBlock(&currentFunctionCall, $1); }
    ;

expression:
    CONSTANT_INT                       {
                                        Symbol sym;
                                        sym.type = INT_T;
                                        sym.value.int_v = $1;
                                        $$ = constNode(&sym);
                                    }
    | CONSTANT_CHAR                    {
                                        Symbol sym;
                                        sym.type = CHAR_T;
                                        sym.value.char_v = $1;
                                        $$ = constNode(&sym);
                                    }
    | CONSTANT_BOOL                    {
                                        Symbol sym;
                                        sym.type = BOOL_T;
                                        sym.value.bool_v = $1;
                                        $$ = constNode(&sym);
                                    }
    | CONSTANT_FLOAT                   {
                                        Symbol sym;
                                        sym.type = FLOAT_T;
                                        sym.value.float_v = $1;
                                        $$ = constNode(&sym);
                                    }
    | CONSTANT_STRING                  {
                                        Symbol sym;
                                        sym.type = STRING_T;
                                        sym.value.string_v = $1;
                                        $$ = constNode(&sym);
                                    }
    | variable                      {
                                        $$ = varNode($1,getSymbolFromCallstackUnit(symbolTable,$1));
                                    }
    | variable '.' variable         { $$ = NULL; }
    | variable '.' function_call    { $$ = NULL; }
    | expression '+' expression     { $$ = binaryOpNode(ADD,$1,$3); }
    | expression '-' expression     { $$ = binaryOpNode(SUB,$1,$3); }
    | expression '*' expression     { $$ = binaryOpNode(MUL,$1,$3); }
    | expression '/' expression     { $$ = binaryOpNode(DIV,$1,$3); }
    | expression '%' expression     { $$ = binaryOpNode(MOD, $1, $3); }
    | condition                     { $$ = $1; }
    | '(' expression ')'            { $$ = $2; } 
    | function_call                                             { $$ = $1; }
    | array_access                                              { $$ = $1; }
    ;

condition:
    expression '<' expression     { $$ = binaryOpNode(LESS,$1,$3); }
    | expression '>' expression     { $$ = binaryOpNode(GREATER,$1,$3); }
    | expression LESSEQUAL expression      { $$ = binaryOpNode(LEQ,$1,$3); }
    | expression GREATEREQUAL expression      { $$ = binaryOpNode(GEQ,$1,$3); }
    | expression NOTEQUAL expression      { $$ = binaryOpNode(NEQ,$1,$3); }
    | expression EQUAL expression      { $$ = binaryOpNode(EQQ,$1,$3); }
    | expression ANDL expression     { $$ = binaryOpNode(AND,$1,$3); }
    | expression ORL expression      { $$ = binaryOpNode(OR,$1,$3); }
    ;

if:
    IF '(' condition ')' THEN block                 { $$ = ifNode($3,$6,NULL); }
    | IF '(' condition ')' THEN block ELSE block    { $$ = ifNode($3,$6,$8); }
    | IF '(' condition ')' THEN block elif          { $$ = ifNode($3,$6,$7); }
    ;

elif:
    ELIF '(' condition ')' THEN block                 { $$ = ifNode($3,$6,NULL); }
    | ELIF '(' condition ')' THEN block ELSE block    { $$ = ifNode($3,$6,$8); }
    | ELIF '(' condition ')' THEN block elif          { $$ = ifNode($3,$6,$7); }
    ;

while:
    WHILE '(' condition ')' THEN block        { $$ = whileNode($3,$6); }
    | WHILE '(' condition ')' ';'           { $$ = whileNode($3,NULL); }
    ;

print:
    PRINT '(' expression ')'                { $$ = printNode($3); }

return:
    RETURN expression   { 
                            if (callingFunction)
                            {
                                $$ = returnNode($2);
                                returnExists = 1 + $2->value_type;
                            }
                            else
                            {
                                $$ = NULL;
                                yyerror("Cannot return. Not in a function.");
                            }
                        }
    ;

eval:
    EVAL '(' expression ',' expression ')'  { 
                                                Node *left = $3;
                                                Node *right = $5;
                                                if(left->value_type != STRING_T){
                                                    $$ = NULL;
                                                    yyerror("Left must be a string");
                                                }
                                                $$ = duoprintNode($3, $5);
                                            }
    ;

%%

void yyerror(const char* format, ...)
{
    errorOccured=1;
    va_list arglist;

    if (!running)
        fprintf(stderr,"Error at line %d:\n",line_number);
    else
        fprintf(stderr,"Error at running:\n");

    va_start(arglist,format);
    vfprintf(stderr,format,arglist);
    va_end(arglist);

    fprintf(stderr,"\n");
}


void enterBlock()
{
    enterScope();
    NodeBlock* new_block = (NodeBlock*)malloc(sizeof(NodeBlock));
    initializeBlock(new_block);
    pushStack(&stack,new_block);
}

void exitBlock()
{
    exitScope();
    popStack(&stack);
}

void enterScope()
{
    int scopeDepth = symbolTable->size-1;
    int callFrameIndex = callStack->size-1;
    for (int i=0;running && i<scopeDepth+callFrameIndex;i++)
    {
        fprintf(sym_file,"\t");
    }
    if (inGlobalScope)
        fprintf(sym_file,"Entered global scope\n");
    else if (running)
        fprintf(sym_file,"Entered new scope\n");
    HashTable* scopeTable = (HashTable*)malloc(sizeof(HashTable));
    initializeHashTable(scopeTable);
    pushCallstackUnit(symbolTable, scopeTable);
}

void exitScope()
{
    free(popCallstackUnit(symbolTable));
    int scopeDepth = symbolTable->size-1;
    int callFrameIndex = callStack->size-1;
    for (int i=0;running && i<scopeDepth+callFrameIndex;i++)
        fprintf(sym_file,"\t");
    if (inGlobalScope)
        fprintf(sym_file,"Exited global scope\n");
    else if (running)
        fprintf(sym_file,"Exited scope\n");
}

void enterDeclaration()
{
    currentDeclarations = (NodeDeclarationBlock*)malloc(sizeof(NodeDeclarationBlock));
    initializeDeclarationBlock(currentDeclarations);
}

void enterCall()
{
    int scopeDepth = symbolTable->size-1;
    int callFrameIndex = callStack->size-1;
    for (int i=0;running && i<scopeDepth+callFrameIndex;i++)
        fprintf(sym_file,"\t");
    if (running)
        fprintf(sym_file,"Entered new call\n");
    CallStackUnit* newSymbolTable = (CallStackUnit*)malloc(sizeof(CallStackUnit));
    initializeCallstackUnit(newSymbolTable);
    pushCallstackUnit(newSymbolTable,topCallstack(callStack)->stack[0]);
    pushCallstack(callStack,newSymbolTable);
    symbolTable = newSymbolTable;
}

void exitCall()
{
    free(popCallstack(callStack));
    symbolTable = topCallstack(callStack);
    int scopeDepth = symbolTable->size-1;
    int callFrameIndex = callStack->size-1;
    for (int i=0;running && i<scopeDepth+callFrameIndex;i++)
        fprintf(sym_file,"\t");
    if (running)
        fprintf(sym_file,"Exited call\n");
}

void* getPointerToArrayElement(Node* root, int print_errors)
{
    interpret(root->node.array_access_node.index);
    Symbol *sym = getSymbolFromCallstackUnit(symbolTable, root->node.array_access_node.name);


    int bad = 0;
    if (sym == NULL)
    {
        if(print_errors == 1)
            yyerror("Undeclared variable %s",root->node.array_access_node.name);
        return NULL;
    }
    else if (!sym->initialized && !assigning)
    {
        if(print_errors == 1)
            yyerror("Unitialized variable %s",root->node.array_access_node.name);
        return NULL;
    }
    else if(sym->value.array_v.dimensions - 1 != root->node.array_access_node.index->node.block_node.size)
    {
        if(print_errors == 1)
            yyerror("Wrong index count, %s has %d dimensions, tried only with %d", root->node.array_access_node.name, sym->value.array_v.dimensions-1, root->node.array_access_node.index->node.block_node.size);
        bad = 1;
        return NULL;
    }
    else
    {
        int size = sym->value.array_v.dimensions - 1;
        int product = 1;
        for(int i = 0; i < size; ++i)
        {
            if(root->node.array_access_node.index->node.block_node.statements[i]->interpret_result.int_v >= sym->value.array_v.size[i])
            {
                if(print_errors == 1)
                    yyerror("Index out of bounds, %d > %d", root->node.array_access_node.index->node.block_node.statements[i]->interpret_result.int_v, sym->value.array_v.size[i] - 1);
                bad = 1;
                return NULL;
            }
            else if(root->node.array_access_node.index->node.block_node.statements[i]->interpret_result.int_v < 0)
            {
                if(print_errors == 1)
                    yyerror("Negative index, %d", root->node.array_access_node.index->node.block_node.statements[i]->interpret_result.int_v, sym->value.array_v.size[i] - 1);
                bad = 1;
                return NULL;
            }
            else
            {
                product *= sym->value.array_v.size[i];
            }
        }
        if(bad == 0)
        {
            int distance = 0;
            for(int i = 0; i < size; ++i)
            {
                product /= sym->value.array_v.size[i];
                distance += (product * root->node.array_access_node.index->node.block_node.statements[i]->interpret_result.int_v);
            }
            if (assigning)
                sym->initialized = 1;
            switch(sym->value.array_v.type)
            {
                case INT_T:
                {
                    return (int*)(sym->value.array_v.value) + distance;
                }
                case CHAR_T:
                {
                    return (char*)(sym->value.array_v.value) + distance;
                }
                case BOOL_T:
                {
                    return (int*)(sym->value.array_v.value) + distance;
                }
                case FLOAT_T:
                {
                    return (float*)(sym->value.array_v.value) + distance;
                }
                case STRING_T:
                {
                    return (char**)(sym->value.array_v.value) + distance;
                }
            }
        }
    }
    return NULL;
}

void fprintQueue()
{
    if (printQueue != NULL)
        printf("%s",printQueue);
}

void addPrintQueue(const char* format, ...)
{
    char message[256];
    va_list arglist;

    va_start(arglist,format);
    vsprintf(message,format,arglist);
    int size = strlen(message)+1;
    if (printQueue == NULL)
    {
        printQueue = (char*)malloc(size);
        strcpy(printQueue,message);
    }
    else
    {
        int length = strlen(printQueue);
        printQueue = (char*)realloc(printQueue,length+size);
        strcat(printQueue,message);
    }
    
    va_end(arglist);
}

void interpret(struct Node* root)
{
    if (!root)
    {
        return;
    }

    if (root->value_type == INVALID_T)
    {
        return;
    }

    if (returnNodePointer != NULL)
    {
        return;
    }
    switch (root->type)
    {
        case VAR_N:
        {
            Symbol* sym = getSymbolFromCallstackUnit(symbolTable,root->node.var_node.name);
            if (sym == NULL)
                yyerror("Undeclared variable %s",root->node.var_node.name);
            else if (!sym->initialized && !assigning)
                yyerror("Variable not initialized %s",root->node.var_node.name);
            else
            {
                switch (root->value_type)
                {
                    case INT_T: root->interpret_result.int_v = sym->value.int_v; break;
                    case FLOAT_T: root->interpret_result.float_v = sym->value.float_v; break;
                    case BOOL_T: root->interpret_result.bool_v = sym->value.bool_v; break;
                    case CHAR_T: root->interpret_result.char_v = sym->value.char_v; break;
                    case STRING_T: root->interpret_result.string_v = sym->value.string_v; break;
                }
            }
            break;
        }
        case CONST_N:
        {   
            switch (root->value_type)
            {
                case INT_T: root->interpret_result.int_v = root->node.const_node.value.value.int_v; break;
                case FLOAT_T: root->interpret_result.float_v = root->node.const_node.value.value.float_v; break;
                case BOOL_T: root->interpret_result.bool_v = root->node.const_node.value.value.bool_v; break;
                case CHAR_T: root->interpret_result.char_v = root->node.const_node.value.value.char_v; break;
                case STRING_T: root->interpret_result.string_v = strdup(root->node.const_node.value.value.string_v); break;
            }
            break;
        }
        case OP_N:
        {
            for(int i = 0; i < root->node.op_node.size; ++i)
            {
                interpret(root->node.op_node.operands[i]);
            }
            if (root->value_type == INT_T)
            {
                {
                    int left = root->node.op_node.operands[0]->interpret_result.int_v;
                    int right = root->node.op_node.operands[1]->interpret_result.int_v;
                    int result = 0;
                    switch (root->node.op_node.op)
                    {
                        case ADD: result = left + right; break;
                        case SUB: result = left - right; break;
                        case MUL: result = left * right; break;
                        case DIV: result = left / right; break;
                        case MOD: result = left % right; break;
                        case LESS: result = left < right; break;
                        case GREATER: result = left > right; break;
                        case LEQ: result = left <= right; break;
                        case GEQ: result = left >= right; break;
                        case EQQ: result = left == right; break;
                        case NEQ: result = left != right; break;
                        case AND: result = left && right; break;
                        case OR: result = left || right; break;
                    }
                    root->interpret_result.int_v = result;
                }
            }
            else if (root->value_type == FLOAT_T)
            {
                {
                    float left = root->node.op_node.operands[0]->interpret_result.float_v;
                    float right = root->node.op_node.operands[1]->interpret_result.float_v;
                    float result = 0;
                    switch (root->node.op_node.op)
                    {
                        case ADD: result = left + right; break;
                        case SUB: result = left - right; break;
                        case MUL: result = left * right; break;
                        case DIV: result = left / right; break;
                        case LESS: result = left < right; break;
                        case GREATER: result = left > right; break;
                        case LEQ: result = left <= right; break;
                        case GEQ: result = left >= right; break;
                        case EQQ: result = left == right; break;
                        case NEQ: result = left != right; break;
                        case AND: result = left && right; break;
                        case OR: result = left || right; break;
                    }
                    root->interpret_result.float_v = result;
                }
            }
            else if (root->value_type == BOOL_T)
            {
                int left = root->node.op_node.operands[0]->interpret_result.bool_v;
                int right = root->node.op_node.operands[1]->interpret_result.bool_v;
                int result = 0;
                switch (root->node.op_node.op)
                {
                    case ADD: result = (left + right) != 0; break;
                    case SUB: result = (left - right) != 0; break;
                    case MUL: result = (left * right) != 0; break;
                    case DIV: result = (left / right) != 0; break;
                    case LESS: result = left < right; break;
                    case GREATER: result = left > right; break;
                    case LEQ: result = left <= right; break;
                    case GEQ: result = left >= right; break;
                    case EQQ: result = left == right; break;
                    case NEQ: result = left != right; break;
                    case AND: result = left && right; break;
                    case OR: result = left || right; break;
                }
                root->interpret_result.bool_v = result;
            }
            else if (root->value_type == CHAR_T) 
            {
                char left = root->node.op_node.operands[0]->interpret_result.char_v;
                char right = root->node.op_node.operands[1]->interpret_result.char_v;
                char result = 0;
                switch (root->node.op_node.op)
                {
                    case ADD: result = left + right; break;
                    case SUB: result = left - right; break;
                    case MUL: result = left * right; break;
                    case DIV: result = left / !right; break;
                    case LESS: result = left < right; break;
                    case GREATER: result = left > right; break;
                    case LEQ: result = left <= right; break;
                    case GEQ: result = left >= right; break;
                    case EQQ: result = left == right; break;
                    case NEQ: result = left != right; break;
                    case AND: result = left && right; break;
                    case OR: result = left || right; break;
                }
                root->interpret_result.char_v = result;
            }
            break;
        }
        case BLOCK_N:
        {
            enterScope();
            for (int i=0;i<root->node.block_node.size;i++)
                interpret(root->node.block_node.statements[i]);
            exitScope();
            break;
        }
        case IF_N:
        {
            interpret(root->node.if_node.condition);
            if (root->node.if_node.condition->interpret_result.int_v)
            {
                interpret(root->node.if_node.if_block);
            }
            else
            {
                interpret(root->node.if_node.else_block);
            }
            break;
        }
        case WHILE_N:
            interpret(root->node.while_node.condition);
            while (root->node.while_node.condition->interpret_result.int_v)
            {
                interpret(root->node.while_node.block);
                interpret(root->node.while_node.condition);
            }
            break;
        case ASSGN_N:
        {
            assigning = 1;
            interpret(root->node.assgn_node.var);
            assigning = 0;
            interpret(root->node.assgn_node.expression);
            if(root->node.assgn_node.var->type == VAR_N) 
            {
                Symbol *sym = getSymbolFromCallstackUnit(symbolTable,root->node.assgn_node.var->node.var_node.name);
                
                if(sym->isConstant == 1)
                {
                    yyerror("Cannot assign to constant variable %s.",root->node.assgn_node.var->node.var_node.name);
                    break;
                }
                
                sym->initialized = 1;

                if(root->value_type == STRING_T)
                {
                    sym->value.string_v = root->node.assgn_node.expression->interpret_result.string_v;
                }
                else if(root->value_type == CHAR_T)
                {
                    sym->value.char_v = root->node.assgn_node.expression->interpret_result.char_v;
                }
                else if(root->value_type == FLOAT_T)
                {
                    sym->value.float_v = root->node.assgn_node.expression->interpret_result.float_v;
                }
                else if(root->value_type == BOOL_T)
                {
                    sym->value.bool_v = root->node.assgn_node.expression->interpret_result.bool_v;
                }
                else if(root->value_type == INT_T)
                {
                    sym->value.int_v = root->node.assgn_node.expression->interpret_result.int_v;
                }
            }
            else if(root->node.assgn_node.var->type == ARRAY_ACCESS_N)
            {
                void *p = getPointerToArrayElement(root->node.assgn_node.var, 0);
                if(p != NULL)
                {
                    if(root->value_type == STRING_T)
                    {
                        *((char**)p) = root->node.assgn_node.expression->interpret_result.string_v;
                    }
                    else if(root->value_type == CHAR_T)
                    {
                        *((char*)p) = root->node.assgn_node.expression->interpret_result.char_v;
                    }
                    else if(root->value_type == FLOAT_T)
                    {
                        *((float*)p) = root->node.assgn_node.expression->interpret_result.float_v;
                    }
                    else if(root->value_type == BOOL_T)
                    {
                        *((int*)p) = root->node.assgn_node.expression->interpret_result.bool_v;
                    }
                    else if(root->value_type == INT_T)
                    {
                        *((int*)p) = root->node.assgn_node.expression->interpret_result.int_v;
                    }
                }
            }
            break;
        }
        case PRINT_N:
        {
            interpret(root->node.print_node.expression);
            switch (root->node.print_node.expression->value_type)
            {
                case INT_T:
                    addPrintQueue("%d\n",root->node.print_node.expression->interpret_result.int_v);
                    break;
                case FLOAT_T:
                    addPrintQueue("%f\n",root->node.print_node.expression->interpret_result.float_v);
                    break;
                case BOOL_T:
                    addPrintQueue("%s\n",root->node.print_node.expression->interpret_result.bool_v ? "true" : "false");
                    break;
                case CHAR_T:
                    addPrintQueue("%c\n",root->node.print_node.expression->interpret_result.char_v);
                    break;
                case STRING_T:
                    addPrintQueue("%s\n",root->node.print_node.expression->interpret_result.string_v);
                    break;
            }
            break;
        }
        case DUOPRINT_N:
        {
            interpret(root->node.duoprint_node.expression1);
            addPrintQueue("%s ", root->node.duoprint_node.expression1->interpret_result.string_v);
            interpret(root->node.duoprint_node.expression2);
            switch (root->node.duoprint_node.expression2->value_type)
            {
                case INT_T:
                    addPrintQueue("%d\n",root->node.duoprint_node.expression2->interpret_result.int_v);
                    break;
                case FLOAT_T:
                    addPrintQueue("%f\n",root->node.duoprint_node.expression2->interpret_result.float_v);
                    break;
                case BOOL_T:
                    addPrintQueue("%s\n",root->node.duoprint_node.expression2->interpret_result.bool_v ? "true" : "false");
                    break;
                case CHAR_T:
                    addPrintQueue("%c\n",root->node.duoprint_node.expression2->interpret_result.char_v);
                    break;
                case STRING_T:
                    addPrintQueue("%s\n",root->node.duoprint_node.expression2->interpret_result.string_v);
                    break;
            }
            break;
        }
        case DECLARATION_N:
        {
            Symbol sym;
            sym.type = root->node.declaration_node.type;
            sym.initialized = 0;
            if (root->node.declaration_node.expression != NULL && root->node.declaration_node.expression->type == BLOCK_N)
            {
                int array_dimensions = root->node.declaration_node.expression->node.block_node.size;
                sym.value.array_v.size = malloc(sizeof(int) * array_dimensions);
                sym.value.array_v.dimensions = array_dimensions;
                int allocate = 1;

                for(int i = 0; i < array_dimensions - 1; ++i)
                {
                    allocate *= root->node.declaration_node.expression->node.block_node.statements[i]->node.const_node.value.value.int_v;
                    sym.value.array_v.size[i] = root->node.declaration_node.expression->node.block_node.statements[i]->node.const_node.value.value.int_v;
                }
                switch(root->node.declaration_node.expression->node.block_node.statements[array_dimensions - 1]->node.const_node.value.value.int_v)
                {
                    case INT_T:
                    {
                        sym.value.array_v.type = INT_T;
                        sym.value.array_v.value = malloc(sizeof(int) * allocate);
                        break;
                    }
                    case CHAR_T:
                    {
                        sym.value.array_v.type = CHAR_T;
                        sym.value.array_v.value = malloc(sizeof(char) * allocate);
                        break;
                    }
                    case BOOL_T:
                    {
                        sym.value.array_v.type = BOOL_T;
                        sym.value.array_v.value = malloc(sizeof(int) * allocate);
                        break;
                    }
                    case FLOAT_T:
                    {
                        sym.value.array_v.type = FLOAT_T;
                        sym.value.array_v.value = malloc(sizeof(float) * allocate);
                        break;
                    }
                    case STRING_T:
                    {
                        sym.value.array_v.type = STRING_T;
                        sym.value.array_v.value = malloc(sizeof(char*) * allocate);
                        break;
                    }
                }

                if (NULL != getSymbolFromHashTable(topCallstackUnit(symbolTable),root->node.declaration_node.name))
                {
                    if (printDeclarationErrors)
                        yyerror("Variable %s already declared",root->node.declaration_node.name);
                }
                else
                {
                    insertHashTable(topCallstackUnit(symbolTable),root->node.declaration_node.name,&sym);
                    if (running)
                    {
                        int scope_depth = symbolTable->size-1;
                        int call_frame_index = callStack->size-1;
                        for (int i=0;running && i<scope_depth+call_frame_index;i++)
                            fprintf(sym_file,"\t");
                        fprintf(sym_file,"Inserted symbol %s of type %s at scope depth %d in call frame %d\n",root->node.declaration_node.name,getTypeName(sym.type),scope_depth,call_frame_index);
                    }
                }
                break;
            }
            else
            { 
                sym.isConstant = root->node.declaration_node.isConstant;
                if (root->node.declaration_node.expression != NULL)
                {
                    interpret(root->node.declaration_node.expression);
                    sym.initialized = 1;
                    switch (root->node.declaration_node.type)
                    {
                        case INT_T:
                            sym.value.int_v = root->node.declaration_node.expression->interpret_result.int_v;
                            break;
                        case FLOAT_T:
                            sym.value.float_v = root->node.declaration_node.expression->interpret_result.float_v;
                            break;
                        case BOOL_T:
                            sym.value.bool_v = root->node.declaration_node.expression->interpret_result.bool_v;
                            break;
                        case CHAR_T:
                            sym.value.char_v = root->node.declaration_node.expression->interpret_result.char_v;
                            break;
                        case STRING_T:
                            sym.value.string_v = root->node.declaration_node.expression->interpret_result.string_v;
                            break;
                    }
                }
                else
                {
                    if(sym.isConstant == 1)
                    {
                        if (printDeclarationErrors)
                            yyerror("Constant variables need to be initialized.\n");
                        sym.type = INVALID_T;
                        break;
                    }
                    sym.value.int_v = 0;
                }
                if (NULL != getSymbolFromHashTable(topCallstackUnit(symbolTable),root->node.declaration_node.name))
                {
                    if (printDeclarationErrors)
                        yyerror("Variable %s already declared",root->node.declaration_node.name);
                }
                else
                {
                    insertHashTable(topCallstackUnit(symbolTable),root->node.declaration_node.name,&sym);
                    if (running)
                    {
                        int scope_depth = symbolTable->size-1;
                        int call_frame_index = callStack->size-1;
                        for (int i=0;running && i<scope_depth+call_frame_index;i++)
                            fprintf(sym_file,"\t");
                        fprintf(sym_file,"Inserted symbol %s of type %s at scope depth %d in call frame %d\n",root->node.declaration_node.name,getTypeName(sym.type),scope_depth,call_frame_index);
                    }
                }
                break;
            }
        }
	    case DECL_BLOCK_N:
        {
            for (int i=0;i<root->node.decl_block_node.size;i++)
                interpret(root->node.decl_block_node.declarations[i]);
            break;
        }
        case FUNCTION_N:
        {
            Symbol sym;
            sym.type = FUNCTION_T;
            sym.value.function_v = root;
            char* function_name = createFuncSignature(root);
            if (NULL != getSymbolFromHashTable(topCallstackUnit(symbolTable),function_name))
            {
                if (printDeclarationErrors)
                    yyerror("Function %s already declared",function_name);
            }
            else
            {
                insertHashTable(topCallstackUnit(symbolTable),function_name,&sym);
                if (running)
                {
                    int scope_depth = symbolTable->size-1;
                    int call_frame_index = callStack->size-1;
                    for (int i=0;running && i<scope_depth+call_frame_index;i++)
                    {
                        fprintf(sym_file,"\t");
                    }
                    fprintf(sym_file,"Inserted symbol %s of type %s at scope depth %d in call frame %d\n",function_name,getTypeName(sym.type),scope_depth,call_frame_index);
                }
            }
            break;
        }
        case FUNCTION_CALL_N:
        {
            Symbol* sym = getSymbolFromCallstackUnit(symbolTable,root->node.function_call_node.signature);
            if (sym)
            {
                for (int i=0;i<root->node.function_call_node.parameters->node.block_node.size;i++)
                {
                    interpret(root->node.function_call_node.parameters->node.block_node.statements[i]);
                    Node* parameter_vue = expressionResultNode(root->node.function_call_node.parameters->node.block_node.statements[i]);
                    sym->value.function_v->node.function_node.parameters->node.decl_block_node.declarations[i]->node.declaration_node.expression = parameter_vue;
                }
                enterCall();
                enterScope();
                interpret(sym->value.function_v->node.function_node.parameters);
                returnNodePointer = NULL;
                interpret(sym->value.function_v->node.function_node.block);
    
                switch (root->value_type)
                {
                    case INT_T:
                        root->interpret_result.int_v = returnNodePointer->interpret_result.int_v;
                        
                        break;
                    case FLOAT_T:
                        root->interpret_result.float_v = returnNodePointer->interpret_result.float_v;
                        
                        break;
                    case BOOL_T:
                        root->interpret_result.bool_v = returnNodePointer->interpret_result.bool_v;
                        
                        break;
                    case CHAR_T:
                        root->interpret_result.char_v = returnNodePointer->interpret_result.char_v;
                    
                        break;
                    case STRING_T:
                        root->interpret_result.string_v = returnNodePointer->interpret_result.string_v;
                        
                        break;
                }
                returnNodePointer = NULL;
                exitScope();
                exitCall();
                for (int i=0;i<root->node.function_call_node.parameters->node.block_node.size;i++)
                {
                    free(sym->value.function_v->node.function_node.parameters->node.decl_block_node.declarations[i]->node.declaration_node.expression);
                    sym->value.function_v->node.function_node.parameters->node.decl_block_node.declarations[i]->node.declaration_node.expression = NULL;
                }
            }
            break;
        }
        case RETURN_N:
        {
            interpret(root->node.return_node.expression);
            root->interpret_result = root->node.return_node.expression->interpret_result;
            returnNodePointer = root;
            break;
        }
        case ARRAY_ACCESS_N:
        {
            root->interpret_result.ptr_v = NULL;
            Symbol *sym = getSymbolFromCallstackUnit(symbolTable, root->node.array_access_node.name);
            void* ptr = getPointerToArrayElement(root, 1);
            if (ptr == NULL)
            {
                break;
            }
            switch(sym->value.array_v.type)
            {
                case INT_T:
                {
                    root->interpret_result.int_v = *(int*)ptr;
                    break;
                }
                case CHAR_T:
                {
                    root->interpret_result.char_v = *(char*)ptr;
                    break;
                }
                case BOOL_T:
                {
                    root->interpret_result.bool_v = *(int*)ptr;
                    break;
                }
                case FLOAT_T:
                {
                    root->interpret_result.float_v = *(float*)ptr;
                    break;
                }
                case STRING_T:
                {
                    root->interpret_result.string_v = *(char**)ptr;
                    break;
                }
            }

            break;
        }
    }
}

int main(int argc, char* argv[]){
    if(argc > 1)
        yyin = fopen(argv[1], "r");
    else
        return 0;
    sym_file = fopen("symbol_table.txt","w");
    symbolTable = (CallStackUnit*)malloc(sizeof(CallStackUnit));
    callStack = (CallStack*)malloc(sizeof(CallStack));
    initializeCallstack(callStack);
    initializeCallstackUnit(symbolTable);
    pushCallstack(callStack,symbolTable);
    initializeStack(&stack);
    initializeStack(&currentArraySize);
    initializeDeclarationBlock(&globalDeclarations);
    inGlobalScope = true;
    enterScope();
    inGlobalScope = false;
    yyparse();
}




















