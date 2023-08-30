/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:23:26 by gcavanna          #+#    #+#             */
/*   Updated: 2023/08/30 11:31:16 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char  **ft_realloc(char **env, size_t size)
{
  char  **new;
  int   i;

  i = 0;
  new = (char **)malloc(size);
  while (env && env[i])
  {
    new[i] = ft_strdup(env[i]);
    i++;
  }
  new[i] = NULL;
  free(env);
  return (new);
}

int   ft_setenv(t_shell *shell, char *name, char *value)
{
  int i;
  char **env;

  i = 0;
  env = shell->env;
  while (env && env[i])
  {
    if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
    {
      free(env[i]);
      env[i] = ft_strjoin(ft_strjoin(name, "="), value);
      return (0);
    }
    i++;
  }
  env = ft_realloc(env, sizeof(char *) * (i + 2));
  env[i] = ft_strjoin(ft_strjoin(name, "="), value);
  env[i + 1] = NULL;
  return (0);
}