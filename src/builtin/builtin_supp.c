/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_supp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Xifeng <xifeng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:37:48 by Xifeng            #+#    #+#             */
/*   Updated: 2025/03/05 17:07:16 by Xifeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../libs/libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

// @brief return the error when there is an option.
//
// @param ast: the pointer to ast tree.
// @param prop: the property of node.
// @return the status code.
int	check_option(t_ast *ast, t_cmd_prop *prop)
{
	if (prop->size < 2)
		return (EXIT_OK);
	if (ft_strlen(ast->tokens[prop->start + 1]) > 1 && ast->tokens[prop->start
			+ 1][0] == '-')
	{
		ft_putstr_fd(ast->tokens[prop->start], 2);
		ft_putstr_fd(": invalid option -- \'", 2);
		ft_putchar_fd(ast->tokens[prop->start + 1][1], 2);
		ft_putstr_fd("\'\n", 2);
		return (EXIT_INVALID_OPTION);
	}
	return (EXIT_OK);
}

// @brief help `echo` to print out the parameters.
//
// @param ast: the pointer to ast tree.
// @param prop: the property of ast node.
// @param no_line_break: the flag of the line break sign in the end.
void	echo_helper(t_ast *ast, t_cmd_prop *prop, bool no_line_break)
{
	int	i;

	i = 1;
	if (no_line_break)
		i = 2;
	while (i < prop->size)
	{
		if (ms_strcmp("$?", ast->tokens[prop->start + i]) == 0)
			printf("%d", ast->prev_status);
		else
			printf("%s", ast->tokens[prop->start + i]);
		if (i + 1 < prop->size)
			printf(" ");
		++i;
	}
	if (!no_line_break)
		printf("\n");
}

// @brief help the echo to handle the empty args.
//
// @param ast: the pointer to ast tree.
// @param prop: the property of the node.
void	empty_echo_helper(t_ast *ast, t_cmd_prop *prop)
{
	if (prop->size == 1)
	{
		printf("\n");
		close_builtin_proc(&ast, EXIT_OK, NULL);
	}
}
