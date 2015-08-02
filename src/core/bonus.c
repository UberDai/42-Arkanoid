/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 18:39:28 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 22:30:07 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <libft.h>
#include <stdlib.h>

extern t_arka	g_arka;

static void	bonus_viagra(void)
{
	if (g_arka.players[0]->bar.bonus_width == 0)
	{
		g_arka.players[0]->bar.bonus_width = 0.3f;
		g_arka.players[0]->bar.position -= 0.15f;
	}
}

static void	bonus_balls_of_steel(t_ball *ball)
{
	ball->balls_of_steel = 1;
}

static void	bonus_mario(void)
{
	g_arka.players[0]->life++;
}

static void	bonus_gangbang(void)
{
	t_ball	*ball;
	t_uint	i;
	int		random;

	ball = g_arka.balls;
	while (ball->next)
		ball = ball->next;
	i = 0;
	while (i < GANGBANG_BALL_COUNT)
	{
		ball->next = ball_create();
		ball->next->speed = ball->speed;
		ball->next->position.x = ball->position.x;
		ball->next->position.y = ball->position.y;
		random = rand();
		ball->next->direction.x = (random % 20) / 10.0f;
		ball->next->direction.y = 1;
		ball = ball->next;
		i++;
	}
}

void		bonus_apply(t_ball *ball, t_bonus bonus)
{
	if (bonus == B_VIAGRA)
		bonus_viagra();
	else if (bonus == B_MARIO)
		bonus_mario();
	else if (bonus == B_AXE_EFFECT)
		bonus_axe_effect();
	else if (bonus == B_BALLS_OF_STEEL)
		bonus_balls_of_steel(ball);
	else if (bonus == B_GANGBANG)
		bonus_gangbang();
}
