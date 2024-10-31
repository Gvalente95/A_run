#include "header.h"

int		update_input()
{
	int	new = getchar();
	movement[0] = new == 'a' ? -MOVE_AMOUNT : new == 'd' ? MOVE_AMOUNT : 0;
	movement[1] = new == 'w' ? -MOVE_AMOUNT : new == 's' ? MOVE_AMOUNT : 0;
	prev_input = input != new ? input : prev_input;
	input = new;
	return (1);
}

int		is_grounded(ENTITY *entity, int check)
{
	int check_index = (SCRN_WIDTH + 1) * (entity->position[1] + scroll[1] + entity->height) + entity->position[0] + scroll[0];
	if (check_index <= (int)strlen(screen))
	{
		for (int i = 0; i < entity->width; i++)
		{
			if (screen[check_index + i] != ' ')
				return (1);
			if (check)
				screen[check_index + i] = 'a';
		}
	}
	return (0);
}

int get_colliders(ENTITY *entity, int check)
{
	int height = MAX(3, entity->height);
	int width = MAX(3, entity->width);

	int x_pos = entity->position[0] - scroll[0];
	int y_pos = entity->position[1] - scroll[1];
    int start_index = (SCRN_WIDTH + 1) * (y_pos - 1) + x_pos;
	int index = start_index;


    if (index <= (int)strlen(prvscrn))
    {
        for (int y = -3; y <= (height + 3); y++)
        {
            for (int i = -3; i <= width + 3; i++)
            {
                index = (SCRN_WIDTH + 1) * (y_pos) + (x_pos) + i + y + y * SCRN_WIDTH + 1;
                if (index < (int)strlen(prvscrn))
                {
					int is_col = prvscrn[index] == HOR_COL || prvscrn[index] == VER_COL;
                    if (entity->movement[1] < 0 && y == -1 && i > 0  && i < width - 2)
					{
                        if (is_col) {
							if (check && screen[index != '\n']) screen[index] = COL_CHECKL;
							return (0);
						}
						if (check && screen[index != '\n']) screen[index] = COL_CHECKL;
					}
                    else if (entity->movement[1] > 0 && y >= height + 1 && i > 0 && i < width - 2)
					{
                         if (is_col) {
							if (check && screen[index != '\n']) screen[index] = COL_CHECKL;
							return (0);
						}
						if (check && screen[index != '\n']) screen[index] = COL_CHECKL;
					}
                    if (entity->movement[0] < 0 && i < 1 && y >= height - 3 && y < height + 2)
					{
                         if (is_col) {
							if (check && screen[index != '\n']) screen[index] = COL_CHECKL;
							return (0);
						}
						if (check && screen[index != '\n']) screen[index] = COL_CHECKL;
					}
                    else if (entity->movement[0] > 0 && i > width - 1 && y >= height - 3 && y < height + 2)
					{
                         if (is_col) {
							if (check && screen[index != '\n']) screen[index] = COL_CHECKL;
							return (0);
						}
						if (check && screen[index != '\n']) screen[index] = COL_CHECKL;
					}
                }
            }
        }
    }
	if (check)
	{
		char txt[100];
		strncpy(txt, entity->label, 100);
		int i = 0;
		start_index -= SCRN_WIDTH - 1;
		while (txt[++i] && screen[++start_index])
		{
			if (screen[start_index] != '\n') screen[start_index] = txt[i];
		}
	} 
    return 1;
}

