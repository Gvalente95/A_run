#include "header.h"

int render_screen()
{
	int i = -1;
	system("clear");
	while (screen[++i])
	{
		if (screen[i] == '#' || screen[i] == INV_VER_COL || screen[i] == INV_HOR_COL)
			printf(" ");
		else if (screen[i] == HOR_COL || screen[i] == VER_COL)
			printf("%c", screen[i] == HOR_COL ? '-' : '|');
		else if (screen[i] == WATER_IC || screen[i] == MUD_IC || screen[i] == ICE_IC || screen[i] == GRASS_IC)
			print_colored_text(NULL, screen[i], screen[i] == MUD_IC ? BROWN : screen[i] == WATER_IC ? BLUE : GREEN);
		else if (screen[i] == GRN_GRASS || screen[i] == ORNG_GRASS || screen[i] == RED_GRASSS)
			print_colored_text(NULL, ',', screen[i] == GRN_GRASS ? GREEN : screen[i] == ORNG_GRASS ? ORANGE : RED);
		else if (screen[i] == LEAF_IC)
			print_colored_text(NULL, ',', ORANGE);
		else if (screen[i] == PROJ_IC)
			print_colored_text(NULL, '*', RED);
		else
			printf("%c", screen[i]);
		prvscrn[i] = screen[i];
	}
	prvscrn[i] = '\0';
	// printf("\n%d %d   ", PLAYER.movement[0], PLAYER.movement[1]);
	// printf("\nSCROLL %d %d    ", scroll[0], scroll[1]);
	// printf("\nINPUT %c PRV: %c\n\n", input, prev_input);

	return (1);
}

void render_mobs(ENTITY *entity, int amount)
{
	for (int x = 0; x < amount; x++)
	{
		if (entity[x].hp > 0 && (entity[x].hurt && game_time % 2 == 0)) continue;
		if (entity[x].position[0] - scroll[0] > 0 && entity[x].position[0] - scroll[0] < SCRN_WIDTH -1 - entity[x].width && entity[x].position[1] - scroll[1] > 0 && entity[x].position[1] - scroll[1] < SCRN_HEIGHT - entity[x].height)
		print_entity(entity[x], screen);
	}
}

void render_player()
{
	print_entity(PLAYER, screen);

	int swd_p[2] = {PLAYER.position[0],PLAYER.position[1]};
	if (PLAYER.weap.active)
	{
		if (input == CHNG_WEAP)
		{
			WEAPON_INDEX++;
			if (WEAPON_INDEX >= WEAP_AMNT) WEAPON_INDEX = 0;
		}
		switch (PLAYER.dir)
		{
			case up: swd_p[0] += 5; swd_p[1] += 0; break;
			case down: swd_p[0] += 0; swd_p[1] += 4;break;
			case left: swd_p[0] -= 4; swd_p[1] += 2; break;
			case right: swd_p[0] += 6; swd_p[1] += 2; break;
		}
		print_string((char *)WEAPONS[WEAPON_INDEX].gfx[PLAYER.dir][PLAYER.action == attack], screen, swd_p[0] - scroll[0], swd_p[1] - scroll[1]);
	}
}

int is_in_canv(int x, int y, char *src, char *dst)
{
    int src_width = get_width(src);
    int src_height = get_height(src);
    int dst_width = get_width(dst);
    int dst_height = get_height(dst);
    return (x + src_width > 0 && x < dst_width && y + src_height > 0 && y < dst_height);
}

void set_env_element(int *element, char *txt)
{
    int x = element[0] - scroll[0];
    int y = element[1] - scroll[1];
    int limit = SCRN_WIDTH/2;

    if (is_in_canv(x, y, txt, screen))
    {
        int screen_index = y * (SCRN_WIDTH + 1) + x;
        if (screen_index < (int)strlen(screen))
            print_string(txt, screen, x, y);
    }
    else if (x <= -limit || x >= SCRN_WIDTH + limit || y <= -limit || y >= SCRN_HEIGHT + limit)
    {
        int border_side = rand_range(0, 3);
        switch (border_side)
        {
            case 0:  // Top border
                element[0] = rand_range(0, SCRN_WIDTH) + scroll[0];
                element[1] = scroll[1] - get_height(txt);  // Position above the screen
                break;
            case 1:  // Bottom border
                element[0] = rand_range(0, SCRN_WIDTH) + scroll[0]; 
                element[1] = SCRN_HEIGHT + scroll[1];  // Position below the screen
                break;
            case 2:  // Left border
                element[0] = scroll[0] - get_width(txt);  // Position left of the screen
                element[1] = rand_range(0, SCRN_HEIGHT - 1) + scroll[1]; 
                break;
            case 3:  // Right border
                element[0] = SCRN_WIDTH + scroll[0];  // Position right of the screen
                element[1] = rand_range(0, SCRN_HEIGHT - 1) + scroll[1]; 
                break;
        }
    }
}

