#include "Model.hpp"

static I32 creationCalls = 0;

void* operator new(size_t t)
{
	creationCalls++;
	return malloc(t);
}
I32U TextureFromFile(std::string& path, const std::string& directory, bool gamma = false)
{
	std::string filename = directory + "/" + path;

	I32U textureID;
	glGenTextures(1, &textureID);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = 0;
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
		Logger::Log(ERROR, "Texture failed to load at path: " + path);
		stbi_image_free(data);
	}
	Logger::Log(INFO, "Created texture with id: " + std::to_string(textureID));
	return textureID;
}

Model::Model(std::string path)
{
	LoadModel(path);
}

void Model::LoadModel(std::string path)
{
	//m_meshes.clear();
	//m_texturesLoaded.clear();
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, 
		aiProcess_Triangulate |           // Convert all primitives to triangles
		aiProcess_FlipUVs |               // Flip UV coordinates for OpenGL
		aiProcess_CalcTangentSpace |      // Calculate tangents/bitangents
		aiProcess_GenNormals |            // Generate normals if missing
		aiProcess_JoinIdenticalVertices | // Join identical vertices (VERY important for OBJ)
		aiProcess_ImproveCacheLocality |  // Optimize for cache
		aiProcess_OptimizeMeshes |        // Optimize mesh data
		aiProcess_ValidateDataStructure);  // Validate the data

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Logger::Log(ERROR, importer.GetErrorString());
		return;
	}

	m_directory = path.substr(0, path.find_last_of('/'));
	m_meshes.reserve(scene->mRootNode->mNumChildren);
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (I32U i = 0; i < node->mNumMeshes; i++)
	{
		m_meshes.push_back(ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene));
	}

	for (I32U i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vertices.reserve(mesh->mNumVertices);
	vector<I32U> indices;
	vector<Texture> textures;

	for (I32U i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

		if (mesh->HasNormals())
		{
			vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		}

		if (mesh->mTextureCoords[0])
		{
			vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}

		vertices.push_back(vertex);
	}

	I32U numIndices = 0;
	for (I32U i = 0; i < mesh->mNumFaces; i++)
	{
		numIndices += mesh->mFaces[i].mNumIndices;
	}

	indices.reserve(numIndices);
	for (I32U i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace& face = mesh->mFaces[i];
		indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
	}

	aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
	vector<Texture> diffuseMaps = LoadMaterialTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	vector<Texture> specularMaps = LoadMaterialTextures(mat, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	return Mesh(vertices, indices, textures);
}

vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	vector<Texture> textures;
	textures.reserve(1);
	for (I32U i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		std::string path;
		mat->GetTexture(type, i, &str);
		path = str.C_Str();

		auto it = m_texturesLoaded.find(path);
		if (it != m_texturesLoaded.end())
		{
			textures.push_back(it->second);
		}
		else
		{
			Texture texture;
			texture.id = TextureFromFile(path, m_directory);
			texture.type = typeName;
			texture.path = path;
			m_texturesLoaded[path] = texture;
			textures.emplace_back(std::move(texture));
		}
	}
	return textures;
}

void Model::Draw(Shader& shader)
{
	for (Mesh& mesh : m_meshes)
	{
		mesh.Draw(shader);
	}
}