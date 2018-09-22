#include <emscripten.h>
#include <stdio.h>
#include <string.h>


int main() {
    EM_ASM(
            console.log("hello from console!");
    );
    return 0;
}
