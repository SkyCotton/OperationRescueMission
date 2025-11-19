#include "_sceneSwitcher.h"
#include "_landingPage.h"
#include "_menu.h"
#include "_scene.h"
#include "_helpPage.h"
#include "_scene2.h"
#include "_scene3.h"
#include "_lockerScene.h"


// ctor
_sceneSwitcher::_sceneSwitcher(_LandingPage* lp, _Menu* m, _Scene* s, _HelpPage* h, _Scene2* s2, _Scene3* s3, _lockerScene* l1)
    : landing(lp), menu(m), scene(s), help(h), scene2(s2), scene3(s3), lockerScene(l1)
{
    // start on landing page
    if (landing) landing->isActive = true;
    if (menu)    menu->isActive    = false;
    if (scene)   scene->isActive   = false;
    if (help)    help->isActive    = false;
    if (scene2)  scene2->isActive  = false;
    if (scene3)  scene3->isActive  = false;
    if (lockerScene) lockerScene->isActive = false;
}


void _sceneSwitcher::setScene(sceneState newScene)
{
    // deactivate scenes
    landing->isActive = false;
    menu->isActive    = false;
    scene->isActive   = false;
    help->isActive    = false;
    scene2->isActive  = false;
    scene3->isActive  = false;
    lockerScene->isActive = false;


    // deactivate ALL buttons first
    for (auto& b : landing->buttons) b.active = false;
    for (auto& b : menu->buttons)    b.active = false;
    for (auto& b : scene->buttons)   b.active = false;
    for (auto& b : help->buttons)    b.active = false;
    for (auto& b : scene2->buttons)  b.active = false;
    for (auto& b : scene3->buttons)  b.active = false;
    for (auto& b : lockerScene->buttons) b.active = false;


    switch(newScene)
    {
        case LANDING_PAGE:
            landing->isActive = true;
            for (auto& b : landing->buttons)
                b.active = (b.scene == LANDING_PAGE);
            break;


        case MENU:
            menu->isActive = true;
            for (auto& b : menu->buttons)
                b.active = (b.scene == MENU);
            break;


        case LOCKER:
            lockerScene->isActive = true;
            for(auto& b : lockerScene->buttons)
                b.active = (b.scene == LOCKER);
            break;

        case LEVEL_ONE:
            scene->isActive = true;
            for (auto& b : scene->buttons)
                b.active = (b.scene == LEVEL_ONE);
            break;


        case HELP:
            help->isActive = true;
            for (auto& b : help->buttons)
                b.active = (b.scene == HELP);
            break;


        case LEVEL_TWO:
            scene2->isActive = true;
            for (auto& b : scene2->buttons)
                b.active = (b.scene == LEVEL_TWO);
            break;
        case LEVEL_THREE:
            scene3->isActive = true;
            for (auto& b : scene3->buttons)
                b.active = (b.scene == LEVEL_THREE);
            break;
    }


    current = newScene;
}




void _sceneSwitcher::update() {
    // Landing -> Menu
    if (landing && landing->isActive && landing->startClicked) {
        setScene(MENU);
        landing->startClicked = false;
    }


    // Menu -> Locker
    if (menu && menu->isActive && menu->newGameClicked) {
        menu->newGameClicked = false;
        setScene(LOCKER);

    }

    // Locker -> Level One (after jet selected)
    if(lockerScene && lockerScene->isActive && lockerScene->startMission){
        lockerScene->startMission = false;

        scene->selectedJet = lockerScene->selectedJet;  // int /0/1/2
        scene->resetObstacles();
        setScene(LEVEL_ONE);

    }


    // Menu -> Help Page
    if (menu && menu->isActive && menu->helpClicked) {
        setScene(HELP);
        menu->helpClicked = false;
    }


    // Help Page -> Menu
    if (help->backClicked)
    {
        help->backClicked = false;
        help->isActive = false;
        menu->isActive = true;


        setScene(MENU);
    }


    if (scene->backClicked)
    {
        scene->backClicked = false;
        scene->isActive = false;
        menu->isActive = true;
        pauseNum = 0;


        setScene(MENU);
    }


    if (scene->nextLevel)
    {
        scene->nextLevel = false;
        scene->isActive = false;
        scene2->isActive = true;


        setScene(LEVEL_TWO);
    }
    if (scene2->nextLevel)
    {
        scene2->nextLevel = false;
        scene2->isActive = false;
        scene3->isActive = true;


        setScene(LEVEL_THREE);
    }
    if (scene3->nextLevel){
        scene3->nextLevel = false;
        scene3->isActive = false;

        std::cout << "All Levels Completed!";
        setScene(MENU);
    }
}


void _sceneSwitcher::draw() {
    switch (current) {
        case LANDING_PAGE:
            if (landing && landing->isActive) landing->draw();
            break;
        case MENU:
            if (menu && menu->isActive) menu->draw();
            break;
        case LOCKER:
            if(lockerScene && lockerScene->isActive)lockerScene->draw();
            break;
        case LEVEL_ONE:
            if (scene && scene->isActive) scene->drawScene();
            break;
        case LEVEL_TWO:
            if (scene2 && scene2->isActive) scene2->drawScene();
            break;
        case LEVEL_THREE:
            if (scene3 && scene3->isActive) scene3->drawScene();
            break;
        case PAUSE:
        case HELP:
            if (help && help->isActive) help->draw();
        default:
            break;
    }
}


void _sceneSwitcher::handleWinMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (current)
    {
        case LANDING_PAGE:
            if (landing) landing->winMsg(hWnd, uMsg, wParam, lParam);
            break;


        case MENU:
            if (menu) menu->winMsg(hWnd, uMsg, wParam, lParam);
            break;

        case LOCKER:
            if(lockerScene) lockerScene->winMsg(hWnd, uMsg, wParam, lParam);
            break;

        case LEVEL_ONE:
            if (scene) scene->winMsg(hWnd, uMsg, wParam, lParam);
            break;


        case HELP:
            if (help) help->winMsg(hWnd, uMsg, wParam, lParam);
            break;
        case LEVEL_TWO:
            if (scene2) scene2->winMsg(hWnd, uMsg, wParam, lParam);
            break;
        case LEVEL_THREE:
            if (scene3) scene3->winMsg(hWnd, uMsg, wParam, lParam);
            break;
    }
}

