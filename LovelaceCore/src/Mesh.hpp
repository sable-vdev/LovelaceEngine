#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "Shader.hpp"
#include "Buffer.hpp"
#include "VertexArrayObject.hpp"

template <typename T> 
using vector = std::vector<T>;
typedef uint32_t I32U; // stole the naming from game engine architecture book

struct Vertex
{
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 normal = glm::vec3(0.0f);
	glm::vec2 texCoords = glm::vec2(0.0f);
};

struct Texture
{
	std::string type;
	std::string path;
	I32U id;
};

class Mesh
{
public:
	Mesh(vector<Vertex>& vertices, vector<I32U>& indices, vector<Texture>& textures);
	//~Mesh();
	void Draw(Shader& shader);
private:
	void SetupMesh();
public:
	vector<Vertex> vertices;
	vector<I32U> indices;
	vector<Texture> textures;
private:
	I32U m_vao = 0, m_vbo = 0, m_ebo = 0;
	VAO m_vaoB;
	Buffer m_vboB;
	Buffer m_eboB;
};