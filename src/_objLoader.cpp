#include "_objLoader.h"

_objLoader::_objLoader()
{
    myTex = new _textureLoader();
    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = 0.0f;
    dirAngleZ = 0.0f;
}

_objLoader::~_objLoader()
{
    delete myTex;
}
void _objLoader::loadTexture(string fileName)
{
    myTex->loadTexture((char*) fileName.c_str());
    texID = myTex->textID;
}
void _objLoader::loadOBJ(string fileName)
{
    ifstream file(fileName);
    if(!file.is_open())
    {
        cout << "Error opening file: " << fileName << endl;
    }

    string line;
    while(getline(file, line))
    {
        stringstream ss(line);
        string prefix;
        ss >> prefix;

        if(prefix == "v")
        {
            Vertex temp;
            ss >> temp.x >> temp.y >> temp.z;
            vertices.push_back(temp);
        }
        else if(prefix == "vt")
        {
            TexCoord temp;
            ss >> temp.u >> temp.v;
            texCoords.push_back(temp);
        }
        else if(prefix == "vn") // vector normal
        {
            Normal temp;
            ss >> temp.x >> temp.y >> temp.z;
            normals.push_back(temp);
        }
        else if(prefix == "f")
        {
            Face face;
            char slash;

            for(int i = 0; i < 3; i++)
            {
                ss >> face.vIndex[i] >> slash >> face.tIndex[i] >> slash >> face.nIndex[i];

                face.vIndex[i]--;
                face.tIndex[i]--;
                face.nIndex[i]--;
            }
            faces.push_back(face);
        }
    }
    file.close();
    cout << "Loaded OBJ: " << fileName << " with " << faces.size() << " faces." << endl;
}
void _objLoader::drawOBJ()
{
    if(texID != 0)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texID);
    }
    glBegin(GL_TRIANGLES);
    for(const auto& face : faces)
    {
        for(int i = 0; i < 3; i++)
        {
            if(!texCoords.empty())
            {
                glTexCoord2f(texCoords[face.tIndex[i]].u, 1.0f - texCoords[face.tIndex[i]].v);
            }
            if(!normals.empty())
            {
                glNormal3f(normals[face.nIndex[i]].x, normals[face.nIndex[i]].y, normals[face.nIndex[i]].z);
            }
            glVertex3f(vertices[face.vIndex[i]].x, vertices[face.vIndex[i]].y, vertices[face.vIndex[i]].z);
        }
    }
    glEnd();
}
