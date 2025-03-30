/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:18:20 by npederen          #+#    #+#             */
/*   Updated: 2024/11/26 14:28:22 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isfromset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *charset)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*str;

	if (!charset || charset[0] == '\0')
		return (ft_strdup(s1));
	i = 0;
	k = 0;
	j = ft_strlen(s1) - 1;
	if (j <= 0)
		return (ft_strdup(""));
	while (isfromset(s1[i], charset) == 1 && s1[i] != '\0')
		i++;
	while (isfromset(s1[j], charset) == 1 && j > 0)
		j--;
	if (i > j)
		return (ft_strdup(""));
	str = malloc((j - i + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < j + 1)
		str[k++] = s1[i++];
	str[k] = '\0';
	return (str);
}

/*
#include <stdio.h>
//printf("size : %lld\n", size);
int	main(void)
{
	printf("str : [%s]", ft_strtrim("", "aaa"));
	return (0);
}
*/