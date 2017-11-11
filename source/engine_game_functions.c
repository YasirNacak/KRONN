#include "engine_game_functions.h"

void game_autopilot_movement(aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, missile_template * missiles, int ticks, int screen_height, int screen_width){
    aircraft_linked_list * aircraft_list_temp = aircraft_list;
    missile_linked_list * missile_list_temp = missile_list;
    int i, j, is_moved = 0;
    for(i=aircraft_list->pos_x - 20; i<=aircraft_list->pos_x + aircraft_list->size_x + 20; i++){
        for(j=aircraft_list->pos_y-120; j<=aircraft_list->pos_y; j++){
            missile_list_temp = missile_list;
            while(missile_list_temp != NULL){
                if(missile_list_temp->pos_x == i && missile_list_temp->pos_y == j && missile_list_temp->team != aircraft_list->team){
                    is_moved = 1;
                    if((aircraft_list->pos_x + aircraft_list->size_x/2) - i > 0 && aircraft_list->pos_x + aircraft_list->size_x <= screen_width - aircraft_list->size_x)
                        aircraft_list->direction = 1;
                    else if((aircraft_list->pos_x + aircraft_list->size_x/2) - i <= 0 && aircraft_list->pos_x >= aircraft_list->size_x) aircraft_list->direction = -1;
                }
                missile_list_temp = missile_list_temp->next;
            }
        }
    }
    for(i=aircraft_list->pos_x - 50; i<=aircraft_list->pos_x + aircraft_list->size_x + 50; i++){
        for(j=aircraft_list->pos_y-240; j<=aircraft_list->pos_y + aircraft_list->size_y; j++){
            aircraft_list_temp = aircraft_list->next;
            while(aircraft_list_temp != NULL){
                if(aircraft_list_temp->pos_x == i && aircraft_list_temp->pos_y == j){
                    is_moved = 1;
                    if((aircraft_list->pos_x + aircraft_list->size_x/2) - i > 0 && aircraft_list->pos_x + aircraft_list->size_x <= screen_width - aircraft_list->size_x)
                        aircraft_list->direction = 1;
                    else if((aircraft_list->pos_x + aircraft_list->size_x/2) - i <= 0 && aircraft_list->pos_x >= aircraft_list->size_x) aircraft_list->direction = -1;
                }
                aircraft_list_temp = aircraft_list_temp->next;
            }
        }
    }
    if(aircraft_list->special_attack_counter == 5 && aircraft_list->special_attack_missile_type != -1){
            aircraft_list->special_attack_counter = 0;
            aircraft_list->is_using_special_attack = 1;
            aircraft_list->missile_type = aircraft_list->missile_type + aircraft_list->special_attack_missile_type;
            aircraft_list->special_attack_missile_type = aircraft_list->missile_type - aircraft_list->special_attack_missile_type;
            aircraft_list->missile_type = aircraft_list->missile_type - aircraft_list->special_attack_missile_type;
    }
    if(ticks % 15 == 0 && aircraft_list->is_using_special_attack == 1)
        missile_add_new(&missile_list, missiles[aircraft_list->missile_type], aircraft_list->pos_x+(aircraft_list->size_x/2)-(missiles[aircraft_list->missile_type].size_x/2), aircraft_list->pos_y);
    else if(ticks % 10 == 0){
        for(i=aircraft_list->pos_x+2; i<=aircraft_list->pos_x + aircraft_list->size_x+10; i++){
            aircraft_list_temp = aircraft_list->next;
            while(aircraft_list_temp != NULL){
                if(aircraft_list_temp->pos_x + aircraft_list_temp->size_x/2 == i){
                    missile_add_new(&missile_list, missiles[aircraft_list->missile_type], aircraft_list->pos_x+(aircraft_list->size_x/2)-(missiles[aircraft_list->missile_type].size_x/2), aircraft_list->pos_y);
                }
                aircraft_list_temp = aircraft_list_temp->next;
            }
        }
    }
    if(is_moved == 0) aircraft_list->direction = 0;
}

