/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:18:06 by mrezki            #+#    #+#             */
/*   Updated: 2024/09/28 22:20:12 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	skip_spaces_plus(const char **str, t_errno *error)
{
	while (*(*str) == ' ' || (*(*str) >= 9 && *(*str) <= 13))
		(*str)++;
	if (*(*str) == '-')
	{
		*error = NEGATIVE_NUM;
		return (0);
	}
	if (!ft_isdigit(*(*str)) && *(*str) != '+')
	{
		*error = INVALID_CHAR;
		return (0);
	}
	if (*(*str) == '+')
		(*str)++;
	return (1);
}

int	check_errors(const char *str, t_errno *error, int res)
{
	while ((*str) == ' ' || ((*str) >= 9 && (*str) <= 13))
		str++;
	if (*str != '\0')
	{
		*error = INVALID_CHAR;
		return (-1);
	}
	if (res == 0)
	{
		*error = NEGATIVE_NUM;
		return (-1);
	}
	return (res);
}

int	str_to_int(const char *str, t_errno *error)
{
	long	res;

	res = 0;
	if (!skip_spaces_plus(&str, error))
		return (-1);
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		if (res > INT_MAX)
		{
			*error = BIG_NUM;
			return (-1);
		}
		str++;
	}
	return (check_errors(str, error, res));
}
