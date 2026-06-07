#include "../../include/Classes.h"

#include "./classes.h"

#include <stdarg.h>
#include <stdio.h>

void AttackByPlayer(Player* self) {
	printf("Attacked by obj id: %zu\n", self->base.id);
}

void InitPlayer(object_t* object, va_list va) {
	Player* self = (Player*)object;

	self->attack = AttackByPlayer;

	printf("Passed %d to InitPlayer\n", va_arg(va, int));
}
