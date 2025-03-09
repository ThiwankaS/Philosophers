/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:48:11 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/09 23:56:33 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str && str[count])
		count++;
	return (count);
}

int	ft_exit(t_table *table)
{
	if (!table)
		return (0);
	if (table->froks)
		free(table->froks);
	if (table->rules)
		free(table->rules);
	if (table->philos)
		free(table->philos);
	free(table);
	return (1);
}
