/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrow <marrow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 17:54:36 by marrow            #+#    #+#             */
/*   Updated: 2020/12/12 18:54:56 by marrow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_dota_f(va_list parameters, const char *restrict format,\
t_spec *specifier)
{
	size_t	i;
	size_t	printed;
	char	*str;

	str = (char*)format;
	printed = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '{')
			ft_setcolor(str, &i, specifier);
		if (str[i] != '%' && ++printed)
			ft_putchar_fd(str[i++], specifier->fd);
		else
		{
			initialization(specifier);
			ft_format_specifier(str, &i, specifier);
			ft_type(specifier, parameters);
			printed += specifier->len;
		}
	}
	free(specifier);
	return (printed);
}

int			ft_fprintf(const int fd, const char *restrict format, ...)
{
	va_list		parameters;
	int			printed;
	t_spec		*specifier;

	if (!(specifier = (t_spec*)ft_memalloc(sizeof(t_spec))))
		exit(-1);
	initialization(specifier);
	specifier->fd = fd;
	specifier->fprintf_flag = true;
	printed = 0;
	va_start(parameters, format);
	printed = ft_dota_f(parameters, format, specifier);
	va_end(parameters);
	return (printed);
}
