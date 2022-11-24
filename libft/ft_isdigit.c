/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:00:23 by apila-va          #+#    #+#             */
/*   Updated: 2021/10/01 02:29:00 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int val)
{
	if (val >= '0' && val <= '9')
		return (1);
	else if (val == '+' || val == '-')
		return (1);
	return (0);
}
