#include "engine_menu_functions.h"

void menu_fade_out(float audio_level){
    ALLEGRO_SAMPLE * menu_enter = al_load_sample("data/audio/menu_enter.ogg");
    ALLEGRO_BITMAP * fade_sprites[4];
    fade_sprites[0] = al_load_bitmap("data/sprites/fade0.png");
    fade_sprites[1] = al_load_bitmap("data/sprites/fade1.png");
    fade_sprites[2] = al_load_bitmap("data/sprites/fade2.png");
    fade_sprites[3] = al_load_bitmap("data/sprites/fade3.png");
    al_play_sample(menu_enter, audio_level, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    al_draw_bitmap(fade_sprites[0], 0, 0, 0);al_flip_display();al_rest(0.02f);
    al_draw_bitmap(fade_sprites[1], 0, 0, 0);al_flip_display();al_rest(0.02f);
    al_draw_bitmap(fade_sprites[2], 0, 0, 0);al_flip_display();al_rest(0.02f);
    al_draw_bitmap(fade_sprites[3], 0, 0, 0);al_flip_display();al_rest(0.02f);
    al_destroy_bitmap(fade_sprites[0]);al_destroy_bitmap(fade_sprites[1]);
    al_destroy_bitmap(fade_sprites[2]);al_destroy_bitmap(fade_sprites[3]);
    al_destroy_sample(menu_enter);
}

int get_menu_button_size(menu_button button_array[10]){
    int size = 0;
    while(strcmp(button_array[size].text, "END") != 0)
        size++;
    return size;
}

void parse_menu_button_data(menu_button button_array[10], char * filename){
    int i = 0, val;
    char temp_string[50];
    FILE * to_parse;
    to_parse = fopen(filename, "rt");
    while(fgets(temp_string, 50, to_parse)){
        if(temp_string[strlen(temp_string)-1] == '\n')
            temp_string[strlen(temp_string)-1] = '\0';
        strcpy(button_array[i].text, temp_string);
        fscanf(to_parse, "%d\n", &val);
        button_array[i].effect = val;
        i++;
    }
    fclose(to_parse);
}

void parse_game_text_data(char result[20][50], char * filename){
    int i = 0; char temp_string[50];
    FILE * to_parse;
    to_parse = fopen(filename, "rt");
    while(1){
        if(fgets(temp_string, 50, to_parse) == NULL) break;
        if(temp_string[strlen(temp_string)-1] == '\n')
            temp_string[strlen(temp_string)-1] = '\0';
        strcpy(result[i], temp_string);
        i++;
    }
}

void menu_main_menu(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, ALLEGRO_EVENT event_keyboard, int * game_state, int * selected_button, int screen_height, int screen_width, menu_button main_menu_buttons[10], char main_menu_text[20][50], float audio_level){
    int button_array_size, i, move_dir = 0;
    ALLEGRO_SAMPLE * button_sound = al_load_sample("data/audio/button_sound.ogg");
    button_array_size = get_menu_button_size(main_menu_buttons);
    al_draw_text(game_font_two, al_map_rgb(255, 255, 255), screen_width/2, 200, ALLEGRO_ALIGN_CENTRE, main_menu_text[0]);
    al_draw_text(game_font_two, al_map_rgb(255, 255, 255), screen_width/2, 250, ALLEGRO_ALIGN_CENTRE, main_menu_text[1]);
    for(i=0; i<button_array_size; i++){
        if((*selected_button) == i){
            al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2 - al_get_text_width(game_font, main_menu_buttons[i].text)/2 - 20, 350+30*(i+1), ALLEGRO_ALIGN_LEFT, ">");
        }
        al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2, 350+30*(i+1), ALLEGRO_ALIGN_CENTRE, main_menu_buttons[i].text);
    }
    if(event_keyboard.type == ALLEGRO_EVENT_KEY_DOWN){
        if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_UP && (*selected_button) > 0){
            al_play_sample(button_sound, audio_level, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            move_dir = -1;
        }
        else if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_DOWN && (*selected_button) < button_array_size-1){
            al_play_sample(button_sound, audio_level, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);;
            move_dir = 1;
        }
        else if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_ENTER){
            al_destroy_sample(button_sound);
            menu_fade_out(audio_level);
            (*game_state) = main_menu_buttons[(*selected_button)].effect;
            (*selected_button) = 0;
        }
    } else if(event_keyboard.type == ALLEGRO_EVENT_KEY_UP){
        if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_RIGHT || event_keyboard.keyboard.keycode == ALLEGRO_KEY_LEFT)
            move_dir = 0;
    }
    (*selected_button) += move_dir;
}

