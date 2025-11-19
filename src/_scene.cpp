#include "_scene.h"


_Scene::_Scene()
{
    //ctor
    isActive = false;


}


_Scene::~_Scene()
{
    //dtor
}


void _Scene::reset()
{
    isActive = false;
    backClicked = false;
}


void _Scene::reSizeScene(int width, int height)
{
    float aspectRatio = (float)width/(float)height;
    glViewport(0,0,width,height);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspectRatio,0.1,1000.0);


    this->width = GetSystemMetrics(SM_CXSCREEN);
    this->height= GetSystemMetrics(SM_CYSCREEN);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    myButtons->initButtons(width, height, buttons);
}


void _Scene::initGL()
{
    glShadeModel(GL_SMOOTH); // to handle GPU shaders
    glClearColor(0.0f,0.0f,0.0f,0.0f); // black background color
    glClearDepth(2.0f);         //depth test for layers
    glEnable(GL_DEPTH_TEST);    //activate depth test
    glDepthFunc(GL_LEQUAL);     // depth function type


    glEnable(GL_TEXTURE_2D);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


    myPrlx->parallaxInit("images/parallax3.jpg");
    pauseOverlay.init();


    mdl3D->initModel("models/Tekk/tris.md2");

    switch(selectedJet)
    {
    case 0: player.loadModel("models/jetA.md2"); break;
    case 1: player.loadModel("models/jetB.md2"); break;
    case 2: player.loadModel("models/jetC.md2"); break;
    }


    srand(time(NULL));


    for (int i = 0; i < 6; i++)
    {
        obstacles[i].x = 14.0f + (i * 9.0f);
        obstacles[i].y = -5.0f + ((rand() % 20 - 10) / 10.0f);
        obstacles[i].z = -20.0f;


        obstacles[i].size = 1.0f + ((rand() % 20 - 10) / 100.0f);
        obstacles[i].moveSpeed = 1.0f + ((rand() % 20 - 10) / 100.0f);
    }


}


void _Scene::drawScene()
{

    if (!isActive) return;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();




    glPushMatrix();
        glDisable(GL_DEPTH_TEST);
        glScalef(4.33, 4.33, 1);
        myPrlx->drawParallax(width, height);


        if (!sceneSwitcher->paused)
            myPrlx->prlxScrollAuto("left", dir);


        glEnable(GL_DEPTH_TEST);
    glPopMatrix();




    glPushMatrix();
        glTranslatef(0.0f, -5.0f + jump, -20.0f);
        glRotatef(charDir, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        glScalef(0.08f, 0.08f, 0.08f);


        if (!sceneSwitcher->paused)
        {
            mdl3D->Actions();
            mdl3D->Draw();
        }
    glPopMatrix();


    if (!sceneSwitcher->paused)
    {
        for (int i = 0; i < 6; i++)
        {
            obstacles[i].moveObstacle("left", speed);


            vec3 playerPos   = { 0.0f, -5.0f + jump, -20.0f };
            vec3 obstaclePos = { obstacles[i].x, obstacles[i].y, obstacles[i].z };


            bool hit = collisionCheck->isSphereCol(
                playerPos,
                obstaclePos,
                0.8f,
                obstacles[i].size,
                0.0f
            );

            if(hit){
                obstacles[i].active = false;
                playerHit = true;
            }
            if (obstacles[i].active)
            {
                glPushMatrix();
                obstacles[i].draw();
                glPopMatrix();


            }

        }
    }


    if (sceneSwitcher->paused)
        pauseOverlay.draw(width, height);




    bool allPassed = true;
    for (int i = 0; i < 6; i++)
    {
        if (obstacles[i].active && obstacles[i].x > -30.0f)
        {
            allPassed = false;
            break;
        }
    }


    if (allPassed)
    {
        std::cout << "Level Complete! Moving to next scene...\n";
        // sceneSwitcher->switchScene(SCENE_MENU);  // or whatever
        nextLevel = true;
    }
}




void _Scene::mouseMapping(int x, int y)
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








int _Scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_KEYDOWN:
            myInput->wParam = wParam;
            myInput->keyPressed(mdl3D);
            switch (wParam)
            {
                case VK_ESCAPE:
                    cout << "PAUSED" << endl;
                    break;
                case VK_RETURN:
                    if (sceneSwitcher->paused) {
                        //PostQuitMessage(0);
                        backClicked = true;
                        cout << "BACK";
                        sceneSwitcher->paused = false;
                    }
                case 68:    //D
                    dir = 0.005;
                    speed = 0.6;
                    charDir = 0;
                    break;
                case 65:    //A
                    dir = -0.005;
                    speed = -0.1;
                    charDir = 180;
                    break;
                case 32:    //space
                    jump = 5;
                    break;


            }
        break;


        case WM_KEYUP:
            dir = 0;
            myInput->wParam = wParam;
            mdl3D->actionTrigger=mdl3D->STAND;
            jump = 0;
            speed = 0.4f;
        break;


        case WM_LBUTTONDOWN:




             mouseMapping(LOWORD(lParam), HIWORD(lParam));


            break;


        case WM_RBUTTONDOWN:


            break;


         case WM_MBUTTONDOWN:




            break;


        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:


            break;


        case WM_MOUSEMOVE:


            break;
        case WM_MOUSEWHEEL:


            break;


        default:
            break;


    }
}




void _Scene::resetObstacles()
{
    srand(time(NULL));


    for (int i = 0; i < 6; i++)
    {
        obstacles[i].x = 14.0f + (i * 9.0f);
        obstacles[i].y = -5.0f + ((rand() % 20 - 10) / 10.0f);
        obstacles[i].z = -20.0f;


        obstacles[i].size = 1.0f + ((rand() % 20 - 10) / 100.0f);
        obstacles[i].moveSpeed = 1.0f + ((rand() % 20 - 10) / 100.0f);
    }


    playerHit = false;
}
