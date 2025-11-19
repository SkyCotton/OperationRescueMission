#ifndef _SCENE3_H
#define _SCENE3_H


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
#include<_buttons.h>
#include<_sceneSwitcher.h>
#include<_pauseOverlay.h>
#include<_textureloader.h>
#include<_inputs.h>
#include<_obstacles.h>
#include<_collisioncheck.h>
#include<_menu.h>


class _Scene3
{
public:
    _Scene3();
    virtual ~_Scene3();


    _parallax *myPrlx = new _parallax();
    _buttons* myButtons = new _buttons();
    _sceneSwitcher* sceneSwitcher = nullptr;
    _pauseOverlay pauseOverlay;
    _textureLoader* myTex = new _textureLoader();
    _3DModelLoader* mdl3D = new _3DModelLoader();
    _inputs* myInput = new _inputs();


    _collisionCheck* collisionCheck = new _collisionCheck();


    _obstacles obstacles[6];


    int clickCnt =0;
    bool isActive;
    float dir = 0;
    float speed = 0.4f;
    float jump;
    int charDir;
    bool playerHit = false;


    void reSizeWindow(int width, int height);
    void initGL();
    void drawScene();
    void update();
    int winMsg(HWND,UINT,WPARAM,LPARAM);
    void mouseMapping(int,int);


    double msX,msY,msZ;


    void reset();
    void spawnObstacles();
    void resetObstacles();


    int width, height;


    bool startClicked = false;
    bool newGameClicked = false;
    bool helpClicked = false;
    bool backClicked = false;
    bool nextLevel = false;
    std::vector<Button> buttons;


    Button button;
};


#endif // _SCENE3_H
