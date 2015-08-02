/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 19:51:06 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 19:42:56 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"
#include <stdlib.h>

t_player	*player_create(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	player->score = 0;
	player->life = 3;
	player->axe_effect = 0;
	player->bar.base_width = 0.3f;
	player->bar.bonus_width = 0.0f;
	player->bar.speed = BAR_BASE_SPEED;
	player->bar.moving = BAR_STOP;
	player->bar.position = -(player->bar.base_width / 2);
	return (player);
}
