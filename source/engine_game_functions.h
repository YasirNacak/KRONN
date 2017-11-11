#ifndef ENGINE_GAME_FUNCTIONS_H
#define ENGINE_GAME_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#include "aircraft.h"
#include "missile.h"
#include "explosions.h"
#include "scenario.h"

void game_autopilot_movement(aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, missile_template * missiles, int ticks, int screen_height, int screen_width);

void game_handle_input(ALLEGRO_EVENT event_keyboard, aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, missile_template * missiles, int screen_height, int screen_width);

void game_reset_current_lists(aircraft_linked_list ** aircraft_list, missile_linked_list ** missile_list, explosion_linked_list ** explosion_list);

void game_set_spawn_variables(int * enemy_spawn_frequency, int * random_enemy_range, int ticks, int spawnable_enemy_types_size);

void game_endless_spawn_enemies(aircraft_linked_list * aircraft_list, aircraft_template * aircrafts, int screen_height, int screen_width, int ticks);

void game_enemies_attack(aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, missile_template * missiles, int ticks);

void game_detect_collision(aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, explosion_linked_list * explosion_list, explosion_template explosions[255], float audio_level);

void game_move_entities(aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, int screen_height, int screen_width, int ticks);

void game_draw_sprites(aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, explosion_linked_list * explosion_list);

void game_check_health_levels(aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, float audio_level);

void game_scenario_check_health_levels(int * game_state, scenario_base current_scenario, aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, float audio_level);

void game_scenario_spawn_enemies(aircraft_linked_list * aircraft_list, aircraft_template * aircrafts, scenario_base current_scenario, int ticks);

void game_scenario_boss_behaviour(aircraft_linked_list * aircraft_list, scenario_base current_scenario);

void game_control_special_attack(aircraft_linked_list * aircraft_list, int * special_attack_ticks);

void game_calculate_high_scores(int score, int high_scores[11]);

void game_check_explosion_health_levels(explosion_linked_list * explosion_list);

#endif
