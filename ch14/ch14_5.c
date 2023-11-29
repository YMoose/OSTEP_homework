#include <stdlib.h>

int 
main (int argc, char* argv[])
{
    int* ptr = malloc(100*sizeof(int));
    ptr[100] = 1;
    return 0;
}