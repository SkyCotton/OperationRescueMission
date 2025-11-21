#include "_menu.h"


_Menu::_Menu()
{
    //ctor
    button;// = {0, 0, 0, 0};
    isActive = false;
}


_Menu::~_Menu()
{
    //dtor
}


void _Menu::reSizeWindow(int width, int height)
{
    this->width = width;
    this->height = height;


    float aspectRatio = (float)width / (float)height;
    glViewport(0, 0, width, height);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspectRatio, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    /**
    float buttonWidthRatio  = 0.25f;  // 25% of screen width
    float buttonHeightRatio = 0.08f;  // 8% of screen height


    button.w = width  * buttonWidthRatio;
    button.h = height * buttonHeightRatio;


    button.x = (width  - button.w) / 2; // center horizontally
    button.y = (height - button.h) / 2; // center vertically


    myButtons->initButtons(width, height, buttons);


    buttons[BTN_NEWGAME].active = true;
    buttons[BTN_HELP].active = true;
    buttons[BTN_QUIT2].active = true;
    buttons[BTN_START].active = false;
    buttons[BTN_QUIT].active = false;
    **/
}




void _Menu::initGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(2.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);


    glEnable(GL_TEXTURE_2D);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


    myPrlx->parallaxInit("images/Plane.jpg");
    myTex->loadTexture("images/mainMenu.png");
}


void _Menu::draw()
{
    if (!isActive) return;


    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();




    ////////////////////////////////////////////////////////
    //draw parallax
    ////////////////////////////////////////////////////////
    glPushMatrix();
    glScalef(4.33, 4.33, 1);
    myPrlx->drawParallax(width, height);
    myPrlx->prlxScrollAuto("left", 0.001);
    glPopMatrix();




    ////////////////////////////////////////////////////////
    //draw button
    ////////////////////////////////////////////////////////
    /**glDisable(GL_DEPTH_TEST);
    for (auto& b : buttons) {
        if (b.scene == SCENE_MENU) {
            myButtons->drawButton(b, nullptr, width, height);
        }
    }
    glEnable(GL_DEPTH_TEST);**/






    /////////////////////////////////////////////
    //Info
    /////////////////////////////////////////////
    // Draw 2D quad overlay
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);


    glEnable(GL_TEXTURE_2D);
    myTex->bindTexture();
    glColor4f(1.0f,1.0f,1.0f,1.0f);


    float widthPercent  = 0.6f;
    float heightPercent = 0.5f;


    float quadW = width  * widthPercent;
    float quadH = height * heightPercent;


    float horizontalOffset = 0;
    float x0 = (width - quadW) / 2.0f + horizontalOffset;


    float verticalOffset = 0;
    float y0 = (height - quadH) / 2.0f + verticalOffset;


    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,1.0f); glVertex2f(x0, y0);
        glTexCoord2f(1.0f,1.0f); glVertex2f(x0+quadW, y0);
        glTexCoord2f(1.0f,0.0f); glVertex2f(x0+quadW, y0+quadH);
        glTexCoord2f(0.0f,0.0f); glVertex2f(x0, y0+quadH);
    glEnd();


    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);


    glPopMatrix(); // MODELVIEW
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);




}




void _Menu::mouseMapping(int x, int y)
{
    GLint viewPort[4];
    GLdouble ModelViewM[16];
    GLdouble projectionM[16];
    GLfloat winX,winY,winZ;


    glGetDoublev(GL_MODELVIEW_MATRIX, ModelViewM);
    glGetDoublev(GL_PROJECTION_MATRIX,projectionM);
    glGetIntegerv(GL_VIEWPORT,viewPort);


    winX =(GLfloat)x;
    winY = (GLfloat)y;


    glReadPixels(x,(int)winY,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&winZ);
    gluUnProject(winX,winY,winZ,ModelViewM,projectionM,viewPort,&msX,&msY,&msZ);
}








int _Menu::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_MOUSEMOVE: {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            //myButtons->handleMouseMove(x, y, height, buttons, SCENE_MENU);
            break;
        }
        case WM_LBUTTONDOWN: {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            //myButtons->handleMouseClick(true, x, y, height, buttons, startClicked, newGameClicked, helpClicked, backClicked, isActive, SCENE_MENU);
            break;
        }
        case WM_LBUTTONUP: {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            //myButtons->handleMouseClick(false, x, y, height, buttons, startClicked, newGameClicked, helpClicked, backClicked, isActive, SCENE_MENU);
            break;
        }
        case WM_KEYDOWN: {
            //myButtons->handleKeyboardPress(wParam, buttons, startClicked, newGameClicked, helpClicked, backClicked, isActive, SCENE_LANDING);
            switch (wParam)
            {
                case VK_RETURN:
                    startClicked = true;
                    cout << "START" << endl;
                    break;
                case 78:
                    newGameClicked = true;
                    cout << "NEWGAME" << endl;
                    break;
                case 72:
                    helpClicked = true;
                    cout << "HELP" << endl;
                    break;
                case VK_ESCAPE:
                    PostQuitMessage(0);
                    break;
            }
            cout << wParam << endl;
        default:
            break;
        }
    }
    return 0;
}
