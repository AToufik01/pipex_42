/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:37:19 by ataoufik          #+#    #+#             */
/*   Updated: 2023/11/11 19:23:23 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ca;

	ca = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ca)
			return (&((char *) s)[i]);
		i++;
	}
	if (s[i] == ca)
		return (&((char *) s)[i]);
	return (0);
}
