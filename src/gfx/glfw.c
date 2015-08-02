/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 02:40:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 21:16:11 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <libft.h>
#include <unistd.h>
#include <glfw/glfw3.h>

extern t_arka	g_arka;

static void	gfx_update(void)
{
	float	ratio;

	glfwGetFramebufferSize(g_arka.gfx.window, &(g_arka.gfx
		.width), &(g_arka.gfx.height));
	glViewport(0, 0, g_arka.gfx.width, g_arka.gfx.height);
	ratio = g_arka.gfx.width / (float)g_arka.gfx.height;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	game_update();
	if (g_arka.in_menu)
		draw_menu();
	else
		draw_game();
	glfwSwapBuffers(g_arka.gfx.window);
	glfwPollEvents();
}

void		gfx_launch(void)
{
	if (!glfwInit())
		die("Could not init GLFW.");
	g_arka.gfx.window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
		"Arkanono", NULL, NULL);
	if (!g_arka.gfx.window)
		die("Could not create the GLFW window.");
	glfwMakeContextCurrent(g_arka.gfx.window);
	glfwSwapInterval(1);
	gfx_get_callbacks();
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (!glfwWindowShouldClose(g_arka.gfx.window))
		gfx_update();
}

void		gfx_destroy(void)
{
	if (g_arka.gfx.window)
		glfwDestroyWindow(g_arka.gfx.window);
	glfwTerminate();
}
