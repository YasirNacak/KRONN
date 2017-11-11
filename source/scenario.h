#ifndef SCENARIO_H
#define SCENARIO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "aircraft.h"

typedef struct scenario_enemy_s{
    int spawn_time, type, pos_x, pos_y;
} scenario_enemy;

typedef struct scenario_base_s{
    char title[50], description[20][50];
    int ally_aircraft_type, win_enemy_aircraft_type;
    scenario_enemy enemy_list[100];
} scenario_base;

void parse_scenario_data(scenario_base scenarios[20], int screen_height, int screen_width, aircraft_template * aircrafts);

#endif
