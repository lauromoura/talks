#include <stdio.h>

int main() {
    FILE *file = fopen("tests/input.txt", "rb");

    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    while(!feof(file)) {
        char c = fgetc(file);
        if (c != EOF) { putchar(c); }
    }

    fclose(file);

    return 0;
}