void game_handle_input(ALLEGRO_EVENT event_keyboard, aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, missile_template * missiles, int screen_height, int screen_width){
    if(event_keyboard.type == ALLEGRO_EVENT_KEY_DOWN){
        if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_RIGHT)
            aircraft_list->direction = 1;
        else if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_LEFT)
            aircraft_list->direction = -1;
        else if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_UP)
            aircraft_list->direction = -2;
        else if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_DOWN)
            aircraft_list->direction = 2;
        else if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_SPACE)
            missile_add_new(&missile_list, missiles[aircraft_list->missile_type], aircraft_list->pos_x+(aircraft_list->size_x/2)-(missiles[aircraft_list->missile_type].size_x/2), aircraft_list->pos_y);
        else if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_ENTER && aircraft_list->special_attack_counter == 5 && aircraft_list->special_attack_missile_type != -1){
            aircraft_list->special_attack_counter = 0;
            aircraft_list->is_using_special_attack = 1;
            /**SWAPS TWO INTEGERS USING ADDITION AND SUBTRACTION*/
            aircraft_list->missile_type = aircraft_list->missile_type + aircraft_list->special_attack_missile_type;
            aircraft_list->special_attack_missile_type = aircraft_list->missile_type - aircraft_list->special_attack_missile_type;
            aircraft_list->missile_type = aircraft_list->missile_type - aircraft_list->special_attack_missile_type;
        }
    } else if(event_keyboard.type == ALLEGRO_EVENT_KEY_UP){
        if(event_keyboard.keyboard.keycode == ALLEGRO_KEY_RIGHT || event_keyboard.keyboard.keycode == ALLEGRO_KEY_LEFT || event_keyboard.keyboard.keycode == ALLEGRO_KEY_UP || event_keyboard.keyboard.keycode == ALLEGRO_KEY_DOWN)
            aircraft_list->direction = 0;
    }
}

void game_reset_current_lists(aircraft_linked_list ** aircraft_list, missile_linked_list ** missile_list, explosion_linked_list ** explosion_list){
    free(*aircraft_list);
    free(*missile_list);
    free(*explosion_list);
    *aircraft_list = (aircraft_linked_list*)malloc(sizeof(aircraft_linked_list));
    *missile_list = (missile_linked_list*)malloc(sizeof(missile_linked_list));
    *explosion_list = (explosion_linked_list*)malloc(sizeof(explosion_linked_list));
    *aircraft_list = NULL;
    *missile_list = NULL;
    *explosion_list = NULL;
}

void game_set_spawn_variables(int * enemy_spawn_frequency, int * random_enemy_range, int ticks, int spawnable_enemy_types_size){
    *enemy_spawn_frequency = 90;
    *random_enemy_range = 0;
    *enemy_spawn_frequency -= ((ticks/60) / 10) * 5;
    *random_enemy_range += ((ticks/60) / 5);
    if(*random_enemy_range > spawnable_enemy_types_size)
        *random_enemy_range = spawnable_enemy_types_size;
    if(*enemy_spawn_frequency <= 0)
        *enemy_spawn_frequency = 1;
}

void game_endless_spawn_enemies(aircraft_linked_list * aircraft_list, aircraft_template * aircrafts, int screen_height, int screen_width, int ticks){
    aircraft_linked_list * aircraft_list_temp = aircraft_list;
    aircraft_template spawnable_enemy_types[10];
    int spawn_position_x, spawnable_enemy_types_size = 0,  i = 0;
    int enemy_spawn_frequency = 90, random_enemy = 0, random_enemy_range = 0;

    for(i=0; i<255; i++){
        if(aircrafts[i].team == 1 && aircrafts[i].health == 3)
            spawnable_enemy_types[spawnable_enemy_types_size++] = aircrafts[i];
        if(aircrafts[i].type == -1)
            break;
    }
    game_set_spawn_variables(&enemy_spawn_frequency, &random_enemy_range, ticks, spawnable_enemy_types_size);
    if(ticks % enemy_spawn_frequency == 0){
        random_enemy = rand() % (random_enemy_range+1);
        if(random_enemy >= spawnable_enemy_types_size) random_enemy--;
        spawn_position_x = rand() % (screen_width-40);
        aircraft_add_new(&aircraft_list, spawnable_enemy_types[random_enemy], spawn_position_x, -50);
        while(aircraft_list_temp->next->next != NULL)
            aircraft_list_temp = aircraft_list_temp->next;
        aircraft_list_temp->next->id = aircraft_list_temp->id+1;
    }
}

