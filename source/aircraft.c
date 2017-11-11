#include "aircraft.h"

int aircraft_get_size(aircraft_linked_list * head){
    int size = 1;
    while(head->next != NULL){
        head = head->next;
        size++;
    }
    return size;
}

void aircraft_add_new(aircraft_linked_list ** head, aircraft_template new_aircraft, int pos_x, int pos_y){
    aircraft_linked_list * new, * head_temp = (*head);
    new = (aircraft_linked_list*)malloc(sizeof(aircraft_linked_list));
    strcpy(new->name, new_aircraft.name);
    new->team = new_aircraft.team;
    new->health = new_aircraft.health;
    new->type = new_aircraft.type;
    new->direction = new_aircraft.direction;
    new->id = new_aircraft.id;
    new->cost = new_aircraft.cost;
    new->speed = new_aircraft.speed;
    new->missile_type = new_aircraft.missile_type;
    new->special_attack_missile_type = new_aircraft.special_attack_missile_type;
    new->is_follower = new_aircraft.is_follower;
    new->is_using_special_attack = new_aircraft.is_using_special_attack;
    new->special_attack_counter = new_aircraft.special_attack_counter;
    new->pos_x = pos_x;
    new->pos_y = pos_y;
    new->size_x = new_aircraft.size_x;
    new->size_y = new_aircraft.size_y;
    new->sprite = new_aircraft.sprite;
    new->next = NULL;
    if(head_temp != NULL){
        while(head_temp->next != NULL){
            head_temp = head_temp->next;
        }
        head_temp->next = new;
    } else (*head) = new;
}

void aircraft_remove_index(aircraft_linked_list ** head, int index){
    int i, size = 1;
	aircraft_linked_list * sizeTemp, * headTemp, * tailTemp;
	tailTemp = (*head);
	headTemp = (*head);
	sizeTemp = (*head);
	while(sizeTemp->next!=NULL){
		sizeTemp = sizeTemp->next;
		size++;
	}
    for(i=0; i<index-1; i++)
        tailTemp = tailTemp->next;
    for(i=0; i<index; i++)
        headTemp = headTemp->next;
    if(size > 2)
        tailTemp->next = headTemp->next;
    else
        tailTemp->next = NULL;
	free(headTemp);
}
