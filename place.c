/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yura <yura@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:23:15 by yura              #+#    #+#             */
/*   Updated: 2020/11/23 18:41:02 by yura             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void print_place(t_place *place)
{
	printf("Place(%d, %d)\n", place->x, place->y);
}

static int check_direction(char d)
{
	return (strchr("udlr", d) != NULL);
}

static int hitory_size(t_place **history)
{
	int i;

	i = 0;
	while (history[i])
		i++;
	return (i);
}

static void free_history(t_place **history)
{
	int i;

	i = hitory_size(history);
	while (i > 0)
	{
		free(history[i - 1]);
		i--;
	}
	free(history);
}

static t_place *copy_place(t_place *from)
{
	t_place *to;
	to = (t_place *)malloc(sizeof(t_place));
	if (to == NULL)
		return (NULL);
	to->x = from->x;
	to->y = from->y;
	return (to);
}

t_place *_get_next_place(t_place *place, char direction)
{
	t_place *next;

	if (!check_direction(direction))
		return (NULL);
	next = copy_place(place);
	if (next == NULL)
		return (NULL);
	if (direction == 'u')
		next->y--;
	if (direction == 'd')
		next->y++;
	if (direction == 'l')
		next->x--;
	if (direction == 'r')
		next->x++;
	return (next);
}

t_place	**_move(t_place **history, char direction)
{
	t_place *next;
	t_place **next_history;
	int i;

	next = _get_next_place(*history, direction);
	if (next == NULL)
		return (NULL);
	i = hitory_size(history);
	next_history = (t_place **)malloc(sizeof(t_place *) * (i + 1));
	if (next_history == NULL)
		return (NULL);
	next_history[i] = NULL;
	while (i > 1)
	{
		next_history[i - 1] = copy_place(history[i - 2]);
		i--;
	}
	next_history[0] = next;
	free_history(history);
	return (next_history);
}

t_place	**_grow(t_place **history, char direction)
{
	t_place *next;
	t_place **next_history;
	int i;

	next = _get_next_place(*history, direction);
	if (next == NULL)
		return (NULL);
	i = hitory_size(history);
	next_history = (t_place **)malloc(sizeof(t_place *) * (i + 2));
	if (next_history == NULL)
		return (NULL);
	next_history[i + 1] = NULL;
	while (i > 0)
	{
		next_history[i] = copy_place(history[i - 1]);
		i--;
	}
	next_history[0] = next;
	free_history(history);
	return (next_history);
}

t_place **initial_history(t_place *head)
{
	t_place **history;
	int i;

	history = (t_place **)malloc(sizeof(t_place) * (INITIAL_SNAKE + 1));
	if (history == NULL)
		return (NULL);
	i = 0;
	while (i < INITIAL_SNAKE)
	{
		history[i] = (t_place *)malloc(sizeof(t_place));
		if (history[i] == NULL)
		{
			history[i + 1] = NULL;
			free_history(history);
			return (NULL);
		}
		history[i]->x = head->x;
		history[i]->y = head->y + i;
		i++;
	}
	history[i] = NULL;
	return (history);
}

int is_same_place(t_place *place1, t_place *place2)
{
	return (place1->x == place2->x && place1->y == place2->y);
}

t_place *random_place()
{
	t_place *place;

	place = (t_place *)malloc(sizeof(t_place));
	if (place == NULL)
		return (NULL);
	place->x = random_int(0, MAX_X - 1);
	place->y = random_int(0, MAX_Y - 1);
	return (place);
}

void	place_draw(t_place *place, void *mlx, void *win,  int color)
{
	int x;
	int y;

	x = 0;
	while (x < DOT_SIZE)
	{
		y = 0;
		while (y < DOT_SIZE)
		{
			mlx_pixel_put(
				mlx,
				win,
				FRAME_MAGIN + place->x * (DOT_SIZE - DOT_MAGIN * 2) + x,
				FRAME_MAGIN + place->y * (DOT_SIZE - DOT_MAGIN * 2) + y,
				color
			);
			y++;
		}
		x++;
	}
}

t_place *last_history(t_place **history)
{
	int i;

	i = 0;
	while (history[i])
		i++;
	return (history[i - 1]);
}
