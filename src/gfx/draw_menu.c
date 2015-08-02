/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 03:33:13 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 21:16:29 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <glfw/glfw3.h>
#include <stdlib.h>
#include <libft.h>

extern t_arka	g_arka;

static void	draw_selection(float y, float width)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glLineWidth(2);
	glVertex2f(-1.0f, y);
	glVertex2f(-1.0f + width, y);
	glEnd();
}

static void	draw_level_selection(void)
{
	t_lmap		*map;
	t_uint		i;
	t_vector	position;
	float		width;
	char		*name;

	position.x = -1.0f;
	position.y = 0.6f;
	width = draw_string("Levels", position, 0.3f);
	position.x = -1.0f;
	position.y = 0.3f;
	i = 0;
	map = g_arka.map_list;
	while (map)
	{
		name = ft_strjoin(ft_strchr(map->path, '/') + 1, " !");
		width = draw_string(name, position, 0.08f);
		free(name);
		if (g_arka.menu.selection == i)
			draw_selection(position.y - 0.02f, width);
		position.y -= 0.12f;
		map = map->next;
		i++;
	}
}

void		draw_menu(void)
{
	t_vector	position;
	float		width;

	if (g_arka.menu.select_level)
	{
		draw_level_selection();
		return ;
	}
	position.x = -1.0f;
	position.y = 0.6f;
	width = draw_string("Arkanono PD", position, 0.3f);
	position.x = -1.0f;
	position.y = -0.3f;
	width = draw_string("Selection du niveau", position, 0.1f);
	if (g_arka.menu.selection == 0)
		draw_selection(position.y - 0.02f, width);
	position.x = -1.0f;
	position.y = -0.5f;
	width = draw_string("Quitter", position, 0.1f);
	if (g_arka.menu.selection == 1)
		draw_selection(position.y - 0.02f, width);
}
