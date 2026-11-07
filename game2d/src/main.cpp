#include <cstdlib>
#include <exception>
#include <iostream>

#include "engine/Game.h"

int main() {
    try {
        Game().run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unknown exception occurred.\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
