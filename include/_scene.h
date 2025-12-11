#ifndef _SCENE_H
#define _SCENE_H

#include<_common.h>
#include<_light.h>
#include<_model.h>
#include<_inputs.h>
#include<_textureloader.h>
#include<_parallax.h>
#include<_skybox.h>
#include<_sprite.h>
#include<_timer.h>
#include<_3dmodelloader.h>
#include<_camera.h>
#include<_bullets.h>
#include<_collisioncheck.h>
#include<vector>
#include<_targets.h>
#include<_objLoader.h>

struct Button
{
    int x, y;
    int width, height;
    enum ActionId{BUTTON_NONE, BUTTON_NEW_GAME, BUTTON_HELP, BUTTON_EXIT};
    ActionId action;
};
class _Scene
{
    public:
        _Scene();           //constructor
        virtual ~_Scene();  //destructor

        int clickCnt =0;

        void reSizeScene(int width, int height);  // resize window
        void initGL();                            // initialize GL graphics
        void drawScene();                         // render scene
        int winMsg(HWND,UINT,WPARAM,LPARAM);      // to get keyboard interrupts and pass it to inputs
        void mouseMapping(int,int);
        double msX,msY,msZ;

        int width, height;  // keep record of the screen size
        enum PageState
        {
            LANDING_PAGE,
            MAIN_MENU,
            HELP_PAGE,
            GAME_ACTIVE,
            GAME_PAUSED
        };
        bool shouldQuit() {return currentPageState == GAME_ACTIVE;};
    protected:

    private:
        PageState currentPageState;
        _textureLoader texLoader;
        _skyBox *skyBox = new _skyBox();
        _camera *gameCamera = new _camera();
        // _3DModelLoader *playerModel = new _3DModelLoader(); the old placeholder ufo model
        _objLoader *playerModel = new _objLoader();

        GLuint landingPageTexID;
        GLuint mainMenuPageTexID;
        GLuint helpPageTexID;
        GLuint newGameButtonTexID;
        GLuint helpButtonTexID;
        GLuint exitButtonTexID;
        GLuint pauseTexID;

        std::vector<Button> menuButtons;

        void start2D();
        void end2D();
        void drawTexture(GLuint texID, int x, int y, int w, int h);
        void drawButton(GLuint texID, int x, int y, int w, int h, Button::ActionId id);
        void fireBullet();

        _collisionCheck col; // collision checker
        _bullets bulletPool[50]; // there can be up to 50 bullets at a time
        _targets targetPool[50]; // and 50 targets
        _timer *gameTimer = new _timer(); // timer will determine when targets spawn

        int lastMouseX;
        int lastMouseY;
};

#endif // _SCENE_H
