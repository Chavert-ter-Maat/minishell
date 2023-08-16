/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:50:29 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/08/16 15:27:41 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_substr() creates a new string from s.									  */
/* The substring begins at index ’start’ and is of maximum size ’len’.		  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*sub_string;
	const unsigned int	string_length = ft_strlen(s);
	size_t				index;

	index = 0;
	if (start > string_length || len == 0)
		return (ft_strdup(""));
	if (start + len >= string_length)
		len = string_length - start;
	sub_string = ft_calloc (len + 1, sizeof(char));
	if (!sub_string)
		return (NULL);
	while (index < len && s[start + index])
	{
		sub_string[index] = s[start + index];
		index++;
	}
	sub_string[index] = '\0';
	return (sub_string);
}
