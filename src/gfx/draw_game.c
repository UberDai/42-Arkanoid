/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 03:15:05 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 21:29:13 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <glfw/glfw3.h>
#include <libft.h>
#include <stdlib.h>
#include <SOIL.h>

extern t_arka	g_arka;

static void		draw_block_border(t_vector *pos, float block_width,
	float block_height)
{
	glLineWidth(GFX_BLOCK_BORDER);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(pos->x, pos->y);
	glVertex2f(pos->x, pos->y + block_height);
	glVertex2f(pos->x, pos->y + block_height);
	glVertex2f(pos->x + block_width, pos->y + block_height);
	glVertex2f(pos->x + block_width, pos->y + block_height);
	glVertex2f(pos->x + block_width, pos->y);
	glVertex2f(pos->x + block_width, pos->y);
	glVertex2f(pos->x, pos->y);
	glEnd();
}

static void		draw_block(t_block *block, int *draw)
{
	float		block_width;
	float		block_height;
	t_vector	pos;
	float		color[4];

	block_width = 2.0f / g_arka.map->width;
	block_height = block_width / 2.5;
	pos.x = block->position.x * block_width - 1.0f;
	pos.y = -block->position.y * block_height + 0.9f;
	if (block->type == 1)
		glColor3f(GFX_BRICK_1);
	else if (block->type == 2)
		glColor3f(GFX_BRICK_2);
	else
		glColor3f(GFX_BRICK_DEFAULT);
	glGetFloatv(GL_CURRENT_COLOR, color);
	glBegin(GL_QUADS);
	glVertex2f(pos.x, pos.y);
	glVertex2f(pos.x + block_width, pos.y);
	glColor3f(color[0] * 3, color[1] * 3, color[2] * 3);
	glVertex2f(pos.x + block_width, pos.y + block_height);
	glVertex2f(pos.x, pos.y + block_height), glEnd();
	draw_block_border(&pos, block_width, block_height);
	if (block->type != 3)
		*draw += 1;
}

static void		draw_blocks(t_map *map)
{
	t_uint	x;
	t_uint	y;
	int		draw;

	y = 0;
	draw = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->blocks[y][x]->life > 0 && map->blocks[y][x]->type != 0)
				draw_block(map->blocks[y][x], &draw);
			x++;
		}
		y++;
	}
	if (!draw)
		game_ended();
}

void			draw_game(void)
{
	t_ball	*ball;

	draw_background();
	draw_blocks(g_arka.map);
	draw_bar(&(g_arka.players[0]->bar));
	ball = g_arka.balls;
	while (ball)
	{
		draw_ball(ball);
		ball = ball->next;
	}
	draw_gui();
}
