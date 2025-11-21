#include "_scene.h"
#include<GL/glu.h>

_Scene::_Scene()
{
    currentPageState = LANDING_PAGE;
}

_Scene::~_Scene()
{
    //dtor
}

void _Scene::reSizeScene(int width, int height)
{
    float aspectRatio = (float)width/(float)height;// keep track of the ratio
    glViewport(0,0,width,height); // adjust my viewport

    glMatrixMode(GL_PROJECTION);  // To setup ptrojection
    glLoadIdentity();             // calling identity matrix
    gluPerspective(45, aspectRatio,0.1,10000.0); // setting perspective projection

    this->width = GetSystemMetrics(SM_CXSCREEN);
    this->height= GetSystemMetrics(SM_CYSCREEN);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();             // calling identity matrix
}

void _Scene::initGL()
{
    glShadeModel(GL_SMOOTH); // to handle GPU shaders
    glClearColor(0.0f,0.0f,0.0f,0.0f); // black background color
    glClearDepth(2.0f);         //depth test for layers
    glEnable(GL_DEPTH_TEST);    //activate depth test
    glDepthFunc(GL_LEQUAL);     // depth function type

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    skyBox->skyBoxInit();
    gameCamera->camInit();
    // gameTimer->startTime(); // this timer actually starts when the _Scene object is constructed, but ill keep for debugging
    /*
    _targets *testTarget = &targetPool[0];
    testTarget->live = true;
    testTarget->pos.x = 0.0f;
    testTarget->pos.y = 2.0f;
    testTarget->pos.z = -20.0f;
    testTarget->speed = 0.0f; // stay still!
    */ // test target block commented out

    lastMouseX = width / 2;
    lastMouseY = height / 2;

    landingPageTexID = texLoader.loadTexture("images/landing_page.jpg");
    mainMenuPageTexID = texLoader.loadTexture("images/main_menu.jpg");
    helpPageTexID = texLoader.loadTexture("images/help_page.png"); // not help but help_page.png
    newGameButtonTexID = texLoader.loadTexture("images/new_game.png");
    helpButtonTexID = texLoader.loadTexture("images/help.jpg");
    exitButtonTexID = texLoader.loadTexture("images/exit.jpg");
    pauseTexID = texLoader.loadTexture("images/pause.png");
    // loading the model
    playerModel->initModel("models/UFO/tris.md2");
}

