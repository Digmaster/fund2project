/*
This is the main file for the SpriteMaker. Don't include it in the Game Engine or shit WILL GO Down
*/

#include "SpriteMakingEngine.h"

int main() {
    SpriteMakingEngine eng;
    try {
        eng.run();
    }
    catch(exception &e) {
        cout << e.what() << endl;
    }
}
