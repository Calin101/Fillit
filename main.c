/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/28 16:01:59 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/01/22 16:01:26 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fillit.h"

static void		ft_print_result(t_tetri *first, char **tab)
{
	t_tetri	*tmp;
	char	**map;
	int		size;
	int		k;

	tmp = first;
	k = 0;
	size = rccar(ft_list_len(first) * 4);
	if (!(map = create_map(size)))
		ft_2dstrdel(map);
	while (resolve(map, size, &first, 'A') == 0)
	{
		ft_2dstrdel(map);
		size++;
		map = create_map(size);
	}
	while (k < size)
	{
		ft_putendl(map[k]);
		k++;
	}
	ft_2dstrdel(map);
	ft_2dstrdel(tab);
	ft_listdel(&first);
}

static int		error(t_tetri **afirst, char **tab)
{
	ft_listdel(afirst);
	ft_2dstrdel(tab);
	return (write(1, "error\n", 6));
}

int				main(int argc, char **argv)
{
	int		fd;
	int		fd1;
	int		ret;
	char	**tab;
	t_tetri	*first;

	first = NULL;
	tab = NULL;
	if (argc == 2)
	{
		if (((fd = open(argv[1], O_RDONLY)) < 0) ||
		((fd1 = open(argv[1], O_RDONLY)) < 0) || ft_first_read(fd1) == -1)
			return (write(1, "error\n", 6));
		while ((ret = ft_fill_tab(&tab, fd)) > 0)
		{
			if (add_tetri(&tab, &first) == -1)
				return (error(&first, tab));
		}
		if (ret == -1)
			return (error(&first, tab));
		ft_print_result(first, tab);
	}
	else
		ft_putendl_fd("usage: ./fillit need one argument", 1);
	return (0);
}
