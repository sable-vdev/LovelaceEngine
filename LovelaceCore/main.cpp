#include "src/Camera.hpp"
#include "src/Renderer.hpp"
#include "src/Material.hpp"
#include "src/Light.hpp"
#include "src/Model.hpp"
#include <filesystem>
int main()
{
    Window window;
    
    glm::vec4 objColor(1.0f);
    
    float vertices1[] = {
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -0.577f, -0.577f, 0.577f,
        1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.577f, -0.577f, 0.577f,
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.577f, 0.577f, 0.577f,
        -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, -0.577f, 0.577f, 0.577f,
        1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.577f, -0.577f, -0.577f,
        1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.577f, 0.577f, -0.577f,
        -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -0.577f, -0.577f, -0.577f,
        -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -0.577f, 0.577f, -0.577f,
    };
    
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
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f
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
    Buffer ebo(GL_ELEMENT_ARRAY_BUFFER, ebod, sizeof(ebod), sizeof(ebod)/sizeof(unsigned int));
    VAO va;
    VertexBufferLayout vbl;
    vbl.Push<float>(3);
    vbl.Push<float>(2);
    vbl.Push<float>(3);
    va.AddBuffer(vb, vbl);

    Shader shader;
    shader.Initialize(GL_VERTEX_SHADER, "shader\\default.vert.shader", GL_FRAGMENT_SHADER, "shader\\default.frag.shader");
    shader.AddTexture("resources\\container2.png");
    shader.AddTexture("resources\\container2_specular.png", 1);
    shader.Bind();

    shader.Unbind();
    vb.Unbind();
    va.Unbind();
    ebo.Unbind();

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

    glm::vec3 lightPos = glm::vec3();
    
    
    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
    glm::vec3 translation(0.0f);
    glm::vec3 rotDegrees(0.0f);
    glm::vec3 scale(1.0f);

    Camera cam(window.GetWidth(), window.GetHeight());
    Input input(window.GetWindow());
    Light lightObj;
    bool wireframe = false;

    bool lightingCubeDemo = false;

    Shader backPackShader;
    backPackShader.Initialize(GL_VERTEX_SHADER, "shader\\model_backpack_vertex.shader", GL_FRAGMENT_SHADER, "shader\\model_backpack_frag.shader");
    std::filesystem::path path = "assets/peachy-balloon-gift/peachy_balloon.fbx";

    Model backPack(path.string());

    while (window.Run())
    {

        if (lightingCubeDemo)
        {
            if (rotDegrees.y >= 360.0f) rotDegrees.y = 0.0f;
            rotDegrees.y += window.GetDeltaTime() * 20.0f;
            
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(translation)) *
                glm::rotate(model, glm::radians(rotDegrees.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
                glm::rotate(model, glm::radians(rotDegrees.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
                glm::rotate(model, glm::radians(rotDegrees.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
                glm::scale(model, scale);

            glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));

            renderer->Draw(va, vb, shader, wireframe);
            shader.SetUniformMat4f("model", model);
            shader.SetUniformMat4f("camera", cam.GetMatrix());
            shader.SetUniformMat3f("normalMat", normalMatrix);
            shader.SetUniform3f("light[0].position", lightObj.position);
            shader.SetUniform3f("light[0].direction", lightObj.rotation);
            shader.SetUniform3f("light[0].ambient", lightObj.ambient);
            shader.SetUniform3f("light[0].diffuse", lightObj.diffuse);
            shader.SetUniform3f("light[0].specular", lightObj.specular);
            shader.SetUniform3f("cameraPos", cam.GetPosition());
            shader.SetUniform1i("material.diffuse", 0);
            shader.SetUniform1i("material.specular", 1);
            shader.SetUniform1f("material.shininess", 64.0f);
            shader.SetUniform1f("light[0].constant", lightObj.attenuationConstant);
            shader.SetUniform1f("light[0].linear", lightObj.attenuationLinear);
            shader.SetUniform1f("light[0].quadratic", lightObj.attenuationQuadratic);
            shader.SetUniform1i("light[0].type", lightObj.lightMode);
            shader.SetUniform1f("light[0].cutOff", glm::cos(glm::radians(12.0f)));
        }

        backPackShader.Bind();
        glm::mat4 model(1.0f);
        model = glm::translate(model, translation) *
            glm::rotate(model, glm::radians(rotDegrees.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::rotate(model, glm::radians(rotDegrees.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::rotate(model, glm::radians(rotDegrees.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::scale(model, scale);
        backPackShader.SetUniformMat4f("view", cam.GetMatrix());
        backPackShader.SetUniformMat4f("model", model);
        backPack.Draw(backPackShader);
        cam.UpdateCamera(input, window);

        backPackShader.Unbind();
        
        lightObj.ModelUpdate();
        renderer->Draw(light, ebolight, lightShader, wireframe);
        lightShader.SetUniformMat4f("camera", cam.GetMatrix());
        lightShader.SetUniformMat4f("model", lightObj.modelMatrix);
        renderer->Unbind(light, ebolight, lightShader);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("App");
        ImGui::Text("Application average %.2f ms/frame (%.2f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Delta time %.10f", window.GetDeltaTime());
        ImGui::Text("Application running for %.1f", window.GetApplicationRunTime());
        ImGui::Checkbox("Wireframe view", &wireframe);
        ImGui::Checkbox("Lighting cube demo", &lightingCubeDemo);
        ImGui::End();
        
        if (lightingCubeDemo)
        {
            ImGui::Begin("Cube");
            ImGui::DragFloat3("Position", &translation.x, 0.1f);
            ImGui::DragFloat3("Rotation", &rotDegrees.x, 0.1f);
            ImGui::DragFloat3("Scale", &scale.x, 0.1f);

            ImGui::End();
        }
        ImGui::Begin("Light");
        ImGui::DragFloat3("Lightpos", &lightObj.position.x, 0.1f);
        ImGui::DragFloat3("Lightrotation", &lightObj.rotation.x, 0.1f);
        ImGui::DragFloat3("Light ambient", &lightObj.ambient.r, 0.1f);
        ImGui::DragFloat3("Light diffuse", &lightObj.diffuse.r, 0.1f);
        ImGui::DragFloat3("Light specular", &lightObj.specular.r, 0.1f);
        ImGui::End();

        cam.RenderImGui();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.SwapBuffers();
    }

    window.Destroy();
    return 0;
}