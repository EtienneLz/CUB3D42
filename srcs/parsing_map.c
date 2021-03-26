#include "../includes/cube.h"

void    count_line()
{
    int ret;
    char *line;
    int i;

    i = 0;
    g_vars.size_line_max = 0;
    while ((ret = get_next_line(g_data.fd, &line) != 0))
    {
        if (g_vars.size_line_max < ft_strlen(line))
            g_vars.size_line_max = ft_strlen(line);
        g_vars.size_map++;
        free (line);
    }
    close(g_data.fd);
    if (!(g_data.map = malloc(sizeof(char*) *  100)))
        ft_error(2);
    if ((g_data.fd = open("config.cub", O_RDONLY)) == -1)
        ft_error(1);
    printf("%d\n", g_vars.size_map);
    while (i <= 9)
    {
        get_next_line(g_data.fd, &line);
        i++;
        free (line);
    }
}

void    parse_map(void)
{
    int i;
    unsigned int j;
    int ret;
    char *line;

    i = 0;
    ret = 1;
    while (ret != 0)
    {
        ret = get_next_line(g_data.fd, &line);
        g_data.map[i] = NULL;
        j = 0;
        if (!(g_data.map[i] = malloc(sizeof(char) * g_vars.size_line_max + 1)))
            ft_error(1);
        while (line[j])
        {
            if (line[j] == ' ' || line[j] == '1')
                g_data.map[i][j] = '1';
            else if (line[j] == '2')
                g_data.map[i][j] = '2';
            else if (line[j] == '0')
                g_data.map[i][j] = '0';
            else if (line[j] == 'N' || line[j] == 'S' || line[j] == 'W' || line[j] == 'E')
                g_data.map[i][j] = line[j];
            else
                ft_error(1);
            j++;
        }
        while (j++ < g_vars.size_line_max)
            g_data.map[i][j] = '1';
        g_data.map[i][j] = '\0';
        free (line);
        i++;
    }
}

