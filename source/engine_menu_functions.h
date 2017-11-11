#ifndef ENGINE_MENU_FUNCTIONS
#define ENGINE_MENU_FUNCTIONS

#include <stdio.h>
#include <string.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>

#include "aircraft.h"
#include "missile.h"
#include "scenario.h"
#include "explosions.h"

typedef struct menu_button_s{
    char text[50];
    int effect;
} menu_button;

void menu_fade_out(float audio_level);

int get_menu_button_size(menu_button button_array[10]);

void parse_menu_button_data(menu_button button_array[10], char * filename);

void parse_game_text_data(char result[20][50], char * filename);

void menu_main_menu(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, ALLEGRO_EVENT event_keyboard, int * game_state, int * selected_button, int screen_height, int screen_width, menu_button main_menu_buttons[10], char main_menu_text[5][50], float audio_level);

void menu_scenario_choose_scenario(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, ALLEGRO_EVENT event_keyboard, int * game_state, int * selected_button, int * selected_scenario, int screen_height, int screen_width, menu_button scenario_choose_scenario_buttons[10], char scenario_choose_scenario_text[20][50], float audio_level);

void menu_scenario_description(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, ALLEGRO_EVENT event_keyboard, int * is_music_playing, int * game_state, int screen_height, int screen_width, missile_linked_list ** missile_list, aircraft_linked_list ** aircraft_list, explosion_linked_list ** explosion_list, missile_template missiles[255], aircraft_template aircrafts[255], explosion_template explosions[255], scenario_base current_scenario, menu_button scenario_description_buttons[10], float audio_level);

void menu_scenario_win(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, int screen_height, int screen_width, char scenario_win_text[20][50]);

void menu_scenario_lose(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, int screen_height, int screen_width, char scenario_lose_text[20][50]);

void menu_endless_choose_plane(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, ALLEGRO_EVENT event_keyboard, int * is_music_playing, int * game_state, int * selected_button, int screen_height, int screen_width, missile_linked_list ** missile_list, aircraft_linked_list ** aircraft_list, explosion_linked_list ** explosion_list, missile_template missiles[255], aircraft_template aircrafts[255], explosion_template explosions[255], menu_button endless_choose_plane_buttons[10], char endless_choose_plane_text[5][50], float audio_level);

void menu_game_over_endless_mode(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, int score, int screen_height, int screen_width, char game_over_endless_mode_text[5][50]);

void menu_high_scores(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, int high_scores[11], int screen_height, int screen_width, char high_scores_text[20][50]);

#endif
