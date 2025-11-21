#ifndef _LANDINGPAGE_H
#define _LANDINGPAGE_H


#include <vector>


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


class _LandingPage
{
public:
    _LandingPage();           // constructor
    virtual ~_LandingPage();  // destructor


    _parallax *myPrlx = new _parallax();
    _textureLoader *myTex = new _textureLoader();
    _textureLoader *myTex2 = new _textureLoader();
    _buttons* myButtons = new _buttons();


    int clickCnt = 0;
    bool isActive;


    void reSizeWindow(int width, int height);  // resize window
    void initGL();                            // initialize GL graphics
    void draw();                          // render scene
    int winMsg(HWND, UINT, WPARAM, LPARAM);  // handle keyboard/mouse input
    void mouseMapping(int,int);
    double msX, msY, msZ;


    bool startClicked = false;
    bool newGameClicked = false;
    bool helpClicked = false;
    bool backClicked = false;
    std::vector<Button> buttons;


    Button button;


    int width, height;  // screen size
protected:


private:
};


#endif // _LANDINGPAGE_H
