#include "_lockerScene.h"

_lockerScene::_lockerScene()
{
    //ctor
}

_lockerScene::~_lockerScene()
{
    //dtor
}
void _lockerScene::initGL()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    myPrlx->parallaxInit("images/Plane.jpg");

    // TEMPORARY PLACEHOLDERS
    jetTex[0]->loadTexture("images/jet1.png");
    jetTex[1]->loadTexture("images/jet2.png");
    jetTex[2]->loadTexture("images/jet3.png");

     // layout: three jets in the middle of the screen
    float jetW    = 256.0f;
    float jetH    = 256.0f;
    float spacing = 80.0f;

    float totalW = 3 * jetW + 2 * spacing;
    float startX = (width - totalW) / 2.0f;
    float y      = height * 0.5f - jetH * 0.5f;

    for (int i = 0; i < 3; ++i)
    {
        jetRect[i].x = startX + i * (jetW + spacing);
        jetRect[i].y = y;
        jetRect[i].w = jetW;
        jetRect[i].h = jetH;
    }

    // confirm button below jets
    confirmRect.w = 220.0f;
    confirmRect.h = 60.0f;
    confirmRect.x = (width - confirmRect.w) / 2.0f;
    confirmRect.y = y - 100.0f; // a bit below the jets

    startMission = false;
    selectedJet  = -1;

}

void _lockerScene::reSizeScene(int w, int h)
{
    float aspectRatio = (float)w / (float)h;
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspectRatio, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    width = w;
    height = h;



}

void _lockerScene::draw()
{
 if (!isActive) return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // draw background parallax (your existing parallax draw)
    myPrlx->drawBack();

    // switch to 2D overlay for jets & UI
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // draw jets
    for (int i = 0; i < 3; ++i)
    {
        const Rect& r = jetRect[i];

        jetTex[i]->bindTexture();
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(r.x,         r.y        );
            glTexCoord2f(1, 0); glVertex2f(r.x + r.w,   r.y        );
            glTexCoord2f(1, 1); glVertex2f(r.x + r.w,   r.y + r.h  );
            glTexCoord2f(0, 1); glVertex2f(r.x,         r.y + r.h  );
        glEnd();

        // highlight selected jet with a colored border
        if (selectedJet == i)
        {
            glDisable(GL_TEXTURE_2D);
            glLineWidth(4.0f);
            glColor3f(1.0f, 1.0f, 0.0f); // yellow border

            glBegin(GL_LINE_LOOP);
                glVertex2f(r.x - 5,       r.y - 5);
                glVertex2f(r.x + r.w + 5, r.y - 5);
                glVertex2f(r.x + r.w + 5, r.y + r.h + 5);
                glVertex2f(r.x - 5,       r.y + r.h + 5);
            glEnd();

            glEnable(GL_TEXTURE_2D);
            glColor3f(1.0f, 1.0f, 1.0f); // reset
        }
    }

    // confirm button (simple colored quad)
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(confirmRect.x,                confirmRect.y);
        glVertex2f(confirmRect.x + confirmRect.w, confirmRect.y);
        glVertex2f(confirmRect.x + confirmRect.w, confirmRect.y + confirmRect.h);
        glVertex2f(confirmRect.x,                confirmRect.y + confirmRect.h);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);

    // TODO: if you want text on the button, you can add bitmap text here

    // restore previous matrices
    glPopMatrix();                // MODELVIEW
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

}
void _lockerScene::update()
{
     // When user clicks jet 1
    if (jetButton1.isClicked(myInputs->mouseX, myInputs->mouseY))
        selectedJet = 0;

    // jet 2
    if (jetButton2.isClicked(myInputs->mouseX, myInputs->mouseY))
        selectedJet = 1;

    // jet 3
    if (jetButton3.isClicked(myInputs->mouseX, myInputs->mouseY))
        selectedJet = 2;

    // Confirm button → allow game to start
    if (confirmBtn.isClicked(myInputs->mouseX, myInputs->mouseY))
    {
        if(selectedJet != -1)
            startMission = true;
    }

}
int _lockerScene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (!isActive) return 0;

    switch (uMsg)
    {
        case WM_LBUTTONDOWN:
        {
            int mx = LOWORD(lParam);
            int my = HIWORD(lParam);

            // pick jet
            for (int i = 0; i < 3; ++i)
            {
                if (insideRect(mx, my, jetRect[i], height))
                    selectedJet = i;
            }

            // confirm
            if (insideRect(mx, my, confirmRect, height) && selectedJet != -1)
            {
                startMission = true;

                // go to Level One
                if (sceneSwitcher)
                    sceneSwitcher->setScene(LEVEL_ONE);
            }
        }
        break;

        case WM_KEYDOWN:
        {
            if (wParam == '1') selectedJet = 0;
            if (wParam == '2') selectedJet = 1;
            if (wParam == '3') selectedJet = 2;

            if (wParam == VK_RETURN && selectedJet != -1)
            {
                startMission = true;
                if (sceneSwitcher)
                    sceneSwitcher->setScene(LEVEL_ONE);
            }

            if (wParam == VK_ESCAPE)
            {
                // back to menu
                if (sceneSwitcher)
                    sceneSwitcher->setScene(MENU);
            }
        }
        break;
    }
    return 0;

}
