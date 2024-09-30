/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:44:29 by yourLogin         #+#    #+#             */
/*   Updated: 2024/09/14 12:49:05 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	print_text(char *txt)
{
	int	i;

	i = 0;
	while (txt[i])
		write(2, &txt[i++], 1);
	write(1, "\n", 1);
}

int	main(int argc, char *argv[])
{
	FILE	*file;
	int		b_index;
	char	buffer[999999];

	if (argc <= 1 || argc > 2)
	{
		if (argc <= 1)
			print_text("File name missing.");
		else
			print_text("Too many arguments.");
		return (0);
	}
	file = fopen(argv[1], "r");
	if (!file)
	{
		print_text("Cannot read file.");
		return (0);
	}
	fread(buffer, 4, sizeof(buffer), file);
	b_index = 0;
	while (b_index < 999999 && buffer[b_index])
		write(1, &buffer[b_index++], 1);
	fclose(file);
	return (0);
}
