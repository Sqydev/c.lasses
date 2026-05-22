#include "../../include/Classes.h"

#include "./classes.h"
#include <stdio.h>

class_t* EntityClass;
class_t* PlayerClass;

int main() {
	EntityClass = RegisterClass(sizeof(Entity), InitEntity, NULL);
	PlayerClass = RegisterClass(sizeof(Player), InitPlayer, NULL);

	Player* player = (Player*)CreateObject(PlayerClass);

	$(player, attack);

	printf("Player X before move: %d\n", player->parent->positionX);
	$(player->parent, move, 10, 0);
	printf("Player X after move dx == 10 X: %d\n", player->parent->positionX);
}
