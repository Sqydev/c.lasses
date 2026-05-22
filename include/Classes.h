/*
* Copyright (c) 2025-present Wojciech Kaptur ( _Sqyd_ / Sqydev )
* Github: https://github.com/Sqydev
* GPG Fingerprint: 6DC2516B0DFDA9C59661650722F7B8A777F33B56
* 
* This software is provided "as-is", without any express or implied warranty. In no event
* will the authors be held liable for any damages arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose, including commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
* 
* 1. Non-Misrepresentation: The origin of this software must not be misrepresented; 
*	you must not claim that you wrote the original software. An acknowledgment in 
*	product documentation is appreciated but not required.
* 
* 2. Source-Level Copyleft: Any altered versions (forks) of this software's source code, 
*	or files containing significant portions of this code, must be distributed under 
*	these same license terms. Such modified source code must be made publicly available 
*	to any recipient, even if used over a network (SaaS).
* 
* 3. Proprietary Integration: This software may be integrated into, linked with, or 
*	used as a component of proprietary and closed-source products. In such cases, 
*	the surrounding proprietary application code does not need to be disclosed, 
*	provided that the original or modified source code of THIS software remains 
*	available under the terms of Section 2.
* 
* 4. Persistent Metadata: All original credits, including those in the source code headers 
*	and binary metadata (e.g., ELF .comment section, PE StringFileInfo, or equivalent), 
*	must not be removed. You may add your own credits to forks, provided the original 
*	authorship remains clearly identified.
* 
* 5. Notice Retention: This license notice may not be removed or altered from any 
*	source or binary distribution.
*/

#ifndef CLASSES_LIB_H
#define CLASSES_LIB_H

#define CLASSES_VERSION_MAJOR 1
#define CLASSES_VERSION_MINOR 0
#define CLASSES_VERSION_PATCH 0

// NOTE: Thoes library specyfiers
#if defined(_WIN32) || defined (_WIN64)
	#if defined(__TINYC__)
		#define __declspec(x) __attribute__((x))
	#endif
	#if defined(BUILD_LIBTYPE_SHARED)
		#define RLAPI __declspec(dllexport)
	#elif defined(USE_LIBTYPE_SHARED)
		#define RLAPI __declspec(dllimport)
	#endif
#else
	#if defined(BUILD_LIBTYPE_SHARED)
		#define RLAPI __attribute__((visibility("default")))
	#endif
#endif

#ifndef RLAPI
	#define RLAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#define Class class_t
#define Object object_t

#define class_struct(name) struct name { object_t base

#define Self(cls, object) (cls*)object

typedef struct class_t class_t;
typedef struct object_t object_t;

struct class_t {
	size_t id;
	size_t index;

	void (*initTask)(object_t*);
	void (*cleanupTask)(object_t*);

	object_t** objects;

	size_t objectSize;

	size_t lastObjectId;
	size_t objectsCount;
};

struct object_t {
	size_t id;
	size_t index;

	class_t* root;
};

RLAPI class_t* RegisterClass(size_t objectSizeof, void (*initTask)(object_t*), void (*cleanupTask)(object_t*));
RLAPI void DestroyAllClasses(void);
RLAPI object_t* CreateObject(class_t* cls);
RLAPI void DestroyObject(object_t* object);
RLAPI void DestroyClass(class_t* cls);

#ifdef __cplusplus
}
#endif

#endif
