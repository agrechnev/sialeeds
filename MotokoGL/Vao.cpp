#include <numeric>

#include "./MotokoError.h"
#include "./Vao.h"


namespace MotokoGL {

//=================================================================
void Vao::assign(const std::vector<unsigned> &signature, const GLfloat *vertices, size_t verticesSize, const GLuint *indices, size_t indicesSize)
{
    using namespace std;
    clear(); // Remove the old stuff, if any
    empty = false;
    useEbo = (indices != nullptr && indicesSize > 0);  // Do we use EBO ?
    // Sum of all elements in the signature
    unsigned sigSum = accumulate(signature.begin(), signature.end(), 0);

    if (sigSum ==0)
        throw MotokoError("Vao::assign() : Wrong signature.");
    if (verticesSize % sigSum !=0)
        throw MotokoError("Vao::assign() : verticesSize % sigSum != 0.");
    // Calculate count = number of vertices to draw
    if (useEbo)
        count = indicesSize / sizeof(GLuint);
    else
        count = verticesSize / (sigSum*sizeof(GLfloat));

    // ===== Create VAO, VBO, EBO
    // Create VBO, VAO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao); // Bind VAO first
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // Bind VBO
    // Fill EBO with the vertex data
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    // Create and bind EBO if needed
    if (useEbo){
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
    }

    // Loop over all signature elements (aka GL array indices)
    // i is the same as layout (location=i) in the vertex shader
    unsigned pos = 0; // Current position in the data
    for (GLuint i = 0; i < signature.size(); ++i){
        unsigned n = signature[i]; // Number of elements for i
        if (n) {  // Skip if n==0
            glVertexAttribPointer(i, n, GL_FLOAT, GL_FALSE,
                                  sigSum*sizeof(GLfloat), (GLvoid *)(pos*sizeof(GLfloat)));
            glEnableVertexAttribArray(i); // Enable this index
        }
        pos += n; // Move pos
    }
    // Unbind VBO+VAO, but not EBO !!!
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
//=================================================================
void Vao::clear()
{
    if (!empty) {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        if (useEbo)
            glDeleteBuffers(1, &ebo);
    }
    empty = true;
}
//=================================================================
void Vao::draw() {
    if (empty)
        throw MotokoError("Vao::draw() : Cannot draw empty object !");
    glBindVertexArray(vao);
    if (useEbo)   // Draw with ebo
        glDrawElements(drawMode, count, GL_UNSIGNED_INT, 0);
    else  // Draw w/o ebo
        glDrawArrays(drawMode, 0, count);
    glBindVertexArray(0);
}
//=================================================================

}
