#include "../../include/Classes.h"

#include "./classes.h"

int main() {
	class_t* EntityClass = RegisterClass(sizeof(Entity), InitEntity, NULL);
	class_t* PlayerClass = RegisterClass(sizeof(Player), InitPlayer, NULL);
}
