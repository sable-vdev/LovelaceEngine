#include <iostream>
#include "Mesh.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Logger.hpp"

class Model
{
public:
	Model(std::string path);
	void Draw(Shader& shader);
private:
	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
private:
	vector<Texture> m_texturesLoaded;
	vector<Mesh> m_meshes;
	std::string m_directory;
};