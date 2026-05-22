#include "../../include/Classes.h"

#include "./classes.h"

#include <stdio.h>

void AttackByPlayer(Player* self) {
	printf("Attacked by obj id: %zu\n", self->base.id);
}

void InitPlayer(object_t* object) {
	Player* self = (Player*)object;

	self->attack = AttackByPlayer;

	// Can be just self->parent = CreateObject(EntityClass); if parent is object_t but that way it's prettier
	self->parent = (Entity*)CreateObject(EntityClass);
}
