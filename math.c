/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yura <yura@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:34:33 by yura              #+#    #+#             */
/*   Updated: 2020/11/23 13:34:36 by yura             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int random_int(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}
