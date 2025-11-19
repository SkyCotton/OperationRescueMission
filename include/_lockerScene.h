#ifndef _LOCKERSCENE_H
#define _LOCKERSCENE_H

#pragma once
#include <_common.h>
#include <_parallax.h>
#include <_buttons.h>
#include <_inputs.h>
#include <vector>


class _lockerScene
{
    public:
        _lockerScene();
        virtual ~_lockerScene();

        bool isActive = false;
        bool backClicked = false;
        bool confirmSelection = false;
        bool startMission = false;   // when player hits confirm becomes true


        int width, height;
        int selectedJet = -1; // 0,1,2

        std::vector<Button> buttons; // to create clickable jets
        _buttons *myButtons = new _buttons();
        _parallax *myPrlx = new _parallax();
        _inputs *myInputs = new _inputs();
        _sceneSwitcher *sceneSwitcher = nullptr;

        void initGL();
        void reSizeScene(int w, int h);
        void draw();
        void update();
        int winMsg(HWND, UINT, WPARAM, LPARAM);

    protected:

    private:
        //hit testing
        struct Rect {
            float x,y,w,h;
        };
        Rect jetRec[3];
        Rect confirmRect;

        int width = 0;
        int height = 0;

        _parallax* myPrlx;
        _textureLoader* jetTex[3];
};

#endif // _LOCKERSCENE_H
