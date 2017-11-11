#include "explosions.h"

void explosion_add_new(explosion_linked_list ** head, explosion_template new_explosion, int pos_x, int pos_y){
    explosion_linked_list * new, * head_temp = (*head);
    new = (explosion_linked_list*)malloc(sizeof(explosion_linked_list));
    new->health = new_explosion.health;
    new->pos_x = pos_x;
    new->pos_y = pos_y;
    new->ticks = 0;
    new->sprites[0] = new_explosion.sprites[0];
    new->sprites[1] = new_explosion.sprites[1];
    new->sprites[2] = new_explosion.sprites[0];
    new->next = NULL;
    if(head_temp != NULL){
        while(head_temp->next != NULL){
            head_temp = head_temp->next;
        }
        head_temp->next = new;
    } else (*head) = new;
}

void explosion_remove_index(explosion_linked_list ** head, int index){
    int i, size = 1;
	explosion_linked_list * sizeTemp, * headTemp, * tailTemp;
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

void explosion_setup_base(explosion_template explosions[255]){
    explosions[0].health=3, explosions[0].pos_x=0, explosions[0].pos_y = 0;
    explosions[0].sprites[0] = al_load_bitmap("data/sprites/explosion0.png");
    explosions[0].sprites[1] = al_load_bitmap("data/sprites/explosion1.png");
    explosions[0].sprites[2] = explosions[0].sprites[0];
}
