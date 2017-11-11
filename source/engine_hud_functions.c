#include "engine_hud_functions.h"

void hud_load_sprites(ALLEGRO_BITMAP * hud_special_attack[5], ALLEGRO_BITMAP * hud_health[3]){
    int i;
    char sprite_path[40], temp_string[10];
    for(i=0; i<5; i++){
        strcpy(sprite_path, "data/sprites/hud_special_attack_");
        temp_string[0] = i+'1';
        strcat(temp_string, ".png");
        temp_string[5] = '\0';
        strcat(sprite_path, temp_string);
        hud_special_attack[i] = al_load_bitmap(sprite_path);
    }
    for(i=0; i<3; i++){
        strcpy(sprite_path, "data/sprites/hud_health_");
        temp_string[0] = i+'1';
        strcat(temp_string, ".png");
        temp_string[5] = '\0';
        strcat(sprite_path, temp_string);
        hud_health[i] = al_load_bitmap(sprite_path);
    }
}

void hud_draw_health(ALLEGRO_BITMAP * hud_health[3], aircraft_linked_list * aircraft_list, int screen_height, int screen_width){
    if(aircraft_list->health != 0)
        al_draw_bitmap(hud_health[aircraft_list->health-1], screen_width - al_get_bitmap_width(hud_health[aircraft_list->health-1]) - 10, 10, 0);
}

void hud_draw_special_power(ALLEGRO_BITMAP * hud_special_power[5], ALLEGRO_FONT * game_font, aircraft_linked_list * aircraft_list, int special_attack_ticks, int screen_height, int screen_width, char endless_in_game_text[5][50]){
    char remaining_to_string[10], resulting_string[20];
    if(aircraft_list->special_attack_counter > 0)
        al_draw_bitmap(hud_special_power[aircraft_list->special_attack_counter-1], 10, screen_height - al_get_bitmap_height(hud_special_power[aircraft_list->special_attack_counter-1]) - 10, 0);
    if(aircraft_list->is_using_special_attack == 1){
        sprintf(remaining_to_string, "%d", (360 - special_attack_ticks) / 60);
        strcpy(resulting_string, endless_in_game_text[1]);
        strcat(resulting_string, remaining_to_string);
        al_draw_text(game_font, al_map_rgb(255, 255, 255), screen_width - al_get_text_width(game_font, resulting_string) - 10, screen_height - 50, 0, resulting_string);
    }
}

void hud_draw_score(int * score, int ticks, ALLEGRO_FONT * game_font, char endless_in_game_text[5][50]){
    char score_to_string[10], resulting_string[20];
    (*score) = ticks/30;
    sprintf(score_to_string, "%d", (*score));
    strcpy(resulting_string, endless_in_game_text[0]);
    strcat(resulting_string, score_to_string);
    al_draw_text(game_font, al_map_rgb(255, 255, 255), 10, 10, 0, resulting_string);
}
