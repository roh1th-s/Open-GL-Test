#include "mesh.h"

Mesh::Mesh(Vertex *vertices, unsigned int numVertices)
{
    m_drawCount = numVertices; // no of vertices we want to draw
 
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW); // moving data to GPU memory

    glEnableVertexAttribArray(0);                          // telling openGl about the attribute array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // our vec3 'pos' can be interpreted as an array of 3 units

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
    glBindVertexArray(m_vertexArrayObject);

    glDrawArrays(GL_TRIANGLES, 0, m_drawCount); 

    glBindVertexArray(0);
}