/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Xifeng <xifeng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:50:00 by Xifeng            #+#    #+#             */
/*   Updated: 2025/03/04 15:40:02 by Xifeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/global.h"

int	g_here_doc_status = 0;
int	run_shell(char	**envp);

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	return (run_shell(envp));
}
