#include "src/Camera.hpp"
#include "src/Renderer.hpp"
#include "src/Material.hpp"
#include "src/Light.hpp"
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
    shader.AddTexture("resources\\container2_specular.png");
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

    const char* lightOptions[] = {
        "Directional light", "Point light", "Spotlight"
    };

    bool lightingCubeDemo = true;

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    while (window.Run())
    {

        if (lightingCubeDemo)
        {
            for (int i = 0; i < 10; i++)
            {


                //if (rotDegrees.y >= 360.0f) rotDegrees.y = 0.0f;
                if (rotDegrees.x >= 360.0f) rotDegrees.x = 0.0f;
                //rotDegrees.y += window.GetDeltaTime() * 20.0f;
                //rotDegrees.x += window.GetDeltaTime() * 50.0f;
                /*
                glm::mat4 model(1.0f);
                model = glm::translate(model, glm::vec3(0, i * 1.5f, 0)) *
                    glm::rotate(model, glm::radians(rotDegrees.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
                    glm::rotate(model, glm::radians(rotDegrees.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
                    glm::rotate(model, glm::radians(rotDegrees.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
                    glm::scale(model, scale);
                */

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

                glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));

                renderer->Draw(va, vb, shader, wireframe);
                shader.SetUniformMat4f("model", model);
                shader.SetUniformMat4f("camera", cam.GetMatrix());
                shader.SetUniformMat3f("normalMat", normalMatrix);
                shader.SetUniform3f("light.position", lightObj.position);
                shader.SetUniform3f("light.direction", lightObj.rotation);
                shader.SetUniform3f("light.ambient", lightObj.ambient);
                shader.SetUniform3f("light.diffuse", lightObj.diffuse);
                shader.SetUniform3f("light.specular", lightObj.specular);
                shader.SetUniform3f("cameraPos", cam.GetPosition());
                shader.SetUniform1i("material.diffuse", 0);
                shader.SetUniform1i("material.specular", 1);
                shader.SetUniform1f("material.shininess", 64.0f);
                shader.SetUniform1f("light.constant", lightObj.attenuationConstant);
                shader.SetUniform1f("light.linear", lightObj.attenuationLinear);
                shader.SetUniform1f("light.quadratic", lightObj.attenuationQuadratic);
                shader.SetUniform1i("light.type", lightObj.lightMode);
                shader.SetUniform1f("light.cutOff", glm::cos(glm::radians(12.0f)));
                renderer->Unbind(va, vb, shader);
            }
        }

        lightObj.ModelUpdate();
        cam.UpdateCamera(input, window);

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
        //TODO: Fix spotlight
        ImGui::Begin("Light");
        if (ImGui::Combo("Lighting Type", &lightObj.lightMode, lightOptions, IM_ARRAYSIZE(lightOptions)))
        {
            if (lightObj.lightMode == 0) lightObj.ChangeToDirectionalLight();
            else if (lightObj.lightMode == 1) lightObj.ChangeToPointLight();
            else if (lightObj.lightMode == 2) lightObj.ChangeToSpotlight();
        }
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