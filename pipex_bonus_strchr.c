
#include "pipex_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	char	l;

	l = (char)c;
	while (*s)
	{
		if (*s == l)
			return ((char *)s);
		s++;
	}
	if (*s == l)
		return ((char *)s);
	return (0);
}

void	f_error(void)
{
	perror("Error");
	exit(0);
}
