#include "Shader.h"

Shader::Shader(ShaderInfo SI)
:VertexShaderFile(SI.VertexShader),FragmentShaderFile(SI.FragmentShader),ShaderName(SI.Name)
{}

Shader::~Shader()
{

}

GLuint Shader::CompileShader(string FileName, GLenum ShaderType, GLuint &Shader)
{
    Shader = glCreateShader(ShaderType);
    if(!Shader)
    {
        cout << "Can't Create Shader\n";
        return 0;
    }

    ifstream ShaderFile;
    ShaderFile.open(FileName);
    if(!ShaderFile)
    {
        cout << "Can't Open Shader file::" << FileName << endl;
        return 0;
    }

    string Line, FileData;
    while(getline(ShaderFile,Line))
    {
        FileData.append(Line);
        FileData.append("\n");
    }
    ShaderFile.close();
    const GLchar* CodeArray[] = {FileData.c_str()};

    cout << endl << endl << CodeArray[0] << endl << endl;

    GLint LengthArray[] = {FileData.size()};
    glShaderSource(Shader,1,CodeArray,LengthArray);
    glCompileShader(Shader);

    //debug
    GLint Result;
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &Result);
    if(GL_FALSE == Result)
    {
        cout << "Shader unable to compile \n";
        glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &Result);
        if(Result > 0)
        {
            char* Log = new char[Result];
            GLsizei Written;
            glGetShaderInfoLog(Shader, Result, &Written, Log);
            std::cout << Log;
            delete Log;
            return false;
        }
    }
    //end debug

    return Shader;
}

bool Shader::GenerateProgram()
{
    cout << "Called GenerateProgram\n";
    Program = glCreateProgram();
    cout << "Program:" << Program << endl;
    if(!Program)
    {
        cout << "Invalid Program\n";
        return false;
    }
    if(VertexShaderFile.size() >= 1)
    {
        if(CompileShader(VertexShaderFile,GL_VERTEX_SHADER,VertexShader)!=0)
        {
            cout << "Vert Shader Success\n";

        }
        else
        {
            cout << "Compile Vert Shader fucked up \n";
            return false;
        }
    }
    if(FragmentShaderFile.size() >= 1)
    {
        if(CompileShader(FragmentShaderFile,GL_FRAGMENT_SHADER,FragmentShader)!=0)
        {
            cout << "Frag Shader Success\n";
            glAttachShader(Program, FragmentShader);
        }
        else
        {
            cout << "Compile Frag Shader fucked up \n";
            return false;
        }
    }
    glAttachShader(Program, VertexShader);
    glLinkProgram(Program);
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShaderManager::ShaderManager(const char* SF)
:ShadersFile(SF)
{}

ShaderManager::~ShaderManager()
{
    for(unsigned int i = 0; i < Shaders.size(); ++i)
    {
        Shaders[i].DeleteShader();
    }
}

bool ShaderManager::Initialize()
{
    fstream ShaderFile;
    ShaderFile.open(ShadersFile);
    if(!ShaderFile)
        return false;
    else
    {
        string ShaderName;
        while(ShaderFile >> ShaderName)
        {
            cout << ShaderName <<endl;
            NewShader(ShaderName.c_str());
            ShaderName.empty();
        }
    }

    for(unsigned int i = 0; i <Shaders.size(); ++i)
    {
        cout << Shaders[i].GetName() << endl;
        cout << &Shaders[i] << endl;
        cout << Shaders[i].GetProgram() << endl;
    }

    return true;
}

Shader* ShaderManager::GetShader(string Name)
{

    for(unsigned int i = 0; i < Shaders.size(); ++i)
    {
        if(Shaders[i].GetName() == Name)
        {
            return &Shaders[i];
        }
    }
    cout << "Have not found name\n";
    return NULL;
}


Shader* ShaderManager::NewShader(const char* ShaderFile)
{
    ShaderInfo SI;
    fstream ShaderInfoFile;
    ShaderInfoFile.open(ShaderFile,ios::in);
    if(!ShaderInfoFile)
    {
        cout <<"Shader failed to open\n";
        return NULL;
    }
    ShaderInfoFile >> SI.Name;
    ShaderInfoFile >> SI.VertexShader;
    ShaderInfoFile >> SI.FragmentShader;
    cout << "Name:" << SI.Name << " VertexShader:" << SI.VertexShader << " FragShader:" << SI.FragmentShader << endl;
    ShaderInfoFile.close();
    Shader NewShader(SI);
    Shaders.push_back(NewShader);
    if(!Shaders[Shaders.size()-1].GenerateProgram())
    {
        cout << "Failed to Generate Program\n";
        return NULL;
    }

    cout << "return Shader\n";
return GetShader(SI.Name);
}

Shader* ShaderManager::NewShader(ShaderInfo SI)
{
    Shaders.push_back(Shader(SI));
    Shaders[Shaders.size()-1].GenerateProgram();

    return GetShader(SI.Name);
}
