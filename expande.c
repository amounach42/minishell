#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	is_dollar(int c)
{
	return (c == '$');
}

int	is_character(int c)
{
	return ((c >='a' && c <= 'z') ||
		(c >='A' && c <= 'Z') || c == '_');
}

char	*print_until_ws(char *line)
{
	int		i;
	int		x;
	char	*ret;

	i = 0;
	x = 0;
	while (line[i])
	{
		if(is_dollar(line[i]) && is_character(line[i + 1]))
		{
			while (line[i] != ' ')
			{
				x = write (1, line + i, 1);
				i++;
			}
			ret = (char*)malloc(sizeof(char) * i + 1);
		}
		i++;
	}
	return (ret);
}

int main ()
{
	char	s[] = "echo heeey  $_HOME $ENV ls   ls sls ls >> ";
	print_until_ws(s);
}
