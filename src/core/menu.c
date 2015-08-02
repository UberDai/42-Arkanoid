/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 05:35:22 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 22:34:04 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <libft.h>

extern t_arka	g_arka;

void	select_level(void)
{
	t_uint	i;
	t_lmap	*map;
	int		x;

	x = 0;
	i = 0;
	if (g_arka.map_count == 0)
		return ;
	map = g_arka.map_list;
	while (i != g_arka.menu.selection)
	{
		i++;
		map = map->next;
	}
	g_arka.current_map = map;
	if (g_arka.map)
		x = 1;
	free_map(g_arka.map);
	g_arka.map = parse_map(map->path);
	recreate();
	g_arka.players[0]->life = 3;
	g_arka.players[0]->score = 0;
	resume_game();
}

void	menu_valid(void)
{
	if (g_arka.menu.select_level)
	{
		select_level();
	}
	else
	{
		if (g_arka.menu.selection == 0)
			g_arka.menu.select_level = 1;
		else if (g_arka.menu.selection == 1)
			quit();
	}
	g_arka.menu.selection = 0;
}

void	menu_init(void)
{
	g_arka.menu.selection = 0;
	g_arka.menu.select_level = 0;
}
