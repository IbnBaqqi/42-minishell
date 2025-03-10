/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_supp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Xifeng <xifeng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:05:24 by Xifeng            #+#    #+#             */
/*   Updated: 2025/02/22 11:43:03 by Xifeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_env.h"
#include "../libs/libft/libft.h"
#include <stdlib.h>

// @brief help to set the env item.
//
// @param i: the index of separator.
// @param item_str: the env item string.
// @param item: the env item to set.
static void	set_item_helper(int i, char *item_str, t_env_item *item)
{
	if (((item_str[i + 1] == '\'' && item_str[ft_strlen(item_str) - 1] == '\'')
			|| (item_str[i + 1] == '\"' && item_str[ft_strlen(item_str)
					- 1] == '\"')) && ((size_t)i != ft_strlen(item_str) - 2))
		ft_memcpy(item->value, item_str + i + 2, ft_strlen(item_str) - i - 3);
	else
		ft_memcpy(item->value, item_str + i + 1, ft_strlen(item_str) - i - 1);
}

// @brief to parse the key, value from given env item.
//
// To parse the key, value from item, then save the value to pair.
// Example:
// `pair` {"KEY", "VALUE"}, `item` {"KEY=value"};
// `pair` {"KEY", ""}, `item` {"KEY="};
//
// @param pair: the container for result.
// @param item: the env item to parse.
// @return false on error, otherwise returns true.
bool	set_item(t_env_item *item, char *item_str)
{
	int	i;

	i = 0;
	while (item_str[i])
	{
		if (item_str[i++] == '=')
			break ;
	}
	if ((size_t)i < ft_strlen(item_str) || item_str[i - 1] == '=')
		--i;
	item->key = ft_calloc(i + 1, sizeof(char));
	if (!item->key)
		return (false);
	ft_memcpy(item->key, item_str, i);
	if ((size_t)i == ft_strlen(item_str) && item_str[i - 1] != '=')
		return (true);
	item->value = ft_calloc(ft_strlen(item_str) - i, sizeof(char));
	if (!item->value)
	{
		free(item->key);
		return (false);
	}
	if ((size_t)i < ft_strlen(item_str) || item_str[i - 1] == '=')
		set_item_helper(i, item_str, item);
	return (true);
}

// @brief append an item to env.
//
// @param env: the pointer to env.
// @param item: the non-NULL string of item, like "KEY=value" or "KEY=".
// @return false on error, returns true otherwise.
bool	env_append(t_env *env, char *item)
{
	t_env_item	*items;

	if (env->size == env->capacity)
	{
		env->capacity *= 2;
		items = ft_calloc(env->capacity, sizeof(t_env_item));
		if (!items)
			return (false);
		ft_memcpy(items, env->items, env->size * sizeof(t_env_item));
		free(env->items);
		env->items = items;
	}
	++(env->size);
	return (set_item(&(env->items[env->size - 1]), item));
}

// @brief helper function to find a key from env.
//
// @param env: the pointer to env.
// @param key: the key to find.
// @return: the index of the found item. returns the size of env when not found.
int	find_key(t_env *env, char *key)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (ms_strcmp(env->items[i].key, key) == 0)
			break ;
		i++;
	}
	return (i);
}

// @brief returns serilized the env item
//
// @param item: the env item to be output.
// @return (key=value);
char	*output_env_item(t_env_item *item)
{
	int		key_len;
	int		value_len;
	char	*joined;
	char	*value;

	value = "";
	if (item->value)
		value = item->value;
	key_len = ft_strlen(item->key);
	value_len = ft_strlen(value);
	joined = ft_calloc((key_len + value_len + 2), sizeof(char));
	if (!joined)
		return (NULL);
	ft_memcpy(joined, item->key, key_len);
	joined[key_len] = '=';
	ft_memcpy(joined + key_len + 1, value, value_len);
	return (joined);
}
