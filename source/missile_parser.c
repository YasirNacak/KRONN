#include "missile_parser.h"

int parse_missile_data(missile_template * missiles){
    FILE * missiles_krm;
    char temp_string[MAX_LEN], data_type[MAX_LEN], equals[MAX_LEN], spritepath[MAX_LEN], audiopath[MAX_LEN];
    int size = 0, val;

    missiles_krm = fopen("data/unitdata/missiles.krm", "rt");

    while(fscanf(missiles_krm, "%s", temp_string) != EOF){
        fscanf(missiles_krm, "%s %s %d", data_type, equals, &val);
        missiles[size].team = val;
        fscanf(missiles_krm, "%s %s %d", data_type, equals, &val);
        missiles[size].speed = val;
        fscanf(missiles_krm, "%s %s %d", data_type, equals, &val);
        missiles[size].health = val;
        fscanf(missiles_krm, "%s %s %d", data_type, equals, &val);
        missiles[size].type = val;
        fscanf(missiles_krm, "%s %s %d", data_type, equals, &val);
        missiles[size].is_follower = val;
        fscanf(missiles_krm, "%s %s %d", data_type, equals, &val);
        missiles[size].follow_accuracy = val;
        fscanf(missiles_krm, "%s %s %d", data_type, equals, &val);
        missiles[size].pos_x = val;
        fscanf(missiles_krm, "%s %s %d", data_type, equals, &val);
        missiles[size].pos_y = val;
        fscanf(missiles_krm, "%s %s %d", data_type, equals, &val);
        missiles[size].size_x = val;
        fscanf(missiles_krm, "%s %s %d", data_type, equals, &val);
        missiles[size].size_y = val;
        fscanf(missiles_krm, "%s %s %s", data_type, equals, spritepath);
        missiles[size].sprite = al_load_bitmap(spritepath);
        fscanf(missiles_krm, "%s %s %s", data_type, equals, audiopath);
        missiles[size].hitsound = al_load_sample(audiopath);
        size++;
    }
    fclose(missiles_krm);
    return size;
}
