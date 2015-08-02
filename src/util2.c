/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 21:32:30 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 21:33:37 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <glfw/glfw3.h>
#include <SOIL.h>

static GLuint	get_text_texture(void)
{
	static GLuint	texture;

	if (texture != 0)
		return (texture);
	glGenTextures(1, &texture);
	texture = SOIL_load_OGL_texture("resources/text.jpg", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture == 0)
		die("Could not load the text texture.");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return (texture);
}

float			draw_char(char c, t_vector position, float height)
{
	float		width;
	t_vector	offset;
	GLuint		texture;

	texture = get_text_texture();
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	width = height * GFX_LETTER_RATIO;
	c -= 32;
	offset.x = c % 10;
	offset.y = c / 10;
	offset.x /= 10;
	offset.y /= 10;
	offset.y = 1.0 - offset.y - 0.1;
	glBegin(GL_QUADS);
	glTexCoord2d(offset.x, offset.y);
	glVertex2f(position.x, position.y);
	glTexCoord2d(offset.x + 0.1, offset.y);
	glVertex2f(position.x + width, position.y);
	glTexCoord2d(offset.x + 0.1, offset.y + 0.1);
	glVertex2f(position.x + width, position.y + height);
	glTexCoord2d(offset.x, offset.y + 0.1);
	glVertex2f(position.x, position.y + height), glEnd();
	glDisable(GL_TEXTURE_2D);
	return (width);
}
