#include "src/Camera.hpp"
#include "src/Renderer.hpp"
#include "src/Material.hpp"
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
    shader.AddTexture("container2.png");
    shader.AddTexture("container2_specular.png");
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

    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
    glm::mat4 lightMat = glm::mat4(1.0f);
    lightMat = glm::translate(lightMat, lightPos);

    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
    glm::vec3 translation(0.0f);
    glm::vec3 rotDegrees(0.0f);
    glm::vec3 scale(1.0f);

    Camera cam(window.GetWidth(), window.GetHeight());
    Input input(window.GetWindow());

    bool wireframe = false;

    glm::vec4 lightColor = glm::vec4(1.0f);
    /*
    int materialChoice = 0;

    const Material materials[] = {
        Material::Emerald(), Material::Jade(), Material::Obsidian(), Material::Pearl(), Material::Ruby(), Material::Turquoise(), Material::Brass(),
        Material::Bronze(), Material::Chrome(), Material::Copper(), Material::Gold(), Material::Silver(), Material::BlackPlastic(), Material::CyanPlastic(),
        Material::GreenPlastic(), Material::RedPlastic(), Material::WhitePlastic(), Material::YellowPlastic(), Material::BlackRubber(), Material::CyanRubber(),
        Material::GreenRubber(), Material::RedRubber(), Material::WhiteRubber(), Material::YellowRubber()
    };

    Material mat = materials[materialChoice];

    const char* materialNames[] = {
        "Emerald", "Jade", "Obsidian", "Pearl", "Ruby", "Turquoise",
        "Brass", "Bronze", "Chrome", "Copper", "Gold", "Silver",
        "Black Plastic", "Cyan Plastic", "Green Plastic", "Red Plastic",
        "White Plastic", "Yellow Plastic", "Black Rubber", "Cyan Rubber",
        "Green Rubber", "Red Rubber", "White Rubber", "Yellow Rubber"
    };
    */
    Material lightMaterial(vec3(0.2f, 0.2f, 0.2f), vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), 0.0f);

    bool lightingCubeDemo = true;

    while (window.Run())
    {

        if (lightingCubeDemo)
        {

            //if (rotDegrees.y >= 360.0f) rotDegrees.y = 0.0f;
            if (rotDegrees.x >= 360.0f) rotDegrees.x = 0.0f;
            //rotDegrees.y += window.GetDeltaTime() * 20.0f;
            //rotDegrees.x += window.GetDeltaTime() * 50.0f;

            glm::mat4 model(1.0f);
            model = glm::translate(model, translation) *
                glm::rotate(model, glm::radians(rotDegrees.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
                glm::rotate(model, glm::radians(rotDegrees.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
                glm::rotate(model, glm::radians(rotDegrees.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
                glm::scale(model, scale);

            glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));

            renderer->Draw(va, vb, shader, wireframe);
            shader.SetUniformMat4f("model", model);
            shader.SetUniformMat4f("camera", cam.GetMatrix());
            shader.SetUniformMat3f("normalMat", normalMatrix);
            //shader.SetUniform3f("objectColor", objColor);
            shader.SetUniform3f("lightColor", lightColor);
            shader.SetUniform3f("light.position", lightPos);
            shader.SetUniform3f("light.direction", 1.0, -1.0, -0.3);
            shader.SetUniform3f("light.ambient", lightMaterial.ambient);
            shader.SetUniform3f("light.diffuse", lightMaterial.diffuse);
            shader.SetUniform3f("light.specular", lightMaterial.specular);
            shader.SetUniform3f("cameraPos", cam.GetPosition());
            shader.SetUniform1i("material.diffuse", 0);
            shader.SetUniform1i("material.specular", 1);
            shader.SetUniform1f("material.shininess", 64.0f);
            shader.SetUniform1f("light.constant", 1.0f);
            shader.SetUniform1f("light.linear", 0.09f);
            shader.SetUniform1f("light.quadratic", 0.032f);
            renderer->Unbind(va, vb, shader);
            
        }

        lightMat = glm::mat4(1.0f);
        lightMat = glm::translate(lightMat, lightPos);

        cam.UpdateCamera(input, window);

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
        ImGui::Checkbox("Lighting cube demo", &lightingCubeDemo);
        ImGui::End();

        if (lightingCubeDemo)
        {
            ImGui::Begin("Cube");
            ImGui::DragFloat3("Position", &translation.x, 0.1f);
            ImGui::DragFloat3("Rotation", &rotDegrees.x, 0.1f);
            ImGui::DragFloat3("Scale", &scale.x, 0.1f);
            /*
            if (ImGui::Combo("Material", &materialChoice, materialNames, IM_ARRAYSIZE(materialNames)))
            {
                mat = materials[materialChoice];
            }
            ImGui::Text("Ambient:  %.2f %.2f %.2f", mat.ambient.r, mat.ambient.g, mat.ambient.b);
            ImGui::Text("Diffuse:  %.2f %.2f %.2f", mat.diffuse.r, mat.diffuse.g, mat.diffuse.b);
            ImGui::Text("Specular: %.2f %.2f %.2f", mat.specular.r, mat.specular.g, mat.specular.b);
            ImGui::Text("Shininess: %.2f", mat.shininess);
            */
            ImGui::End();
        }

        ImGui::Begin("Light");
        ImGui::DragFloat3("Lightpos", &lightPos.x, 0.1f);
        ImGui::DragFloat3("Light ambient", &lightMaterial.ambient.r, 0.1f);
        ImGui::DragFloat3("Light diffuse", &lightMaterial.diffuse.r, 0.1f);
        ImGui::DragFloat3("Light specular", &lightMaterial.specular.r, 0.1f);
        ImGui::End();
        cam.RenderImGui();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.SwapBuffers();
    }

    window.Destroy();
    return 0;
}