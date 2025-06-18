#include <string.h>
#include <string>
#include <cassert>
// requires const to be equivalent to a string
// otherwise c-string would not work properly
int countArray(const char* str, char a) {
    int len = strlen(str);
    int amt = 0;
    for(int i = 0; i < len; i++) {
        if(str[i] == a) {
            amt++;
        }
    }
    return amt;
}

// requires const to be equivalent to a string
int countPointer(const char* str, char a) {
    int amt = 0;
    for (const char *p = str; *p; p++) {
        if (*p == a) {
            amt++;
        }
    }
    return amt;
}
int main() {
    assert(countArray("banana", 'a') == 3);
    assert(countPointer("banana", 'a') == 3);
    return 0;
}