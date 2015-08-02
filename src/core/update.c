/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 03:57:18 by fothon            #+#    #+#             */
/*   Updated: 2015/05/03 21:44:59 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <stdlib.h>
#include <stdio.h>

extern t_arka	g_arka;

void		bounce(int dir, t_ball *ball)
{
	if (dir)
	{
		ball->direction.x *= -1;
		ball->position.x += ball->direction.x * ball->speed;
	}
	else
	{
		ball->direction.y *= -1;
		ball->position.y += ball->direction.y * ball->speed;
	}
}

float		angle(float pos, float impact)
{
	return ((pos - impact) * 8);
}

void		recreate(void)
{
	g_arka.players[0]->axe_effect = 0;
	g_arka.players[0]->bar.base_width = 0.3f;
	g_arka.players[0]->bar.bonus_width = 0.0f;
	g_arka.players[0]->bar.position = -(g_arka.players[0]->bar.base_width / 2);
	free_balls();
	g_arka.balls = ball_create();
}

static void	update_bar(t_bar *bar)
{
	float	max;
	t_ball	*ball;

	max = 1.0f - (bar->base_width + bar->bonus_width);
	bar->position += bar->speed * bar->moving;
	if (bar->position < -1.0f)
		bar->position = -1.0f;
	else if (bar->position > max)
		bar->position = max;
	ball = g_arka.balls;
	while (ball)
	{
		if (ball->speed == 0)
		{
			if (bar->position > -1.0f && bar->position < max)
				ball->position.x += bar->speed * bar->moving;
		}
		ball = ball->next;
	}
}

void		game_update(void)
{
	t_uint	i;
	float	size;
	t_ball	*ball;

	if (!g_arka.balls)
		return ;
	ball = g_arka.balls;
	size = ball->player->bar.base_width + ball->player->bar.bonus_width;
	if (g_arka.paused)
		return ;
	while (ball)
	{
		if (ball->speed != 0)
			balls_update(ball, size);
		ball = ball->next;
	}
	i = 0;
	while (i < g_arka.player_count)
	{
		update_bar(&(g_arka.players[i]->bar));
		i++;
	}
}
