#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_color.h>

#include "aircraft.h"
#include "aircraft_parser.h"

#include "missile.h"
#include "missile_parser.h"

#include "explosions.h"

#include "engine_game_functions.h"
#include "engine_hud_functions.h"
#include "engine_menu_functions.h"

#include "scenario.h"

#define frames_per_second 60.0

int main(){
    int is_game = 1, game_state = 1, is_music_playing = 0, is_fullscreen = 0,
        selected_button = 0, selected_scenario = 0,
        ticks = 0, special_attack_ticks = 0, score = 0, high_scores[11],
        screen_height = 640, screen_width = 480,
        aircrafts_size = 0, missiles_size = 0;
    float audio_level = 0;
    FILE * player_config_krcfg;
    char    endless_in_game_text[20][50], game_over_endless_mode_text[20][50], main_menu_text[20][50],
            endless_choose_plane_text[20][50], high_scores_text[20][50], scenario_choose_scenario_text[20][50],
            scenario_win_text[20][50], scenario_lose_text[20][50];

    /**Reads config data for the player*/
    player_config_krcfg = fopen("data/playerconfig/player_config.krcfg", "rt");
    fscanf(player_config_krcfg, "%d %d %f", &screen_height, &screen_width, &audio_level);
    if(screen_height == -1 && screen_width == -1) is_fullscreen = 1;
    fclose(player_config_krcfg);

    /**Allegro specific data types*/
    ALLEGRO_DISPLAY * display;
    ALLEGRO_DISPLAY_MODE display_data;
    ALLEGRO_EVENT_QUEUE * event_queue_timer, * event_queue_keyboard;
    ALLEGRO_EVENT event_timer, event_keyboard;
    ALLEGRO_TIMER * timer;
    ALLEGRO_FONT * game_font_small, * game_font_medium, * game_font_large, * game_font_huge;
    ALLEGRO_BITMAP * hud_special_attack[5], * hud_health[3], * game_background;
    ALLEGRO_SAMPLE * game_music, * menu_music;

    /**Project specific data types*/
    aircraft_template aircrafts[255];
    aircraft_linked_list * aircraft_list;

    missile_template missiles[255];
    missile_linked_list * missile_list;

    explosion_template explosions[255];
    explosion_linked_list * explosion_list;

    menu_button main_menu_buttons[10], endless_choose_plane_buttons[10], scenario_choose_scenario_buttons[10], scenario_description_buttons[10];
    scenario_base scenarios[20];

    /**Starting timer for random number creation*/
    srand(time(NULL));

    /**Allegro specific initialization*/
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_acodec_addon();
    al_install_audio();
    al_install_keyboard();
    al_reserve_samples(50);

    /**Initializations of Allegro specific data types*/
    display_data.height = screen_height, display_data.width = screen_width;
    if(is_fullscreen == 1){
        al_get_display_mode(13, &display_data);
        al_set_new_display_flags(ALLEGRO_FULLSCREEN);
        screen_height = display_data.height, screen_width = display_data.width;
    }
    display = al_create_display(display_data.width, display_data.height);
    event_queue_keyboard = al_create_event_queue();
    event_queue_timer = al_create_event_queue();
    timer = al_create_timer(1.0/frames_per_second);
    game_font_small = al_load_font("data/fonts/gamefont.ttf", 16, 0);
    game_font_medium = al_load_font("data/fonts/gamefont.ttf", 22, 0);
    game_font_large = al_load_font("data/fonts/gamefont.ttf", 24, 0);
    game_font_huge = al_load_font("data/fonts/gamefont.ttf", 48, 0);

    /**Loading Screen Text Display*/
    al_draw_text(game_font_large, al_map_rgb(255, 255, 255), screen_width/2, screen_height/2, ALLEGRO_ALIGN_CENTRE, "LOADING");al_flip_display();

    /**Initializations of more Allegro specific data types*/
    game_background = al_load_bitmap("data/sprites/game_background.png");
    game_music = al_load_sample("data/audio/ice_cap_zone.ogg");
    menu_music = al_load_sample("data/audio/camanis.ogg");

    /**Registers possible event sources*/
    al_register_event_source(event_queue_keyboard, al_get_display_event_source(display));
    al_register_event_source(event_queue_timer, al_get_timer_event_source(timer));
    al_register_event_source(event_queue_keyboard, al_get_keyboard_event_source());

    /**Parses game data files that are out of the code*/
    explosion_setup_base(explosions);
    aircrafts_size = parse_aircraft_data(aircrafts);
    missiles_size = parse_missile_data(missiles);
    parse_scenario_data(scenarios, screen_height, screen_width, aircrafts);
    game_reset_current_lists(&aircraft_list, &missile_list, &explosion_list);
    hud_load_sprites(hud_special_attack, hud_health);
    parse_game_text_data(endless_in_game_text, "data/gametext/endless_in_game.krot");
    parse_game_text_data(game_over_endless_mode_text, "data/gametext/game_over_endless_mode.krot");
    parse_game_text_data(main_menu_text, "data/gametext/main_menu.krot");
    parse_game_text_data(endless_choose_plane_text, "data/gametext/endless_choose_plane.krot");
    parse_game_text_data(high_scores_text, "data/gametext/high_scores.krot");
    parse_game_text_data(scenario_choose_scenario_text, "data/gametext/scenario_choose_scenario.krot");
    parse_game_text_data(scenario_win_text, "data/gametext/scenario_win.krot");
    parse_game_text_data(scenario_lose_text, "data/gametext/scenario_lose.krot");
    parse_menu_button_data(main_menu_buttons, "data/gametext/main_menu.krbtn");
    parse_menu_button_data(endless_choose_plane_buttons, "data/gametext/endless_choose_plane.krbtn");
    parse_menu_button_data(scenario_choose_scenario_buttons, "data/gametext/scenario_choose_scenario.krbtn");
    parse_menu_button_data(scenario_description_buttons, "data/gametext/scenario_description.krbtn");

    al_hide_mouse_cursor(display);
    al_set_window_title(display, "Kronn");
    al_start_timer(timer);
    al_rest(2); /*In case of music getting cut*/

    /**Main game loop*/
    while(is_game){
        al_draw_bitmap(game_background, 0, 0, 0);
        al_get_next_event(event_queue_keyboard, &event_keyboard);
        al_wait_for_event(event_queue_timer, &event_timer);

        if(event_keyboard.type == ALLEGRO_EVENT_DISPLAY_CLOSE){             /**If the windows is closed, quit the game*/
            is_game = 0;
        } else if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_ESCAPE){   /**If the player presses escape, go back to menu and reset game*/
            if(game_state == 7 || game_state == 4 || game_state == 12)
                is_music_playing = 0;
            if(game_state != 1)
                menu_fade_out(audio_level);
            ticks = 0, game_state = 1, selected_button = 0;
        } else if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_F8){       /**If the player presses F8, set up the autopilot game mode*/
            aircraft_add_new(&aircraft_list, aircrafts[8], (screen_width/2)+(aircrafts[8].size_x/2), screen_height-100);
            aircraft_list->next = NULL;
            missile_add_new(&missile_list, missiles[0], -90, 0);
            is_music_playing = 0;
            game_state = 12;
        }

        if(game_state == 1){                                                /**GAME STATE: Main Menu*/
            ticks = 0, special_attack_ticks = 0, score = 0;
            if(!is_music_playing){
                al_stop_samples();
                al_play_sample(menu_music, audio_level, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
                is_music_playing = 1;
            }
            game_reset_current_lists(&aircraft_list, &missile_list, &explosion_list);
            menu_main_menu(game_font_large, game_font_huge, event_keyboard, &game_state, &selected_button, screen_height, screen_width, main_menu_buttons, main_menu_text, audio_level);
        } else if(game_state == 2){                                         /**GAME STATE: Scenario Selection*/
            menu_scenario_choose_scenario(game_font_large, game_font_huge, event_keyboard, &game_state, &selected_button, &selected_scenario, screen_height, screen_width, scenario_choose_scenario_buttons, scenario_choose_scenario_text, audio_level);
        } else if(game_state == 3){                                         /**GAME STATE: Display information about selected scenario*/
            menu_scenario_description(game_font_medium, game_font_huge, event_keyboard, &is_music_playing, &game_state, screen_height, screen_width, &missile_list, &aircraft_list, &explosion_list, missiles, aircrafts, explosions, scenarios[selected_scenario], scenario_description_buttons, audio_level);
        } else if(game_state == 4){                                         /**GAME STATE: Scenario Mode in-game*/
            if(!is_music_playing){                                          /**Handles audio outputs*/
                al_stop_samples();
                al_play_sample(game_music, audio_level, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
                is_music_playing = 1;
            }
            game_handle_input(event_keyboard, aircraft_list, missile_list, missiles, screen_height, screen_width);
            if(event_timer.type == ALLEGRO_EVENT_TIMER){
                game_control_special_attack(aircraft_list, &special_attack_ticks);
                game_scenario_spawn_enemies(aircraft_list, aircrafts, scenarios[selected_scenario], ticks);
                game_detect_collision(aircraft_list, missile_list, explosion_list, explosions, audio_level);
                game_enemies_attack(aircraft_list, missile_list, missiles, ticks);
                game_move_entities(aircraft_list, missile_list, screen_height, screen_width, ticks);
                game_draw_sprites(aircraft_list, missile_list, explosion_list);
                game_scenario_check_health_levels(&game_state, scenarios[selected_scenario], aircraft_list, missile_list, audio_level);
                game_scenario_boss_behaviour(aircraft_list, scenarios[selected_scenario]);
                game_check_explosion_health_levels(explosion_list);

                hud_draw_health(hud_health, aircraft_list, screen_height, screen_width);
                hud_draw_special_power(hud_special_attack, game_font_medium, aircraft_list, special_attack_ticks, screen_height, screen_width, endless_in_game_text);
                if(aircraft_list->health <= 0){
                    menu_fade_out(audio_level);
                    game_state = 11;
                }
                ticks++;
            }
        } else if(game_state == 5){                                         /**GAME STATE: Scenario Won*/
            ticks = 0, special_attack_ticks = 0;
            al_stop_samples();
            is_music_playing = 0;
            menu_scenario_win(game_font_large, game_font_huge, screen_height, screen_width, scenario_win_text);
        } else if(game_state == 6){                                         /**GAME STATE: Endless Mode choose plane*/
            menu_endless_choose_plane(game_font_large, game_font_huge, event_keyboard, &is_music_playing, &game_state, &selected_button, screen_height, screen_width, &missile_list, &aircraft_list, &explosion_list, missiles, aircrafts, explosions, endless_choose_plane_buttons, endless_choose_plane_text, audio_level);
        } else if(game_state == 7){                                         /**GAME STATE: Endless Mode in-game*/
            if(!is_music_playing){                                          /**Handles audio outputs*/
                al_stop_samples();
                al_play_sample(game_music, audio_level, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
                is_music_playing = 1;
            }
            game_handle_input(event_keyboard, aircraft_list, missile_list, missiles, screen_height, screen_width);
            if(event_timer.type == ALLEGRO_EVENT_TIMER){
                game_control_special_attack(aircraft_list, &special_attack_ticks);
                game_endless_spawn_enemies(aircraft_list, aircrafts, screen_height, screen_width, ticks);
                game_detect_collision(aircraft_list, missile_list, explosion_list, explosions, audio_level);
                game_enemies_attack(aircraft_list, missile_list, missiles, ticks);
                game_move_entities(aircraft_list, missile_list, screen_height, screen_width, ticks);
                game_draw_sprites(aircraft_list, missile_list, explosion_list);
                game_check_health_levels(aircraft_list, missile_list, audio_level);
                game_check_explosion_health_levels(explosion_list);

                hud_draw_score(&score, ticks, game_font_large, endless_in_game_text);
                hud_draw_health(hud_health, aircraft_list, screen_height, screen_width);
                hud_draw_special_power(hud_special_attack, game_font_medium, aircraft_list, special_attack_ticks, screen_height, screen_width, endless_in_game_text);
                if(aircraft_list->health <= 0){
                    game_calculate_high_scores(score, high_scores);
                    menu_fade_out(audio_level);
                    game_state = 8;
                }
                ticks++;
            }
        } else if(game_state == 8){                                         /**GAME STATE: Endless Mode game over*/
            ticks = 0, special_attack_ticks = 0;
            al_stop_samples();
            is_music_playing = 0;
            menu_game_over_endless_mode(game_font_large, game_font_huge, score, screen_height, screen_width, game_over_endless_mode_text);
        } else if(game_state == 9){                                         /**GAME STATE: High Scores Menu*/
            menu_high_scores(game_font_large, game_font_huge, high_scores, screen_height, screen_width, high_scores_text);
        } else if(game_state == 10){                                        /**GAME STATE: Quit*/
            is_game = 0;
        } else if(game_state == 11){                                        /**GAME STATE: Scenario lose*/
            ticks = 0, special_attack_ticks = 0;
            al_stop_samples();
            is_music_playing = 0;
            menu_scenario_lose(game_font_large, game_font_huge, screen_height, screen_width, scenario_lose_text);
        } else if(game_state == 12){                                        /**GAME STATE: Autopilot Mode*/
            if(!is_music_playing){
                al_stop_samples();
                al_play_sample(game_music, audio_level, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
                is_music_playing = 1;
            }
            game_autopilot_movement(aircraft_list, missile_list, missiles, ticks, screen_height, screen_width);
            if(event_timer.type == ALLEGRO_EVENT_TIMER){
                game_control_special_attack(aircraft_list, &special_attack_ticks);
                game_endless_spawn_enemies(aircraft_list, aircrafts, screen_height, screen_width, ticks);
                game_detect_collision(aircraft_list, missile_list, explosion_list, explosions, audio_level);
                game_enemies_attack(aircraft_list, missile_list, missiles, ticks);
                game_move_entities(aircraft_list, missile_list, screen_height, screen_width, ticks);
                game_draw_sprites(aircraft_list, missile_list, explosion_list);
                game_check_health_levels(aircraft_list, missile_list, audio_level);
                game_check_explosion_health_levels(explosion_list);

                hud_draw_score(&score, ticks, game_font_large, endless_in_game_text);
                hud_draw_health(hud_health, aircraft_list, screen_height, screen_width);
                hud_draw_special_power(hud_special_attack, game_font_medium, aircraft_list, special_attack_ticks, screen_height, screen_width, endless_in_game_text);
                if(aircraft_list->health <= 0){
                    game_calculate_high_scores(score, high_scores);
                    menu_fade_out(audio_level);
                    game_state = 8;
                }
                ticks++;
            }
        }
        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));

    }

    /**Destroys all space invaded in the memory*/
    while(--aircrafts_size >= 0) al_destroy_bitmap(aircrafts[aircrafts_size].sprite);
    while(--missiles_size >= 0){  al_destroy_bitmap(missiles[missiles_size].sprite);
                                    al_destroy_sample(missiles[missiles_size].hitsound); }
    free(aircraft_list);
    free(missile_list);
    al_destroy_event_queue(event_queue_keyboard);
    al_destroy_event_queue(event_queue_timer);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_font(game_font_small);
    al_destroy_font(game_font_medium);
    al_destroy_font(game_font_large);
    al_destroy_font(game_font_huge);
    return 0;
}
