#include "scenario.h"

void parse_scenario_data(scenario_base scenarios[20], int screen_height, int screen_width, aircraft_template * aircrafts){
    int i = 0, j = 0;
    char temp_string[50], * p_temp_string;
    FILE * scenarios_krscn, * scenario_choose_scenario_krbtn;
    scenarios_krscn = fopen("data/scenarios/scenarios.krscn", "rt");
    while(fscanf(scenarios_krscn, "%s ", temp_string)){
        if(strcmp(temp_string, "END_FILE") == 0) break;
        while(fgets(temp_string, 50, scenarios_krscn)){
            if(temp_string[strlen(temp_string)-1] == '\n')
                temp_string[strlen(temp_string)-1] = '\0';
            if(j>0)
                strcpy(scenarios[i].description[j], temp_string);
            else strcpy(scenarios[i].title, temp_string);
            if(strcmp(temp_string, "END") == 0 ) break;
            j++;
        }
        j=0;
        fscanf(scenarios_krscn, "%d %d ", &scenarios[i].ally_aircraft_type, &scenarios[i].win_enemy_aircraft_type);
        while(fscanf(scenarios_krscn, "%d %d %s %d ", &scenarios[i].enemy_list[j].spawn_time, &scenarios[i].enemy_list[j].type, temp_string, &scenarios[i].enemy_list[j].pos_y)){
            if(temp_string[0] == 'w'){
                p_temp_string = &temp_string[1];
                scenarios[i].enemy_list[j].pos_x = screen_width - atoi(p_temp_string) - aircrafts[scenarios[i].enemy_list[j].type].size_x;
            } else if(temp_string[0] == 'h'){
                scenarios[i].enemy_list[j].pos_x = screen_width/2 - aircrafts[scenarios[i].enemy_list[j].type].size_x/2;
            } else
                scenarios[i].enemy_list[j].pos_x = atoi(temp_string);
            if(scenarios[i].enemy_list[j].spawn_time == -1) break;
            j++;
        }
        j=0;
        i++;
    }
    scenario_choose_scenario_krbtn = fopen("data/gametext/scenario_choose_scenario.krbtn", "wt");
    for(j=0; j<i; j++)
        fprintf(scenario_choose_scenario_krbtn, "%s\n%d\n", scenarios[j].title, j);
    fprintf(scenario_choose_scenario_krbtn, "%s\n%d\n", "END", 0);
    fclose(scenario_choose_scenario_krbtn);
    fclose(scenarios_krscn);
}
