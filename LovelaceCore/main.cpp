#include <iostream>
#include "src/Camera.hpp"
#include "src/Renderer.hpp"
#include "core/Vertex.h"

int main()
{
    Window window;

    Vertex vertices[] = {
        Vertex(-1.0f, -1.0f, 1.0f, 137, 207, 240),
        Vertex(1.0f, -1.0f, 1.0f, 200, 255, 2),
        Vertex(1.0f, 1.0f, 1.0f, 137, 207, 240),
        Vertex(-1.0f, 1.0f, 1.0f, 200, 255, 2),
        Vertex(1.0f, -1.0f, -1.0f, 137, 207, 240),
        Vertex(1.0f, 1.0f, -1.0f, 200, 255, 2),
        Vertex(-1.0f, -1.0f, -1.0f, 137, 207, 240),
        Vertex(-1.0f, 1.0f, -1.0f, 200, 255, 1)
    };

    unsigned int ibod[] = { 
        0, 1, 2,
        2, 3, 0,

        1, 4, 5,
        5, 2, 1,

        4, 6, 7,
        7, 5, 4,

        6, 0, 3,
        3, 7, 6,

        6, 4, 1,
        1, 0, 6,

        3, 2, 5,
        5, 7, 3
    };

    Buffer vb(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    Buffer ibo(GL_ELEMENT_ARRAY_BUFFER, ibod, sizeof(ibod), sizeof(ibod)/sizeof(unsigned int));
    VAO va;
    VertexBufferLayout vbl;
    vbl.Push<float>(3);
    vbl.Push<float>(3);
    va.AddBuffer(vb, vbl);

    Shader shader;
    shader.Initialize(GL_VERTEX_SHADER, "shader\\vertex.shader", GL_FRAGMENT_SHADER, "shader\\frag.shader");
    shader.Bind();

    shader.Unbind();
    vb.Unbind();
    va.Unbind();
    ibo.Unbind();

    Renderer* renderer{};
    glm::vec3 translation(0.0f, 0.0f, 0.0f);
    glm::vec3 rotDegrees(0.0f, 0.0f, 0.0f);
    glm::vec3 scale(1.0f, 1.0f, 1.0f);

    Camera cam;

    while (window.Run())
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, translation) *
            glm::rotate(model, glm::radians(rotDegrees.y) , glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::rotate(model, glm::radians(rotDegrees.x), glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::rotate(model, glm::radians(rotDegrees.z), glm::vec3(1.0f, 0.0f, 0.0f)) * 
            glm::scale(model, scale);

        cam.UpdateCamera(&window);
        renderer->Draw(va, ibo, shader);
        shader.SetUniformMat4f("model", model);
        shader.SetUniformMat4f("camera", cam.GetMatrix());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Text("Application average %.3f ms/frame (%.2f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Delta time %.10f", window.GetDeltaTime());
        ImGui::Text("Application running for %.1f", window.GetApplicationRunTime());
        ImGui::Begin("Cube");
        ImGui::DragFloat3("Position", &translation.x, 0.1f);
        ImGui::DragFloat3("Rotation", &rotDegrees.x, 0.1f);
        ImGui::DragFloat3("Scale", &scale.x, 0.1f);
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        shader.Unbind();
        va.Unbind();
        ibo.Unbind();
        window.SwapBuffers();

    }
    delete renderer;

    window.Destroy();
    return 0;
}