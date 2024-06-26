/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frukundo <frukundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:15:40 by frukundo          #+#    #+#             */
/*   Updated: 2024/05/23 18:15:41 by frukundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	move_forword(t_datas *game)
{
	int	x;
	int	y;

	x = (int)(game->pos_x);
	y = (int)(game->pos_y + game->y_dir * game->movespeed);
	if (ft_strchr("0SENWd", game->map->map2d[x][y]))
		game->pos_y += game->y_dir * game->movespeed;
	x = (int)(game->pos_x + game->x_dir * game->movespeed);
	if (ft_strchr("0SENWd", game->map->map2d[x][(int)(game->pos_y)]))
		game->pos_x += game->x_dir * game->movespeed;
}

void	move_backward(t_datas *game)
{
	int	x;
	int	y;

	x = (int)(game->pos_x);
	y = (int)(game->pos_y - game->y_dir * game->movespeed);
	if (ft_strchr("0SENWd", game->map->map2d[x][y]))
		game->pos_y -= game->y_dir * game->movespeed;
	x = (int)(game->pos_x - game->x_dir * game->movespeed);
	if (ft_strchr("0SENWd", game->map->map2d[x][(int)(game->pos_y)]))
		game->pos_x -= game->x_dir * game->movespeed;
}

void	move_left(t_datas *game)
{
	int	x;
	int	y;

	x = (int)(game->pos_x - game->x_plane * game->movespeed);
	y = (int)(game->pos_y);
	if (ft_strchr("0SENWd", game->map->map2d[x][y]))
		game->pos_x -= game->x_plane * game->movespeed;
	y = (int)(game->pos_y - game->y_plane * game->movespeed);
	if (ft_strchr("0SENWd", game->map->map2d[(int)(game->pos_x)][y]))
		game->pos_y -= game->y_plane * game->movespeed;
}

void	move_right(t_datas *game)
{
	int	x;
	int	y;

	x = (int)(game->pos_x + game->x_plane * game->movespeed);
	y = (int)(game->pos_y);
	if (ft_strchr("0SENWd", game->map->map2d[x][y]))
		game->pos_x += game->x_plane * game->movespeed;
	y = (int)(game->pos_y + game->y_plane * game->movespeed);
	if (ft_strchr("0SENWd", game->map->map2d[(int)(game->pos_x)][y]))
		game->pos_y += game->y_plane * game->movespeed;
}

void	rotate(t_datas *game, double angle)
{
	double	old_dirx;
	double	old_planex;

	old_planex = game->x_plane;
	old_dirx = game->x_dir;
	game->x_dir = game->x_dir * cos(angle) - \
		game->y_dir * sin(angle);
	game->y_dir = old_dirx * sin(angle) + game->y_dir * cos(angle);
	game->x_plane = game->x_plane * cos(angle) - \
		game->y_plane * sin(angle);
	game->y_plane = old_planex * sin(angle) + game->y_plane * cos (angle);
}
