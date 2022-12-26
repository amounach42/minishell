#include "minishell.h"

int	ft_pwd(void)
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (1);
	}
	else
		return (0);
}