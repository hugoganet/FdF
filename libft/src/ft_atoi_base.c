/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:01:14 by hganet            #+#    #+#             */
/*   Updated: 2025/04/15 19:09:13 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Converts a string representing a number in a given base to an integer.
 *
 * Supports bases from 2 to 16. Handles optional "0x"/"0X" prefix for hex.
 * Stops at first invalid character. Returns 0 if input is invalid.
 *
 * @param str The string to convert (e.g., "0xFF", "1A", "1010").
 * @param base The numeric base (2 to 16).
 * @return The converted integer, or 0 on error.
 */
int	ft_atoi_base(const char *str, int base)
{
	int		result;
	int		value;
	char	c;

	if (!str || base < 2 || base > 16)
		return (0);
	result = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		str += 2;
	while (*str)
	{
		c = *str;
		if (c >= '0' && c <= '9')
			value = c - '0';
		else if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
			value = (c | 32) - 'a' + 10;
		else
			break ;
		if (value >= base)
			break ;
		result = result * base + value;
		str++;
	}
	return (result);
}
