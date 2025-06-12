#pragma once
#include <globals/imports.h>
#include <sdk/maths/vecTor.h>
#include <globals/offsets.h>

enum BoneIndex : DWORD
{
	HEAD = 6,
	NECK = 5,
	CHEST = 4,
	STOMACH = 2,
	COCK = 0,
	LSHOULDER = 8,
	LARM = 9,
	LHAND = 10,
	RSHOULDER = 13,
	RARM = 14,
	RHAND = 15,
	LTHIGH = 22,
	LCALF = 23,
	LFOOT = 24,
	RTHIGH = 25,
	RCALF = 26,
	RFOOT = 27,
};

struct BoneConnection // Bone Connection Struct
{
	INT bone1;
	INT bone2;

	BoneConnection(INT b1, INT b2) : bone1(b1), bone2(b2) {}
};

namespace BoneConnectionList
{
	inline BoneConnection Connections[16] = {
			BoneConnection(6, 5),	// HEAD To NECK
			BoneConnection(5, 4),	// NECK To SPINE
			BoneConnection(4, 0),	// SPINE To HIP
			BoneConnection(4, 8),	// SPINE To LSHOULDER
			BoneConnection(8, 9),	// LSHOULDER To LARM
			BoneConnection(9, 11),	// LARM To HAND
			BoneConnection(4, 13),  // CHEST To RSHOULDER
			BoneConnection(13, 14), // RSHOULDER To RARM
			BoneConnection(14, 16), // RARM To ---
			BoneConnection(4, 2),	// SPINE To SPINE_1
			BoneConnection(0, 22),	// HIP To LEFT_HIP
			BoneConnection(0, 25),	// HIP To RIGHT_HIP
			BoneConnection(22, 23), // LEFT_HIP To LEFT_knee
			BoneConnection(23, 24), // LEFT knee To LEFT foot
			BoneConnection(25, 26), // RIGHT_HIP To RIGHT_knee
			BoneConnection(26, 27)	// RIGHT knee To RIGHT foot
	};
}
