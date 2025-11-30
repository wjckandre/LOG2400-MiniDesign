#include "MiniDesign.h"
#include <iostream>

#include <string>

int main(int argc, char* argv[]) {
    // Reconstruct input string from args if necessary, or just pass the first arg if quoted.
    // The example ./MiniDesign "(5,0)..." implies argv[1] contains the whole string.

    std::string input;
    if (argc > 1) {
        input = argv[1];
    }

    MiniDesign app(input);
    app.run();
    return 0;
}
