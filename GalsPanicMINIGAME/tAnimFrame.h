#pragma once
#include "struct.h"

struct tAnimFrame
{
	Vec2	vLeftTop;	// 좌상단 좌표 정보
	Vec2	vSlice;		// vLeftTop 기준으로 얼마큼 크기만큼 자를건지?
	Vec2	vOffset;	// 피벗 위치 (실제 좌표)
	float	fDuration;	// 프레임 지속시간
};