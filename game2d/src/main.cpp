#include <iostream>
#include "engine/Game.h"


int main() {
    try {
        Game().run();
    }
     catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unknown exception occurred." << std::endl;
        return EXIT_FAILURE;
    }
    
}