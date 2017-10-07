#include <stdio.h>
#include <stdlib.h>

static void __attribute__((constructor)) beforemain(void) {
    printf("Before main.\n");
}


int main(void) {
    printf("This is main function.\n");


    return 0;
}