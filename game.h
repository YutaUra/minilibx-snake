/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yura <yura@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:09:44 by yura              #+#    #+#             */
/*   Updated: 2020/11/23 18:36:34 by yura             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minilibx/mlx.h"
#include "key_code.h"

typedef struct	s_place
{
	int	x;
	int	y;
}				t_place;

typedef struct	s_snake
{
	char direction; // one of u(p),d(own),l(eft),r(ight)
	t_place **history;
}				t_snake;

typedef struct	s_game
{
	t_snake *snake;
	t_place *apple;
	void	*mlx;
	void	*win;
	int game_over;
	int tick;
}				t_game;

#define INITIAL_SNAKE 4
#define DOT_SIZE 30
#define FRAME_MAGIN 10
#define DOT_MAGIN 0
#define MAX_X 30
#define MAX_Y 20
#define WIDTH_PXS FRAME_MAGIN * 2 + DOT_SIZE * MAX_X
#define HEIGHT_PXS FRAME_MAGIN * 2 + DOT_SIZE * MAX_Y
#define COLOR_NONE 0x00000000
#define COLOR_SNAKE 0x00ffffff
#define COLOR_APPLE 0x00ff0000
#define COLOR_WALL 0x00aaaaaa
/*
**  game.c
*/
void	window_init(t_game *game);
void	snake_apple_init(t_game *game);
int		main_loop(t_game *game);
void	put_init_game(t_game *game);
int		handle_key(int key_code, t_game *game);

/*
**  place.c
*/
t_place	**_move(t_place **history, char direction);
t_place	**_grow(t_place **history, char direction);
t_place **initial_history(t_place *head);
t_place *_get_next_place(t_place *place, char direction);
int is_same_place(t_place *place1, t_place *place2);
t_place *random_place();
void	place_draw(t_place *place, void *mlx, void *win,  int color);
t_place *last_history(t_place **history);

/*
**  snake.c
*/
t_snake *init_snake();
t_place *get_next_place(t_snake *snake);
t_snake	*snake_move(t_snake *snake);
t_snake	*snake_grow(t_snake *snake);
void print_snake(t_snake *snake);
int snake_is_overlapped(t_snake *snake, t_place *place);

/*
**  math.c
*/
int random_int(int min, int max);

#endif