void _Scene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//clear bits in each itteration
    glLoadIdentity();             // calling identity matrix

    switch(currentPageState)
    {
        case LANDING_PAGE:
            start2D();
            drawTexture(landingPageTexID, 0, 0, this->width, this->height);
            end2D();
        break;

        case MAIN_MENU:
            start2D();

            drawTexture(mainMenuPageTexID, 0, 0, this->width, this->height);

            menuButtons.clear();
            drawButton(newGameButtonTexID, 1200, 300, 200, 50, Button::BUTTON_NEW_GAME);
            drawButton(helpButtonTexID,    700, 300, 200, 50, Button::BUTTON_HELP);
            drawButton(exitButtonTexID,    100, 300, 200, 50, Button::BUTTON_EXIT);

            end2D();
        break;

        case HELP_PAGE:
            start2D();

            drawTexture(helpPageTexID, 0, 0, this->width, this->height);

            end2D();
        break;

        case GAME_ACTIVE:
        case GAME_PAUSED:
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            float camDist = 15.0f; // how far behind the jet
            float camHeight = 5.0f; // how high above the jet
            float rad = playerModel->dirAngleZ * 3.14159f / 180.0f;

            gameCamera->eye.x = playerModel->pos.x - sin(rad) * camDist;
            gameCamera->eye.z = playerModel->pos.z + cos(rad) * camDist;
            gameCamera->eye.y = playerModel->pos.y + camHeight;

            // the camera looks at the jet
            gameCamera->des.x = playerModel->pos.x;
            gameCamera->des.y = playerModel->pos.y;
            gameCamera->des.z = playerModel->pos.z;

            // 2. APPLY CAMERA
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gameCamera->setUpCamera();

            glPushMatrix();
                glTranslatef(gameCamera->eye.x, gameCamera->eye.y, gameCamera->eye.z);
                skyBox->drawSkyBox();
            glPopMatrix();

            glDisable(GL_TEXTURE_2D);
            glDisable(GL_LIGHTING);
            // start of the grid
            glBegin(GL_LINES);
            glColor3f(0.0f, 1.0f, 0.0f);
            for (int i = -50; i <= 50; i += 2)
            {
                glVertex3f((float)i, 0.0f, -50.0f);
                glVertex3f((float)i, 0.0f, 50.0f);

                glVertex3f(-50.0f, 0.0f, (float)i);
                glVertex3f(50.0f, 0.0f, (float)i);
            }
            glEnd();
            // end of the grid
            // playerModel drawing
            glPushMatrix();
                glTranslatef(playerModel->pos.x, playerModel->pos.y, playerModel->pos.z);

                // rotate the Jet to face its direction
                // rotate around Y-axis (Up) based on dirAngleZ
                glTranslatef(0.0f, 1.0f, 0.0f); // trying to adjust playerModel pos
                glRotatef(playerModel->dirAngleZ, 0, 1, 0);

                glScalef(0.1f, 0.1f, 0.1f);
                glRotatef(-90, 1, 0, 0);
                glRotatef(-90, 0, 0, 1);

                glEnable(GL_TEXTURE_2D);
                glColor3f(1.0f, 1.0f, 1.0f); // Ensure white color for texture

                playerModel->Draw(); // Draw the jet

                glDisable(GL_TEXTURE_2D);
            glPopMatrix();
            if (currentPageState == GAME_ACTIVE)
            {
                // spawn targets
                if (gameTimer->getTicks() > 2000)
                {
                    for (int i = 0; i < 20; i++)
                    {
                        if (!targetPool[i].live)
                        {
                            targetPool[i].initTarget();
                            break;
                        }
                    }
                    gameTimer->reset();
                }
                // update targets
                for (int i = 0; i < 20; i++)
                {
                    if (targetPool[i].live)
                    {
                        targetPool[i].updateTarget();
                    }
                }
                // update bullets
                for (int i = 0; i < 50; i++)
                {
                    if (bulletPool[i].live)
                    {
                        bulletPool[i].bulletActions();
                    }
                }
                // collision checking
                for (int i = 0; i < 50; i++)
                {
                    if(!bulletPool[i].live) continue; // if a bullet is dead it can't collide with anything

                    for (int j = 0; j < 20; j++)
                    {
                        if (!targetPool[j].live) continue; // if the target is already dead no point in checking collision
                        if (col.isSphereCol(bulletPool[i].pos, targetPool[j].pos, 0.5f, targetPool[j].radius, 0.1f))
                        {
                            bulletPool[i].actionTrigger = _bullets::HIT; // hit consequences
                            targetPool[j].live = false;
                        }
                    }
                }
            }
            // bullet drawing
            for (int i = 0; i < 50; i++)
            {
                if (bulletPool[i].live)
                {
                    bulletPool[i].drawBullet();
                }
            }
            // target drawing
            for (int i = 0; i < 20; i++)
            {
                if (targetPool[i].live)
                {
                    targetPool[i].drawTarget();
                }
            }
            glEnable(GL_TEXTURE_2D); // bringing back 2D
            if (currentPageState == GAME_PAUSED)
            {
                start2D();

                drawTexture(pauseTexID, (this->width / 2) - 200, (this->height / 2) - 100, 400, 200);

                end2D();
            }
        break;
    }
}
void _Scene::drawTexture(GLuint texID, int x, int y, int w, int h)
{
    glBindTexture(GL_TEXTURE_2D, texID); // bind texture

    glColor4f(1.0f, 1.0f, 1.0f, 0.99f); // .99 to help with blending

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2i(x, y);

        glTexCoord2f(1.0f, 1.0f);
        glVertex2i(x + w, y);

        glTexCoord2f(1.0f, 0.0f);
        glVertex2i(x + w, y + h);

        glTexCoord2f(0.0f, 0.0f);
        glVertex2i(x, y + h);
    glEnd();
}
void _Scene::drawButton(GLuint textureID, int x, int y, int w, int h, Button::ActionId id)
{
    Button btn = {x, y, w, h, id};
    menuButtons.push_back(btn);
    drawTexture(textureID, x, y, w, h);
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

void _Scene::fireBullet()
{
    for (int i = 0; i < 50; i++)
    {
        if (!bulletPool[i].live)
        {
            _bullets *b = &bulletPool[i];

            float rad = playerModel->dirAngleZ * 3.14159f / 180.0f;

            // calculate the normalized direction vector
            // forward is -Z in our coordinate system
            vec3 modelForward;
            modelForward.x = sin(rad);
            modelForward.y = 0.0f;     // model currently doesn't aim up/down
            modelForward.z = -cos(rad);

            float noseOffset = 2.0f; // so bullets don't spawn inside the playerModel

            b->src.x = playerModel->pos.x + (modelForward.x * noseOffset);
            b->src.y = playerModel->pos.y; // Same height as model
            b->src.z = playerModel->pos.z + (modelForward.z * noseOffset);

            b->pos = b->src; // init current position

            float bulletSpeed = 0.5f; // units per frame

            b->velocity.x = modelForward.x * bulletSpeed;
            b->velocity.y = modelForward.y * bulletSpeed;
            b->velocity.z = modelForward.z * bulletSpeed;

            b->live = true;
            b->actionTrigger = _bullets::SHOOT;
            b->t = 0;

            break; // break after one bullet
        }
    }
}
int _Scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        {
            if (currentPageState == LANDING_PAGE &&
                 (uMsg == WM_LBUTTONDOWN))
            {
                currentPageState = MAIN_MENU;
            } else if (currentPageState == MAIN_MENU && uMsg == WM_LBUTTONDOWN)
            {
                int mouseX = LOWORD(lParam);
                int mouseY = HIWORD(lParam);
                // coord flipping due to the different ways that OpenGL and Windows calculate screen positions
                int glY = this->height - mouseY;
                Button::ActionId clickedAction = Button::BUTTON_NONE; // default button action state that does nothing

                for (const auto& btn : menuButtons)
                {
                    if (mouseX >= btn.x && mouseX <= (btn.x + btn.width) &&
                        glY >= btn.y && glY <= (btn.y + btn.height))
                    {
                        clickedAction = btn.action;
                    }
                }
                if (clickedAction != Button::BUTTON_NONE)
                {
                    menuButtons.clear();
                    if (clickedAction == Button::BUTTON_NEW_GAME)
                    {
                        currentPageState = GAME_ACTIVE;
                    } else if (clickedAction == Button::BUTTON_EXIT)
                    {
                        PostQuitMessage(0); // uses windows to close entire application
                    } else if (clickedAction == Button::BUTTON_HELP)
                    {
                        currentPageState = HELP_PAGE;
                    }
                }
            } else if (currentPageState == GAME_ACTIVE)
            {
                if (uMsg == WM_LBUTTONDOWN)
                {
                    fireBullet();
                    mouseMapping(LOWORD(lParam), HIWORD(lParam));
                }
            }
            break;
        }

        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE)
            {
                if (currentPageState == GAME_ACTIVE)
                {
                    currentPageState = GAME_PAUSED;
                } else if (currentPageState == GAME_PAUSED)
                {
                    currentPageState = GAME_ACTIVE;
                } else if (currentPageState == HELP_PAGE)
                {
                    currentPageState = MAIN_MENU;
                }
                break;
                return 0; // signals windows and prevents default process closure behavior
            } else if (wParam == VK_RETURN) // handle return AKA Enter key
            {
                if (currentPageState == LANDING_PAGE)
                {
                    currentPageState = MAIN_MENU;
                } else if (currentPageState == GAME_PAUSED)
                {
                    PostQuitMessage(0);
                }
                break;
                return 0;
            } else if (currentPageState == GAME_ACTIVE) // process arrow keys if the game is active
            {
                float rad = playerModel->dirAngleZ * 3.14159f / 180.0f;
                float speed = 0.5f;

                if (wParam == 'W')
                {
                    // adjust signs if playerModel movement is inverted
                    playerModel->pos.x += sin(rad) * speed; // 0.5f is speed
                    playerModel->pos.z -= cos(rad) * speed;
                } else if (wParam == 'S')
                {
                    playerModel->pos.x -= sin(rad) * speed;
                    playerModel->pos.z += cos(rad) * speed;
                } else if (wParam == 'D')
                {
                    playerModel->dirAngleZ -= 2.0f;
                } else if (wParam == 'A')
                {
                    playerModel->dirAngleZ += 2.0f;
                } else if (wParam == VK_LEFT)
                {
                    gameCamera->rotAngle.x -= 2.0f;
                    gameCamera->rotateXY();
                } else if (wParam == VK_RIGHT)
                {
                    gameCamera->rotAngle.x += 2.0f;
                    gameCamera->rotateXY();
                } else if (wParam == VK_UP)
                {
                    gameCamera->rotAngle.y += 2.0f;
                    if (gameCamera->rotAngle.y > 89.0f)
                    {
                        gameCamera->rotAngle.y = 89.0f; // clamping the rotation angle so it does not flip
                    }
                    gameCamera->rotateXY();
                } else if (wParam == VK_DOWN)
                {
                    gameCamera->rotAngle.y -= 2.0f;
                    if (gameCamera->rotAngle.y < -89.0f)
                    {
                        gameCamera->rotAngle.y = -89.0f;
                    }
                    gameCamera->rotateXY();
                }
            } else if (currentPageState == MAIN_MENU)
            {
                if (wParam == 'N')
                {
                    currentPageState = GAME_ACTIVE;
                } else if (wParam == 'H')
                {
                    currentPageState = HELP_PAGE;
                } else if (wParam == 'E')
                {
                    PostQuitMessage(0);
                }
            }
        break;

        case WM_KEYUP:
        break;

        case WM_MBUTTONDOWN:
        break;

        case WM_MBUTTONUP:
        break;

        case WM_MOUSEMOVE:
            if (currentPageState == GAME_ACTIVE)
            {
                int mouseX = LOWORD(lParam);
                int mouseY = HIWORD(lParam);

                float deltaX = (float)(mouseX - lastMouseX);
                float deltaY = (float)(mouseY - lastMouseY);

                gameCamera->rotAngle.x += deltaX * 0.1f;
                gameCamera->rotAngle.y -= deltaY * 0.1f; // subtraction due to windows coords (or not)

                if (gameCamera->rotAngle.y > 89.0f)
                {
                    gameCamera->rotAngle.y = 89.0f; // more clamping
                }
                if (gameCamera->rotAngle.y < -89.0f)
                {
                    gameCamera->rotAngle.y = -89.0f;
                }
                gameCamera->rotateXY();
                // windows mouse logic
                POINT center = {width / 2, height / 2};
                ClientToScreen(hWnd, &center);
                SetCursorPos(center.x, center.y);
                lastMouseX = width / 2;
                lastMouseY = height / 2;
            }
        break;

        case WM_MOUSEWHEEL:
        break;

        default:
        break;
    }
}
void _Scene::start2D()
{
    glDisable(GL_DEPTH_TEST);   // not needed in 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();             // pushes 3D scene
    glLoadIdentity();
    gluOrtho2D(0, this->width, 0, this->height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}
void _Scene::end2D()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix(); // restore 3D

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix(); // restore modelview 3D
    glEnable(GL_DEPTH_TEST);
}
