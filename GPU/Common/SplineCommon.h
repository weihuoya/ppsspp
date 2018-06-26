// Copyright (c) 2013- PPSSPP Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0 or later versions.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official git repository and contact information can be found at
// https://github.com/hrydgard/ppsspp and http://www.ppsspp.org/.

#pragma once

#include "Common/CommonTypes.h"
#include "Common/Swap.h"
#include "GPU/Math3D.h"
#include "GPU/ge_constants.h"

// PSP compatible format so we can use the end of the pipeline in beziers etc
struct SimpleVertex {
	float uv[2];
	union {
		u8 color[4];
		u32_le color_32;
	};
	Vec3Packedf nrm;
	Vec3Packedf pos;
};

// We decode all vertices into a common format for easy interpolation and stuff.
// Not fast but can be optimized later.

struct SplineBezierBatch {
	u8  *batchVertices = nullptr;
	u16 *batchIndices = nullptr;
	int batchVertexCount = 0;
	int batchIndexCount = 0;
	GEPrimitiveType batchPrimType;
	u32 batchVertType;
	u32 batchOrigVertType;
	u32 batchVertTypeID;
	int maxVertexCount;

	
	// Bezier: These are used to generate UVs.
	int u_index, v_index;
	int index;

	// Spline
	int count_u;
	int count_v;
	int type_u;
	int type_v;

	// common
	int tess_u;
	int tess_v;
	const SimpleVertex **points;
	GEPatchPrimType primType;
	bool computeNormals;
	bool patchFacing;
};

enum SplineBezierQuality {
	LOW_QUALITY = 0,
	MEDIUM_QUALITY = 1,
	HIGH_QUALITY = 2,
};

// for ge debugger preview
void TessellateSplinePatch(SplineBezierBatch &spatch);
void TessellateBezierPatch(SplineBezierBatch &bezier);
