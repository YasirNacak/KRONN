#ifndef ENGINE_HUD_FUNCTIONS_H
#define ENGINE_HUD_FUNCTIONS_H

#include <stdio.h>
#include <string.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>

#include "aircraft.h"
#include "missile.h"

void hud_load_sprites(ALLEGRO_BITMAP * hud_special_attack[5], ALLEGRO_BITMAP * hud_health[3]);

void hud_draw_health(ALLEGRO_BITMAP * hud_health[3], aircraft_linked_list * aircraft_list, int screen_height, int screen_width);

void hud_draw_special_power(ALLEGRO_BITMAP * hud_special_power[3], ALLEGRO_FONT * game_font, aircraft_linked_list * aircraft_list, int special_attack_ticks, int screen_height, int screen_width, char endless_in_game_text[5][50]);

void hud_draw_score(int * score, int ticks, ALLEGRO_FONT * game_font, char endless_in_game_text[5][50]);

#endif
