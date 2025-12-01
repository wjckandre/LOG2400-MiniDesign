#include "MiniDesign.h"
#include <iostream>

#include <string>

int main(int argc, char* argv[]) {
    std::string input;
    if (argc > 1) {
        input = argv[1];
    }

    MiniDesign app(input);
    app.run();
    return 0;
}
