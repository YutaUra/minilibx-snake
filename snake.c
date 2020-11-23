/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yura <yura@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:14:25 by yura              #+#    #+#             */
/*   Updated: 2020/11/23 18:37:24 by yura             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_snake *init_snake()
{
	t_snake *snake;
	t_place center;

	snake = (t_snake *)malloc(sizeof(t_snake));
	if (snake == NULL)
		return (NULL);
	center.x = MAX_X / 2;
	center.y = MAX_Y / 2;
	snake->direction = 'u';
	snake->history = initial_history(&center);
	if (snake->history == NULL)
	{
		free(snake);
		return (NULL);
	}
	return (snake);
}

t_place *get_next_place(t_snake *snake)
{
	return (_get_next_place(snake->history[0], snake->direction));
}

t_snake	*snake_move(t_snake *snake)
{
	snake->history = _move(snake->history, snake->direction);
	if (snake->history == NULL)
		return (NULL);
	return (snake);
}

t_snake	*snake_grow(t_snake *snake)
{
	snake->history = _grow(snake->history, snake->direction);
	if (snake->history == NULL)
		return (NULL);
	return (snake);
}

void print_snake(t_snake *snake)
{
	int i;

	printf("Snake(");
	i = 0;
	while (snake->history[i])
	{
		printf("[%d, %d]", snake->history[i]->x, snake->history[i]->y);
		i++;
		if (i > 20)
			break;
	}
	printf(")\n");
}

int snake_is_overlapped(t_snake *snake, t_place *place)
{
	int i;

	i = 1;
	while (snake->history[i])
	{
		if (is_same_place(snake->history[i], place))
			return (1);
		i++;
	}
	return (0);
}