void update_ENTITY(ENTITY *entity, int new_movement[2])
{
    char new_frame[MAX_CONTENT];

	if (entity->hp <= -1)
	{
		int i = -1;
		while (entity->frame[++i])
			if (entity->frame[i] != '\n' && entity->frame[i] != ' ' && rand() % 30) entity->frame[i] = -entity->hp > rand() % 15 ? ' ' : rand_range(50, 120);
		return;
	}

    entity->movement[0] = new_movement[0] ? new_movement[0] : entity->movement[0];
    entity->movement[1] = new_movement[1] ? new_movement[1] : entity->movement[1];

	if (new_movement[0] || new_movement[1])
	{
		entity->action = move;
		entity->dir = new_movement[0] > 0 ? right : new_movement[0] < 0 ? left : new_movement[1] > 1 ? down : up;
	}
    if (entity->movement[0] > 0)
        entity->movement[0] = MAX(0, entity->movement[0] - 1);
    if (entity->movement[0] < 0)
        entity->movement[0] = MIN(0, entity->movement[0] + 1);
    if (entity->movement[1] > 0)
        entity->movement[1] = MAX(0, entity->movement[1] - 1);
    if (entity->movement[1] < 0)
        entity->movement[1] = MIN(0, entity->movement[1] + 1);

	int can_move = 1;
	if (is_in_canv(entity->position[0] - scroll[0], entity->position[1] - scroll[1], entity->frame, prvscrn)) can_move = get_colliders(entity, DEBUG_CHECK);
	if (strcmp(entity->label, "PLAYER") && !can_move) screen[5] = '*';
	if (!can_move)
	{
		entity->movement[0] = entity->movement[1] = new_movement[0] = new_movement[1] = input = 0;
		if (entity->action == move) entity->action = idle;
	}
    
	if (entity->action == move)
	{
		strncpy(new_frame, game_time % 2 == 0? entity->move[entity->dir][0] : entity->move[entity->dir][1], MAX_CONTENT);
		if (!entity->movement[0] && !entity->movement[1]) entity->action = idle;
	}
	else if (entity->action == attack)
		strncpy(new_frame, entity->attack[entity->dir], MAX_CONTENT);
	else if (entity->action == idle)
		strncpy(new_frame, entity->idle[entity->dir], MAX_CONTENT); 

	if (strcmp(new_frame, entity->frame)) strncpy(entity->frame, new_frame, MAX_CONTENT);

	if (!entity->hurt && can_move)
	{
		entity->position[0] += (entity->movement[0] > 0) ? entity->speed : (entity->movement[0] < 0) ? -entity->speed : 0;
		entity->position[1] += (entity->movement[1] > 0) ? MAX(1, entity->speed/2) : (entity->movement[1] < 0) ? MIN(-1, -entity->speed/2) : 0;
	}
}

int PUSH_ATK = 0;
void	update_player()
{
	int mv[2]; 
	mv[0] = movement[0];
	mv[1] = movement[1];
	int is_mov = !(input == 'a' || input == 'w' || input == 's' || input == 'd' || input == CHNG_WEAP) && input != -1;

	if ((mv[0] && PLAYER.movement[0]) || is_mov) PLAYER.movement[1] = 0;
	if ((mv[1] && PLAYER.movement[1]) || is_mov) PLAYER.movement[0] = 0;
	if (input == ' ' && PLAYER.action != attack && !PUSH_ATK)
	{
		if (WEAPON_INDEX == 0)
		{
			PUSH_ATK++;
			PROJ_FIRED++;
			for (int i = 0; i < 100; i++)
				if (projectiles[i][3] == 0)
				{
					projectiles[i][0] = PLAYER.position[0] + (PLAYER.dir == left ? -5 : PLAYER.dir == right? 5 : PLAYER.dir == up ? 6 : 1);
					projectiles[i][1] = PLAYER.position[1] + (PLAYER.dir == down ? 5 : PLAYER.dir == up? -2 : 2);
					projectiles[i][3] = 1;
					projectiles[i][2] = PLAYER.dir;
					break;
				}
		}
	}
	if (PUSH_ATK)
	{
		PLAYER.action = attack;
		PUSH_ATK++;
		PLAYER.movement[0] = PLAYER.movement[1] = mv[0] = mv[1] = 0;
		PLAYER.movement[0] = PLAYER.dir == left ? 2 : PLAYER.dir == right? -2 : 0;
		PLAYER.movement[1] = PLAYER.dir == up ? 2 : PLAYER.dir == down? -2 : 0;
		if (PUSH_ATK > 3)
		{
			PUSH_ATK = 0;
			PLAYER.action = idle;
		}
	}
	update_ENTITY(&PLAYER, mv);
	if (INV_FRAME && INV_FRAME % 2 == 0) strncpy(PLAYER.frame, " ", 2);

	int i = 0;
	if (PLAYER.dir == up && PLAYER.action == move)
	{
		while (screen_houses[i].type != HOUSE_TYPES_COUNT)
		{
			int x_dist = (abs(PLAYER.position[0] - (screen_houses[i].position[0] + screen_houses[i].size[0] / 2)));
			int y_dist = (abs(PLAYER.position[1] - (screen_houses[i].position[1] + screen_houses[i].size[1] - 2)));
			if (x_dist < 10 && y_dist < 10) PLAYER_HOUSE = i;
			i++;
		}
	}
}

