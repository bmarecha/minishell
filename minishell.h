/*
** pipe : 0 == entree, 1 == sortie, 2 == sortie et entree, 3 == aucun des deux
** next et/ou prev sont mis a NULL dans les cas correspondants
*/


typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	
	char			*cmd;
	char			**argv;
	int				pipe;

//	t_redir			*i_red;
//	t_redir			*o_red;
}					t_cmd;
