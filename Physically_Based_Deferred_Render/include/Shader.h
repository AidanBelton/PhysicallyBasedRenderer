#ifndef SHADER_H
#define SHADER_H
#include <gl/glew.h>
#include "glm/glm.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;
using namespace glm;

struct ShaderInfo
{
    string Name;
    string VertexShader;
    string FragmentShader;
};

class Shader
{
    public:
        Shader(ShaderInfo);
        Shader(){};
        virtual ~Shader();
        bool GenerateProgram();
        GLuint GetProgram() const {return Program;}
        inline void DeleteShader() {glDeleteProgram(Program);glDeleteShader(VertexShader);glDeleteShader(FragmentShader);}
        inline void UseProgram() {glUseProgram(Program);}
        string GetName() const {return ShaderName;}

        inline void Uniform(const char* Name, int &Data) {glProgramUniform1i(Program, glGetUniformLocation(Program,Name), Data);}
        inline void Uniform(const char* Name, float &Data) {glProgramUniform1f(Program, glGetUniformLocation(Program,Name), Data);}
        inline void Uniform(const char* Name, vec2 Data[], int Num) {glProgramUniform2fv(Program, glGetUniformLocation(Program,Name),Num, &Data[0][0]);}
        inline void Uniform(const char* Name, vec3 Data[], int Num) {glProgramUniform3fv(Program, glGetUniformLocation(Program,Name),Num, &Data[0][0]);}
        inline void Uniform(const char* Name, vec4 Data[], int Num) {glProgramUniform4fv(Program, glGetUniformLocation(Program,Name),Num, &Data[0][0]);}
        inline void Uniform(const char* Name, mat2 Data[], int Num) {glProgramUniformMatrix2fv(Program, glGetUniformLocation(Program,Name),Num,GL_FALSE, &Data[0][0][0]);}
        inline void Uniform(const char* Name, mat3 Data[], int Num) {glProgramUniformMatrix3fv(Program, glGetUniformLocation(Program,Name),Num,GL_FALSE, &Data[0][0][0]);}
        inline void Uniform(const char* Name, mat4 Data[], int Num) {glProgramUniformMatrix4fv(Program, glGetUniformLocation(Program,Name),Num,GL_FALSE, &Data[0][0][0]);}
        inline void Uniform(GLint Loc, int &Data) {glProgramUniform1i(Program, Loc, Data);}
        inline void Uniform(GLint Loc, float &Data) {glProgramUniform1f(Program, Loc, Data);}
        inline void Uniform(GLint Loc, vec2 Data[], int Num) {glProgramUniform2fv(Program, Loc,Num, &Data[0][0]);}
        inline void Uniform(GLint Loc, vec3 Data[], int Num) {glProgramUniform3fv(Program, Loc,Num, &Data[0][0]);}
        inline void Uniform(GLint Loc, vec4 Data[], int Num) {glProgramUniform4fv(Program, Loc,Num, &Data[0][0]);}
        inline void Uniform(GLint Loc, mat2 Data[], int Num) {glProgramUniformMatrix2fv(Program, Loc,Num,GL_FALSE, &Data[0][0][0]);}
        inline void Uniform(GLint Loc, mat3 Data[], int Num) {glProgramUniformMatrix3fv(Program, Loc,Num,GL_FALSE, &Data[0][0][0]);}
        inline void Uniform(GLint Loc, mat4 Data[], int Num) {glProgramUniformMatrix4fv(Program, Loc,Num,GL_FALSE, &Data[0][0][0]);}

        inline void Uniform(const char* Name, vec2 &Data) {glProgramUniform2fv(Program, glGetUniformLocation(Program,Name),1, &Data[0]);}
        inline void Uniform(const char* Name, vec3 &Data) {glProgramUniform3fv(Program, glGetUniformLocation(Program,Name),1, &Data[0]);}
        inline void Uniform(const char* Name, vec4 &Data) {glProgramUniform4fv(Program, glGetUniformLocation(Program,Name),1, &Data[0]);}
        inline void Uniform(const char* Name, mat2 &Data) {glProgramUniformMatrix2fv(Program, glGetUniformLocation(Program,Name),1,GL_FALSE, &Data[0][0]);}
        inline void Uniform(const char* Name, mat3 &Data) {glProgramUniformMatrix3fv(Program, glGetUniformLocation(Program,Name),1,GL_FALSE, &Data[0][0]);}
        inline void Uniform(const char* Name, mat4 &Data) {glProgramUniformMatrix4fv(Program, glGetUniformLocation(Program,Name),1,GL_FALSE, &Data[0][0]);}
        inline void Uniform(GLint Loc, vec2 &Data) {glProgramUniform2fv(Program, Loc,1, &Data[0]);}
        inline void Uniform(GLint Loc, vec3 &Data) {glProgramUniform3fv(Program, Loc,1, &Data[0]);}
        inline void Uniform(GLint Loc, vec4 &Data) {glProgramUniform4fv(Program, Loc,1, &Data[0]);}
        inline void Uniform(GLint Loc, mat2 &Data) {glProgramUniformMatrix2fv(Program, Loc,1,GL_FALSE, &Data[0][0]);}
        inline void Uniform(GLint Loc, mat3 &Data) {glProgramUniformMatrix3fv(Program, Loc,1,GL_FALSE, &Data[0][0]);}
        inline void Uniform(GLint Loc, mat4 &Data) {glProgramUniformMatrix4fv(Program, Loc,1,GL_FALSE, &Data[0][0]);}
    private:
        GLuint Program = 0, VertexShader = 0, FragmentShader = 0;
        string VertexShaderFile, FragmentShaderFile, ShaderName;
        GLuint CompileShader(string, GLenum, GLuint&);
};

class ShaderManager
{
    public:
        ShaderManager(const char*);
        virtual ~ShaderManager();
        bool Initialize();
        Shader* GetShader(string);
        Shader* NewShader(const char*);
        Shader* NewShader(ShaderInfo);
    private:
        const char* ShadersFile;
        vector<Shader> Shaders;
};

#endif // SHADER_H
