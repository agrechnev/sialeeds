#include <iostream>
#include <fstream>
#include <streambuf>

#include "./MotokoError.h"

#include "./ShaderProg.h"


namespace MotokoGL{
//==============================================================
ShaderProg ShaderProg::fromMem(const GLchar *vertexSource, const GLchar *fragmentSource)
{
    ShaderProg newProg;
    GLuint & prog = newProg.prog;

    using namespace std;

    // Create shaders and Compile
    // Vertex
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        throw MotokoError(string("ShaderProg::fromMem() : Cannot compile vertex shader") + infoLog);
    }

    // Fragment
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        throw MotokoError(string("ShaderProg::fromMem() : Cannot compile fragment shader") + infoLog);
    }

    // Shader program
    prog = glCreateProgram();
    glAttachShader(prog, vertexShader);
    glAttachShader(prog, fragmentShader);
    glLinkProgram(prog);

    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(prog, 512, nullptr, infoLog);
        throw MotokoError(string("ShaderProg::fromMem() : Cannot link shader program") + infoLog);
    }

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set uniforms
    newProg.uCam = newProg.loc("uCam");
    newProg.uModel = newProg.loc("uModel");
    newProg.uView = newProg.loc("uView");
    newProg.uProj = newProg.loc("uProj");

    return newProg;
}
//==============================================================
ShaderProg ShaderProg::fromFiles(const std::string & vertexFileName, const std::string & fragmentFileName)
{
    using namespace std;

    auto s1 = parseFile(vertexFileName);
    auto s2 = parseFile(fragmentFileName);

    ShaderProg newProg = ShaderProg::fromMem(s1.c_str(), s2.c_str());
    return newProg;
}
//==============================================================
std::string ShaderProg::parseFile(const std::string &fileName)
{
    using namespace std;
    ifstream in(fileName);
    if (!in)
        throw MotokoError("ShaderProg::parseFile() : cannot open file " + fileName);
    string result, line;
    while (getline(in, line)) {
        result.append(line);
        result.push_back('\n');    // EOL-safe version
    }
    return result;
//    return string((istreambuf_iterator<char>(in)), istreambuf_iterator<char>()); // Simplest
}
//==============================================================


}
