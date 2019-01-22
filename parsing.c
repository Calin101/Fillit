/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/07 13:42:49 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/01/22 16:01:31 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fillit.h"

int		ft_first_read(int fd1)
{
	char	**tab;
	char	*line;
	int		count;
	char	**tmp;

	count = 0;
	tab = NULL;
	while (get_next_line(fd1, &line) > 0)
	{
		tmp = tab;
		tab = ft_addline(tab, line, count);
		ft_2dstrdel(tmp);
		ft_strdel(&line);
		count++;
	}
	if (count == 0)
		return (-1);
	count--;
	if (ft_strlen(tab[count]) <= 1 || count > 130)
	{
		ft_2dstrdel(tab);
		return (-1);
	}
	ft_2dstrdel(tab);
	return (0);
}

int		ft_get_link(char **tab, t_point index)
{
	int		count;
	int		line_max;

	count = 0;
	line_max = 0;
	while (tab[line_max])
		line_max++;
	if (line_max != 4 && line_max != 5)
		return (-1);
	if ((index.x != 3) && (tab[index.y][index.x + 1]) == '#')
		count++;
	if ((index.x > 0) && (tab[index.y][index.x - 1]) == '#')
		count++;
	if ((index.y != 3) && (tab[index.y + 1][index.x]) == '#')
		count++;
	if ((index.y > 0) && (tab[index.y - 1][index.x]) == '#')
		count++;
	return (count);
}

int		ft_fillit_error(char **tab)
{
	t_point		index;
	t_util		max;
	int			count;

	index = new_point(0, 0);
	count = 0;
	max.max_hash = 0;
	while (tab[index.y])
	{
		index.x = 0;
		while (tab[index.y][index.x])
		{
			if (tab[index.y][index.x] == '#')
			{
				max.max_hash++;
				count += ft_get_link(tab, index);
			}
			else if (!(tab[index.y][index.x] == '.'))
				return (-1);
			index.x++;
		}
		index.y++;
	}
	return (((count != 8 && count != 6) || max.max_hash != 4) ? -1 : 0);
}

int		in_tab(char *line, char ***tab, int i)
{
	if ((ft_strlen(line) != 4 && ft_strlen(line) != 0))
	{
		ft_strdel(&line);
		return (-1);
	}
	if ((i % 5 == 4 && ft_strlen(line) != 0))
	{
		ft_strdel(&line);
		return (-1);
	}
	(*tab)[i] = ft_strdup(line);
	ft_strdel(&line);
	return (0);
}

int		ft_fill_tab(char ***tab, int fd)
{
	char	*line;
	int		ret;
	int		ret1;
	int		i;

	line = NULL;
	ret = 0;
	ret1 = 0;
	i = -1;
	if ((*tab = (char **)malloc(sizeof(char *) * (5))) == NULL)
		return (-1);
	while (++i < 5)
		(*tab)[i] = NULL;
	i = -1;
	while (++i <= 4 && (ret = get_next_line(fd, &line)) > 0)
		if ((ret1 = in_tab(line, tab, i)) == -1)
			return (-1);
	(*tab)[i] = NULL;
	if (ret == 0 && i == 0)
		return (0);
	return (ft_fillit_error(*tab) == -1 ? -1 : 1);
}
