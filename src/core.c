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

#include "../include/Classes.h"

#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>

class_t** Classes = NULL;
size_t classesCount = 0;
size_t classesLastIndex = 0;
size_t classesLastId = 0;

bool Inited = false;

object_t* FindObjectById(class_t* cls, size_t id) {
	for(size_t i = 0; i < cls->objectsCount; i++) {
		if(cls->objects[i]->id == id) { return cls->objects[i]; }
	}
	return NULL;
}

class_t* FindClassById(size_t id) {
	for(size_t i = 0; i < classesCount; i++) {
		if(Classes[i]->id == id) { return Classes[i]; }
	}
	return NULL;
}

void ForEachObject(class_t* cls, void (*function)(object_t*)) {
	for(size_t i = 0; i < cls->objectsCount; i++) {
		function(cls->objects[i]);
	}
}

class_t* RegisterClass(size_t objectSizeof, void (*initTask)(object_t*), void (*cleanupTask)(object_t*)) {
	classesCount++;

	class_t** tmp_classes = realloc(Classes, classesCount * sizeof(class_t*));
	if(!tmp_classes) {
		errno = ENOMEM;
		return NULL;
	}
	Classes = tmp_classes;

	class_t* tmp_class = malloc(sizeof(class_t));
	if(!tmp_class) {
		classesCount--;
		errno = ENOMEM;
		return NULL;
	}
	Classes[classesLastIndex] = tmp_class;

	Classes[classesLastIndex]->index = classesLastIndex;
	Classes[classesLastIndex]->id = classesLastId;
	classesLastId++;

	Classes[classesLastIndex]->initTask = initTask;
	Classes[classesLastIndex]->cleanupTask = cleanupTask;

	Classes[classesLastIndex]->objects = NULL;
	Classes[classesLastIndex]->objectsCount = 0;

	Classes[classesLastIndex]->objectSize = objectSizeof;

	Classes[classesLastIndex]->lastObjectId = 0;

	classesLastIndex++;

	return Classes[classesLastIndex - 1];
}

void DestroyAllClasses(void) {
    for(size_t i = 0; i < classesCount; i++) {
        for(size_t j = 0; j < Classes[i]->objectsCount; j++) {
            if(Classes[i]->cleanupTask) {
				Classes[i]->cleanupTask(Classes[i]->objects[j]);
			}
            free(Classes[i]->objects[j]);
        }
        free(Classes[i]->objects);
        free(Classes[i]);
    }
    free(Classes);
    Classes = NULL;
    classesCount = 0;
    classesLastIndex = 0;

	Inited = false;
}

object_t* CreateObject(class_t* cls) {
	if(!Inited) { atexit(DestroyAllClasses); Inited = true; }

	cls->objectsCount++;

	object_t** tmp_objs = realloc(cls->objects, cls->objectsCount * sizeof(object_t*));
	if(!tmp_objs) {
		errno = ENOMEM;
		return NULL;
	}
	cls->objects = tmp_objs;
	object_t* tmp_obj = calloc(1, cls->objectSize);
	if(!tmp_obj) {
		cls->objectsCount--;
		errno = ENOMEM;
		return NULL;
	}
	cls->objects[cls->objectsCount - 1] = tmp_obj;

	cls->objects[cls->objectsCount - 1]->root = cls;

	cls->objects[cls->objectsCount - 1]->id = cls->lastObjectId;

	cls->objects[cls->objectsCount - 1]->index = cls->objectsCount - 1;
    cls->lastObjectId++;

    if(cls->initTask) {
		cls->initTask(cls->objects[cls->objectsCount - 1]);
	}
    
	return cls->objects[cls->objectsCount - 1];
}

void DestroyObject(object_t* object) {
	if(Classes == NULL) { return; }

	if(object->root->cleanupTask) { object->root->cleanupTask(object); }

	for(size_t i = object->index; i < object->root->objectsCount - 1; i++) {
		object->root->objects[i] = object->root->objects[i + 1];
		object->root->objects[i]->index = i;
	}
	object->root->objectsCount--;

	if(object->root->objectsCount > 0) {
		object->root->objects = realloc(object->root->objects, object->root->objectsCount * sizeof(object_t*));
	}
	else {
		free(object->root->objects);
		object->root->objects = NULL;
    }

	free(object);
}

void DestroyClass(class_t* cls) {
	if(Classes == NULL) { return; }

	for(size_t i = 0; i < cls->objectsCount; i++) {
		if(cls->cleanupTask) { cls->cleanupTask(cls->objects[i]); }
		free(cls->objects[i]);
	}

	free(cls->objects);

	for(size_t i = cls->index; i < classesCount - 1; i++) {
		Classes[i] = Classes[i + 1];
		Classes[i]->index = i;
	}
	classesCount--;
	classesLastIndex--;

	// Cls is already not in Classes
	free(cls);
	if(classesCount > 0) {
    	Classes = realloc(Classes, classesCount * sizeof(class_t*));
	}
	else {
    	free(Classes);
    	Classes = NULL;
	}
}
