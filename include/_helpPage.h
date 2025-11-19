#ifndef _HELPPAGE_H
#define _HELPPAGE_H

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


class _HelpPage
{
public:
    _HelpPage();           // constructor
    virtual ~_HelpPage();  // destructor


    _parallax *myPrlx = new _parallax();
    _textureLoader *myTex = new _textureLoader();
    _textureLoader *myTex2 = new _textureLoader();
    _buttons* myButtons = new _buttons();


    int clickCnt = 0;
    bool isActive;


    void reSizeWindow(int width, int height);
    void initGL();
    void draw();
    int winMsg(HWND, UINT, WPARAM, LPARAM);
    void mouseMapping(int, int);


    double msX, msY, msZ;


    bool startClicked = false;
    bool newGameClicked = false;
    bool helpClicked = false;
    bool backClicked = false;
    std::vector<Button> buttons;


    Button button;


    int width, height;
protected:


private:
};




#endif // _HELPPAGE_H
