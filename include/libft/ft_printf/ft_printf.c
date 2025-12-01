/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:58:47 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/30 18:58:50 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

static int	ft_datatypes(va_list *args, const char c, int *cnt)
{
	if (c == 'c')
		*cnt += ft_charinput((char)(va_arg(*args, int)));
	else if (c == 's')
		*cnt += ft_strinput(va_arg(*args, char *));
	else if (c == 'p')
		*cnt += ft_ptrinput(va_arg(*args, long));
	else if (c == 'i' || c == 'd')
		*cnt += ft_intinput(va_arg(*args, int));
	else if (c == 'u')
		*cnt += ft_uinput(va_arg(*args, unsigned int));
	else if (c == 'x')
		*cnt += ft_nbrbase(va_arg(*args, unsigned int), "0123456789abcdef", 1);
	else if (c == 'X')
		*cnt += ft_nbrbase(va_arg(*args, unsigned int), "0123456789ABCDEF", 1);
	return (*cnt);
}

int	ft_printf(const char *s, ...)
{
	size_t	i;
	va_list	args;
	int		cnt;

	cnt = 0;
	if (!s)
		return (write(1, "", 0), -1);
	va_start(args, s);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%' && s[i + 1] != '\0')
		{
			if (s[i + 1] == '%')
				cnt += ft_charinput('%');
			else
				ft_datatypes(&args, s[i + 1], &cnt);
			i += 2;
		}
		else
			cnt += ft_charinput(s[i++]);
	}
	va_end(args);
	return (cnt);
}
