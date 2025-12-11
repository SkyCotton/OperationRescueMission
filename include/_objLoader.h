#ifndef _OBJLOADER_H
#define _OBJLOADER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <_common.h>
#include <_textureloader.h>

using namespace std;

class _objLoader
{
    public:
        _objLoader();
        virtual ~_objLoader();

        vec3 pos;
        float dirAngleZ;
        struct Vertex{float x, y, z;};
        struct TexCoord{float u, v;};
        struct Normal{float x, y, z;}; // as in normal vector

        struct Face
        {
            int vIndex[3];
            int tIndex[3];
            int nIndex[3];
        };
        vector<Vertex>      vertices;
        vector<TexCoord>    texCoords;
        vector<Normal>      normals;
        vector<Face>        faces;

        GLuint texID;
        _textureLoader *myTex;

        void loadOBJ(string fileName);
        void loadTexture(string fileName);
        void drawOBJ();

    protected:

    private:
};

#endif // _OBJLOADER_H
