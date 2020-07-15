#pragma once

#ifdef OcclusionDLL
#define SOUND_API __declspec(dllexport)
#else
#define SOUND_API __declspec(dllimport)
#endif
