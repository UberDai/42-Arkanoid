/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 03:18:43 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 06:12:01 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <libft.h>
#include <unistd.h>
#include <glfw/glfw3.h>

extern t_arka	g_arka;

static void	gfx_error_callback(int error, const char *description)
{
	ft_putstr_fd("Error #", STDERR_FILENO);
	ft_putnbr_fd(error, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(description, STDERR_FILENO);
}

static void	gfx_key_callback(GLFWwindow *window, int key, int scancode,
	int action, int mods)
{
	(void)window;
	(void)scancode;
	(void)mods;
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		action_space();
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		action_move_y(MENU_UP);
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		action_move_y(MENU_DOWN);
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		action_move_x(g_arka.players[0], BAR_MOVE_RIGHT);
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		action_move_x(g_arka.players[0], BAR_MOVE_LEFT);
	else if ((key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) &&
		action == GLFW_RELEASE)
		action_move_x(g_arka.players[0], BAR_STOP);
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		action_escape();
}

void		gfx_get_callbacks(void)
{
	glfwSetErrorCallback(gfx_error_callback);
	glfwSetKeyCallback(g_arka.gfx.window, gfx_key_callback);
}
