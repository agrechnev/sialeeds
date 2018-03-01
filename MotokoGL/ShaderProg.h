#pragma once
// By Oleksiy Grechnyev

#include <string>
#include <memory>

#include "./glheader.h"
#include "./Material.h"
#include "./MaterialT.h"
#include "./Light.h"


namespace MotokoGL{
/// Shader program and compiling shaders
class ShaderProg
{
private: //==== Constructors ===
    /// Default private
    ShaderProg() {}

public: //==== Static factory methods
    /// Create shader program from memory strings
    static ShaderProg fromMem(const GLchar *vertexSource, const GLchar *fragmentSource);

    /// Create shader program from files
    static ShaderProg fromFiles(const std::string & vertexFileName, const std::string & fragmentFileName);

public: //==== Methods
    /// Destructor
    ~ShaderProg() {
        glDeleteProgram(prog);
    }

    /// Use this shader prog
    void use() const{
        glUseProgram(prog);
    }

    /// Locate a uniform
    GLint loc(const std::string & uniformName) const{
        return glGetUniformLocation(prog, uniformName.c_str());
    }

    /// Set cam and model  matrices (uniforms uCam, uModel)
    void setMatCM(const glm::mat4 & cam, const glm::mat4 & model){
        glUniformMatrix4fv(uCam, 1, GL_FALSE, glm::value_ptr(cam));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));
    }

    /// Set model, view, proj matrices (uniforms uModel, uView, uProj)
    void setMatMVP(const glm::mat4 & model, const glm::mat4 & view, const glm::mat4 & proj){
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(uProj, 1, GL_FALSE, glm::value_ptr(proj));
    }

    /// Set the normal matrix
    void setMatN(const glm::mat4 & model){
        glm::mat4 normal = glm::transpose(glm::inverse(model));
        glUniformMatrix4fv(loc("uNorm"), 1, GL_FALSE, glm::value_ptr(normal));
    }

    /// Set the Material
    void setMaterial(const Material & m){
        glUniform3fv(loc("uMaterial.ambient"), 1, glm::value_ptr(m.ambient));
        glUniform3fv(loc("uMaterial.diffuse"), 1, glm::value_ptr(m.diffuse));
        glUniform3fv(loc("uMaterial.specular"), 1, glm::value_ptr(m.specular));
        glUniform3fv(loc("uMaterial.emission"), 1, glm::value_ptr(m.emission));
        glUniform1f(loc("uMaterial.shininess"), m.shininess);
    }

    /// Set the MaterialT (with textures)
    void setMaterialT(const MaterialT & m){

        glUniform1i(loc("uMaterialT.ambient"), 0);
        m.ambient.bind(0);

        glUniform1i(loc("uMaterialT.diffuse"), 1);
        m.diffuse.bind(1);

        glUniform1i(loc("uMaterialT.specular"), 2);
        m.specular.bind(2);

        glUniform1i(loc("uMaterialT.emission"), 3);
        m.emission.bind(3);

        glUniform1f(loc("uMaterialT.shininess"), m.shininess);
        glUniform1i(loc("uMaterialT.flags"), m.flags);
    }

    /// Set the light
    void setLight(const Light & l){
        glUniform3fv(loc("uLight.position"), 1, glm::value_ptr(l.position));
        glUniform3fv(loc("uLight.ambient"), 1, glm::value_ptr(l.ambient));
        glUniform3fv(loc("uLight.diffuse"), 1, glm::value_ptr(l.diffuse));
        glUniform3fv(loc("uLight.specular"), 1, glm::value_ptr(l.specular));
    }

private: //==== Methods
    // Read a whole file as a string
    static std::string parseFile(const std::string & fileName);

private: //==== Fields
    /// The program's OpenGL id
    GLuint prog = 0;
    /// Uniforms
    GLint uModel, uCam, uView, uProj;
};
}

