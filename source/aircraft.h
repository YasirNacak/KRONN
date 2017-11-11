#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <stdlib.h>

#include <allegro5/allegro.h>

#define MAX_LEN 100

typedef struct aircraft_linked_list_s{
    char name[MAX_LEN];
    int team,
        health,
        type,
        direction,
        id,
        cost,
        speed,
        missile_type,
        special_attack_missile_type,
        is_follower,
        is_using_special_attack,
        special_attack_counter,
        size_x,
        size_y,
        pos_x,
        pos_y;
    ALLEGRO_BITMAP * sprite;
    struct aircraft_linked_list_s * next;
} aircraft_linked_list;

typedef struct aircraft_template_s{
    char name[MAX_LEN];
    int team,
        health,
        type,
        direction,
        id,
        cost,
        speed,
        missile_type,
        special_attack_missile_type,
        is_follower,
        is_using_special_attack,
        special_attack_counter,
        size_x,
        size_y,
        pos_x,
        pos_y;
    ALLEGRO_BITMAP * sprite;
} aircraft_template;

int aircraft_get_size(aircraft_linked_list * head);

void aircraft_add_new(aircraft_linked_list ** head, aircraft_template new_aircraft, int pos_x, int pos_y);

void aircraft_remove_index(aircraft_linked_list ** head, int index);

#endif
