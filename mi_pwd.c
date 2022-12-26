#include "minishell.h"

int mi_pwd(void)
{
    char    *buff;

    buff = getcwd(buff, 0);
    printf("%s\n",buff);
    free(buff);
    return (0);
}