void menu_scenario_choose_scenario(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, ALLEGRO_EVENT event_keyboard, int * game_state, int * selected_button, int * selected_scenario, int screen_height, int screen_width, menu_button scenario_choose_scenario_buttons[10], char scenario_choose_scenario_text[20][50], float audio_level){
    int button_array_size, i, move_dir = 0;
    ALLEGRO_SAMPLE * button_sound = al_load_sample("data/audio/button_sound.ogg");
    button_array_size = get_menu_button_size(scenario_choose_scenario_buttons);
    al_draw_text(game_font_two, al_map_rgb(255, 255, 255), screen_width/2, 200, ALLEGRO_ALIGN_CENTRE, scenario_choose_scenario_text[0]);
    al_draw_text(game_font_two, al_map_rgb(255, 255, 255), screen_width/2, 250, ALLEGRO_ALIGN_CENTRE, scenario_choose_scenario_text[1]);
    for(i=0; i<button_array_size; i++){
        if((*selected_button) == i){
            al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2 - al_get_text_width(game_font, scenario_choose_scenario_buttons[i].text)/2 - 20, 350+30*(i+1), ALLEGRO_ALIGN_LEFT, ">");
        }
        al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2, 350+30*(i+1), ALLEGRO_ALIGN_CENTRE, scenario_choose_scenario_buttons[i].text);
    }
    if(event_keyboard.type == ALLEGRO_EVENT_KEY_DOWN){
        if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_UP && (*selected_button) > 0){
            al_play_sample(button_sound, audio_level, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            move_dir = -1;
        }
        else if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_DOWN && (*selected_button) < button_array_size-1){
            al_play_sample(button_sound, audio_level, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            move_dir = 1;
        }
        else if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_ENTER){
            (*selected_scenario) = scenario_choose_scenario_buttons[(*selected_button)].effect;
            al_destroy_sample(button_sound);
            menu_fade_out(audio_level);
            (*game_state)++;
            (*selected_button) = 0;
        }
    } else if(event_keyboard.type == ALLEGRO_EVENT_KEY_UP){
        if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_RIGHT || event_keyboard.keyboard.keycode == ALLEGRO_KEY_LEFT)
            move_dir = 0;
    }
    (*selected_button) += move_dir;
}

