/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:42:25 by weiyang           #+#    #+#             */
/*   Updated: 2025/05/28 11:39:55 by weiyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	end_line(char *str)
{
	// verifier si la ligne contient '\n'
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strdup(char *s)
{
	// copy un string, et fini par '\0', si s est NULL, retourne NULL directement
	char	*ptr;
	char	*dst;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	ptr = malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	dst = ptr;
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (ptr);
}

int	ft_strlen(char *str)
{
	// calculer la taille d'un str
	int	size;
	
	size = 0;
	while (str[size])
		size++;
	return (size);
}

char	*extract_line(char *str)
{
	// pour extrait une ligne qui fini par \n d'un str 
	int		i;
	char	*extract;
	int		j;

	j = 0;
	i = 0;
	// si str est NULL ou vide, retourne NULL
	if (!str || str[0] == '\0')
		return (NULL);
	// avance lindex jusqu \n ou '\0'
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	// allocation de memoire ( +1 pour ajouter \0 a la fin)
	extract = (char *) malloc ((i + 1) * sizeof (char));
	if (!extract)
		return (NULL);
	// copier tous les elements de str dans la ligned extrait
	while (j < i)
	{
		extract[j] = str[j];
		j++;
	}
	// ajouter \0 a la fin de la ligne extrait
	extract[j] = '\0';
	return (extract);
}

char	*ft_strjoin(char *s1, char *s2)
{
	// pour joindre deux strs 
	char	*ptr;
	char	*dst;
	// is s1 ou s2 est NULL, le change en vide
	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	// allocation de memoire 
	ptr = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	dst = ptr;
	while (*s1)
	{
		*dst = *s1;
		dst++;
		s1++;
	}
	while (*s2)
	{
		*dst = *s2;
		dst++;
		s2++;
	}
	*dst = '\0';
	return (ptr);
}
