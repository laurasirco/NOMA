/* 
 * File:   TShaderProgram.cpp
 * Author: Laura Sirvent Collado
 * 
 * Created on 14 de marzo de 2014, 19:45
 */

#include "../headers/TShaderProgram.h"

using namespace std;

TShaderProgram::TShaderProgram() {
    setDefaults();
}

TShaderProgram::TShaderProgram(const TShaderProgram& orig) {
}

TShaderProgram::~TShaderProgram() {
}

TShaderProgram::operator GLuint ()
{
    return Program;
}

bool TShaderProgram::Link(){
    
    glLinkProgram(Program);

    int LinkStatus;
    glGetProgramiv(Program, GL_LINK_STATUS, &LinkStatus);

    if(LinkStatus == GL_FALSE)
    {
        cout<<"Error linking program"<<endl;

        int InfoLogLength = 0;
        glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &InfoLogLength);
    
        if(InfoLogLength > 0)
        {
            char *InfoLog = new char[InfoLogLength];
            int CharsWritten  = 0;
            glGetProgramInfoLog(Program, InfoLogLength, &CharsWritten, InfoLog);
            cout<<InfoLog<<endl;
            delete [] InfoLog;
        }

        Destroy();

        return false;
    }

    return true;
}

bool TShaderProgram::Load(char* VertexShaderFileName, char* FragmentShaderFileName){
    bool Error = false;

    Destroy();

    Error |= ((VertexShader = LoadShader(VertexShaderFileName, GL_VERTEX_SHADER)) == 0);
    Error |= ((FragmentShader = LoadShader(FragmentShaderFileName, GL_FRAGMENT_SHADER)) == 0);

    if(Error)
    {
        Destroy();
        return false;
    }

    Program = glCreateProgram();
    glAttachShader(Program, VertexShader);
    glAttachShader(Program, FragmentShader);
    
    return true;
}

void TShaderProgram::Destroy(){
    
    glDetachShader(Program, VertexShader);
    glDetachShader(Program, FragmentShader);

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    glDeleteProgram(Program);

    delete [] UniformLocations;
    delete [] AttribLocations;

    setDefaults();
}

GLuint TShaderProgram::LoadShader(char* FileName, GLenum Type){
    
    FILE *File = fopen(FileName, "rb");
    
    if(!File)
    {
        cout<<"Error loading file "<<FileName<<endl;
        return 0;
    }

    fseek(File, 0, SEEK_END);
    long Size = ftell(File);
    fseek(File, 0, SEEK_SET);
    char *Source = new char[Size + 1];
    fread(Source, 1, Size, File);
    fclose(File);
    Source[Size] = 0;

    GLuint Shader = glCreateShader(Type);

    glShaderSource(Shader, 1, (const char**)&Source, NULL);
    delete [] Source;
    glCompileShader(Shader);

    int CompileStatus;
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &CompileStatus);

    if(CompileStatus == GL_FALSE)
    {
        cout<<"Error compiling shader"<<FileName<<endl;

        int InfoLogLength = 0;
        glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    
        if(InfoLogLength > 0)
        {
            char *InfoLog = new char[InfoLogLength];
            int CharsWritten  = 0;
            glGetShaderInfoLog(Shader, InfoLogLength, &CharsWritten, InfoLog);
            cout<<InfoLog<<endl;
            delete [] InfoLog;
        }

        glDeleteShader(Shader);

        return 0;
    }

    return Shader;
}

void TShaderProgram::setDefaults(){
    
    VertexShader = 0;
    FragmentShader = 0;

    Program = 0;

    UniformLocations = NULL;
    AttribLocations = NULL;
}