/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 03:57:48 by fothon            #+#    #+#             */
/*   Updated: 2015/05/03 20:35:41 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <stdlib.h>

extern t_arka	g_arka;

t_ball	*ball_create(void)
{
	t_ball	*ball;

	ball = malloc(sizeof(t_ball));
	ball->player = g_arka.players[0];
	ball->balls_of_steel = 0;
	ball->position.x = 0;
	ball->position.y = -0.87f;
	ball->direction.x = 0;
	ball->direction.y = 1;
	ball->speed = 0;
	ball->next = NULL;
	return (ball);
}

void	free_balls(void)
{
	t_ball	*ball;
	t_ball	*tmp;

	ball = g_arka.balls;
	while (ball)
	{
		tmp = ball;
		ball = ball->next;
		free(tmp);
	}
}
