#include "./classes.h"

#include <stdio.h>
#include <string.h>

class_t* PlayerClass = NULL;

void _interact_with_int(object_t* self_obj, poly_arg_t* a, size_t n) {
	(void)n;
    Player* self = (Player*)self_obj;
    int damage = a[0].i;
    self->hp -= damage;
    printf("[%s] TOOK DAMAGE (int): %d. Remaining HP: %d\n", self->name, damage, self->hp);
}

void _interact_with_string(object_t* self_obj, poly_arg_t* a, size_t n) {
	(void)n;
    Player* self = (Player*)self_obj;
    const char* item_name = a[0].s;
    self->score += 10;
    printf("[%s] Interacted: \"%s\"! +10 (Sum: %d)\n", self->name, item_name, self->score);
}

void _interact_with_other_player(object_t* self_obj, poly_arg_t* a, size_t n) {
	(void)n;
    Player* self  = (Player*)self_obj;
    Player* other = (Player*)a[0].p;
    printf("[%s] Interacted with: %s!\n", self->name, other->name);
}

void Player_Init(object_t* obj) {
    Player* self = (Player*)obj;
    strcpy(self->name, "What?");

    self->hp = 100;
    self->score = 0;

    self->interact = CreatePoly();

    PolyReg(self->interact, _interact_with_int, PM_INT);
    PolyReg(self->interact, _interact_with_string, PM_STR);
    PolyReg(self->interact, _interact_with_other_player, PM_OBJ(PlayerClass));
}
