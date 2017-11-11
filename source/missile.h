#ifndef MISSILE_H
#define MISSILE_H

#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

#define MAX_LEN 100

typedef struct missile_linked_list_s{
    int team,
        speed,
        health,
        type,
        is_follower,
        follow_accuracy,
        size_x,
        size_y,
        pos_x,
        pos_y;
    ALLEGRO_BITMAP * sprite;
    ALLEGRO_SAMPLE * hitsound;
    struct missile_linked_list_s * next;
} missile_linked_list;

typedef struct missile_template_s{
    int team,
        speed,
        health,
        type,
        is_follower,
        follow_accuracy,
        size_x,
        size_y,
        pos_x,
        pos_y;
    ALLEGRO_BITMAP * sprite;
    ALLEGRO_SAMPLE * hitsound;
} missile_template;

int missile_get_size(missile_linked_list * head);

void missile_add_new(missile_linked_list ** head, missile_template new_missile, int pos_x, int pos_y);

void missile_remove_index(missile_linked_list ** head, int index);

#endif
