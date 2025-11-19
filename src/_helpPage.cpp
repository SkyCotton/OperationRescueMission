#include "_helpPage.h"


_HelpPage::_HelpPage()
{
    button;
    isActive = false;
}


_HelpPage::~_HelpPage()
{
}


void _HelpPage::reSizeWindow(int width, int height)
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




    float buttonWidthRatio  = 0.25f;
    float buttonHeightRatio = 0.08f;


    button.w = width  * buttonWidthRatio;
    button.h = height * buttonHeightRatio;


    button.x = (width  - button.w) / 2;
    button.y = (height - button.h) / 2;


    myButtons->initButtons(width, height, buttons);


    buttons[BTN_NEWGAME].active = false;
    buttons[BTN_HELP].active = false;
    buttons[BTN_QUIT2].active = false;
    buttons[BTN_START].active = false;
    buttons[BTN_QUIT].active = false;
    buttons[BTN_BACK].active = true;
}


void _HelpPage::initGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(2.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);


    glEnable(GL_TEXTURE_2D);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


    myPrlx->parallaxInit("images/Air.jpg");
    myTex2->loadTexture("images/helpORM.png");
}




void _HelpPage::draw()
{
    if (!isActive) return;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    /////////////////////////////////////////////
    // Draw parallax background
    /////////////////////////////////////////////
    glPushMatrix();
    glScalef(4.33f, 4.33f, 1.0f);
    myPrlx->drawParallax(width, height);
    myPrlx->prlxScrollAuto("left", 0.001f);
    glPopMatrix();




    /////////////////////////////////////////////
    // Draw 2D help background overlay
    /////////////////////////////////////////////
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);  // bottom-left origin


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();


    glDisable(GL_DEPTH_TEST);          // draw on top of 3D scene
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    myTex2->bindTexture();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


    float widthPercent  = 0.8f;
    float heightPercent = 0.8f;


    float quadW = width  * widthPercent;
    float quadH = height * heightPercent;


    float x0 = (width - quadW) / 2.0f;
    float y0 = (height - quadH) / 2.0f;


    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x0, y0);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x0 + quadW, y0);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x0 + quadW, y0 + quadH);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x0, y0 + quadH);
    glEnd();


    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);


    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}




void _HelpPage::mouseMapping(int x, int y)
{
    GLint viewPort[4];
    GLdouble ModelViewM[16];
    GLdouble projectionM[16];
    GLfloat winX,winY,winZ;


    glGetDoublev(GL_MODELVIEW_MATRIX, ModelViewM);
    glGetDoublev(GL_PROJECTION_MATRIX, projectionM);
    glGetIntegerv(GL_VIEWPORT, viewPort);


    winX = (GLfloat)x;
    winY = (GLfloat)y;


    glReadPixels(x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
    gluUnProject(winX, winY, winZ, ModelViewM, projectionM, viewPort, &msX, &msY, &msZ);
}


int _HelpPage::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_MOUSEMOVE: {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            break;
        }
        case WM_LBUTTONDOWN: {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            break;
        }
        case WM_LBUTTONUP: {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            break;
        }
        case WM_KEYDOWN: {
            //myButtons->handleKeyboardPress(wParam, buttons, startClicked, newGameClicked, helpClicked, backClicked, isActive, SCENE_LANDING);
            switch (wParam)
            {
                case VK_ESCAPE:
                    backClicked = true;
                    cout << "BACK";
            }
            //cout << wParam << endl;
        default:
            break;
        }
    }
    return 0;
}
