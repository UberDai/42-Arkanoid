/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 21:28:59 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 21:31:51 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <glfw/glfw3.h>

extern t_arka	g_arka;

static void	set_ball_colors(float inner_color[], float outer_color[])
{
	inner_color[0] = 0.8f;
	inner_color[1] = 0.8f;
	inner_color[2] = 0.8f;
	inner_color[3] = 1.0f;
	outer_color[0] = 0.4f;
	outer_color[1] = 0.4f;
	outer_color[2] = 0.4f;
	outer_color[3] = 1.0f;
}

void		draw_ball(t_ball *ball)
{
	t_vector	reflection;
	float		inner_color[4];
	float		outer_color[4];

	set_ball_colors(inner_color, outer_color);
	if (ball->balls_of_steel)
	{
		inner_color[0] = 1.0f;
		inner_color[1] = 0.6f;
		inner_color[2] = 0.6f;
		outer_color[0] = 1.0f;
		outer_color[1] = 0.1f;
		outer_color[2] = 0.1f;
	}
	draw_disk_gradient(&(ball->position), GFX_BALL_RADIUS, inner_color,
		outer_color);
	reflection.x = ball->position.x + GFX_BALL_RADIUS / 10;
	reflection.y = ball->position.y + GFX_BALL_RADIUS / 3;
	inner_color[3] = 0.4f;
	outer_color[0] = 1.0f;
	outer_color[1] = 1.0f;
	outer_color[2] = 1.0f;
	outer_color[3] = 0.7f;
	draw_disk_gradient(&reflection, GFX_BALL_RADIUS / 2, outer_color,
		inner_color);
}
