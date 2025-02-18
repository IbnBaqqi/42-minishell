/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Xifeng <xifeng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:05:13 by Xifeng            #+#    #+#             */
/*   Updated: 2025/02/17 22:38:48 by Xifeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include <readline/history.h>
#include <readline/readline.h>
#include "main.h"

t_shell	shell;

// @brief start the executor.
//
// @param env: pointer to env.
// @param tokens: the NULL-terminated array of tokens.
// @param status: the status code of last command.
// @return code of the executor.
int execute(t_env *env, char **tokens, int status)
{
    int     i;
    t_ast   *ast;
    
    i = 0;
    while (tokens[i])
        ++i;
    ast = build_tree(tokens, i, env);
    ast->prev_status = status;
    ast->root->node_pre_handler(ast, ast->root);
    status = ast->root->node_handler(ast, ast->root);
    close_ast(&ast);
    return (status);
}

// @brief start the minishell.
//
// @param envp: the env.
int run_shell(char **envp)
{
    int     status;
    char    *line;
    //char    **tokens;
    t_env   *env;
    
    env = create_env(envp);
    status = EXIT_OK;
    while (true)
    {
        line = readline("minishell: ");
        if (!line)
            exit_with_err(NULL, EXIT_FAIL, "minishell: malloc");
        add_history(line);
        // parser(line, tokens); @Abdul
        free(line);
        //status = execute(env, parser(line, tokens), status); 
    }
    close_env(&env);
    return (status);
}

t_shell	shell;

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	return (run_shell(envp));
}
