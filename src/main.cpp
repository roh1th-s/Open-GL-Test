#include <iostream>
#include <GL/glew.h>

#include "display.h"
#include "shader.h"
#include "mesh.h"

int main(int argv, char **args)

{
    std::cout << "Open GL Test";
    Display display(800, 600, "Open GL Test");

    Shader shader("./res/basicShader");

    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5, -0.5, 0)),
        Vertex(glm::vec3(0, 0.5, 0)),
        Vertex(glm::vec3(0.5, -0.5, 0))}; //triangle!

    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

    while (!display.IsClosed())
    {
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
        shader.Bind();

        mesh.Draw();
        
        display.Update();
    }
    return 0;
}
