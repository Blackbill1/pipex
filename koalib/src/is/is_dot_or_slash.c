/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dot_or_slash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:27:59 by tle-dref          #+#    #+#             */
/*   Updated: 2024/11/05 09:29:19 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_dot_or_slash(char s)
{
	if(s == '.' || s == '/')
		return(1);
	return (0);
}