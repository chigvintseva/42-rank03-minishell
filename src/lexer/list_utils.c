#include "../../include/minishell.h"

t_token	*create_token(const char *value, t_token_type type)
{
	t_token	*token;
	char	*dup_value;

	if (!value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	dup_value = ft_strdup(value);
	if (!dup_value)
		return (free(token), NULL);
	token->type = type;
	token->value = dup_value;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

int	tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!lst || !new)
		return (-1);
	if (!*lst)
	{
		*lst = new;
		return (0);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (0);
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
