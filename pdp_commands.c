#include "mem.c"
#include "log.c"
#include <stdlib.h>
#define pc reg[7]

typedef void (*do_commandp)(void);
void do_add();
void do_mov();
void do_nothing();
void do_halt();


typedef struct {
    word mask;
    word opcode;
    char * name;
    do_commandp do_command;
    
} Command;

struct Argument {
    word value;     // значение (что)
    address adr;    // адрес (куда)
} ss, dd;

Command command[] = {
    {0170000, 0060000, "add", do_add},
    {0170000, 0010000,"mov", do_mov},
    {0177777, 0000000,"halt", do_halt}
    
};


void do_halt()
{
    trace(INFO, "THE END!!!\n");
    exit(0);
}

void do_add(){}
void do_mov(){}
void do_nothing(){}

void f(word w){
    for (int i = 0; i < 3;i++){
        if ((w & command[i].mask) == command[i].opcode) {
            trace(TRACE, "%s\n", command[i].name);
            command[i].do_command();
            return;
        }
    }
    trace(INFO, "unknown\n");
    do_nothing();


}
    


void run()
{
    // следующее слово будем читать по адресу 1000 (восьмеричное)
    
   
    word w;     // текущее слово, которое содержит команду
    // главный цикл выполнения программы
    load_data();
    while(1) {
        // читаем текущее слово
        w = w_read(pc);
        // печатаем адрес и слово по этому адресу, как в листинге
        trace(TRACE, "%06o %06o: ", pc, w);
        // pc сразу же указывает на следующее неразобранное слово
        pc += 2;
        f(w);
        // тут будем искать какая команда закодирована в слове w
        // ...


    }
}

int main(){
    log_level = TRACE;
   run();
}

