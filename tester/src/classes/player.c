#include "./player.h"

void movePlayer(Player* self, Direction dir) {
	if(dir == UP) { self->positionY++; }
	if(dir == DOWN) { self->positionY--; }
	if(dir == RIGHT) { self->positionX++; }
	if(dir == LEFT) { self->positionX--; }
}

void InitPlayer(object_t* object) {
	Player* self = Self(Player, object);
	// Or: Player* self = (Player*)object;

	self->positionX = 10;
	self->positionY = 20;

	self->movePlayer = movePlayer;
}
