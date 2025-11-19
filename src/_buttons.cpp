#include "_buttons.h"


_buttons::_buttons()
{
    //ctor
}
_buttons::~_buttons()
{
    //dtor
}


void _buttons::initButtons(int width, int height, std::vector<Button>& buttons) {
    Button play, quit, newGame, help, quit2, backBtn;


    play.scene = SCENE_LANDING;
    quit.scene = SCENE_LANDING;


    newGame.scene = SCENE_MENU;
    help.scene    = SCENE_MENU;
    quit2.scene   = SCENE_MENU;


    backBtn.scene    = SCENE_HELP;


    float bw = width * 0.2f;
    float bh = height * 0.08f;


    play.x = width * 0.4f;
    play.y = height * 0.5f;
    play.w = bw;
    play.h = bh;
    play.r = 0.3f; play.g = 0.8f; play.b = 0.4f;
    play.texture = new _textureLoader();
    play.texture->loadTexture("images/startTexture.png");
    play.type = BTN_START;


    quit.x = width * 0.4f;
    quit.y = height * 0.35f;
    quit.w = bw;
    quit.h = bh;
    quit.r = 0.9f; quit.g = 0.3f; quit.b = 0.3f;
    quit.texture = new _textureLoader();
    quit.texture->loadTexture("images/quitTexture.png");
    quit.type = BTN_QUIT;






    newGame.x = width * 0.2f;
    newGame.y = height * 0.65f;
    newGame.w = bw;
    newGame.h = bh;
    newGame.r = 0.3f; newGame.g = 0.8f; newGame.b = 0.4f;
    newGame.texture = new _textureLoader();
    newGame.texture->loadTexture("images/newGameTexture.png");
    newGame.type = BTN_NEWGAME;


    help.x = width * 0.2f;
    help.y = height * 0.5f;
    help.w = bw;
    help.h = bh;
    help.r = 0.3f; help.g = 0.8f; help.b = 0.4f;
    help.texture = new _textureLoader();
    help.texture->loadTexture("images/helpTexture.png");
    help.type = BTN_HELP;


    quit2.x = width * 0.2f;
    quit2.y = height * 0.35f;
    quit2.w = bw;
    quit2.h = bh;
    quit2.r = 0.3f; quit2.g = 0.8f; quit2.b = 0.4f;
    quit2.texture = new _textureLoader();
    quit2.texture->loadTexture("images/quitTexture.png");
    quit2.type = BTN_QUIT2;






    backBtn.x = width * 0.4f;
    backBtn.y = height * 0.1f;
    backBtn.w = bw;
    backBtn.h = bh;
    backBtn.r = 0.9f; backBtn.g = 0.3f; backBtn.b = 0.3f;
    backBtn.texture = new _textureLoader();
    backBtn.texture->loadTexture("images/quitTexture.png");
    backBtn.type = BTN_BACK;








    buttons.push_back(play);
    buttons.push_back(quit);


    buttons.push_back(newGame);
    buttons.push_back(help);
    buttons.push_back(quit2);


    buttons.push_back(backBtn);
}


void _buttons::drawButton(const Button& btn, _textureLoader* defaultTex, int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();


    float y = btn.y;


    ////////////////////////////////////////////////////////
    //button color defaults
    ////////////////////////////////////////////////////////
    float r = btn.r, g = btn.g, b = btn.b;


    if (btn.pressed)
    {
        r *= 0.6f;
        g *= 0.6f;
        b *= 0.6f;
    }
    else if (btn.hovered)
    {
        r = std::min(r * 1.25f, 1.0f);
        g = std::min(g * 1.25f, 1.0f);
        b = std::min(b * 1.25f, 1.0f);
    }


    ////////////////////////////////////////////////////////
    //create button shape
    ////////////////////////////////////////////////////////
    glDisable(GL_TEXTURE_2D);
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(btn.x, y);
        glVertex2f(btn.x + btn.w, y);
        glVertex2f(btn.x + btn.w, y + btn.h);
        glVertex2f(btn.x, y + btn.h);
    glEnd();


    ////////////////////////////////////////////////////////
    //bind texture to button
    ////////////////////////////////////////////////////////
    if (btn.texture)
    {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        btn.texture->bindTexture();
        glColor4f(1, 1, 1, 1); // full texture color


        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(btn.x, y);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(btn.x + btn.w, y);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(btn.x + btn.w, y + btn.h);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(btn.x, y + btn.h);
        glEnd();


        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
    }


    ////////////////////////////////////////////////////////
    //outline
    ////////////////////////////////////////////////////////
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(btn.x, y);
        glVertex2f(btn.x + btn.w, y);
        glVertex2f(btn.x + btn.w, y + btn.h);
        glVertex2f(btn.x, y + btn.h);
    glEnd();


    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}


void _buttons::handleMouseMove(int x, int y, int height, std::vector<Button>& buttons, SceneType currentScene)
{
    //if (!isActive2) return;


    float adjY = height - y;
    for (auto& b : buttons)
    {
        if (b.scene == currentScene && b.active)
        {
            b.hovered = (x >= b.x && x <= b.x + b.w && adjY >= b.y && adjY <= b.y + b.h);
        }
        else
        {
            b.hovered = false;
        }
    }
}




void _buttons::handleMouseClick(bool down, int x, int y, int height, std::vector<Button>& buttons, bool& startClicked, bool& newGameClicked, bool& helpClicked, bool& backclicked, bool& isActive, SceneType currentScene)
{
    float adjY = height - y;
    for (auto& b : buttons)
    {
        if (!b.active || b.scene != currentScene) continue;


        if (down && x >= b.x && x <= b.x + b.w && adjY >= b.y && adjY <= b.y + b.h)
        {
            b.pressed = true;
            switch (b.type)
            {
                case BTN_START:
                    startClicked = true;
                    //isActive = false;
                    b.active = false;
                    cout << "ggg" << endl;
                    break;


                case BTN_NEWGAME:
                    cout << "EWEWEWEW" << endl;
                    newGameClicked = true;
                    //isActive = false;
                    b.active = false;
                    break;


                case BTN_HELP:
                    cout << "AHHHHHHH" << endl;
                    helpClicked = true;
                    b.active = false;
                    break;


                case BTN_QUIT:
                    PostQuitMessage(0);
                    b.active = false;
                    break;


                case BTN_QUIT2:
                    PostQuitMessage(0);
                    b.active = false;
                    break;
                case BTN_BACK:
                    cout << "BACK" << endl;
                    backclicked = true;
                    b.active = false;
                    break;


            }
        }
        else if (!down)
        {
            b.pressed = false;
        }
    }
}




void _buttons::handleKeyboardPress(WPARAM wParam, std::vector<Button>& buttons, bool& startClicked, bool& newGameClicked, bool& helpClicked, bool& backclicked, bool& isActive, SceneType currentScene)
{
    //if (!isActive2) return;


    if (wParam == VK_ESCAPE && currentScene == LEVEL_ONE)
    {
        cout << "ESC pressed: switch to MENU" << endl;
    }


    for (auto& b : buttons)
    {
        if (b.scene != currentScene) continue;


        if (b.type == BTN_START && wParam == VK_RETURN)
        {
            b.pressed = true;
            startClicked = true;
            isActive = false;
            isActive2 = false;
        }


    }
}

