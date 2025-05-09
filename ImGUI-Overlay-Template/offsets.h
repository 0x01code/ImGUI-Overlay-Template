#pragma once
#include <Windows.h>

namespace Offset
{
	uintptr_t ViewMatrix = 0x6A1BD0;
	uintptr_t EntityList = 0x70A458;
	uintptr_t EntityListNext = 0x20;

	uintptr_t HealthMax = 0x160;
	uintptr_t Health = 0x164;

	uintptr_t PositionHeadX = 0x4C;
	uintptr_t PositionHeadY = 0x50;
	uintptr_t PositionHeadZ = 0x54;

	uintptr_t PositionBottomX = 0x42C;
	uintptr_t PositionBottomY = 0x430;
	uintptr_t PositionBottomZ = 0x434;
}