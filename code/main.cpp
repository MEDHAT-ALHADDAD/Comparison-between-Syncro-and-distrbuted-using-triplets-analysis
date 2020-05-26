#include "main.h"

//(@name: main)
//(@signature: argc,argv ->int)
//(@purpose: initthe program)
//
//(@progress: completed)
//(@template: cmd$make run)
int main(int argc, char const *argv[])
{
    serial_proccessing();
    nonserial_proccessing();
    parallel_proccessing();
    tasks_proccessing();
    sections_proccessing();
    return 0;
}
