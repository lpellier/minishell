/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manipulations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:26:46 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/24 11:44:42 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** replaces every $ with its env variable counterpart
** need to replace lib functions with libft ones
*/

// TO BE NORMED

#include <string.h>

// You must free the result if result is non-NULL.
char *str_replace(char *orig, char *rep, char *with)
{
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}


char *replace_dollars_env(char *line)
{
	char *test;
	char *dst;
	t_list *value;
	char *cmp;
	int i;

	test = ft_strdup(line);
	while ((test = strstr(test, "$")))
	{
		if (test[1] && is_whitespace(test[1]) && test[1] != '$')
		{
			i = 1;
			while (test[i] && is_whitespace(test[i]) && test[i] != '$')
				i++;
			if (!(dst = malloc(sizeof(char) * i)))
				return (NULL);
			strncpy(dst, test, i);
			dst[i] = '\0';
			value = (ft_list_find(info.env_head,
				create_env_struct(dst + 1, "NULL"), cmp_env));
			if (value && (cmp = ft_strdup(((t_env *)value->data)->value)))
			{
			    line = str_replace(line, dst, cmp);
			    free(cmp);
			 	cmp = NULL;
			}
		}
		test++;
	}
	return (line);
}
