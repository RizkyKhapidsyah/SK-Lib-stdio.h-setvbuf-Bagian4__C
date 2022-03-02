#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/*
    Source by CPPReference
    Modified For Learn by RK
    I.D.E : VS2019
*/

int main(void) {
    FILE* fp = fopen("/tmp/test.txt", "w+");
    if (fp == NULL) {
        perror("fopen"); return EXIT_FAILURE;
    }

    struct stat stats;
    int fileno(FILE*);
    if (fstat(fileno(fp), &stats) == -1) { // POSIX only
        perror("fstat"); return EXIT_FAILURE;
    }

    printf("BUFSIZ is %d, but optimal block size is %ld\n", BUFSIZ, stats.st_blksize);
    if (setvbuf(fp, NULL, _IOFBF, stats.st_blksize) != 0) {
        perror("setvbuf failed"); // POSIX version sets errno
        return EXIT_FAILURE;
    }

    int ch;
    while ((ch = fgetc(fp)) != EOF); // read entire file: use truss/strace to
                                  // observe the read(2) syscalls used

    fclose(fp);
    return EXIT_SUCCESS;
}