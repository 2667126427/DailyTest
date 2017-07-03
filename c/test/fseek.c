#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int main(int argc, char* argv[])
{
    FILE* fp = NULL;
    assert((fp = fopen(argv[1], "r+")) != NULL);
    long size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fclose(fp);
    printf("SIze of %s : %ld bytes\n", argv[1], size);
    
    return 0;
}
