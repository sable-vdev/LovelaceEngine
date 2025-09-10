#include "Mesh.hpp"

Mesh::Mesh(vector<Vertex>& vertices, vector<I32U>& indices, vector<Texture>& textures) :
	vertices(vertices), indices(indices), textures(textures)
{
	SetupMesh();
}
/*
Mesh::~Mesh()
{
	if(m_vao != 0) glDeleteVertexArrays(1, &m_vao);
	if(m_vbo != 0) glDeleteBuffers(1, &m_vbo);
	if(m_ebo != 0) glDeleteBuffers(1, &m_ebo);
}
*/
void Mesh::SetupMesh()
{
	/*
	m_vboB = Buffer(GL_ARRAY_BUFFER, vertices.data(), vertices.size() * sizeof(Vertex));
	m_eboB = Buffer(GL_ELEMENT_ARRAY_BUFFER, indices.data(), indices.size() * sizeof(I32U));

	VertexBufferLayout vbl;
	vbl.Push<float>(3); //position
	vbl.Push<float>(3); //normal
	vbl.Push<float>(2); //texcoord
	m_vaoB.Bind();
	m_vaoB.AddBuffer(m_vboB, vbl);

	m_eboB.Bind();

	m_vaoB.Unbind();
	m_vboB.Unbind();
	m_eboB.Unbind();
	*/
	
	// create buffers/arrays
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader)
{
	shader.Bind();
	I32U diffuseNr = 1;
	I32U specularNr = 1;

	for (I32U i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		//shader.ActivateTexture(i);
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		GLint location = glGetUniformLocation(shader.GetShaderId(), (name + number).c_str());
		if (location != -1)
		{
			shader.SetUniform1i((name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		//shader.SetUniform1i((name + number).c_str(), i);
	}

	//m_vaoB.Unbind();


	glBindVertexArray(m_vao);
	//m_vaoB.Bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	//m_vaoB.Unbind();
	glActiveTexture(GL_TEXTURE0);
}