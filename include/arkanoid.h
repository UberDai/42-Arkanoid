/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arkanoid.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 00:10:06 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/03 22:36:40 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARKANOID_H
# define ARKANOID_H

# include <glfw/glfw3.h>

# define WINDOW_WIDTH			1240
# define WINDOW_HEIGHT			740
# define BAR_STOP				0
# define BAR_MOVE_LEFT			-1
# define BAR_MOVE_RIGHT			1
# define PLAYER_MAX				2
# define BAR_BASE_SPEED			0.05f
# define GANGBANG_BALL_COUNT	2
# define GFX_BLOCK_BORDER		2
# define GFX_BALL_SEGMENTS		360
# define GFX_BRICK_1			0.3f, 0.1f, 0.1f
# define GFX_BRICK_2			0.1f, 0.3f, 0.1f
# define GFX_BRICK_DEFAULT		0.8f, 0.8f, 0.8f
# define GFX_BACKGROUND_COLOR	0.1f, 0.1f, 0.3f
# define GFX_LETTER_RATIO		0.5f
# define GFX_BAR_POSITION		-0.9f
# define GFX_BAR_HEIGHT			0.08f
# define GFX_BALL_RADIUS		0.03f
# define MENU_UP				-1
# define MENU_DOWN				1

typedef struct dirent	t_dirent;
typedef unsigned int	t_uint;

typedef enum			e_bonus
{
	B_NULL,
	B_VIAGRA,
	B_AXE_EFFECT,
	B_GANGBANG,
	B_BALLS_OF_STEEL,
	B_MARIO
}						t_bonus;

typedef struct			s_vector
{
	float				x;
	float				y;
}						t_vector;

typedef struct			s_block
{
	t_vector			position;
	int					type;
	t_bonus				bonus;
	t_uint				life;
}						t_block;

typedef struct			s_bar
{
	float				base_width;
	float				bonus_width;
	float				position;
	float				speed;
	int					moving;
}						t_bar;

typedef struct			s_player
{
	t_uint				score;
	int					life;
	t_bar				bar;
	int					axe_effect;
}						t_player;

typedef struct			s_ball
{
	t_vector			position;
	t_vector			direction;
	double				speed;
	t_player			*player;
	int					balls_of_steel;
	struct s_ball		*next;
}						t_ball;

typedef struct			s_lmap
{
	char				*path;
	struct s_lmap		*next;
}						t_lmap;

typedef struct			s_map
{
	t_block				***blocks;
	t_uint				width;
	t_uint				height;
	struct s_map		*next;
}						t_map;

typedef struct			s_gfx
{
	int					width;
	int					height;
	GLFWwindow			*window;
}						t_gfx;

typedef struct			s_menu
{
	t_uint				selection;
	int					select_level;
}						t_menu;

typedef struct			s_arka
{
	t_player			**players;
	t_uint				player_count;
	t_gfx				gfx;
	t_map				*map;
	t_ball				*balls;
	t_uint				ball_count;
	t_uint				map_count;
	t_lmap				*map_list;
	t_lmap				*current_map;
	int					in_menu;
	t_menu				menu;
	int					paused;
}						t_arka;

void					gfx_launch(void);
void					gfx_destroy(void);
void					gfx_get_callbacks(void);
void					draw_game(void);
void					draw_menu(void);
int						die(const char *message);
void					draw_disk_gradient(const t_vector *position,
	float radius, float inner_color[], float outer_color[]);
float					draw_char(char c, t_vector position, float height);
float					draw_string(const char *str, t_vector position,
	float height);
t_map					*parse_map(char *path);
void					init_arka(void);
void					key_callback(GLFWwindow *window, int key, int scancode,
	int action, int mods);
void					action_move_x(t_player *player, int direction);
void					action_move_y(int direction);
void					action_escape(void);
void					action_space(void);
t_player				*player_create(void);
t_ball					*ball_create();
void					game_update();
t_lmap					*create_list();
void					recreate();
void					free_list();
void					free2d(char **t);
void					menu_move(int direction);
void					menu_valid(void);
void					menu_init(void);
void					quit(void);
void					pause_game(void);
void					resume_game(void);
void					bonus_apply(t_ball *ball, t_bonus bonus);
void					game_ended(void);
void					free_map(t_map *map);
void					free_balls(void);
void					draw_bar(t_bar *bar);
void					draw_background(void);
void					draw_gui(void);
void					draw_ball(t_ball *ball);
void					bonus_axe_effect(void);
void					balls_update(t_ball *ball, float size);
void					bounce(int dir, t_ball *ball);
float					angle(float pos, float impact);

#endif
