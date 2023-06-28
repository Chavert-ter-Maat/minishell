/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 17:47:15 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/06/22 16:27:09 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* Outputs the character ’c’ to the given file descriptor.					  */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(const char c, int fd)
{
	write (fd, &c, 1);
}
