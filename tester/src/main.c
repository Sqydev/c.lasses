#include "../../include/Classes.h"
#include <stdio.h>

typedef struct {
	int positionX;
	int positionY;
} ClassStructure;

void InitClass(object_t* object) {
	ClassStructure* data = SFV(ClassStructure, object);

	data->positionX = 10;
	data->positionY = 20;
}

int main(void) {
	class_t* TestClass = RegisterClass(sizeof(ClassStructure), InitClass, NULL);

	object_t* player = CreateObject(TestClass);

	printf("player's position after creation is: %d, %d", SFV(ClassStructure, player)->positionX, SFV(ClassStructure, player)->positionY);

	return 0;
}
