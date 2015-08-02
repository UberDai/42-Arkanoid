/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 19:42:39 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 21:08:40 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>
#include <limits.h>

extern t_arka	g_arka;

void	action_move_x(t_player *player, int direction)
{
	if (!g_arka.in_menu)
		player->bar.moving = direction;
}

void	action_move_y(int direction)
{
	t_uint	entry_count;

	if (g_arka.in_menu)
	{
		if (g_arka.menu.select_level)
			entry_count = g_arka.map_count;
		else
			entry_count = 2;
		if (entry_count == 0)
			return ;
		g_arka.menu.selection += direction;
		if (g_arka.menu.selection == UINT_MAX)
			g_arka.menu.selection = entry_count - 1;
		else
			g_arka.menu.selection %= entry_count;
	}
}

void	action_space(void)
{
	t_ball	*ball;

	if (g_arka.in_menu)
		menu_valid();
	else
	{
		ball = g_arka.balls;
		while (ball)
		{
			if (ball->speed == 0)
				ball->speed = 0.03f;
			ball = ball->next;
		}
	}
}

void	action_escape(void)
{
	if (g_arka.in_menu)
	{
		if (g_arka.menu.select_level)
			g_arka.menu.select_level = 0;
		else if (g_arka.paused)
			resume_game();
		else
			quit();
	}
	else
		pause_game();
	g_arka.menu.selection = 0;
}
