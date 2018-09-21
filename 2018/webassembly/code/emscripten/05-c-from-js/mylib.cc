#include <emscripten.h>
#include <stdio.h>
#include <string.h>
#include <string>

extern "C" {

EMSCRIPTEN_KEEPALIVE
int factorial(int x) {
    if (x <= 1)
        return 1;

    return x * factorial(x-1);
}


EMSCRIPTEN_KEEPALIVE
const char *allcaps(char *s) {
    std::string str(s);
    for (auto& c : str)
        c = toupper(c);
    return str.c_str();
}

}
