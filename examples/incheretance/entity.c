#include "../../include/Classes.h"

#include "./classes.h"

void MoveEntity(Entity* self, int dx, int dy) {
	self->positionX = dx;
	self->positionY = dy;
}

void InitEntity(object_t* object) {
	Entity* self = Self(Entity, object);

	self->positionX = 0;
	self->positionY = 0;

	self->move = MoveEntity;
}