void	render_env()
{
	char str[2];
	str[0] = GRN_GRASS;
	str[1] = '\0';
	for (int index = 0; index < GRASS_AMNT; index++)
	{
		str[0] = index < GRASS_AMNT / 3 ? GRN_GRASS : index > GRASS_AMNT - GRASS_AMNT/3 ? ORNG_GRASS : RED_GRASSS;
		set_env_element(grass[index], str);
	}
}

void	render_clouds()
{
	float scroll_speed = 1.5;
	for (int index = 0; index < CLOUDS_MAX - 1; index++)
	{
        //if (clouds[index][0] - scroll[0] < -get_width(cloud_1) - scroll[0])  clouds[index][0] = SCRN_WIDTH  - scroll[0];  // Reposition on the right side
        //if (clouds[index][1] < -get_height(cloud_1)) clouds[index][1] = SCRN_HEIGHT;  // Reposition at the bottom
		int x = clouds[index][0] - (scroll[0] * scroll_speed);
		int y = clouds[index][1] - (scroll[1] * scroll_speed);
		if (is_in_canv(x, y, cloud_2, screen)) print_string(cloud_2, screen, x, y);
		else
		{
			clouds[index][0] = SCRN_WIDTH + (scroll[0] * scroll_speed) + rand_range(0, 3);
			clouds[index][1] = rand_range(0, SCRN_HEIGHT - 10) + scroll[1] * scroll_speed;
		}
		clouds[index][0] -= 1;
	}
}

void	render_terrain()
{
	for (int i = 0; i < TERRAIN_AMNT; i++)
	{
		TERRAIN t = terrains[i];
		if (!is_in_canv(t.pos[0] - scroll[0], t.pos[1] - scroll[1], t.frame, screen)) continue;
		print_string(t.frame, screen, t.pos[0] - scroll[0], t.pos[1] - scroll[1]);
	}
}

void	render_houses()
{
	screen_houses[0].type = HOUSE_TYPES_COUNT;
	int len = 0;
	for (int i = 0; i < HOUSE_AMNT; i++)
	{
		if (!is_in_canv(houses[i].position[0] - scroll[0], houses[i].position[1] - scroll[1], houses[i].frame, screen)) continue;
		print_string(houses[i].frame, screen, houses[i].position[0] - scroll[0], houses[i].position[1] - scroll[1]);
		screen_houses[len++] = houses[i];
	}
	screen_houses[len].type = HOUSE_TYPES_COUNT;
}

void	render_house_interior(int i)
{
	
	if (!is_in_canv(screen_houses[i].position[0] - scroll[0], screen_houses[i].position[1] - scroll[1], screen_houses[i].interior, screen)) return;
	print_string(screen_houses[i].interior, screen, screen_houses[i].position[0] - scroll[0], screen_houses[i].position[1] - scroll[1]);
}

int render_game()
{
	if (INV_FRAME > 0 && INV_FRAME < 10)
	{
		scroll[0] += rand_range(10, 20) * rand() % 2 == 0? -1 : 1;
		scroll[1] += rand_range(5, 10) * rand() % 2 == 0? -1 : 1;
	}
	if (PLAYER.hurt && PLAYER.hp > 0) render_player();
	else
	{
		if (PLAYER_HOUSE == -1)
		{
			render_env();
			render_terrain();
			render_mobs(MOBS, MOBS_AMOUNT);
			render_mobs(SPIDERS, SPIDER_AMOUNT);
			render_mobs(SPIDERS, BOSS_AMNT);
			render_player();
			for (int index = 0; index < TREES_MAX - 1; index++)
			{
				char *tr = strdup(tree1);
				int i = -1;
				while (tr[++i])
					if (tr[i] == ' ' && i == index % 5) tr[i] = LEAF_IC;
				set_env_element(trees[index], tr);
				free(tr);
			}
			render_houses();
			render_clouds();
		}
		else {
			render_player();
			render_house_interior(PLAYER_HOUSE);
			}
	}
	if (PLAYER.hp <= 0) 
	{

		INV_FRAME = 0;
		int rect_width = 60;
		int rect_height = 15;
		char rect_scrn[MAX_CONTENT];
		get_rect(rect_scrn, rect_width, rect_height, '#', 1);
		char text[MAX_CONTENT] = "You is dead. 	Press [r] to retry	PRESS [q] to quit\0";
		int start_index =  (rect_width) * rect_height / 2 - 23;
		int i = 0;
		while (text[i] && rect_scrn[start_index])
			rect_scrn[start_index++] = text[i++];
		print_string(rect_scrn, screen, SCRN_WIDTH/2 - rect_width/2, SCRN_HEIGHT / 2 - rect_height/2);
		if (input == 'r')
		{
			PLAYER.hp = 5;
			PLAYER.position[0] -= 200; PLAYER.position[1] -= 200;
		}
	}
	render_screen();
	return (1);
}