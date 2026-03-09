#include "../include/minishell.h"

t_token	*create_token(const char *value, t_token_type type)
{
	t_token	*node;
	char	*dup_value;

	if (!value)
		return (NULL);
	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	dup_value = strdup(value); // include libft
	node->type = type;
	node->value = dup_value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!lst || !new)
		return ; // error?
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	free_tokens(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->value);
		free(tmp);
	}
}
