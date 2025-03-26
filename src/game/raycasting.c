/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:02:24 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/26 17:29:24 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_raycast_steps(t_player *player, t_loop *loop)
{
	if (loop->rayDirX < 0)
	{
		loop->stepX = -1;
		loop->sideDistX = ((player->x / BLOCK) - loop->mapX) * loop->deltaDistX;
	}
	else
	{
		loop->stepX = 1;
		loop->sideDistX = ((loop->mapX + 1.0) - (player->x / BLOCK)) * loop->deltaDistX;
	}
	if (loop->rayDirY < 0)
	{
		loop->stepY = -1;
		loop->sideDistY = ((player->y / BLOCK) - loop->mapY) * loop->deltaDistY;
	}
	else
	{
		loop->stepY = 1;
		loop->sideDistY = ((loop->mapY + 1.0) - (player->y / BLOCK)) * loop->deltaDistY;
	}
}

void	get_raycast_hits(t_cub *cubed, t_loop *loop)
{
	loop->hit = 0;
	while (loop->hit == 0)
	{
		if (loop->sideDistX < loop->sideDistY)
		{
			loop->sideDistX += loop->deltaDistX;
			loop->mapX += loop->stepX;
			loop->side = 0;
		}
		else
		{
			loop->sideDistY += loop->deltaDistY;
			loop->mapY += loop->stepY;
			loop->side = 1;

		}
		if (loop->mapY < 0 || loop->mapX < 0
			|| loop->mapY >= HEIGHT / BLOCK || loop->mapX >= WIDTH / BLOCK)
    		break ;
		if (cubed->map[loop->mapY][loop->mapX] == '1')
			loop->hit = 1;
	}
}

void draw_ceiling_and_floor(t_cub *cub, t_loop *loop, int x)
{
    int y;
    double distToFloor, distToCeiling;
    double floorX, floorY, ceilingX, ceilingY;
    int textureX, textureY, floorColor, ceilingColor;

    // Dibuja el techo
    y = 0;
    while (y < loop->drawStart)
    {
        distToCeiling = HEIGHT / (2.0 * y - HEIGHT);
        ceilingX = cub->player->x + distToCeiling * loop->rayDirX;
        ceilingY = cub->player->y + distToCeiling * loop->rayDirY;

        textureX = (int)(ceilingX * cub->textures[3]->width) % cub->textures[3]->width;
        textureY = (int)(ceilingY * cub->textures[3]->height) % cub->textures[3]->height;

        ceilingColor = cub->textures[3]->data[textureY * cub->textures[3]->width + textureX];
        put_pixel(x, y, ceilingColor, cub);
        y++;
    }

    // Dibuja el suelo
    y = loop->drawEnd;
    while (y < HEIGHT)
    {
        distToFloor = HEIGHT / (2.0 * y - HEIGHT);
        floorX = cub->player->x + distToFloor * loop->rayDirX;
        floorY = cub->player->y + distToFloor * loop->rayDirY;

        textureX = (int)(floorX * cub->textures[2]->width) % cub->textures[2]->width;
        textureY = (int)(floorY * cub->textures[2]->height) % cub->textures[2]->height;

        floorColor = cub->textures[2]->data[textureY * cub->textures[2]->width + textureX];
        put_pixel(x, y, floorColor, cub);
        y++;
    }
}

void	draw_wall_with_texture(t_cub *cub, t_loop *loop, int x)
{
    int		color;
    int		texture_x;
    int		texture_y;
    double wallX;

    // Calcular la posición de la pared en la textura
    if (loop->side == 0) // Pared Norte o Sur
        wallX = cub->player->y / BLOCK + loop->perpWallDist * loop->rayDirY;
    else // Pared Este o Oeste
        wallX = cub->player->x / BLOCK + loop->perpWallDist * loop->rayDirX;
    wallX -= floor(wallX);

    // Coordenadas de la textura
    texture_x = (int)(wallX * (double)cub->textures[loop->side]->width);
	if(loop->side == 0 && loop->rayDirX > 0) loop->texX = 512 - loop->texX - 1;
    if(loop->side == 1 && loop->rayDirY < 0) loop->texX = 512 - loop->texX - 1;

	double step = 1.0 * 512 / loop->lineHeight;
	double texPos = (loop->drawStart - HEIGHT / 2 +  loop->lineHeight / 2) * step;

	for(int y = loop->drawStart; y<loop->drawEnd; y++)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (cub->textures[0]->height  - 1);
		texPos += step;
		int color = cub->textures[0]->data[cub->textures[0]->height * texY + texture_x];
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if(loop->side == 1) color = (color >> 1) & 8355711;
		if (y >= 0 && y < HEIGHT)
			put_pixel(x, y, color, cub);
	}
/* 	for(int y = loop->drawEnd; y < HEIGHT; y++)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (cub->textures[3]->height  - 1);
		texPos += step;
		int color = cub->textures[3]->data[cub->textures[3]->height * texY + texture_x];
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if(loop->side == 1) color = (color >> 1) & 8355711;
		if (y >= 0 && y < HEIGHT)
			put_pixel(x, y, color, cub);
	} */
	
	(void)texture_y;
	(void)color;
}

void	raycasting(t_cub *cubed, t_player *player, t_loop *loop)
{
	int	x;
	x = -1;
	init_loop(loop);
	while (++x < WIDTH)
	{
		loop->ray_angle = player->angle - (PI / 6) + (x * loop->fov);
		loop->rayDirX = cos(loop->ray_angle);
		loop->rayDirY = sin(loop->ray_angle);
		loop->deltaDistX = fabs(1 / loop->rayDirX);
		loop->deltaDistY = fabs(1 / loop->rayDirY);
		loop->mapX = player->mx;
		loop->mapY = player->my;
		get_raycast_steps(player, cubed->loop);
		get_raycast_hits(cubed, loop);
		if (loop->side == 0)
			loop->perpWallDist = (loop->sideDistX - loop->deltaDistX);
		else
			loop->perpWallDist = (loop->sideDistY - loop->deltaDistY);
		loop->lineHeight = (int)(HEIGHT / loop->perpWallDist);
		loop->drawStart = -loop->lineHeight / 2 + HEIGHT / 2;
		if (loop->drawStart < 0)
			loop->drawStart = 0;
		loop->drawEnd = loop->lineHeight / 2 + HEIGHT / 2;
		if (loop->drawEnd >= HEIGHT)
			loop->drawEnd = HEIGHT - 1;
 		draw_wall_with_texture(cubed, loop, x);
		//draw_ceiling_and_floor(cubed, loop, x);
		//draw_3dmap(cubed, loop->drawStart,  loop->drawEnd, x,  loop->side);
	}
}

