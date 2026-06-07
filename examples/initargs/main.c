#include "../../include/Classes.h"

#include "./classes.h"
#include <stdio.h>

class_t* PlayerClass;

int main() {
	PlayerClass = RegisterClass(sizeof(Player), InitPlayer, NULL);

	Player* player = (Player*)CreateObject(PlayerClass, 10);

	player->attack(player);
}
