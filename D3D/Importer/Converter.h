#pragma once

class Converter
{
public:
	Converter();
	~Converter();

	void ReadFile(wstring file);

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// Export Bone, Mesh Data
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
public:
	void ExportMesh(wstring savePath);

private:
	void ReadBoneData(aiNode* node, int index, int parent);
	void ReadMeshData(aiNode* node, int index);
	void ReadSkinData();
	void WriteMeshData(wstring savePath);	// *.mesh

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// Export Bone, Mesh Data
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
public:
	void ExportMatrial(wstring savePath, bool bOverWrite = true);

private:
	void ReadMaterialData();
	bool FoundMaterialData(aiMaterial* material);
	void WriteMaterialData(wstring savePath);
	string WriteTexture(string saveFolder, string file);

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// Export Animation
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
public:
	void ExportAnimClip(UINT index, wstring savePath);

private:
	struct asClip* ReadClipData(aiAnimation* animation);		// aiMesh, aiBone, aiMaterial
	void ReadKeyframeData(struct asClip* clip, aiNode* node, vector<struct asClipNode>& aniNodeInfos);	// Retarget
	void WriteClipData(struct asClip* clip, wstring savePath);
private:
	wstring file;

	Assimp::Importer* importer;
	const aiScene* scene;

	vector<struct asBone*> bones;
	vector<struct asMesh*> meshes;
	vector<struct asMaterial*> materials;
};
