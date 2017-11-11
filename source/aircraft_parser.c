#include "aircraft_parser.h"

int parse_aircraft_data(aircraft_template * aircrafts){
    FILE * aircrafts_krac, * endless_choose_plane_krbtn;
    char temp_string[MAX_LEN], data_type[MAX_LEN], equals[MAX_LEN], spritepath[MAX_LEN], name[MAX_LEN];
    int size = 0, val, i;

    aircrafts_krac = fopen("data/unitdata/aircrafts.krac", "rt");
    endless_choose_plane_krbtn = fopen("data/gametext/endless_choose_plane.krbtn", "wt");

    while(fscanf(aircrafts_krac, "%s", temp_string) != EOF){
        fscanf(aircrafts_krac, "%s %s %s", data_type, equals, name);
        strcpy(aircrafts[size].name, name);
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].team = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].health = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].type = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].direction = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].id = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].cost = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].speed = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].missile_type = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].special_attack_missile_type = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].is_follower = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].is_using_special_attack = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].special_attack_counter = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].pos_x = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].pos_y = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].size_x = val;
        fscanf(aircrafts_krac, "%s %s %d", data_type, equals, &val);
        aircrafts[size].size_y = val;
        fscanf(aircrafts_krac, "%s %s %s", data_type, equals, spritepath);
        aircrafts[size].sprite = al_load_bitmap(spritepath);
        size++;
    }
    for(i=0; i<size; i++)
        if(aircrafts[i].team == 0 && aircrafts[i].cost == 0)
            fprintf(endless_choose_plane_krbtn, "%s\n%d\n", aircrafts[i].name, aircrafts[i].type);
    fprintf(endless_choose_plane_krbtn, "%s\n%d\n", "END", 0);
    fclose(aircrafts_krac);
    fclose(endless_choose_plane_krbtn);
    return size;
}
