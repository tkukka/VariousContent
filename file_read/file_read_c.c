#include <stdio.h>
#include <stdlib.h>

#define FILENAME u8"eng-uk_web_2002_1M-words.txt"
#define MAX_CHARS 121 // find proper value? 81 too small

static char buffer[MAX_CHARS];

int main(void)
{
    FILE *stream;
    char *line = NULL;
    int i = 0;
    printf("C file reading '%s'...\n", FILENAME);
    stream = fopen(FILENAME, "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while ((line = fgets(buffer, MAX_CHARS, stream)) != NULL) {
        ++i;
    }
    fclose(stream);
    printf("Lines: %d\n", i);
    printf("C file read done.\n");
    return 0;
}

