#include <stdlib.h>

int 
main(int argc, char *argv[])
{
    int *ptr = NULL;
    free(ptr);
    return 0;
}