#pragma once

#include "stdafx.h"

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// Bone
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
struct asBone
{
	int Index;
	string Name;

	int Parent;
	Matrix Transform;
};

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// Mesh
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
struct asMeshPart
{
	string MaterialName;

	UINT StartVertex;
	UINT VertexCount;

	UINT StartIndex;
	UINT IndexCount;
};

struct asMesh
{
	int BoneIndex;

	vector<SkeletalMesh::VertexSkeletalMesh > Vertices;
	vector<UINT> Indices;

	vector<asMeshPart*> MeshParts;
};

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// Material
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
struct asMaterial
{
	string Name;

	Color Ambient;
	Color Diffuse;
	Color Specular;
	Color Emissive;

	string DiffuseFile;
	string SpecularFile;
	string NormalFile;
};

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// Skin
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式

struct asBlendWeight
{
	Vector4 Indices = Vector4(0, 0, 0, 0);
	Vector4 Weights = Vector4(0, 0, 0, 0);

	void Set(UINT index, UINT boneIndex, float weight)
	{
		float i = boneIndex;
		float w = weight;

		switch (index)
		{
			case 0: Indices.x = i; Weights.x = weight; break;
			case 1: Indices.y = i; Weights.y = weight; break;
			case 2: Indices.z = i; Weights.z = weight; break;
			case 3: Indices.w = i; Weights.w = weight; break;
		}
	}
};

struct asBoneWeight
{
private:
	typedef pair<int, float> Pair;
	vector<Pair> BoneWeights;

public:
	void AddWeights(UINT boneIndex, float boneWeight)
	{
		if (boneWeight <= 0) return;

		bool bAdd = false;

		vector<Pair>::iterator it = BoneWeights.begin();
		while(it != BoneWeights.end())
		{
			if (boneWeight > it->second)
			{
				BoneWeights.insert(it, Pair(boneIndex, boneWeight));

				bAdd = true;
				break;
			}

			it++;
		}

		if (bAdd == false)
			BoneWeights.push_back(Pair(boneIndex, boneWeight));
	}

	void Normalize()
	{
		int i = 0;
		vector<Pair>::iterator it = BoneWeights.begin();

		float totalWeight = 0.f;

		while (it != BoneWeights.end())
		{
			if (i < 4)
			{
				totalWeight += it->second;
				i++; it++;
			}
			else
			{
				it = BoneWeights.erase(it);
			}
		}

		float scale = 1.f / totalWeight;

		it = BoneWeights.begin();
		while (it != BoneWeights.end())
		{
			it->second *= scale;
			it++;
		}
	}

	void GetBlendWeights(asBlendWeight& blendWeights)
	{
		for (UINT i = 0; i < BoneWeights.size(); i++)
		{
			if (i >= 4) return;
			blendWeights.Set(i, BoneWeights[i].first, BoneWeights[i].second);
		}

	}
};

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// Animation
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// 1 Bone, 1 Frame
struct asKeyframeData
{
	float Frame;

	Vector3 Scale;
	Quaternion Rotation;
	Vector3 Translation;

};

// 1 Bone , All Frames
struct asKeyframe
{
	string BoneName;
	vector<asKeyframeData> Transforms;
};

// All bones, All Frames (Final)
struct asClip
{
	string Name;

	UINT FrameCount;
	float FrameRate;	// 60FPS, 30FPS

	vector<asKeyframe*> Keyframes;

};

// Cache for Retarget
struct asClipNode
{
	aiString Name;
	vector<asKeyframeData> keyframe;
};
