#include "minishell.h"

char *ft_strjoin(char *s1, char *s2)
{
	int len;
	int l;
	int i;
	char *str;

	if (!s1)
		s1 = ft_strdup("");
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * len);
	l = ft_strlen(s1);
	if (!str)
		return (NULL);
	i = -1;
	while (i++ <= l)
		str[i] = s1[i];
	i = 0;
	while (l < len)
		str[l++] = s2[i++];
	str[len] = '\0';
	return (str);
}