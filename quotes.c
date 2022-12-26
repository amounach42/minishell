#include <stdlib.h>
#include <stdio.h>

int	ft_strlcpy(char *dst,char *src, int dstsize)
{
	int	r;
	int	i;

	i = 0;
	r = 0;
	while (src[i])
		i++;
	if (dstsize == 0)
		return (i);
	while (src[r] && r < dstsize - 1)
	{
		dst[r] = src[r];
		r++;
	}
	dst[r] = '\0';
	return (i);
}

int	is_dollar(char c)
{
	return (c == '$');
}

int	is_character(char c)
{
	return ((c >='A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}

int is_variable(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_dollar(line[i]) && is_character(line[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

char 	*get_variable(char *line)
{
	int     i;
	int     len;
	char	*ret;
	int		j;

	i = 0;
	j = 0;
	len = 0;
	while (line[i])
	{
		if (is_dollar(line[i]))
		{
			i++;
			j = i;
			while (line[i] && line[i] != ' ')
			{
				len++;
				i++;
			}
			ret = (char *)malloc(sizeof(char) * (len + 1));
			if (!ret)
				return (NULL);
			ft_strlcpy(ret, line + j, len + 1);
			if (!line[i])
				return (ret);
		}
		i++;
		//printf ("%s\n", line);;
	}
	return (ret);
}

int main(int ac, char **av)
{
    char *str = get_variable(av[1]);
	printf ("%s\n", str);
	//printf("lolll %s\n", av[1]);
	//printf ("%d\n", is_variable(av[1]));
}