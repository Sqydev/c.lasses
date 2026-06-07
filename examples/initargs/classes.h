#ifndef CLASSES_H
#define CLASSES_H

#include "../../include/Classes.h"

#include <stdarg.h>

extern class_t* PlayerClass;

typedef struct Player Player;
class_struct(Player); 
	void (*attack)(Player*);
};

void InitPlayer(object_t* object, va_list va);

#endif
