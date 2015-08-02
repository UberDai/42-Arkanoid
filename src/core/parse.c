/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 03:56:20 by fothon            #+#    #+#             */
/*   Updated: 2015/05/03 20:30:16 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <libft.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static t_block	*fill_block(int x, int y, const char *line)
{
	t_block		*tmp;
	char		**split_line;

	split_line = ft_strsplit(line, ':');
	tmp = (t_block *)malloc(sizeof(t_block));
	tmp->position.x = x;
	tmp->position.y = y;
	tmp->life = ft_atoi(split_line[0]);
	tmp->type = ft_atoi(split_line[1]);
	tmp->bonus = ft_atoi(split_line[2]);
	free2d(split_line);
	return (tmp);
}

static void		parse_line(t_map *map, const char *line, int y)
{
	char	**splits;
	int		x;

	splits = ft_strsplit(line, ' ');
	if (!map->width)
		map->width = ft_splits_count(splits);
	else if (map->width != ft_splits_count(splits))
	{
		ft_putendl("Longueur ligne incorrecte");
		free2d(splits);
		exit(1);
	}
	map->blocks[y] = malloc(sizeof(t_block *) * map->width);
	x = 0;
	while (splits[x])
	{
		map->blocks[y][x] = fill_block(x, y, splits[x]);
		x++;
	}
	free2d(splits);
}

int				my_open(char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) <= 0)
		exit(EXIT_FAILURE);
	return (fd);
}

t_map			*parse_map(char *path)
{
	int		fd;
	char	*line;
	t_map	*map;
	int		y;

	fd = my_open(path);
	map = malloc(sizeof(t_map));
	map->height = 0;
	map->width = 0;
	while (get_next_line(fd, &line) > 0)
	{
		map->height++;
		free(line);
	}
	close(fd), map->blocks = malloc(sizeof(char **) * map->height);
	fd = my_open(path);
	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		parse_line(map, line, y);
		free(line);
		y++;
	}
	close(fd);
	return (map);
}
