/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 21:25:06 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 21:31:29 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <glfw/glfw3.h>
#include <SOIL.h>
#include <libft.h>
#include <stdlib.h>

extern t_arka	g_arka;

static GLuint	get_bar_texture(void)
{
	static GLuint	texture;

	if (texture != 0)
		return (texture);
	glGenTextures(1, &texture);
	texture = SOIL_load_OGL_texture("resources/bar.png", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture == 0)
		die("Could not load the bar texture.");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return (texture);
}

void			draw_bar(t_bar *bar)
{
	GLuint		texture;

	texture = get_bar_texture();
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2d(0, 1);
	glVertex2f(bar->position, GFX_BAR_POSITION);
	glTexCoord2d(0, 0);
	glVertex2f(bar->position, GFX_BAR_POSITION - GFX_BAR_HEIGHT);
	glTexCoord2d(1, 0);
	glVertex2f(bar->position + bar->base_width + bar->bonus_width,
		GFX_BAR_POSITION - GFX_BAR_HEIGHT);
	glTexCoord2d(1, 1);
	glVertex2f(bar->position + bar->base_width + bar->bonus_width,
		GFX_BAR_POSITION);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

static GLuint	get_background_texture(void)
{
	static GLuint	texture;

	if (texture != 0)
		return (texture);
	glGenTextures(1, &texture);
	texture = SOIL_load_OGL_texture("resources/background.jpg", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture == 0)
		die("Could not load the bar texture.");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return (texture);
}

void			draw_background(void)
{
	GLuint		texture;

	texture = get_background_texture();
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2f(-1, -1);
	glTexCoord2d(1, 0);
	glVertex2f(1, -1);
	glTexCoord2d(1, 1);
	glVertex2f(1, 1);
	glTexCoord2d(0, 1);
	glVertex2f(-1, 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void			draw_gui(void)
{
	char		*str;
	t_vector	position;

	position.x = -1.6f;
	position.y = 0.8f;
	position.x += draw_string("Score : ", position, 0.1f);
	str = ft_itoa((int)g_arka.players[0]->score);
	draw_string(str, position, 0.1f);
	free(str);
	position.x = -1.6f;
	position.y = 0.7f;
	position.x += draw_string("Vies :  ", position, 0.1f);
	str = ft_itoa((int)g_arka.players[0]->life);
	draw_string(str, position, 0.1f);
	free(str);
}
