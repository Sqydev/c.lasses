#include "classes.h"

#include <stdio.h>

int main(void) {
    PlayerClass = RegisterClass(sizeof(struct Player), Player_Init, NULL);

    Player* player1 = (Player*)CreateObject(PlayerClass);
    Player* player2 = (Player*)CreateObject(PlayerClass);

    snprintf(player1->name, sizeof(player1->name), "Namener");
    snprintf(player2->name, sizeof(player2->name), "Plumkator");

    $P(player1->interact, player1, PM_A("PAMPITOM(It's item)"));
    $P(player1->interact, player1, PM_A(15));
    $P(player1->interact, player1, PM_A((object_t*)player2));

    return 0;
}
