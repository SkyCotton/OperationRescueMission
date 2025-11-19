#ifndef _BUTTONS_H
#define _BUTTONS_H


#include <_common.h>
#include <vector>
#include <_textureloader.h>
#include <_sceneSwitcher.h>


enum ButtonType {
    BTN_START,
    BTN_QUIT,
    BTN_NEWGAME,
    BTN_HELP,
    BTN_QUIT2,
    BTN_BACK
};


enum SceneType {
    SCENE_LANDING,
    SCENE_MENU,
    SCENE_PAUSE,
    SCENE_LEVEL_ONE,
    SCENE_LEVEL_TWO,
    SCENE_HELP
};


struct Button {
    float x, y, w, h;
    bool hovered = false;
    bool pressed = false;
    bool active = false;


    float r = 1.0f, g = 1.0f, b = 1.0f;
    _textureLoader* texture = nullptr;


    ButtonType type;
    SceneType scene;
};


class _buttons
{
    public:
        _buttons();
        virtual ~_buttons();


        void initButtons(int width, int height, std::vector<Button>& buttons);
        void drawButton(const Button& btn, _textureLoader* defaultTex, int width, int height);
        void handleMouseMove(int x, int y, int height, std::vector<Button>& buttons, SceneType);
        void handleMouseClick(bool down, int x, int y, int height, std::vector<Button>& buttons, bool& startClicked, bool& newGameClicked, bool& helpClicked, bool& backclicked, bool& isActive, SceneType);


        void handleKeyboardPress(WPARAM wParam, std::vector<Button>& buttons, bool& startClicked, bool& newGameClicked, bool& helpClicked, bool& backclicked, bool& isActive, SceneType currentScene);


        bool isActive2 = true;
        float tempos;


        bool keys[256];


    protected:


    private:


};

#endif // _BUTTON_H
