#include "_skybox.h"

_skyBox::_skyBox()
{
    //ctor
}

_skyBox::~_skyBox()
{
    //dtor
}
void _skyBox::skyBoxInit()
{
    xMin = yMin =0;
    xMax = yMax =1;

    glGenTextures(7,tex);
    tex[0] = textures->loadTexture("images/skybox/front.png");
    tex[1] = textures->loadTexture("images/skybox/back.png");
    tex[2] = textures->loadTexture("images/skybox/top.png");
    tex[3] = textures->loadTexture("images/skybox/bottom.png");
    tex[4] = textures->loadTexture("images/skybox/left.png");
    tex[5] = textures->loadTexture("images/skybox/right.png");

    rotation.x= rotation.y=rotation.z = 0;
    pos.x = pos.y =0;
    pos.z = -9.0;

    boxSize.x = 30.0f;
    boxSize.y = 5.0f;
    boxSize.z = 30.0f;


}

void _skyBox::drawSkyBox()
{
    float MAX_SIZE{5000.0f};

   glDisable(GL_LIGHTING); // if you are using room comment this line
   glDisable(GL_CULL_FACE);

   glDepthMask(GL_FALSE);

   glPushMatrix();

   glColor3f(1.0,1.0,1.0);// set environment to white
   // glScalef(boxSize.x,boxSize.y,boxSize.z); // removed for skybox testing

   glRotatef(rotation.x, 1,0,0);
   glRotatef(rotation.y, 0,1,0);
   glRotatef(rotation.z, 0,0,1);

   //front Wall

   glBindTexture(GL_TEXTURE_2D,tex[0]);
   //glNormal3f()  use this only if you are setting room with lighting
   glBegin(GL_QUADS);
    glTexCoord2f(xMin,yMin); glVertex3f(-MAX_SIZE, MAX_SIZE, MAX_SIZE);
    glTexCoord2f(xMax,yMin); glVertex3f(MAX_SIZE, MAX_SIZE, MAX_SIZE);
    glTexCoord2f(xMax,yMax); glVertex3f(MAX_SIZE,-MAX_SIZE, MAX_SIZE);
    glTexCoord2f(xMin,yMax); glVertex3f(-MAX_SIZE, -MAX_SIZE, MAX_SIZE);
   glEnd();

    //Back Wall

   glBindTexture(GL_TEXTURE_2D,tex[1]);
   //glNormal3f()  use this only if you are setting room with lighting
   glBegin(GL_QUADS);
    glTexCoord2f(xMin,yMax); glVertex3f(MAX_SIZE, -MAX_SIZE, -MAX_SIZE);
    glTexCoord2f(xMax,yMax); glVertex3f(-MAX_SIZE,-MAX_SIZE, -MAX_SIZE);
    glTexCoord2f(xMax,yMin); glVertex3f(-MAX_SIZE, MAX_SIZE, -MAX_SIZE);
    glTexCoord2f(xMin,yMin); glVertex3f(MAX_SIZE, MAX_SIZE, -MAX_SIZE);
   glEnd();

   //Top Wall

   glBindTexture(GL_TEXTURE_2D,tex[2]);
   //glNormal3f()  use this only if you are setting room with lighting
   glBegin(GL_QUADS);
    glTexCoord2f(xMin,yMax); glVertex3f(MAX_SIZE, MAX_SIZE, -MAX_SIZE);
    glTexCoord2f(xMin,yMin); glVertex3f(MAX_SIZE, MAX_SIZE, MAX_SIZE);
    glTexCoord2f(xMax,yMin); glVertex3f(-MAX_SIZE, MAX_SIZE, MAX_SIZE);
    glTexCoord2f(xMax,yMax); glVertex3f(-MAX_SIZE, MAX_SIZE, -MAX_SIZE);
   glEnd();

   //Bottom Wall

   glBindTexture(GL_TEXTURE_2D,tex[3]);
   //glNormal3f()  use this only if you are setting room with lighting
   glBegin(GL_QUADS);
    glTexCoord2f(xMax,yMax); glVertex3f(-MAX_SIZE, -MAX_SIZE, MAX_SIZE);
    glTexCoord2f(xMin,yMax); glVertex3f(MAX_SIZE, -MAX_SIZE, MAX_SIZE);
    glTexCoord2f(xMin,yMin); glVertex3f(MAX_SIZE, -MAX_SIZE, -MAX_SIZE);
    glTexCoord2f(xMax,yMin); glVertex3f(-MAX_SIZE, -MAX_SIZE, -MAX_SIZE);
   glEnd();

   //Right Wall

   glBindTexture(GL_TEXTURE_2D,tex[5]);
   //glNormal3f()  use this only if you are setting room with lighting
   glBegin(GL_QUADS);
    glTexCoord2f(xMax,yMin); glVertex3f(MAX_SIZE, MAX_SIZE, -MAX_SIZE);
    glTexCoord2f(xMax,yMax); glVertex3f(MAX_SIZE, -MAX_SIZE, -MAX_SIZE);
    glTexCoord2f(xMin,yMax); glVertex3f(MAX_SIZE, -MAX_SIZE, MAX_SIZE);
    glTexCoord2f(xMin,yMin); glVertex3f(MAX_SIZE, MAX_SIZE, MAX_SIZE);
   glEnd();

      //Left Wall

   glBindTexture(GL_TEXTURE_2D,tex[4]);
   //glNormal3f()  use this only if you are setting room with lighting
   glBegin(GL_QUADS);
    glTexCoord2f(xMin,yMin); glVertex3f(-MAX_SIZE, MAX_SIZE, -MAX_SIZE);
    glTexCoord2f(xMax,yMin); glVertex3f(-MAX_SIZE, MAX_SIZE, MAX_SIZE);
    glTexCoord2f(xMax,yMax); glVertex3f(-MAX_SIZE, -MAX_SIZE, MAX_SIZE);
    glTexCoord2f(xMin,yMax); glVertex3f(-MAX_SIZE, -MAX_SIZE, -MAX_SIZE);
   glEnd();

   glPopMatrix();

   glDepthMask(GL_TRUE);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
}

void _skyBox::drawSkyBoxSingle()
{

}
