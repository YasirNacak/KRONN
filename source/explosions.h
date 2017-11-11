#ifndef EXPLOSIONS_H
#define EXPLOSIONS_H

#include <stdlib.h>

#include <allegro5/allegro.h>

typedef struct explosion_linked_list_s{
    ALLEGRO_BITMAP * sprites[4];
    int     health,
            pos_x,
            pos_y,
            ticks;
    struct explosion_linked_list_s * next;
} explosion_linked_list;

typedef struct explosion_template_s{
    ALLEGRO_BITMAP * sprites[4];
    int     health,
            pos_x,
            pos_y,
            ticks;
} explosion_template;

void explosion_add_new(explosion_linked_list ** head, explosion_template new_explosion, int pos_x, int pos_y);

void explosion_remove_index(explosion_linked_list ** head, int index);

void explosion_setup_base(explosion_template explosions[255]);

#endif
