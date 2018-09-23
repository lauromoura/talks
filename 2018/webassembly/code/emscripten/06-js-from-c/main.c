#include <emscripten.h>
#include <stdio.h>
#include <string.h>


int main() {
    EM_ASM(
            console.log(Array(10).join("lol" - 2) + "  Batman!");
    );
    return 0;
}
