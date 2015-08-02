/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 00:06:36 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 22:27:53 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <unistd.h>
#include <libft.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>

t_arka	g_arka;

void		push_list(const char *name)
{
	t_lmap	*new;
	t_lmap	*tmp;

	new = malloc(sizeof(t_lmap));
	new->next = NULL;
	new->path = ft_strjoin("levels/", name);
	if (g_arka.map_list == NULL)
		g_arka.map_list = new;
	else
	{
		tmp = g_arka.map_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_lmap		*create_list(void)
{
	t_lmap	*newl;

	newl = malloc(sizeof(t_lmap));
	newl->path = NULL;
	newl->next = NULL;
	return (newl);
}

static void	list_map(void)
{
	DIR			*dirp;
	t_dirent	*dirent;

	g_arka.map_count = 0;
	dirp = opendir("levels/");
	if (!dirp)
		return ;
	while ((dirent = readdir(dirp)))
	{
		if (dirent->d_type == DT_REG)
		{
			push_list(dirent->d_name);
			g_arka.map_count++;
		}
	}
	closedir(dirp);
}

void		free_list(void)
{
	t_lmap	*tmp;

	while (g_arka.map_list && g_arka.map_list->next)
	{
		free(g_arka.map_list->path);
		tmp = g_arka.map_list;
		g_arka.map_list = g_arka.map_list->next;
		free(tmp);
	}
	free(g_arka.map_list);
}

int			main(void)
{
	srand(time(NULL));
	g_arka.gfx.window = NULL;
	init_arka();
	list_map();
	gfx_launch();
	gfx_destroy();
	free_list();
	return (0);
}
