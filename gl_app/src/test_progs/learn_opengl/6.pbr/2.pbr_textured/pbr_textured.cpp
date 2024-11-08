#include "pch.h"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui_docking/imgui.h>
#include <imgui_docking/backends/imgui_impl_glfw.h>
#include <imgui_docking/backends/imgui_impl_opengl3.h>

#include "camera.h"
#include "window.h"
#include "stb_image/stb_image.h"
#include "shader.h"

#include "pbr_textured.h"

// lights
// ------
static glm::vec3 lightPositions[] = {
    /*glm::vec3(-10.0f,  10.0f, 10.0f),
    glm::vec3(10.0f,  10.0f, 10.0f),
    glm::vec3(-10.0f, -10.0f, 10.0f),
    glm::vec3(10.0f, -10.0f, 10.0f),*/

    glm::vec3(0.0f, 0.0f, 10.0f),
};
static glm::vec3 lightColors[] = {
    /*glm::vec3(300.0f, 300.0f, 300.0f),
    glm::vec3(300.0f, 300.0f, 300.0f),
    glm::vec3(300.0f, 300.0f, 300.0f),
    glm::vec3(300.0f, 300.0f, 300.0f)*/

    glm::vec3(150.0f, 150.0f, 150.0f),
};
static int nrRows = 7;
static int nrColumns = 7;
static float spacing = 2.5;

PbrTextured::PbrTextured(Window& window, v2::Camera& camera) :
	m_window{ window }, m_camera{ camera }
{
  float aspect_ratio = (float)m_window.BufferWidth() / (float)m_window.BufferHeight();
  m_camera.SetPerspectiveParams({ aspect_ratio , 45.0f, 1.0f, 50.0f, true });
  m_camera.SetPosition(glm::vec3(-5.0f, 10.0f, 10.0f));
  m_camera.LookAt(glm::vec3{ 0,0,0 });
}

void PbrTextured::Startup()
{
  glEnable(GL_DEPTH_TEST);

  ShaderBuilder shader_builder("src/test_progs/learn_opengl/6.pbr/2.pbr_textured/");
  m_shader = shader_builder.Vert("1.2.pbr.vs").Frag("1.2.pbr.fs").Build("Basic PBR textured");

  m_shader->Bind();

  m_shader->SetUniform1i("albedoMap", 0);
  m_shader->SetUniform1i("normalMap", 1);
  m_shader->SetUniform1i("metallicMap", 2);
  m_shader->SetUniform1i("roughnessMap", 3);
  
  //m_shader->SetUniform1i("aoMap", 4);

  // load PBR material textures
    // --------------------------
  albedo = loadTexture("assets/freepbr/rusted_iron/albedo.png");
  normal = loadTexture("assets/freepbr/rusted_iron/normal.png");
  metallic = loadTexture("assets/freepbr/rusted_iron/metallic.png");
  roughness = loadTexture("assets/freepbr/rusted_iron/roughness.png");
  //unsigned int ao = loadTexture("assets/freepbr/rusted_iron/albedo.png");
}

void PbrTextured::Shutdown()
{
  glfwTerminate();
}

