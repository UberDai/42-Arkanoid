/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 02:43:15 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 21:33:07 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <glfw/glfw3.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>

void			free2d(char **t)
{
	char	**tmp;

	if (!t)
		return ;
	tmp = t;
	while (*tmp)
		free(*tmp++);
	free(t);
}

int				die(const char *message)
{
	ft_putendl(message);
	gfx_destroy();
	exit(EXIT_FAILURE);
	return (0);
}

float			draw_string(const char *str, t_vector position, float height)
{
	float	base_position;

	base_position = position.x;
	while (*str)
	{
		position.x += draw_char(*str, position, height);
		str++;
	}
	return (position.x - base_position);
}

void			draw_disk_gradient(const t_vector *position, float radius,
	float inner_color[], float outer_color[])
{
	float	tmp;
	t_uint	i;
	float	color[4];

	glGetFloatv(GL_CURRENT_COLOR, color);
	glBegin(GL_TRIANGLE_FAN);
	glColor4f(inner_color[0], inner_color[1], inner_color[2], inner_color[3]);
	glVertex2f(position->x, position->y);
	glColor4f(outer_color[0], outer_color[1], outer_color[2], outer_color[3]);
	i = 0;
	while (i <= GFX_BALL_SEGMENTS)
	{
		tmp = 2 * FT_M_PI * (float)i / (float)GFX_BALL_SEGMENTS;
		glVertex2f(position->x + ft_sin(tmp) * radius,
			position->y + ft_cos(tmp) * radius);
		i++;
	}
	glEnd();
	glColor4f(color[0], color[1], color[2], color[3]);
}
