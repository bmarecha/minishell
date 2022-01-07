
//type of redir : 1 == '<', 2 == '<<', 3 == '>>', 4 == '>'

typedef struct s_redir
{
	char	*file;
	int		type;
}

/*
** pipe : 0 == entree, 1 == sortie, 2 == sortie et entree, 3 == aucun des deux
** next et/ou prev sont mis a NULL dans les cas correspondants
*/


typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	
	char			*name;
	char			**argv;
	int				pipe;
	char			***env;

	t_redir			*i_red;
	t_redir			*o_red;
}					t_cmd;
