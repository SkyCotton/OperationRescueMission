#ifndef _SHADER_H
#define _SHADER_H

#include <_common.h>

class _shader
{
    public:
        _shader();
        virtual ~_shader();

        void loadFile(char*, string&);
        unsigned fs, vs, progs;

        unsigned int loadShader(string&, unsigned int);
        void initShader(char*, char*);
        void cleanUp();

    protected:

    private:
};

#endif // _SHADER_H
