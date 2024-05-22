#include "Framework.h"
#include "SkeletalMeshClip.h"

SkeletalMeshKeyframe* SkeletalMeshClip::Keyframe(wstring boneName)
{
	if (keyframesMap.count(name) < 1)
		return nullptr;

	return keyframesMap[boneName];
}
