#include "../includes/cube.h"

void    file_read(char *file_name)
{
    char *line;

    if (!(g_data.fd = open(file_name, O_RDONLY)))
        ft_error(1);
    if (get_next_line(g_data.fd, line) < 1);
        ft_error(1);
    get_resolution(line);
    free (line);
    if (get_next_line(g_data.fd, line) < 1);
        ft_error(1);
    g_textures_data.north_t = get_textures(line, 'N', 'O', 3);
    free (line);
    if (get_next_line(g_data.fd, line) < 1);
        ft_error(1);
    g_textures_data.south_t = get_textures(line, 'S', 'O', 3);
    free (line);
    if (get_next_line(g_data.fd, line) < 1);
        ft_error(1);
    g_textures_data.west_t = get_textures(line, 'W', 'E', 3);
    free (line);
    if (get_next_line(g_data.fd, line) < 1);
        ft_error(1);
    g_textures_data.east_t = get_textures(line, 'E', 'A', 3);
    free (line);
    file_read_2(line);
}

static  file_read_2(char *line)
{
    if (get_next_line(g_data.fd, line) < 1);
        ft_error(1);
    if (line[0] != '\0')
        ft_error(1);
    if (get_next_line(g_data.fd, line) < 1);
        ft_error(1);
    g_textures_data.sprite_t = get_textures(line, 'S', ' ', 2);
}

void    get_resolution(char *line)
{
    int i;

    i = 2;
    if (line[0] != 'R')
        return ;
    while (line[i] && (line[i] <= '9' && line[i] >= '0'))
    {
        g_data.res_x *= 10;
        g_data.res_x += line[i] - '0';
        i++;
    }
    i++;
    while (line[i] && (line[i] <= '9' && line[i] >= '0'))
    {
        g_data.res_y *= 10;
        g_data.res_y += line[i] - '0';
        i++;
    }
}

char    *get_textures(char *line, char c1, char c2, int s)
{
    if (line[0] != c1 && line[1] != c2)
        ft_error(1); 
    return(ft_substr(line, s, ft_strlen(line) - s));
}

static  int get_colors(char *line, char c)
{
    int tmp;
    int i;
    int j;
    int k;

    i = 2;
    j = 0;
    k = 0;
    tmp = 0;
    if (line[0] != c && line[1] != ' ')
        ft_error(1);
    while (k < 3)
    {
        while (line[i] >= '0' && line[i] <= '9')
        {
           tmp *= 10;
           tmp += line[i] - '0';
           i++;
           j++;
        }
        if (j > 3 || line[++i] != ',')
            ft_error(1);
        hexa_color(tmp);
        tmp = 0;
        j = 0;
        k++;
    }
}

static  hexa_color(int n)
{
    
}