void menu_scenario_description(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, ALLEGRO_EVENT event_keyboard, int * is_music_playing, int * game_state, int screen_height, int screen_width, missile_linked_list ** missile_list, aircraft_linked_list ** aircraft_list, explosion_linked_list ** explosion_list,  missile_template missiles[255], aircraft_template aircrafts[255], explosion_template explosions[255], scenario_base current_scenario, menu_button scenario_description_buttons[10], float audio_level){
    int i = 0;
    al_draw_text(game_font_two, al_map_rgb(255, 255, 255), screen_width/2, 100, ALLEGRO_ALIGN_CENTRE, current_scenario.title);
    al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2 - al_get_text_width(game_font, scenario_description_buttons[0].text)/2 - 20, 550, ALLEGRO_ALIGN_LEFT, ">");
    al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2, 550, ALLEGRO_ALIGN_CENTRE, scenario_description_buttons[0].text);
    while(1){
        if(strcmp(current_scenario.description[i], "END") == 0) break;
        al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2, 140+((i+1)*30), ALLEGRO_ALIGN_CENTRE, current_scenario.description[i]);
        i++;
    }
    if(event_keyboard.type == ALLEGRO_EVENT_KEY_DOWN){
        if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_ENTER){
            *is_music_playing = 0;
            al_stop_samples();
            free(*aircraft_list);
            free(*missile_list);
            free(*explosion_list);
            (*aircraft_list) = (aircraft_linked_list*)malloc(sizeof(aircraft_linked_list));
            (*missile_list) = (missile_linked_list*)malloc(sizeof(missile_linked_list));
            (*explosion_list) = (explosion_linked_list*)malloc(sizeof(explosion_linked_list));
            strcpy((*aircraft_list)->name, aircrafts[current_scenario.ally_aircraft_type].name);
            (*aircraft_list)->team = aircrafts[current_scenario.ally_aircraft_type].team;
            (*aircraft_list)->health = aircrafts[current_scenario.ally_aircraft_type].health;
            (*aircraft_list)->type = aircrafts[current_scenario.ally_aircraft_type].type;
            (*aircraft_list)->direction = aircrafts[current_scenario.ally_aircraft_type].direction;
            (*aircraft_list)->id = aircrafts[current_scenario.ally_aircraft_type].id;
            (*aircraft_list)->cost = aircrafts[current_scenario.ally_aircraft_type].cost;
            (*aircraft_list)->speed = aircrafts[current_scenario.ally_aircraft_type].speed;
            (*aircraft_list)->missile_type = aircrafts[current_scenario.ally_aircraft_type].missile_type;
            (*aircraft_list)->special_attack_missile_type = aircrafts[current_scenario.ally_aircraft_type].special_attack_missile_type;
            (*aircraft_list)->is_follower = aircrafts[current_scenario.ally_aircraft_type].is_follower;
            (*aircraft_list)->is_using_special_attack = aircrafts[current_scenario.ally_aircraft_type].is_using_special_attack;
            (*aircraft_list)->special_attack_counter = aircrafts[current_scenario.ally_aircraft_type].special_attack_counter;
            (*aircraft_list)->pos_x = screen_width/2-aircrafts[current_scenario.ally_aircraft_type].size_x/2;
            (*aircraft_list)->pos_y = screen_height-150;
            (*aircraft_list)->size_x = aircrafts[current_scenario.ally_aircraft_type].size_x;
            (*aircraft_list)->size_y = aircrafts[current_scenario.ally_aircraft_type].size_y;
            (*aircraft_list)->sprite = aircrafts[current_scenario.ally_aircraft_type].sprite;
            (*aircraft_list)->next = NULL;
            (*missile_list)->team = missiles[0].team;
            (*missile_list)->speed = missiles[0].speed;
            (*missile_list)->health = missiles[0].health;
            (*missile_list)->is_follower = missiles[0].is_follower;
            (*missile_list)->follow_accuracy = missiles[0].follow_accuracy;
            (*missile_list)->pos_x = -40;
            (*missile_list)->pos_y = 0;
            (*missile_list)->size_x = missiles[0].size_x;
            (*missile_list)->size_y = missiles[0].size_y;
            (*missile_list)->sprite = missiles[0].sprite;
            (*missile_list)->hitsound = missiles[0].hitsound;
            (*missile_list)->next = NULL;
            (*explosion_list)->health = 1;
            (*explosion_list)->pos_x = -40;
            (*explosion_list)->pos_y = 0;
            (*explosion_list)->sprites[0] = explosions[0].sprites[0];
            (*explosion_list)->sprites[1] = explosions[0].sprites[0];
            (*explosion_list)->sprites[2] = explosions[0].sprites[0];
            (*explosion_list)->ticks = 0;
            (*explosion_list)->next = NULL;
            menu_fade_out(audio_level);
            (*game_state)++;
        }
    }
}