void game_enemies_attack(aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, missile_template * missiles, int ticks){
    aircraft_linked_list * aircraft_list_temp = aircraft_list;
    int i;
    while(aircraft_list_temp != NULL){
        if(aircraft_list_temp->team == 1 && aircraft_list_temp->missile_type >= 0 && ticks%60 == 0){
            for(i=0; i<255; i++){
                if(missiles[i].type == aircraft_list_temp->missile_type)
                    break;
            }
            missile_add_new(&missile_list, missiles[i], aircraft_list_temp->pos_x+(aircraft_list_temp->size_x/2)-(missiles[i].size_x/2), aircraft_list_temp->pos_y+aircraft_list_temp->size_y);
        }
        aircraft_list_temp = aircraft_list_temp->next;
    }
}

void game_detect_collision(aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, explosion_linked_list * explosion_list, explosion_template explosions[255], float audio_level){
    aircraft_linked_list * aircraft_list_temp = aircraft_list, * aircraft_list_temp_two = aircraft_list;
    missile_linked_list * missile_list_temp = missile_list;

    while(missile_list_temp != NULL){
        aircraft_list_temp = aircraft_list;
        while(aircraft_list_temp != NULL){
            if(aircraft_list_temp->team != missile_list_temp->team){
                if(abs(aircraft_list_temp->pos_x+20-missile_list_temp->pos_x) < aircraft_list_temp->size_x-20){
                    if(abs(abs(aircraft_list_temp->pos_y-missile_list_temp->pos_y)) < aircraft_list_temp->size_y-10){
                        al_play_sample(missile_list_temp->hitsound, audio_level, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        aircraft_list_temp->health -= 1;
                        missile_list_temp->health -= 1;
                        explosion_add_new(&explosion_list, explosions[0], missile_list_temp->pos_x, missile_list_temp->pos_y);
                    }
                }
            }
            aircraft_list_temp = aircraft_list_temp->next;
        }
        missile_list_temp = missile_list_temp->next;
    }
    aircraft_list_temp = aircraft_list;
    while(aircraft_list_temp != NULL){
        aircraft_list_temp_two = aircraft_list;
        while(aircraft_list_temp_two != NULL){
            if(aircraft_list_temp->team != aircraft_list_temp_two->team){
                if(abs(aircraft_list_temp->pos_x - aircraft_list_temp_two->pos_x) < aircraft_list_temp->size_x){
                    if(abs(aircraft_list_temp->pos_y - aircraft_list_temp_two->pos_y) < aircraft_list_temp->size_y){
                        aircraft_list_temp->health = 0;
                        aircraft_list_temp_two->health = 0;
                    }
                }
            }
            aircraft_list_temp_two = aircraft_list_temp_two->next;
        }
        aircraft_list_temp = aircraft_list_temp->next;
    }
}

void game_move_entities(aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, int screen_height, int screen_width, int ticks){
    aircraft_linked_list * aircraft_list_temp = aircraft_list, * aircraft_list_temp_two = aircraft_list;
    missile_linked_list * missile_list_temp = missile_list;
    int min_follow_dist = 2000, min_follow_id = -1, min_follow_health = 2000;

    while(aircraft_list_temp != NULL){
        if(aircraft_list_temp->pos_y > screen_height + 2*aircraft_list_temp->size_y)
            aircraft_list_temp->health = 0;
        aircraft_list_temp = aircraft_list_temp->next;
    }
    aircraft_list_temp = aircraft_list;
    while(aircraft_list_temp != NULL){
        if(aircraft_list_temp->direction != -2 && aircraft_list_temp->direction != 2)
            aircraft_list_temp->pos_x += aircraft_list_temp->speed * aircraft_list_temp->direction;

        if(aircraft_list_temp->team == 1){
            aircraft_list_temp->pos_y += aircraft_list_temp->speed;
        } else if(aircraft_list_temp->team == 0 && (aircraft_list_temp->direction == -2 || aircraft_list_temp->direction == 2)){
            if(aircraft_list_temp->pos_y > screen_height/2 && aircraft_list_temp->pos_y < screen_height - aircraft_list_temp->size_y)
                aircraft_list_temp->pos_y += aircraft_list_temp->speed * aircraft_list_temp->direction/2;
            else if(aircraft_list_temp->pos_y <= screen_height/2) aircraft_list_temp->pos_y += 1;
            else if(aircraft_list_temp->pos_y >= screen_height - aircraft_list_temp->size_y) aircraft_list_temp->pos_y -= 1;
        }
        if(aircraft_list_temp->pos_x >= screen_width - aircraft_list_temp->size_x || aircraft_list_temp->pos_x <= 0){
            if(aircraft_list_temp->team == 1)
                aircraft_list_temp->direction *= -1;
            else aircraft_list_temp->direction = 0;
        }
        if(aircraft_list_temp->is_follower == 1){
            while(aircraft_list_temp_two != NULL){
                if(aircraft_list_temp_two->team != aircraft_list_temp->team)
                    break;
                aircraft_list_temp_two = aircraft_list_temp_two->next;
            }
            if(aircraft_list_temp->pos_x - aircraft_list_temp_two->pos_x < 0)
                aircraft_list_temp->direction = 1;
            else if(aircraft_list_temp->pos_x - aircraft_list_temp_two->pos_x > 0)
                aircraft_list_temp->direction = -1;
            else aircraft_list_temp->direction = 0;
        } else if(aircraft_list_temp->is_follower == 2){
            while(aircraft_list_temp_two != NULL){
                if(aircraft_list_temp_two->team == aircraft_list_temp->team)
                    break;
                aircraft_list_temp_two = aircraft_list_temp_two->next;
            }
            if(aircraft_list_temp->pos_x - aircraft_list_temp_two->pos_x < 0)
                aircraft_list_temp->direction = 1;
            else if(aircraft_list_temp->pos_x - aircraft_list_temp_two->pos_x > 0)
                aircraft_list_temp->direction = -1;
            else aircraft_list_temp->direction = 0;
        }
        aircraft_list_temp = aircraft_list_temp->next;
    }

    while(missile_list_temp != NULL){
        if(missile_list_temp->pos_y > screen_height + 2*missile_list_temp->size_y || missile_list_temp->pos_y < -10)
            missile_list_temp->health = 0;
        missile_list_temp = missile_list_temp->next;
    }
    missile_list_temp = missile_list;
    aircraft_list_temp = aircraft_list;
    while(missile_list_temp != NULL){
        min_follow_dist = 2000;
        min_follow_health = 2000;
        min_follow_id = -1;
        if(missile_list_temp->team == 0){
            missile_list_temp->pos_y -= missile_list_temp->speed;
        } else missile_list_temp->pos_y += missile_list_temp->speed;
        if(missile_list_temp->is_follower == 1 && ticks%missile_list_temp->follow_accuracy == 0){
            while(aircraft_list_temp != NULL){
                if(missile_list_temp->pos_y - aircraft_list_temp->pos_y < min_follow_dist && aircraft_list_temp->team != missile_list_temp->team){
                    min_follow_dist = aircraft_list_temp->pos_y - missile_list_temp->pos_y;
                    min_follow_id = aircraft_list_temp->id;
                }
                aircraft_list_temp = aircraft_list_temp->next;
            }
            aircraft_list_temp = aircraft_list;
            while(aircraft_list_temp != NULL){
                if(aircraft_list_temp->id == min_follow_id)
                    break;
                aircraft_list_temp = aircraft_list_temp->next;
            }
            if(min_follow_id != -1){
                if(aircraft_list_temp->pos_x+(aircraft_list_temp->size_x/2) - missile_list_temp->pos_x < 0)
                    missile_list_temp->pos_x -= missile_list_temp->speed;
                else if(aircraft_list_temp->pos_x+(aircraft_list_temp->size_x/2) - missile_list_temp->pos_x > 0)
                    missile_list_temp->pos_x += missile_list_temp->speed;
            }
        } else if(missile_list_temp->is_follower == 2 && ticks%missile_list_temp->follow_accuracy == 0){
            while(aircraft_list_temp != NULL){
                if(aircraft_list_temp->health <= min_follow_health && aircraft_list_temp->team != missile_list_temp->team){
                    min_follow_health = aircraft_list_temp->health;
                    min_follow_id = aircraft_list_temp->id;
                }
                aircraft_list_temp = aircraft_list_temp->next;
            }
            aircraft_list_temp = aircraft_list;
            while(aircraft_list_temp != NULL){
                if(aircraft_list_temp->id == min_follow_id)
                    break;
                aircraft_list_temp = aircraft_list_temp->next;
            }
            if(min_follow_id != -1){
                if(aircraft_list_temp->pos_x+(aircraft_list_temp->size_x/2) - missile_list_temp->pos_x < 0)
                    missile_list_temp->pos_x -= missile_list_temp->speed;
                else if(aircraft_list_temp->pos_x+(aircraft_list_temp->size_x/2) - missile_list_temp->pos_x > 0)
                    missile_list_temp->pos_x += missile_list_temp->speed;
            }
        }
        missile_list_temp = missile_list_temp->next;
    }
    if(aircraft_list->pos_x < 0) aircraft_list->pos_x = 0;
    if(aircraft_list->pos_x > screen_width - aircraft_list->size_x) aircraft_list->pos_x = screen_width - aircraft_list->size_x;
}

void game_draw_sprites(aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, explosion_linked_list * explosion_list){
    aircraft_linked_list * aircraft_list_temp = aircraft_list;
    missile_linked_list * missile_list_temp = missile_list;
    explosion_linked_list * explosion_list_temp = explosion_list;
    while(aircraft_list_temp != NULL){
        if(aircraft_list_temp->team == 0){
            if(aircraft_list_temp->direction == 0)
                al_draw_bitmap_region(aircraft_list_temp->sprite, 0, 0, aircraft_list_temp->size_x, aircraft_list_temp->size_y, aircraft_list_temp->pos_x, aircraft_list_temp->pos_y, 0);
            else if(aircraft_list_temp->direction == -1)
                al_draw_bitmap_region(aircraft_list_temp->sprite, aircraft_list_temp->size_x, 0, aircraft_list_temp->size_x, aircraft_list_temp->size_y, aircraft_list_temp->pos_x, aircraft_list_temp->pos_y, 0);
            else
                al_draw_bitmap_region(aircraft_list_temp->sprite, aircraft_list_temp->size_x, 0, aircraft_list_temp->size_x, aircraft_list_temp->size_y, aircraft_list_temp->pos_x, aircraft_list_temp->pos_y, ALLEGRO_FLIP_HORIZONTAL);
        } else{
            if(aircraft_list_temp->direction == 0)
                al_draw_bitmap_region(aircraft_list_temp->sprite, 0, 0, aircraft_list_temp->size_x, aircraft_list_temp->size_y, aircraft_list_temp->pos_x, aircraft_list_temp->pos_y, ALLEGRO_FLIP_VERTICAL);
            else if(aircraft_list_temp->direction == -1)
                al_draw_bitmap_region(aircraft_list_temp->sprite, aircraft_list_temp->size_x, 0, aircraft_list_temp->size_x, aircraft_list_temp->size_y, aircraft_list_temp->pos_x, aircraft_list_temp->pos_y, ALLEGRO_FLIP_VERTICAL);
            else
                al_draw_bitmap_region(aircraft_list_temp->sprite, aircraft_list_temp->size_x, 0, aircraft_list_temp->size_x, aircraft_list_temp->size_y, aircraft_list_temp->pos_x, aircraft_list_temp->pos_y, ALLEGRO_FLIP_HORIZONTAL|ALLEGRO_FLIP_VERTICAL);
        }
        aircraft_list_temp = aircraft_list_temp->next;
    }
    while(missile_list_temp != NULL){
        if(missile_list_temp->team == 0)
        al_draw_bitmap(missile_list_temp->sprite, missile_list_temp->pos_x, missile_list_temp->pos_y, 0);
        else al_draw_bitmap(missile_list_temp->sprite, missile_list_temp->pos_x, missile_list_temp->pos_y, ALLEGRO_FLIP_VERTICAL);
        missile_list_temp = missile_list_temp->next;
    }
    while(explosion_list_temp != NULL){
        if(explosion_list_temp->ticks < 5) al_draw_bitmap(explosion_list_temp->sprites[0], explosion_list_temp->pos_x, explosion_list_temp->pos_y, 0);
        else if(explosion_list_temp->ticks < 10) al_draw_bitmap(explosion_list_temp->sprites[1], explosion_list_temp->pos_x, explosion_list_temp->pos_y, 0);
        else if(explosion_list_temp->ticks < 15) al_draw_bitmap(explosion_list_temp->sprites[2], explosion_list_temp->pos_x, explosion_list_temp->pos_y, 0);
        if(explosion_list_temp->ticks == 15 && explosion_list_temp->pos_x != -40) explosion_list_temp->health = 0;
        explosion_list_temp->ticks++;
        explosion_list_temp = explosion_list_temp->next;
    }
}

void game_check_health_levels(aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, float audio_level){
    aircraft_linked_list * aircraft_list_temp = aircraft_list;
    missile_linked_list * missile_list_temp = missile_list;
    int is_aircraft_destroyed = 0, is_missile_destroyed = 0;
    int aircraft_index = 0, missile_index = 0;

    while(missile_list_temp != NULL){
        if(missile_list_temp->health == 0 && missile_index != 0 && is_missile_destroyed == 0){
            missile_remove_index(&missile_list, missile_index);
            is_missile_destroyed = 1;
        } else if(missile_list_temp->health == 0 && missile_index == 0 && is_missile_destroyed == 0){
            missile_list_temp->pos_x = -10;
            missile_list_temp->pos_y = 0;
        }
        missile_index++;
        missile_list_temp = missile_list_temp->next;
    }

    while(aircraft_list_temp != NULL){
        if(aircraft_list_temp->health <= 0 && aircraft_index != 0 && is_aircraft_destroyed == 0){
            aircraft_remove_index(&aircraft_list, aircraft_index);
            if(aircraft_list->special_attack_counter < 5 && aircraft_list->is_using_special_attack == 0) aircraft_list->special_attack_counter++;
            is_aircraft_destroyed = 1;
        }
        aircraft_index++;
        aircraft_list_temp = aircraft_list_temp->next;
    }
}

void game_scenario_check_health_levels(int * game_state, scenario_base current_scenario, aircraft_linked_list * aircraft_list, missile_linked_list * missile_list, float audio_level){
    aircraft_linked_list * aircraft_list_temp = aircraft_list;
    missile_linked_list * missile_list_temp = missile_list;
    int is_aircraft_destroyed = 0, is_missile_destroyed = 0;
    int aircraft_index = 0, missile_index = 0;

    while(missile_list_temp != NULL){
        if(missile_list_temp->health == 0 && missile_index != 0 && is_missile_destroyed == 0){
            missile_remove_index(&missile_list, missile_index);
            is_missile_destroyed = 1;
        } else if(missile_list_temp->health == 0 && missile_index == 0 && is_missile_destroyed == 0){
            missile_list_temp->pos_x = -10;
            missile_list_temp->pos_y = 0;
        }
        missile_index++;
        missile_list_temp = missile_list_temp->next;
    }

    while(aircraft_list_temp != NULL){
        if(aircraft_list_temp->health <= 0 && aircraft_index != 0 && is_aircraft_destroyed == 0){
            if(aircraft_list_temp->type == current_scenario.win_enemy_aircraft_type)
                (*game_state)++;
            aircraft_remove_index(&aircraft_list, aircraft_index);
            if(aircraft_list->special_attack_counter < 5 && aircraft_list->is_using_special_attack == 0) aircraft_list->special_attack_counter++;
            is_aircraft_destroyed = 1;
        }
        aircraft_index++;
        aircraft_list_temp = aircraft_list_temp->next;
    }
}

void game_scenario_spawn_enemies(aircraft_linked_list * aircraft_list, aircraft_template * aircrafts, scenario_base current_scenario, int ticks){
    aircraft_linked_list * aircraft_list_temp = aircraft_list;
    int i = 0, size = 0;
    while(1){
        if(current_scenario.enemy_list[i].type == -1) break;
        i++;
        size++;
    }
    for(i=0; i<size; i++)
        if(current_scenario.enemy_list[i].spawn_time == ticks)
            aircraft_add_new(&aircraft_list, aircrafts[current_scenario.enemy_list[i].type], current_scenario.enemy_list[i].pos_x, current_scenario.enemy_list[i].pos_y);
    while(aircraft_list_temp->next->next != NULL)
            aircraft_list_temp = aircraft_list_temp->next;
        aircraft_list_temp->next->id = aircraft_list_temp->id+1;
}

void game_scenario_boss_behaviour(aircraft_linked_list * aircraft_list, scenario_base current_scenario){
    aircraft_linked_list * aircraft_list_temp = aircraft_list;
    while(aircraft_list_temp != NULL){
        if(aircraft_list_temp->type == current_scenario.win_enemy_aircraft_type && aircraft_list_temp->pos_y == 150 && aircraft_list->missile_type != -1){
            aircraft_list_temp->speed = 0;
        }
        aircraft_list_temp = aircraft_list_temp->next;
    }
}

void game_control_special_attack(aircraft_linked_list * aircraft_list, int * special_attack_ticks){
    if(aircraft_list->is_using_special_attack == 1){
        (*special_attack_ticks)++;
    }
    if((*special_attack_ticks) == 300){
        (*special_attack_ticks) = 0;
        aircraft_list->is_using_special_attack = 0;
        aircraft_list->missile_type = aircraft_list->missile_type + aircraft_list->special_attack_missile_type;
        aircraft_list->special_attack_missile_type = aircraft_list->missile_type - aircraft_list->special_attack_missile_type;
        aircraft_list->missile_type = aircraft_list->missile_type - aircraft_list->special_attack_missile_type;
    }
}

void game_calculate_high_scores(int score, int high_scores[11]){
    FILE * high_scores_krhs;
    int i, j;
    high_scores_krhs = fopen("data/playerstats/high_scores.krhs", "rt");
    for(i=0; i<10; i++)
        fscanf(high_scores_krhs, "%d", &high_scores[i]);
    for(i=0; i<10; i++){
        if(score > high_scores[i]){
            for(j=8; j>=i; j--){
                high_scores[j+1] = high_scores[j];
            }
            high_scores[i] = score;
            i=10;
        }
    }
    fclose(high_scores_krhs);
    high_scores_krhs = fopen("data/playerstats/high_scores.krhs", "wt");
    for(i=0; i<10; i++)
        fprintf(high_scores_krhs, "%d\n", high_scores[i]);
    fclose(high_scores_krhs);
}

void game_check_explosion_health_levels(explosion_linked_list * explosion_list){
    explosion_linked_list * explosion_list_temp = explosion_list;
    int is_explosion_destroyed = 0, explosion_index = 0;
    while(explosion_list_temp != NULL){
        if(explosion_list_temp->health == 0 && explosion_index != 0 && is_explosion_destroyed == 0){
            explosion_remove_index(&explosion_list, explosion_index);
            is_explosion_destroyed = 1;
        }
        explosion_index++;
        explosion_list_temp = explosion_list_temp->next;
    }
}
