/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 19:33:27 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 20:53:54 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <libft.h>
#include <stdlib.h>

extern t_arka	g_arka;

void	init_arka(void)
{
	t_uint	i;

	g_arka.map_list = NULL;
	g_arka.players = malloc(sizeof(t_player) * PLAYER_MAX);
	i = 0;
	while (i < PLAYER_MAX)
	{
		g_arka.players[i] = NULL;
		i++;
	}
	g_arka.players[0] = player_create();
	g_arka.player_count = 1;
	g_arka.balls = NULL;
	g_arka.ball_count = 0;
	g_arka.in_menu = 1;
	g_arka.paused = 0;
}
