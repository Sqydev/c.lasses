#ifndef CLASSES_H
#define CLASSES_H

#include "../../include/Classes.h"

extern class_t* PlayerClass;

typedef struct Player Player;
class_struct(Player);
	char name[32];
	int hp;
	int score;
    
	poly_t* interact;
};

void Player_Init(object_t* obj);

#endif
