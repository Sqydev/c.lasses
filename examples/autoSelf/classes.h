#ifndef CLASSES_H
#define CLASSES_H

#include "../../include/Classes.h"

extern class_t* EntityClass;
extern class_t* PlayerClass;

typedef struct Entity Entity;
class_struct(Entity);
	int positionX;
	int positionY;

	void (*move)(Entity*, int dx, int dy);
};

typedef struct Player Player;
class_struct(Player); 
	Entity* parent;

	void (*attack)(Player*);
};

void InitEntity(object_t* object);
void InitPlayer(object_t* object);

#endif
