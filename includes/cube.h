#ifndef CUBE_H
# define CUBE_H

# include "../minilibx-linux/mlx.h" 
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# define ROTATE_LEFT	65361
# define ROTATE_RIGHT	65363
# define FORWARD	    119
# define BACK		    115
# define RIGHT		    100
# define LEFT		    97
# define BUFFER_SIZE    4096
# define _USE_MATH_DEFINES

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
    size_t      size_line_max;
    int         size_case;
}               t_vars;

typedef struct  s_textures_data
{
    char        *north_t;
    char        *south_t;
    char        *west_t;
    char        *east_t;
    char        *sprite_t;
    int         floor_c;
    int         sky_c;
    int         r;
    int         g;
    int         b;
}               t_textures_data;

typedef struct  s_check_flags
{
    int         start_pos;
    int         s_pos_i;
    int         s_pos_j;
    double      pos_i;
    double      pos_j;
    double      pos_a;
    int         fov_s;
    int         fov_e;
    char        s_direction;
    int         init_done;
}               t_check_flags;

typedef struct  s_ray_vars
{
    int         column;
    float       ray_angle;
}               t_ray_vars;

t_vars          g_vars;
t_data          g_data;
t_textures_data g_textures_data;
t_check_flags   g_check_flags;
t_ray_vars      g_ray_vars;

unsigned int    get_r(unsigned int rgb);
unsigned int    get_g(unsigned int trgb);
unsigned int    get_b(unsigned int trgb);
void            win_init();
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
int             ft_exit(void);
void            ft_free(void);
void            parse_map(void);
void            count_line(void);
void            check_map(void);
void            input_loop(void);
void            draw_player(double d_i, double d_j);
void            move_player(int direction, int axis);
void            rotate_player(int direction);
void            raycasting(void);
int             check_collision(int direction, int axis);
#endif