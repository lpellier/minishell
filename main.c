#include "libft/libft.h"
#include <sys/wait.h>
#define PATH_MAX 4096
#define TRUE 1
#define FALSE 0
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int     count_directories(char *cwd)
{
    int     count;

    count = 0;
    while (*cwd)
    {
        if (*cwd == '/')
            count++;
        cwd++;
    }
    return (count - 1);
}

int     len_wspace(char *line)
{
    int count;

    count = 0;
    while (*line)
    {
        if (*line != ' ')
            count++;
        line++;
    }
    return (count);
}

char     *nospace_after(char *line)
{
    char    *nospace;
    int     i;

    i = 0;
    if (!(nospace = malloc(sizeof(char) * len_wspace(line) + 1)))
        return (NULL);
    while (*line)
    {
        if (*line == ' ')
            while (*line == ' ')
                line++;
        nospace[i] = *line;
        line++;
        i++;
    }
    nospace[i] = '\0';
    return (nospace);
}

char    *read_line()
{
    char *line;
    char cwd[PATH_MAX];
    char **dir;
    int     nbrdir;

    line = NULL;
    if (getcwd(cwd, sizeof(cwd)))
    {
        dir = ft_split(cwd, '/');
        nbrdir = count_directories(cwd);
        ft_printf(ANSI_COLOR_BLUE "~ ");
        ft_printf("%s%s" ANSI_COLOR_RESET, dir[nbrdir], " > ");
        get_next_line(0, &line);
    }
    return (line);
}

char    *after_command(char *cmd, int len)
{
    char *after_command;
    int i;
    int j;


    if (!(after_command = malloc(sizeof(char) * (ft_strlen(cmd) - len + 2))))
            return NULL;
    if (!ft_strncmp(cmd, "cd", 2))
    {
        after_command[0] = '/';
        j = 1;
    }
    else
        j = 0;
    i = len;
    while (cmd[i])
    {
        after_command[j] = cmd[i];
        j++;
        i++;
    }
    after_command[j] = '\0';
    return (after_command);
}

void    shell_loop()
{
    int crashed;
    char *cmd;
    char *line_read;
    char *extra;
    char cwd[PATH_MAX];
    char    *str;

    crashed = FALSE;
    ft_printf(ANSI_COLOR_RED     "Welcome to Minishell!"     ANSI_COLOR_RESET "\n");
    while (crashed == FALSE)
    {
        line_read = read_line();
        cmd = nospace_after(line_read);
        if (!ft_strncmp(cmd, "exit", 4))
            crashed = TRUE;
        if (!ft_strncmp(cmd, "pwd", 3))
        {
            getcwd(cwd, sizeof(cwd));
            ft_printf("%s\n", cwd);
        }
        if (!ft_strncmp(cmd, "cd", 2))
        {   
            getcwd(cwd, sizeof(cwd));
            extra = after_command(cmd, 2);
            str = ft_strjoin(cwd, extra);
            chdir(str);
            free(extra);
        }
        if (!ft_strncmp(cmd, "echo-n", 6))
        {
            extra = ft_strdup(after_command(cmd, 6));
            ft_printf("%s", extra);
            free(extra);
        }
        else if (!ft_strncmp(cmd, "echo", 4))
        {
            extra = ft_strdup(after_command(cmd, 4));
            ft_printf("%s\n", extra);
            free(extra);
        }
    }
}

int main()
{
    system("clear");
    shell_loop();
}