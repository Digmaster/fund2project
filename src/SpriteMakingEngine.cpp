#include "SpriteMakingEngine.h"

using namespace std;
using namespace sf;

SpriteMakingEngine::SpriteMakingEngine()
{
    //ctor
}

SpriteMakingEngine::~SpriteMakingEngine()
{
    //dtor
}

void SpriteMakingEngine::run()
{
    string fileName;
    cout << "Which file to modify (If it doesn't exist it will be opened empty): ";
    cin >> fileName;
    ifstream file;
    file.open(fileName);
    SpriteSheet sheet;
    sheet.setFileName(fileName);
    if(!file) {
        string textureName;
        cout << "New file. What image is associated with this file? ";
        cin >> textureName;
        sheet.setImageFile(textureName);
    }
    else {
        file.close();
        sheet.load(fileName);
    }
    Sprite* background = new Sprite();
    rendEng.addSprite(background);
    rendEng.render();
    while(true);
}