void menu_scenario_win(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, int screen_height, int screen_width, char scenario_win_text[20][50]){
    al_draw_text(game_font_two, al_map_rgb(255, 255, 255), screen_width/2, screen_height/2 - 150, ALLEGRO_ALIGN_CENTRE, scenario_win_text[0]);
    al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2, screen_height/2 - 50, ALLEGRO_ALIGN_CENTRE, scenario_win_text[1]);
    al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2, screen_height/2, ALLEGRO_ALIGN_CENTRE, scenario_win_text[2]);
}

void menu_scenario_lose(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, int screen_height, int screen_width, char scenario_lose_text[20][50]){
    al_draw_text(game_font_two, al_map_rgb(255, 255, 255), screen_width/2, screen_height/2 - 150, ALLEGRO_ALIGN_CENTRE, scenario_lose_text[0]);
    al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2, screen_height/2 - 50, ALLEGRO_ALIGN_CENTRE, scenario_lose_text[1]);
    al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2, screen_height/2, ALLEGRO_ALIGN_CENTRE, scenario_lose_text[2]);
}

void menu_endless_choose_plane(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, ALLEGRO_EVENT event_keyboard, int * is_music_playing, int * game_state, int * selected_button, int screen_height, int screen_width, missile_linked_list ** missile_list, aircraft_linked_list ** aircraft_list, explosion_linked_list ** explosion_list, missile_template missiles[255], aircraft_template aircrafts[255],explosion_template explosions[255], menu_button endless_choose_plane_buttons[10], char endless_choose_plane_text[20][50], float audio_level){
    int button_array_size, i, move_dir = 0;
    ALLEGRO_SAMPLE * button_sound = al_load_sample("data/audio/button_sound.ogg");
    button_array_size = get_menu_button_size(endless_choose_plane_buttons);
    al_draw_text(game_font_two, al_map_rgb(255, 255, 255), screen_width/2, 200, ALLEGRO_ALIGN_CENTRE, endless_choose_plane_text[0]);
    al_draw_text(game_font_two, al_map_rgb(255, 255, 255), screen_width/2, 250, ALLEGRO_ALIGN_CENTRE, endless_choose_plane_text[1]);
    for(i=0; i<button_array_size; i++){
        if((*selected_button) == i){
            al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2 - al_get_text_width(game_font, endless_choose_plane_buttons[i].text)/2 - 20, 350+30*(i+1), ALLEGRO_ALIGN_LEFT, ">");
        }
        al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2, 350+30*(i+1), ALLEGRO_ALIGN_CENTRE, endless_choose_plane_buttons[i].text);
    }
    if(event_keyboard.type == ALLEGRO_EVENT_KEY_DOWN){
        if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_UP && (*selected_button) > 0){
            al_play_sample(button_sound, audio_level, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            move_dir = -1;
        }
        else if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_DOWN && (*selected_button) < button_array_size-1){
           al_play_sample(button_sound, audio_level, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
           move_dir = 1;
        }
        else if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_ENTER){
            *is_music_playing = 0;
            al_stop_samples();
            free(*aircraft_list);
            free(*missile_list);
            free(*explosion_list);
            (*aircraft_list) = (aircraft_linked_list*)malloc(sizeof(aircraft_linked_list));
            (*missile_list) = (missile_linked_list*)malloc(sizeof(missile_linked_list));
            (*explosion_list) = (explosion_linked_list*)malloc(sizeof(explosion_linked_list));
            strcpy((*aircraft_list)->name, aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].name);
            (*aircraft_list)->team = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].team;
            (*aircraft_list)->health = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].health;
            (*aircraft_list)->type = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].type;
            (*aircraft_list)->direction = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].direction;
            (*aircraft_list)->id = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].id;
            (*aircraft_list)->cost = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].cost;
            (*aircraft_list)->speed = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].speed;
            (*aircraft_list)->missile_type = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].missile_type;
            (*aircraft_list)->special_attack_missile_type = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].special_attack_missile_type;
            (*aircraft_list)->is_follower = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].is_follower;
            (*aircraft_list)->is_using_special_attack = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].is_using_special_attack;
            (*aircraft_list)->special_attack_counter = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].special_attack_counter;
            (*aircraft_list)->pos_x = screen_width/2-aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].size_x/2;
            (*aircraft_list)->pos_y = screen_height-100;
            (*aircraft_list)->size_x = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].size_x;
            (*aircraft_list)->size_y = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].size_y;
            (*aircraft_list)->sprite = aircrafts[endless_choose_plane_buttons[(*selected_button)].effect].sprite;
            (*aircraft_list)->next = NULL;
            (*missile_list)->team = missiles[0].team;
            (*missile_list)->speed = missiles[0].speed;
            (*missile_list)->health = missiles[0].health;
            (*missile_list)->is_follower = missiles[0].is_follower;
            (*missile_list)->follow_accuracy = missiles[0].follow_accuracy;
            (*missile_list)->pos_x = -40;
            (*missile_list)->pos_y = 0;
            (*missile_list)->size_x = missiles[0].size_x;
            (*missile_list)->size_y = missiles[0].size_y;
            (*missile_list)->sprite = missiles[0].sprite;
            (*missile_list)->hitsound = missiles[0].hitsound;
            (*missile_list)->next = NULL;
            (*explosion_list)->health = 1;
            (*explosion_list)->pos_x = -40;
            (*explosion_list)->pos_y = 0;
            (*explosion_list)->sprites[0] = explosions[0].sprites[0];
            (*explosion_list)->sprites[1] = explosions[0].sprites[0];
            (*explosion_list)->sprites[2] = explosions[0].sprites[0];
            (*explosion_list)->ticks = 0;
            (*explosion_list)->next = NULL;
            (*selected_button) = 0;
            al_destroy_sample(button_sound);
            menu_fade_out(audio_level);
            (*game_state) = 7;
        }
    } else if(event_keyboard.type == ALLEGRO_EVENT_KEY_UP){
        if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_RIGHT || event_keyboard.keyboard.keycode == ALLEGRO_KEY_LEFT)
            move_dir = 0;
    }
    (*selected_button) += move_dir;
}

