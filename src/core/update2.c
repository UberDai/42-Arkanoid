/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 21:38:08 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 22:02:40 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <stdlib.h>
#include <stdio.h>

extern t_arka	g_arka;

static void	lost(t_ball *ball)
{
	t_ball	*tmp;

	if (g_arka.balls == ball)
		g_arka.balls = ball->next;
	else if (g_arka.balls)
	{
		tmp = g_arka.balls;
		while (tmp && tmp->next != ball)
			tmp = tmp->next;
		tmp->next = ball->next;
	}
	free(ball);
	if (g_arka.balls)
		return ;
	g_arka.players[0]->life -= 1;
	if (g_arka.players[0]->life < 0)
	{
		g_arka.players[0]->life = 3;
		g_arka.players[0]->score = 0;
		action_escape();
	}
	recreate();
}

static void	bounce_bar(float bar_min, float bar_max, t_ball *ball)
{
	float size;

	size = ball->player->bar.base_width + ball->player->bar.bonus_width;
	if (ball->position.y <= -0.9f &&
		ball->position.y >= -0.95f && ball->speed != 0)
	{
		if (g_arka.players[0]->axe_effect)
		{
			ball->position.y = GFX_BAR_POSITION + GFX_BALL_RADIUS;
			ball->speed = 0;
		}
		if (ball->position.x >= bar_min &&
			ball->position.x <= bar_min + size / 2)
			ball->direction.x += angle(ball->position.x,
				bar_max - size / 2);
		if (ball->position.x <= bar_max &&
			ball->position.x >= bar_max - size / 2)
			ball->direction.x += angle(ball->position.x,
				bar_min + size / 2);
		bounce(0, ball);
	}
}

static void	check_block_while(t_block *block, t_ball *ball)
{
	float			bw;
	float			bh;
	t_vector		p;
	static float	r = 0.03f;

	bw = 2.0f / g_arka.map->width;
	bh = bw / 2.5;
	p.x = block->position.x * bw - 1.0f;
	p.y = -block->position.y * bh + 0.9f;
	if (block->life > 0)
	{
		if ((ball->position.x + r >= p.x && ball->position.x - r <= p.x + bw) &&
			(ball->position.y + r >= p.y && ball->position.y - r <= p.y + bh))
		{
			if (block->type != 3)
			{
				ball->player->score += 10;
				block->life -= 1;
				if (block->life == 0 && block->bonus)
					bonus_apply(ball, block->bonus);
			}
			if (block->type == 3 || ball->balls_of_steel == 0)
				bounce(0, ball);
		}
	}
}

static void	check_block(t_ball *ball)
{
	int	y;
	int	x;

	y = g_arka.map->height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < (int)g_arka.map->width)
		{
			check_block_while(g_arka.map->blocks[y][x], ball);
			x++;
		}
		y--;
	}
}

void		balls_update(t_ball *ball, float size)
{
	float min;
	float max;
	float b_min;
	float b_max;

	min = -1.0f + 0.03f;
	max = 1.0f - 0.03f;
	b_min = ball->player->bar.position;
	b_max = ball->player->bar.position + size;
	ball->position.x += ball->direction.x * ball->speed;
	ball->position.y += ball->direction.y * ball->speed;
	check_block(ball);
	if (ball->position.x <= min)
		bounce(1, ball);
	if (ball->position.x >= max)
		bounce(1, ball);
	if (ball->position.x + 0.03f >= b_min && ball->position.x - 0.03f <= b_max)
		bounce_bar(b_min, b_max, ball);
	if (ball->position.y <= min)
		lost(ball);
	if (ball->position.y >= max)
	{
		ball->direction.y *= -1;
		ball->position.y += ball->direction.y * ball->speed;
	}
}
