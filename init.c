#include "minishell.h"

// is used to reset all of the info after enter is pressed

void init_built_in()
{
    built_in[0] = ft_echo;
    built_in[1] = ft_echo_n;
    built_in[2] = ft_exit;
    built_in[3] = ft_pwd;
    built_in[4] = ft_export;
    built_in[5] = ft_unset;
    built_in[6] = ft_env;
    built_in[7] = ft_cd;
    built_in[8] = exec_binary;
}

int     init_env(t_info *info, char **envp)
{
    int i;
    char **key_value;

    i = 0;
    while (envp[i])
    {
        key_value = ft_split(envp[i], "=");
        ft_list_push_back(&info->env_head, create_env_struct(key_value[0], key_value[1]));
        free(key_value);
        i++;
    }
    return (SUCCESS);
}

// mallocs and creates cmd struct, returns pointer on struct
t_cmd   *create_cmd_struct()
{
    t_cmd *cmd;

    if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
        return NULL;
    cmd->bui = 9;
    cmd->cmd = NULL;
    cmd->input = NULL;
    cmd->option = NULL;
    cmd->path = NULL;
    return (cmd);
}

// same as above for env struct
t_env   *create_env_struct(char *key, char *value)
{
    t_env *env;

    if (!(env = (t_env *)malloc(sizeof(t_env))))
        return NULL;
    env->key = key;
    env->value = value;
    return (env);
}
