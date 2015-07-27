#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include "env.h"

static const char *token = ":";

void
build_env_list(Elist **list, const char *env)
{
	char	*envstr;
	char	*tok;
	char	*lasts;

	if ((envstr = getenv(env)) == NULL)
		return;
	envstr = strdup(envstr);
	tok = strtok_r(envstr, token, &lasts);
	while (tok) {
		Elist	*lp;
		if ((lp = (Elist *)malloc(sizeof (Elist))) == NULL) {
			(void) printf("build_list: malloc failed\n");
			exit(1);
		}
		lp->l_libname = strdup(tok);
		lp->l_next = *list;
		*list = lp;
		tok = strtok_r(NULL, token, &lasts);
	}
	free(envstr);
}


Elist *
check_list(Elist *list, const char *str)
{
	const char	*basestr;

	if (list == NULL)
		return (NULL);

	/*
	 * Is this a basename or a relative path name
	 */
	if ((basestr = strrchr(str, '/')) != NULL)
		basestr++;
	else
		basestr = str;


	for (; list; list = list->l_next) {
		if (strchr(list->l_libname, '/') == NULL) {
			if (strcmp(basestr, list->l_libname) == 0)
				return (list);
		} else {
			if (strcmp(str, list->l_libname) == 0)
				return (list);
		}
	}
	return (NULL);
}

char *
checkenv(const char *env)
{
	char	*envstr;
	if ((envstr = getenv(env)) == NULL)
		return (NULL);
	while (*envstr == ' ')
		envstr++;
	if (*envstr == '\0')
		return (NULL);
	return (envstr);
}
