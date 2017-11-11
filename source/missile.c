#include "missile.h"

int missile_get_size(missile_linked_list * head){
    int size = 1;
    while(head->next != NULL){
        head = head->next;
        size++;
    }
    return size;
}

void missile_add_new(missile_linked_list ** head, missile_template new_missile, int pos_x, int pos_y){
    missile_linked_list * new, * head_temp = (*head);
    new = (missile_linked_list*)malloc(sizeof(missile_linked_list));
    new->team = new_missile.team;
    new->speed = new_missile.speed;
    new->health = new_missile.health;
    new->type = new_missile.type;
    new->is_follower = new_missile.is_follower;
    new->follow_accuracy = new_missile.follow_accuracy;
    new->pos_x = pos_x;
    new->pos_y = pos_y;
    new->size_x = new_missile.size_x;
    new->size_y = new_missile.size_y;
    new->sprite = new_missile.sprite;
    new->hitsound = new_missile.hitsound;
    new->next = NULL;
    if(head_temp != NULL){
        while(head_temp->next != NULL){
            head_temp = head_temp->next;
        }
        head_temp->next = new;
    } else (*head) = new;
}

void missile_remove_index(missile_linked_list ** head, int index){
    int i, size = 1;
	missile_linked_list * sizeTemp, * headTemp, * tailTemp;
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