void update_mobs(ENTITY *ent, int amount)
{
	int AGGRO_RANGE = 40;
	//int limit = 30;
	for (int x = 0; x < amount; x++)
	{
		int new_movement[2] = {0,0};
		if (ent[x].hurt) ent[x].hurt++;
		if (ent[x].hurt > 5) ent[x].hurt = 0;
		if (ent[x].hp <= 0)
		{
			ent[x].hp--;
			if (ent[x].hp < -10)
			{
				ent[x].position[0] = scroll[0] - rand_range(-500, 500);
				ent[x].position[1] = scroll[1] - rand_range(-500, 500);
				ent[x].hp = ent[x].maxHP;
			}
			ent[x].movement[0] = ent[x].movement[1] = 0;
 			update_ENTITY(&ent[x], new_movement);
			continue;
		}

		for (int p = 0; p < PROJ_FIRED + 5; p++)
		{
			if (projectiles[p][3] == 0) continue;
			int x_dist = (abs((projectiles[p][0] - scroll[0]) - (ent[x].position[0] - scroll[0])));
			int y_dist = (abs((projectiles[p][1] - scroll[1]) - (ent[x].position[1] - scroll[1])));
			if (!ent[x].hurt && x_dist < ent[x].width + 2 && y_dist < ent[x].height)
			{
				projectiles[p][3] = 0;
				ent[x].hp--;
				ent[x].hurt++;
				if (ent[x].hp == 0) play_sound(AU_expl4, 0);
				play_sound(AU_expl2, 0);
				ent[x].position[0] += projectiles[p][2] == left ? -RIFLE_PUSH : projectiles[p][2] == right ? RIFLE_PUSH : 0;
				ent[x].position[1] += projectiles[p][2] == up ? -RIFLE_PUSH : projectiles[p][2] == down ? RIFLE_PUSH : 0;
			}
		}

		int x_dist = (abs)(PLAYER.position[0] - ent[x].position[0]);
		int y_dist = (abs)(PLAYER.position[1] - ent[x].position[1]);
		int aggro = ent[x].hp < ent[x].maxHP ? AGGRO_RANGE * 10 : AGGRO_RANGE;
		if (PLAYER.hp > 0 && x_dist < aggro && y_dist < aggro / 2)
		{
			if (x_dist < 10 && y_dist < 5 && input == ' ')  ent[x].hp-=1;
			if (x_dist < 4 && y_dist < 2) {
				if (!INV_FRAME) {PLAYER.hp -= 1; INV_FRAME = 1; if (!PLAYER.hurt) PLAYER.hurt = 1; play_sound(AU_high_pitch2, 0);}
			}
			if (x_dist > y_dist) new_movement[0] = PLAYER.position[0] > ent[x].position[0] ? ent[x].speed : PLAYER.position[0] < ent[x].position[0] ? -ent[x].speed : 0;
			else new_movement[1] = PLAYER.position[1] > ent[x].position[1] ? ent[x].speed : PLAYER.position[1] < ent[x].position[1] ? -ent[x].speed : 0;
		}
		else if (rand_range(0, 5) == 0) 
		{
			new_movement[0] = rand() % 2 == 0 ? 5 : -5;
			new_movement[1] = rand() % 2 == 0 ? 5 : -5;
		}
		else if (rand() % 500) ent[x].movement[0] = ent[x].movement[1] = 0;
		update_ENTITY(&ent[x], new_movement);
	}
}

void update_projectiles()
{
	int spd = 8;
	for (int i = 0; i < PROJ_FIRED + 5; i++)
	{
		if (projectiles[i][3] == 1)
		{
			DIRECTION dir = projectiles[i][2];
			switch (dir)
			{
				case up: projectiles[i][1]-=spd / 2; break;
				case down: projectiles[i][1]+=spd / 2; break;
				case left: projectiles[i][0]-=spd; break;
				case right: projectiles[i][0]+=spd; break;
			}
			int x = projectiles[i][0] - scroll[0];
			int y = projectiles[i][1] - scroll[1];
			char str[2];
			str[0] = PROJ_IC;
			str[1] = '\0';
			if (is_in_canv(x, y, str, screen))  print_string(str, screen, x, y);
			else 
			{
				projectiles[i][3] = 0;
				PROJ_FIRED--;
			}
		}
	}
}

int 	update_game()
{
	update_input();
	if (INV_FRAME) INV_FRAME++;
	if (INV_FRAME > 20) INV_FRAME = 0;
	if (PLAYER.hurt && PLAYER.hp > 0)
	{
		PLAYER.hurt++;
		if (PLAYER.hp > 0)
		{
			int i = -1;
			while (screen[++i])
				if (screen[i] != '\n') screen[i] = rand_range(100, 150);
		}
		if (PLAYER.hurt >= 2) PLAYER.hurt = 0;
	}
	else
	{
		PLAYER.hurt = 0;
		if (PLAYER.hp > 0) update_player();

		if (PLAYER_HOUSE == -1)
		{
			update_mobs(MOBS, MOBS_AMOUNT);
			update_mobs(SPIDERS, SPIDER_AMOUNT);
			update_mobs(BOSS, BOSS_AMNT);
			update_projectiles();
		}
	}
	scroll[0] = PLAYER.position[0] - SCRN_WIDTH/2;
	scroll[1] = PLAYER.position[1] - (SCRN_HEIGHT/2);
	return (1);
}