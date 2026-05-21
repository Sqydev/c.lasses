#include "../../include/Classes.h"

#include <stdio.h>

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
} Direction;

typedef struct {
	int positionX;
	int positionY;

	void (*movePlayer)(object_t*, Direction);
} ClassStructure;

void movePlayer(object_t* object, Direction dir) {
	if(dir == UP) { SFV(ClassStructure, object)->positionY++; }
	if(dir == DOWN) { SFV(ClassStructure, object)->positionY--; }
	if(dir == RIGHT) { SFV(ClassStructure, object)->positionX++; }
	if(dir == LEFT) { SFV(ClassStructure, object)->positionX--; }
}

void InitClass(object_t* object) {
	ClassStructure* data = SFV(ClassStructure, object);

	data->positionX = 10;
	data->positionY = 20;

	data->movePlayer = movePlayer;
}

int main(void) {
	class_t* TestClass = RegisterClass(sizeof(ClassStructure), InitClass, NULL);

	object_t* player = CreateObject(TestClass);

	printf("player's position after creation is: %d, %d\n", SFV(ClassStructure, player)->positionX, SFV(ClassStructure, player)->positionY);

	SFV(ClassStructure, player)->movePlayer(player, UP);

	printf("player's position after moveUp is: %d, %d", SFV(ClassStructure, player)->positionX, SFV(ClassStructure, player)->positionY);

	return 0;
}
