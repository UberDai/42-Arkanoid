/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 07:14:53 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 21:35:38 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <stdlib.h>

extern t_arka	g_arka;

void	pause_game(void)
{
	menu_init();
	g_arka.in_menu = 1;
	g_arka.paused = 1;
}

void	resume_game(void)
{
	g_arka.in_menu = 0;
	g_arka.paused = 0;
}

void	free_map(t_map *map)
{
	t_uint	y;
	t_uint	x;

	if (!map)
		return ;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			free(map->blocks[y][x]);
			x++;
		}
		free(map->blocks[y]);
		y++;
	}
	free(map->blocks);
	free(map);
}

void	game_ended(void)
{
	if (!g_arka.current_map || !g_arka.current_map->next)
	{
		g_arka.players[0]->score = 0;
		g_arka.players[0]->life = 3;
		g_arka.in_menu = 1;
		menu_init();
	}
	else
	{
		g_arka.current_map = g_arka.current_map->next;
		recreate();
		free_map(g_arka.map);
		g_arka.map = parse_map(g_arka.current_map->path);
	}
}

void	quit(void)
{
	gfx_destroy();
	free_list();
	exit(0);
}
