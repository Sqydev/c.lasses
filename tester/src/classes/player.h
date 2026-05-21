#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include "../../../include/Classes.h"

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
} Direction;

typedef class_struct(Player);
// Or:
// typedef struct Player {
//     object_t base;
// It is accualy very interesting thing I found out fo I'll write why that works on the end of this file(I mean that (object_t)player reads base and (Player*)player is magicly and Player at the same time

	int positionX;
	int positionY;

	void (*movePlayer)(struct Player*, Direction);
} Player;

void InitPlayer(object_t* object);

#endif

// So. Becouse object_t base is the first object of the struct player and base have THE SAME ADDRES:0, and so when you write (Player*)it makes Player root object but with (object_t)It makes the base root struct. Soooo, I getting self mannualy is easier and I can pass object_t* and you can write Player* as argument to movePlayer() and I've sent you object and you'll get the only thing you'll get so Player* :) And why I can't use Player*? becouse I don't know what struct you're going to put there. So I use object_t* and that is everything that I need at the lib level and you have easy access to the structur(becouse in previous version accesing struct was a pain)
