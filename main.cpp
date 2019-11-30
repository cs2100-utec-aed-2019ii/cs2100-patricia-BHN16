#include <iostream>
#include <fstream>
#include "Tries.h"
int main() {
    Tries U;
    std::ifstream f;
    f.open("text.txt");
    std::string line;
    while(f>>line) {
        U.insert(line);
    }
    U.print();
    return 0;
}