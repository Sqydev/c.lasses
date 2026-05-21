#include "../../include/Classes.h"

#include "./classes/player.h"

#include <stdio.h>

int main(void) {
	class_t* PlayerClass = RegisterClass(sizeof(Player), InitPlayer, NULL);

	Player* player = (Player*)CreateObject(PlayerClass);

	printf("player's position after creation is: %d, %d\n", player->positionX, player->positionY);

	player->movePlayer(player, UP);

	printf("player's position after moveUp is: %d, %d", player->positionX, player->positionY);

	return 0;
}
