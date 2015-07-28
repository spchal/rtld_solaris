

#ifndef	_ENV_H
#define	_ENV_H

typedef	struct elist {
	char		*l_libname;
	struct elist	*l_next;
} Elist;

extern void	build_env_list(Elist **, const char *);
extern Elist	*check_list(Elist *, const char *);
extern char	*checkenv(const char *);

#endif	/* _ENV_H */

