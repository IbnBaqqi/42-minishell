#include "../src/include/shell.h"
#include "unity.h"
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

// valgrind --leak-check=full --leak-check=full --show-leak-kinds=all --suppressions=/home/xifeng/Downloads/readline.supp ../minishell 
// --track-fds=yes

int	run_shell(char **envp);

// Setup function called before each test
void	setUp(void)
{
	// Initialize or allocate resources if needed (optional)
}

// Teardown function called after each test
void	tearDown(void)
{
	// Clean up resources if needed (optional)
}

void    test_SingleCmd(void)
{
    char *env[] = {"$AA=aa", NULL};
    run_shell(env);
}

void	test_Runshell(void)
{
	char *env[] = {"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", NULL};
	run_shell(env);
}

int	main(void)
{
	UNITY_BEGIN();
    //RUN_TEST(test_SingleCmd);
	RUN_TEST(test_Runshell);
	return (UNITY_END());
}