void menu_game_over_endless_mode(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, int score, int screen_height, int screen_width, char game_over_endless_mode_text[20][50]){
    char score_to_string[10], resulting_string[25];
    sprintf(score_to_string, "%d", score);
    strcpy(resulting_string, game_over_endless_mode_text[0]);
    strcat(resulting_string, score_to_string);
    al_draw_text(game_font_two, al_map_rgb(255, 255, 255), screen_width/2, screen_height/2 - 150, ALLEGRO_ALIGN_CENTRE, game_over_endless_mode_text[1]);
    al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2, screen_height/2 - 50, ALLEGRO_ALIGN_CENTRE, resulting_string);
    al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2, screen_height/2, ALLEGRO_ALIGN_CENTRE, game_over_endless_mode_text[2]);
}

void menu_high_scores(ALLEGRO_FONT * game_font, ALLEGRO_FONT * game_font_two, int high_scores[11], int screen_height, int screen_width, char high_scores_text[20][50]){
    int i;
    char temp_string[5], resulting_string[10];
    FILE * high_scores_krhs;
    high_scores_krhs = fopen("data/playerstats/high_scores.krhs", "rt");
    al_draw_text(game_font_two, al_map_rgb(255, 255, 255), screen_width/2, screen_height/2 - 250, ALLEGRO_ALIGN_CENTRE, high_scores_text[0]);
    for(i=0; i<10; i++){
        fscanf(high_scores_krhs, "%d", &high_scores[i]);
        sprintf(temp_string, "%d", high_scores[i]);
        strcpy(resulting_string, high_scores_text[i+1]);
        strcat(resulting_string, temp_string);
        al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width/2, screen_height/2 - 150 + 40*i, ALLEGRO_ALIGN_CENTRE, resulting_string);
    }
    fclose(high_scores_krhs);
}
