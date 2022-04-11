/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:46:00 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/05 16:27:39 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <float.h>
# include <sys/types.h>

# define ROTATE_LEFT	65361
# define ROTATE_RIGHT	65363
# define FORWARD	    119
# define BACK		    115
# define RIGHT		    100
# define LEFT		    97
# define BUFFER_SIZE    4096
# define _USE_MATH_DEFINES

typedef int	t_bool;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bbp;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}			t_image;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	int			size_map;
	size_t		size_line_max;
	int			size_case;
}				t_vars;

typedef struct s_textures_data
{
	double		wall_dist;
	double		wall_x;
	int			line_height;
	char		*textures[4];
	t_image		image[4];
	int			floor_c;
	int			sky_c;
	char		orientation;
	int			r;
	int			g;
	int			b;
}				t_textures_data;

typedef struct s_check_flags
{
	int			start_pos;
	int			s_pos_i;
	int			s_pos_j;
	double		pos_i;
	double		pos_j;
	double		pos_a;
	int			fov_s;
	int			fov_e;
	char		s_direction;
	int			init_done;
}				t_check_flags;

typedef struct s_ray_vars
{
	double	side_dist[2];
	double	delta_dist[2];
	double	wall_dist;
	int		map_pos[2];
	int		step[2];
}				t_ray_vars;

typedef struct s_data
{
	int				skip;
	int				error;
	char			*line;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				res_x;
	int				res_y;
	int				fd;
	char			cam_dir;
	double			dir[2];
	double			cam_plane[2];
	double			*depth_buffer;
	char			**map;
	t_vars			vars;
	t_textures_data	textures_data;
	t_check_flags	check_flags;
	t_ray_vars		ray_vars;
	//char			*file;
	int				player;
}				t_data;

unsigned int	get_r(unsigned int rgb);
unsigned int	get_g(unsigned int trgb);
unsigned int	get_b(unsigned int trgb);
void			win_init(t_data *data);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);
char			*ft_strchr(const char *s, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*clean_line(char *save, char **line);
char			*ft_save(char *buffer, char *save);
void			ft_error(t_data *data, int code);
char			*base_convert(unsigned long long n, char *base_figures, int l);
unsigned int	hexa_color(int r, int g, int b);
void			ft_file_read(t_data *data, char *file_name);
int				ft_free(t_data *data);
void			parse_map(t_data *data);
void			count_line(t_data *data, char *file_name);
void			check_map(t_data *data);
void			input_loop(t_data *data);
void			draw_player(t_data *data, double d_i, double d_j);
void			move_player(t_data *data, int direction, int axis);
void			rotate_player(t_data *data, int direction);
void			raycasting(t_data *data);
unsigned int	mlx_get_pixel(t_image text, int x, int y);
void			texture_init(t_data *data);
void			cam_init(t_data *data);
void			*ft_calloc(size_t nmemb, size_t size);
void			*ft_memset(void *dest, int c, size_t n);
int				win_refresh(t_data *data);
void			skip_lines(t_data *data);
#endif