#ifndef CLASSES_H
#define CLASSES_H

#include "../../include/Classes.h"

typedef class_struct(Entity);
	int positionX;
	int positionY;

	void (*move)(object_t*, int dx, int dy);
} Entity;

typedef class_struct(Player); 
	Entity* parent;

	void (*attack)(object_t* self);
} Player;

void InitEntity(object_t* object);
void InitPlayer(object_t* object);

#endif
