#pragma once
// By Oleksiy Grechnyev

#include "./glheader.h"

#include <vector>

#include "./IVao.h"

namespace MotokoGL {
/// The Vao C++ wrapper, allows move and empty objects
class Vao : public IVao
{
public: // ====== Ctors, assign, dtors =====

    /**
     * @brief Ctor
     *
     * Signature example : {3, 0, 2}. Means the following arrays, use this for XYZ_ST data:
     * 0: 3 elements
     * 1: none
     * 2: 2 elements
     *
     * Or {3,3,2} for the XYZ_RGB_ST data, {3,3} for XYZ_RGB, {3} for XYZ etc.
     *
     * @param[in] signature         The signature (see above)
     * @param[in] vertices          Vertex array
     * @param[in] verticesSize      sizeof(vertices)
     * @param[in] indices           Index array (nullptr if no EBO)
     * @param[in] indicesSize       sizeof(indices)
     */
    Vao(const std::vector<unsigned> & signature,
        const GLfloat * vertices, size_t verticesSize,
        const GLuint * indices = nullptr, size_t indicesSize = 0) {
        assign(signature, vertices, verticesSize, indices, indicesSize);
    }

    /// Ctor std::vector version (can be slightly less efficient)
    Vao(const std::vector<unsigned> & signature,
        const std::vector<GLfloat> & vertices,
        const std::vector<GLuint> & indices = std::vector<GLuint>()) {
        assign(signature, vertices, indices);
    }

    /// Default ctor, creates empty VAO
    Vao() {}

    /// Assign, pointer version
    void assign(const std::vector<unsigned> & signature,
                const GLfloat * vertices, size_t verticesSize,
                const GLuint * indices = nullptr, size_t indicesSize = 0);

    /// Assign std::vector version
    void assign(const std::vector<unsigned> & signature,
                const std::vector<GLfloat> & vertices,
                const std::vector<GLuint> & indices = std::vector<GLuint>()) {
        assign(signature, vertices.data(), vertices.size()*sizeof(GLfloat),
               indices.data(), indices.size()*sizeof(GLuint));
    }

    /// Dtor
    virtual ~Vao(){
        clear();
    }

    /// Clear the data if not empty
    void clear();

public: // ====== Methods

    /// Draw this VAO object
    virtual void draw() override;

    GLsizei getCount() const noexcept {
        return count;
    }
    GLenum getDrawMode() const noexcept {
        return drawMode;
    }
    void setDrawMode(const GLenum &value) noexcept {
        drawMode = value;
    }

public: //========= Move ops ========
    /// Move Ctor
    Vao(Vao && rhs) noexcept :
        empty(rhs.empty),
        useEbo(rhs.useEbo),
        count(rhs.count),
        vao(rhs.vao),
        vbo(rhs.vbo),
        ebo(rhs.ebo),
        drawMode(rhs.drawMode)
    {
        rhs.empty = true;
    }

    /// Move assign
    Vao & operator=(Vao && rhs) noexcept {
        if (this != &rhs) {
            clear(); // Important !!!
            empty = rhs.empty;
            useEbo = rhs.useEbo;
            count = rhs.count;
            vao = rhs.vao;
            vbo = rhs.vbo;
            ebo= rhs.ebo;
            drawMode = rhs.drawMode;
            rhs.empty = true;
        }
    }

    /// delete copy ops
    Vao(const Vao &) = delete;
    Vao & operator=(const Vao &) = delete;
private: //========= Fields

    /// Is the Vao empty (created by the default ctor or moved away ?)
    bool empty = true;
    /// Are we using EBO ?
    bool useEbo = false;
    /// Number of elements to draw (vertices or indices)
    GLsizei count = 0;
    /// GL ids of vao, vbo and ebo
    GLuint vao=0, vbo=0, ebo=0;
    /// The draw mode (GL_TRIANGLES by default)
    GLenum drawMode = GL_TRIANGLES;
};
}
