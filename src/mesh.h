#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex
{
public:
    Vertex(const glm::vec3& pos) {
        this->pos = pos;
    }
private:
    glm::vec3 pos;
};

class Mesh
{
public:
    Mesh(Vertex* vertices, unsigned int numVertices);

    void Draw();

    virtual ~Mesh();

private:
    Mesh(const Mesh &other);
    void operator=(const Mesh &other);

    enum {
        POSITION_VB,

        NUM_BUFFERS
    }; // so NUM_BUFFERS will always have the number of buffers (no of entries before it in the enum) since it is at the end.

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];

    unsigned int m_drawCount;
};

#endif