#ifndef CUBE_H
# define CUBE_H

# include "../minilibx-linux/mlx.h" 
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>

# define ROTATE_LEFT	65361
# define ROTATE_RIGHT	65363
# define FORWARD_W_Z	119
# define BACK_S_S		115
# define RIGHT_D_D		100
# define LEFT_A_Q		97
# define BUFFER_SIZE    4096

typedef struct  s_data 
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    int         res_x;
    int         res_y;
    int         fd;
    char        **map;
}               t_data;

typedef struct  s_vars 
{
    void        *mlx;
    void        *win;
    int         size_map;
    size_t         size_line_max;
}               t_vars;

typedef struct  s_textures_data
{
    char *north_t;
    char *south_t;
    char *west_t;
    char *east_t;
    char *sprite_t;
    int     floor_c;
    int     sky_c;
    int     r;
    int     g;
    int     b;
}               t_textures_data;

t_vars  g_vars;
t_data  g_data;
t_textures_data g_textures_data;

int             key_hook(int keycode);
unsigned int    get_r(unsigned int rgb);
unsigned int    get_g(unsigned int trgb);
unsigned int    get_b(unsigned int trgb);
void            win_init(void *mlx);
void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		        get_next_line(int fd, char **line);
size_t	        ft_strlen(const char *s);
char	        *ft_strjoin(char const *s1, char const *s2);
char	        *ft_strdup(const char *s1);
char	        *ft_strchr(const char *s, int c);
char	        *ft_substr(char const *s, unsigned int start, size_t len);
char	        *clean_line(char *save, char **line);
char	        *ft_save(char *buffer, char *save);
void            ft_error(int code);
char	        *base_convert(unsigned long long n, char *base_figures, int l);
unsigned int    hexa_color(int r, int g, int b);
void            ft_file_read(char *file_name);
void            ft_exit(void);
void            ft_free(void);
int             tamere_ft_exit();
void    parse_map(void);
void    count_line(void);
#endif