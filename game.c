/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yura <yura@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:15:23 by yura              #+#    #+#             */
/*   Updated: 2020/11/23 18:40:43 by yura             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(
		game->mlx,
		WIDTH_PXS,
		HEIGHT_PXS,
		"snake game"
	);
}

void	snake_apple_init(t_game *game)
{
	game->snake = init_snake();
	game->apple = random_place();
	game->game_over = 0;
}

void	put_init_game(t_game *game)
{
	int i;
	int j;

	place_draw(game->apple, game->mlx, game->win, COLOR_APPLE);
	i = 0;
	while (game->snake->history[i])
	{
		place_draw(game->snake->history[i], game->mlx, game->win, COLOR_SNAKE);
		i++;
	}
	i = 0;
	while (i < WIDTH_PXS)
	{
		j = 0;
		while (j < HEIGHT_PXS)
		{
			if (i < FRAME_MAGIN || WIDTH_PXS - FRAME_MAGIN < i
				|| j < FRAME_MAGIN || HEIGHT_PXS - FRAME_MAGIN < j)
				mlx_pixel_put(game->mlx, game->win, i, j, COLOR_WALL);
			j++;
		}
		i++;
	}

}

int game_to_game_over(t_game *game)
{
	printf("GAME OVER\n");
	mlx_string_put(game->mlx, game->win, 10, 10, 0x00ffffff, "game over");
	game->game_over = 1;
	return (0);
}

int	exit_unexpectedly()
{
	printf("Some thing error happen.\n");
	exit(1);
	return (0);
}

int	main_loop(t_game *game)
{
	t_place *next;
	t_place *last;

	if (game->game_over)
		return (0);
	next = get_next_place(game->snake);
	last = last_history(game->snake->history);
	if (snake_is_overlapped(game->snake, next))
		return game_to_game_over(game);
	if (is_same_place(next, game->apple))
	{
		if (snake_grow(game->snake) == NULL)
			return exit_unexpectedly();
		place_draw(game->apple, game->mlx, game->win, COLOR_SNAKE);
		free(game->apple);
		game->apple = random_place();
		place_draw(game->apple, game->mlx, game->win, COLOR_APPLE);
	}
	else if (next->x == -1 || next->y == -1 || next->x == MAX_X || next->y == MAX_Y)
		return game_to_game_over(game);
	else
	{
		place_draw(last, game->mlx, game->win, COLOR_NONE);
		if (snake_move(game->snake) == NULL)
			return exit_unexpectedly();
		place_draw(next, game->mlx, game->win, COLOR_SNAKE);
	}
	return (0);
}

int	handle_key(int key_code, t_game *game)
{
	if (key_code == KEY_CODE_ESC)
		exit(0);
	if (key_code == KEY_CODE_LEFT_ARROW && game->snake->direction != 'r')
		game->snake->direction = 'l';
	if (key_code == KEY_CODE_RIGHT_ARROW && game->snake->direction != 'l')
		game->snake->direction = 'r';
	if (key_code == KEY_CODE_DOWN_ARROW && game->snake->direction != 'u')
		game->snake->direction = 'd';
	if (key_code == KEY_CODE_UP_ARROW && game->snake->direction != 'd')
		game->snake->direction = 'u';
	return (0);
}
