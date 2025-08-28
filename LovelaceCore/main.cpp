#include "src/Camera.hpp"
#include "src/Renderer.hpp"
#include "src/Material.hpp"
int main()
{
    Window window;
    glm::vec4 objColor(1.0f);
    /*
    float vertices[] = {
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -0.577f, -0.577f, 0.577f,
        1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.577f, -0.577f, 0.577f,
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.577f, 0.577f, 0.577f,
        -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, -0.577f, 0.577f, 0.577f,
        1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.577f, -0.577f, -0.577f,
        1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.577f, 0.577f, -0.577f,
        -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -0.577f, -0.577f, -0.577f,
        -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -0.577f, 0.577f, -0.577f,
    };
    */

    float lightpos[] = {
        -0.1f, -0.1f, 0.1f,
        0.1f, -0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        -0.1f, 0.1f, 0.1f,
        0.1f, -0.1f, -0.1f,
        0.1f, 0.1f, -0.1f,
        -0.1f, -0.1f, -0.1f,
        -0.1f, 0.1f, -0.1f,
    };

    float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f
    };

    unsigned int ebod[] = {
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
    //Buffer ebo(GL_ELEMENT_ARRAY_BUFFER, ebod, sizeof(ebod), sizeof(ebod)/sizeof(unsigned int));
    VAO va;
    VertexBufferLayout vbl;
    vbl.Push<float>(3);
    vbl.Push<float>(2);
    vbl.Push<float>(3);
    va.AddBuffer(vb, vbl);

    Shader shader;
    shader.Initialize(GL_VERTEX_SHADER, "shader\\default.vert.shader", GL_FRAGMENT_SHADER, "shader\\default.frag.shader");
    shader.AddTexture("Untitled.png");
    shader.Bind();

    shader.Unbind();
    vb.Unbind();
    va.Unbind();
    //ebo.Unbind();

    Buffer vblight(GL_ARRAY_BUFFER, lightpos, sizeof(lightpos));
    Buffer ebolight(GL_ELEMENT_ARRAY_BUFFER, ebod, sizeof(ebod), sizeof(ebod) / sizeof(unsigned int));
    ebolight.Bind();
    VAO light;
    VertexBufferLayout vblLight;
    vblLight.Push<float>(3);
    light.AddBuffer(vblight, vblLight);
    Shader lightShader;
    lightShader.Initialize(GL_VERTEX_SHADER, "shader\\light.vert.shader", GL_FRAGMENT_SHADER, "shader\\light.frag.shader");
    lightShader.Bind();

    lightShader.Unbind();
    vblight.Unbind();
    light.Unbind();
    ebolight.Unbind();

    glm::vec3 lightPos = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 lightMat = glm::mat4(1.0f);
    lightMat = glm::translate(lightMat, lightPos);

    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
    glm::vec3 translation(0.0f);
    glm::vec3 rotDegrees(0.0f);
    glm::vec3 scale(1.0f);

    Camera cam(window.GetWidth(), window.GetHeight());
    Input input(window.GetWindow());

    bool wireframe = false;

    glm::vec4 lightColor = glm::vec4(255.0f / 255.0f, 248.0f / 255.0f, 136.0f / 255.0f, 255.0f / 255.0f);

    //renderer->renderLayout.emplace_back(va, ebo, shader);
    //renderer->renderLayout.emplace_back(light, ebo, lightShader);
    // 
    //jade material source from http://devernay.free.fr/cours/opengl/materials.html
    Material mat = { .ambient = vec3(0.135f, 0.2225f, 0.1575f), .diffuse = vec3(0.54f, 0.89f, 0.63f), .specular = vec3(0.316228f, 0.316228f, 0.316228f), .shininess = 0.1f * 128.0f };

    while (window.Run())
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, translation) *
            glm::rotate(model, glm::radians(rotDegrees.z), glm::vec3(0.0f, 0.0f, 1.0f)) * 
            glm::rotate(model, glm::radians(rotDegrees.y) , glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::rotate(model, glm::radians(rotDegrees.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::scale(model, scale);

        glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));

        glm::mat4 lightMat = glm::mat4(1.0f);
        lightMat = glm::translate(lightMat, lightPos);

        cam.UpdateCamera(input, window);

        renderer->Draw(va, vb, shader, wireframe);
        shader.SetUniformMat4f("model", model);
        shader.SetUniformMat4f("camera", cam.GetMatrix());
        shader.SetUniformMat3f("normalMat", normalMatrix);
        //shader.SetUniform3f("objectColor", objColor);
        shader.SetUniform3f("lightColor", lightColor);
        shader.SetUniform3f("lightPos", lightPos);
        shader.SetUniform3f("cameraPos", cam.GetPosition());
        shader.SetUniform3f("objectMaterial.ambient", mat.ambient);
        shader.SetUniform3f("objectMaterial.diffuse", mat.diffuse);
        shader.SetUniform3f("objectMaterial.specular", mat.specular);
        shader.SetUniform1f("objectMaterial.shininess", mat.shininess);
        renderer->Unbind(va, vb, shader);

        

        renderer->Draw(light, ebolight, lightShader, wireframe);
        lightShader.SetUniformMat4f("camera", cam.GetMatrix());
        lightShader.SetUniformMat4f("model", lightMat);
        lightShader.SetUniform4f("lightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        renderer->Unbind(light, ebolight, lightShader);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("App");
        ImGui::Text("Application average %.2f ms/frame (%.2f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Delta time %.10f", window.GetDeltaTime());
        ImGui::Text("Application running for %.1f", window.GetApplicationRunTime());
        ImGui::Checkbox("Wireframe view", &wireframe);
        ImGui::End();
        ImGui::Begin("Cube");
        ImGui::DragFloat3("Position", &translation.x, 0.1f);
        ImGui::DragFloat3("Rotation", &rotDegrees.x, 0.1f);
        ImGui::DragFloat3("Scale", &scale.x, 0.1f);
        ImGui::DragFloat3("Lightpos", &lightPos.x, 0.1f);
        //ImGui::ColorEdit4("Color", &objColor.x);
        ImGui::ColorEdit4("LightColor", &lightColor.x);
        ImGui::End();
        cam.RenderImGui();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.SwapBuffers();
    }

    window.Destroy();
    return 0;
}