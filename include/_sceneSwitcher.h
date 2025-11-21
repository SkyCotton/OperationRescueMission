#pragma once
#include <_common.h>
#include <windows.h>


// keep the same enum name you used in main.cpp
// If you already have this enum in main.cpp, remove it there and include this header instead.
// (Or keep it here and include this file from main.cpp)
enum sceneState {
    LANDING_PAGE,
    MENU,
    HELP,
    LEVEL_ONE,
    LEVEL_TWO,
    LEVEL_THREE,
    PAUSE,
    LOCKER  // new jet locker scene
};


// forward declarations (good practice for headers)
class _LandingPage;
class _Menu;
class _Scene;
class _HelpPage;
class _Scene2;
class _Scene3;
class _lockerScene;


class _sceneSwitcher {
public:
    _sceneSwitcher(_LandingPage* lp, _Menu* m, _Scene* scene, _HelpPage* help, _Scene2* scene2, _Scene3* scene3, _lockerScene* l1);


    void update();
    void draw();
    void handleWinMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void setScene(sceneState next);
    sceneState current = LANDING_PAGE;


    bool paused = false;
    int pauseNum = 0;




    _LandingPage* landing;
    _Menu* menu;
    _Scene* scene;
    _HelpPage* help;
    _Scene2* scene2;
    _Scene3* scene3;
    _lockerScene* lockerScene;


private:
};

