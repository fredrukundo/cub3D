/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frukundo <frukundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:11:23 by frukundo          #+#    #+#             */
/*   Updated: 2024/05/23 18:11:31 by frukundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//calculate step and initial sideDist
static void	calc_side_dist_step(t_datas *data)
{
	if (data->x_raydir < 0)
	{
		data->x_step = -1;
		data->side_x_dist = (data->pos_x - data->map_x) * data->delta_x_dist;
	}
	else
	{
		data->x_step = 1;
		data->side_x_dist = (data->map_x + 1.0 - data->pos_x)
			* data->delta_x_dist;
	}
	if (data->y_raydir < 0)
	{
		data->y_step = -1;
		data->side_y_dist = (data->pos_y - data->map_y) * data->delta_y_dist;
	}
	else
	{
		data->y_step = 1;
		data->side_y_dist = (data->map_y + 1.0 - data->pos_y)
			* data->delta_y_dist;
	}
}

void	init_ray_distance(t_datas *data)
{
	data->map_x = (int)data->pos_x;
	data->map_y = (int)data->pos_y;
	data->camera_x = 2 * (data->x / (double)(data->screen_w)) - 1;
	data->x_raydir = data->x_dir + data->x_plane \
		* data->camera_x;
	data->y_raydir = data->y_dir + data->y_plane \
		* data->camera_x;
	data->delta_x_dist = sqrt(1 + pow(data->y_raydir, 2) \
		/ pow(data->x_raydir, 2));
	data->delta_y_dist = sqrt(1 + pow(data->x_raydir, 2) \
		/ pow(data->y_raydir, 2));
	data->hit_wall = 0;
	calc_side_dist_step(data);
}

void	raycasting(t_datas *data)
{
	while (data->hit_wall == 0)
	{
		if (data->side_x_dist < data->side_y_dist)
		{
			data->side_x_dist += data->delta_x_dist;
			data->map_x += data->x_step;
			data->side = 0;
		}
		else
		{
			data->side_y_dist += data->delta_y_dist;
			data->map_y += data->y_step;
			data->side = 1;
		}
		if (data->map->map2d[data->map_x][data->map_y] == '1')
			data->hit_wall = 1;
	}
}

void	calc_wall_height(t_datas *data)
{
	if (data->side == 0)
		data->perp_dist_wall = fabs((data->map_x - data->pos_x + \
		(1 - data->x_step) / 2) / data->x_raydir);
	else
		data->perp_dist_wall = fabs((data->map_y - data->pos_y + \
		(1 - data->y_step) / 2) / data->y_raydir);
	if (!data->perp_dist_wall)
		data->perp_dist_wall = 1;
	data->line_height = (int)(data->screen_h \
		/ data->perp_dist_wall);
	data->draw_start = -data->line_height / 2 + data->screen_h / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + data->screen_h / 2;
	if (data->draw_end >= data->screen_h)
		data->draw_end = data->screen_h;
}