void PbrTextured::OnUpdate(double now, double time_step)
{
  m_shader->Bind();
  m_shader->SetUniformMat4f("projection", m_camera.GetProjMatrix());
  m_shader->SetUniformMat4f("view", m_camera.GetViewMatrix());
  m_shader->SetUniform3f("camPos", m_camera.GetPosition());
 

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, albedo);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, normal);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, metallic);
  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, roughness);
  /*glActiveTexture(GL_TEXTURE4);
  glBindTexture(GL_TEXTURE_2D, ao);*/

  // render rows*column number of spheres with material properties defined by textures (they all have the same material properties)
  glm::mat4 model = glm::mat4(1.0f);
  for (int row = 0; row < nrRows; ++row)
  {
    for (int col = 0; col < nrColumns; ++col)
    {
      model = glm::mat4(1.0f);
      model = glm::translate(model, glm::vec3(
        (float)(col - (nrColumns / 2)) * spacing,
        (float)(row - (nrRows / 2)) * spacing,
        0.0f
      ));
      m_shader->SetUniformMat4f("model", model);
      m_shader->SetUniformMat3f("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
      renderSphere();
    }
  }

  // render light source (simply re-render sphere at light positions)
  // this looks a bit off as we use the same shader, but it'll make their positions obvious and 
  // keeps the codeprint small.
  for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
  {
    glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
    newPos = lightPositions[i];
    m_shader->SetUniform3f("lightPositions[" + std::to_string(i) + "]", newPos);
    m_shader->SetUniform3f("lightColors[" + std::to_string(i) + "]", lightColors[i]);

    model = glm::mat4(1.0f);
    model = glm::translate(model, newPos);
    model = glm::scale(model, glm::vec3(0.5f));
    m_shader->SetUniformMat4f("model", model);
    m_shader->SetUniformMat3f("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
    renderSphere();
  }
}

void PbrTextured::ImGuiUpdate()
{
}

// renders (and builds at first invocation) a sphere
// -------------------------------------------------
void PbrTextured::renderSphere()
{
  if (sphereVAO == 0)
  {
    glGenVertexArrays(1, &sphereVAO);

    unsigned int vbo, ebo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    const unsigned int X_SEGMENTS = 64;
    const unsigned int Y_SEGMENTS = 64;
    const float PI = 3.14159265359f;
    for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
    {
      for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
      {
        float xSegment = (float)x / (float)X_SEGMENTS;
        float ySegment = (float)y / (float)Y_SEGMENTS;
        float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
        float yPos = std::cos(ySegment * PI);
        float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

        positions.push_back(glm::vec3(xPos, yPos, zPos));
        uv.push_back(glm::vec2(xSegment, ySegment));
        normals.push_back(glm::vec3(xPos, yPos, zPos));
      }
    }

    bool oddRow = false;
    for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
    {
      if (!oddRow) // even rows: y == 0, y == 2; and so on
      {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
          indices.push_back(y * (X_SEGMENTS + 1) + x);
          indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
        }
      }
      else
      {
        for (int x = X_SEGMENTS; x >= 0; --x)
        {
          indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
          indices.push_back(y * (X_SEGMENTS + 1) + x);
        }
      }
      oddRow = !oddRow;
    }
    indexCount = static_cast<unsigned int>(indices.size());

    std::vector<float> data;
    for (unsigned int i = 0; i < positions.size(); ++i)
    {
      data.push_back(positions[i].x);
      data.push_back(positions[i].y);
      data.push_back(positions[i].z);
      if (normals.size() > 0)
      {
        data.push_back(normals[i].x);
        data.push_back(normals[i].y);
        data.push_back(normals[i].z);
      }
      if (uv.size() > 0)
      {
        data.push_back(uv[i].x);
        data.push_back(uv[i].y);
      }
    }
    glBindVertexArray(sphereVAO);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    unsigned int stride = (3 + 2 + 3) * sizeof(float);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
  }

  glBindVertexArray(sphereVAO);
  glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int PbrTextured::loadTexture(char const* path)
{
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
  if (data)
  {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  }
  else
  {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

void PbrTextured::CheckKeys(double delta_time)
{
  const float move_speed = 5.0f;
  const float t = (float)(delta_time);
  bool* keys = m_window.GetKeys().m_key_code;

  if (keys[GLFW_KEY_W])
    m_camera.MoveForward(-move_speed * t); //note the negative value needed to move forward

  if (keys[GLFW_KEY_S])
    m_camera.MoveForward(move_speed * t); //note the positive value needed to move backward

  if (keys[GLFW_KEY_A])
    m_camera.MoveRight(-move_speed * t);

  if (keys[GLFW_KEY_D])
    m_camera.MoveRight(move_speed * t);
}

void PbrTextured::OnEvent(Event& event)
{
  if (event.Type() == Event::kMouseMove)
  {
    EventMouseMove& e = dynamic_cast<EventMouseMove&>(event);
    auto* window = m_window.GlfwWindow();
    bool* keys = m_window.GetKeys().m_key_code;
    auto state = glfwGetMouseButton(window, static_cast<int32_t>(GLFW_MOUSE_BUTTON_MIDDLE));
    if (state == GLFW_PRESS)
    {
    }
    if (keys[GLFW_KEY_LEFT_CONTROL])
      m_camera.RotateWorld(e.delta_x * 0.03f, e.delta_y * 0.03f);
    else if (keys[GLFW_KEY_LEFT_SHIFT])
      m_camera.MoveForward((e.delta_x + e.delta_y) * 0.01f);
    else
      m_camera.RotateLocal(e.delta_x * 0.001f, e.delta_y * 0.05f);
  }

  if (event.Type() == Event::kMouseScroll)
  {
    EventMouseScroll& e = dynamic_cast<EventMouseScroll&>(event);
    m_camera.Zoom(e.y_offset);
  }

  if (event.Type() == Event::kKeyPressed)
  {
    /*EventKeyPressed& e = dynamic_cast<EventKeyPressed&>(event);
    if (e.key == GLFW_KEY_T)
    {
      if (m_controlled_camera == &m_camera)
        m_controlled_camera = m_camera_vis;
      else
        m_controlled_camera = &m_camera;
    }*/
  }
}
