/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrebs-l <lkrebs-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:30:59 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/04/04 23:45:18 by lkrebs-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tokenizer(t_ms *ms)
{
	size_t	i;
	int		c;

	i = 0;
	while (i < ft_strlen(ms->lexer.line))
	{
		if (ms->lexer.line[i] == SINGLE_QUOTE)
			i = special_case(ms, SINGLE_QUOTE, i);
		else if (ms->lexer.line[i] == DOUBLE_QUOTE)
			i = special_case(ms, DOUBLE_QUOTE, i); 
		else if (ms->lexer.line[i] == FT_SPACE)
		{
			i++;
			continue ;
		}
		else
		{
			c = i;
			while(ms->lexer.line[i] != FT_SPACE && ms->lexer.line[i])
				i++;
			ms->lexer.tokens[ms->lexer.i_token] = ft_substr(ms->lexer.line, c, i - c);
			ms->lexer.i_token++;
		}
		printf("%s\n", ms->lexer.tokens[ms->lexer.i_token - 1]);
		i++;
	}
}


/* V2.0 tokenizer
 	if (strichar(ms->lexer.line, 0, SINGLE_QUOTE) == -1
		&& strichar(ms->lexer.line, 0, DOUBLE_QUOTE) == -1)
		common_case(ms);
	else
		special_case(ms);

*/

/* V1.0 tokenizer
void	tokenizer(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->lexer.line[i])
	{
		if (minishell->lexer.line[i] == '<' || minishell->lexer.line[i] == '>')
			handle_redirect(minishell);
		else if (minishell->lexer.line[i] == '$')
			handle_vars(minishell);
		else if (minishell->lexer.line[i] == '<'
			&& minishell->lexer.line[i + 1] == '<')
			handle_delimiter(minishell);
		else if (minishell->lexer.line[i] == '>'
			&& minishell->lexer.line[i + 1] == '>')
			handle_append(minishell);
		else if (minishell->lexer.line[i] == '\''
			|| minishell->lexer.line[i] == '"')
			handle_quotes(minishell);
		else if (ft_isalpha(minishell->lexer.line[i]))
			handle_cmds(minishell);
		i++;
	}
}
*/

/* [ COMANDO ] echo "e<e"     <   README.md
 * 	| depois de um comando, sempre vem uma option se começar com
 * 	| caracter alfabético, - ou aspas.
 * 	|
 * [ REDIRECT ] <infile  OU   > outfile
 * 	| depois de um caracter de redirect, sempre vem o nome do arquivo
 * 	|
 * [ DELIMITER ] << LIMITER
 * 	| depois de um caracter de delimitação sempre vem a palavra delimitadora
 * 	|
 * [ APPEND ] >>
 * 	|
 * [ ASPAS ] "l"s    OU   'l's
 * 	| depois de aspas quase sempre vem algo para ser tratado como string
 * 	|
 * [ $ ] $ARGS
 * 	|
 * [ SPACE ]           ls -la
 * 	| pode receber qualquer coisa depois dele
 *
 *
 *
 * <   README.md echo               "e<e"
 * REDIRECT_IN CMD OPTION
 * <README.md echo "e<e"
*/