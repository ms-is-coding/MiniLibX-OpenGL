/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:48:48 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/13 15:55:35 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mlx.h"

#define WINDOW_WIDTH    1280
#define WINDOW_HEIGHT   720
#define MAX_PARTICLES   1000000
#define START_PARTICLES 100000

#define KEY_ESC     0xFF1B
#define KEY_UP      0xFF52
#define KEY_DOWN    0xFF54

typedef struct s_particle {
	float		x;
	float		y;
	float		vx;
	float		vy;
	uint32_t	color;
}	t_particle;

typedef struct s_profiler {
    uint64_t    frame_start;
    uint64_t    physics_time;
    uint64_t    render_time;
    uint64_t    last_report;
    uint32_t    frame_count;
    char        padding[4];
}   t_profiler;

typedef struct s_app {
    t_profiler  profiler;
	t_mlx		*mlx;
	t_window	*window;
	t_particle	*particles;
	int32_t     active_count;
    char        padding[4];
}	t_app;

static inline uint64_t get_time_ns(void)
{
    struct timespec ts;

    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1)
        return (0);
    return ((uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec);
}

void init_system(t_app *app)
{
    app->particles = malloc(sizeof(t_particle) * MAX_PARTICLES);
    if (!app->particles)
    {
        fprintf(stderr, "[Critical] Memory allocation failed for particle pool.\n");
        exit(EXIT_FAILURE);
    }
    printf("[System] Initializing pool of %d particles...\n", MAX_PARTICLES);
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        app->particles[i] = (t_particle){
            .x = (float)(rand() % WINDOW_WIDTH),
            .y = (float)(rand() % WINDOW_HEIGHT),
            .vx = ((float)(rand() % 200) / 50.0f) - 2.0f,
            .vy = ((float)(rand() % 200) / 50.0f) - 2.0f,
            .color = (0xFF << 24) |
                     (((i * 255 / MAX_PARTICLES) & 0xFF) << 16) |
                     (((255 - (i * 255 / MAX_PARTICLES)) & 0xFF) << 8) |
                     0xFF
        };
    }
    app->active_count = START_PARTICLES;
}

static inline void update_physics(const t_app *app, const int count)
{
    t_particle  *p;

    for (int i = 0; i < count; i++)
    {
        p = &app->particles[i];
        p->x += p->vx;
        p->y += p->vy;
        if (p->x <= 0 || p->x >= WINDOW_WIDTH)
            p->vx *= -1.0f;
        if (p->y <= 0 || p->y >= WINDOW_HEIGHT)
            p->vy *= -1.0f;
    }
}

int render_loop(void *param)
{
    t_app *app = param;
    uint64_t t0, t1, t2;

    t0 = get_time_ns();
    mlx_clear_window(app->mlx, app->window);
    update_physics(app, app->active_count);
    t1 = get_time_ns();
    const int count = app->active_count;
    for (int i = 0; i < count; i++)
    {
        const t_particle p = app->particles[i];
        if (p.x >= 0 && p.x < WINDOW_WIDTH && p.y >= 0 && p.y < WINDOW_HEIGHT)
            mlx_pixel_put(app->mlx, app->window, (int)p.x, (int)p.y, (int)p.color);
    }
    t2 = get_time_ns();
    app->profiler.frame_count++;
    app->profiler.physics_time += (t1 - t0);
    app->profiler.render_time += (t2 - t1);
    if (t2 - app->profiler.last_report >= 1000000000ULL)
    {
        printf("\r\033[2K[Bench] FPS: %3d | Particles: %7d | Phy: %.2fµs | Draw: %.2fµs | Bandwidth: %.2f MB/s",
            app->profiler.frame_count,
            app->active_count,
            (double)app->profiler.physics_time / app->profiler.frame_count / 1000.0,
            (double)app->profiler.render_time / app->profiler.frame_count / 1000.0,
            (double)(app->active_count * 4 * app->profiler.frame_count) / (1024.0 * 1024.0)
        );
        fflush(stdout);
        app->profiler.frame_count = 0;
        app->profiler.physics_time = 0;
        app->profiler.render_time = 0;
        app->profiler.last_report = t2;
    }
    return (0);
}

static int on_keypress(const int key, void *param)
{
    t_app   *app;

    app = (t_app *)param;
    if (key == KEY_ESC)
        mlx_loop_end(app->mlx);
    else if (key == KEY_UP)
    {
        app->active_count += 5000;
        if (app->active_count > MAX_PARTICLES)
            app->active_count = MAX_PARTICLES;
    }
    else if (key == KEY_DOWN)
    {
        app->active_count -= 5000;
        if (app->active_count < 0)
            app->active_count = 0;
    }
    return (0);
}

int main(void)
{
    t_app   app = {0};

    printf("==========================================\n");
    printf("   MiniLibX OpenGL - Architecture Benchmark\n");
    printf("==========================================\n");
    printf("Controls:\n  [UP]   Add 5000 particles\n  [DOWN] Remove 5000 particles\n  [ESC]  Quit\n\n");
    srand(time(NULL));
    app.mlx = mlx_init();
    if (!app.mlx)
        return (EXIT_FAILURE);
    app.window = mlx_new_window(app.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Arch Bench - OpenGL");
    if (!app.window)
    {
        free(app.mlx);
        return (EXIT_FAILURE);
    }
    init_system(&app);
    app.profiler.last_report = get_time_ns();
    mlx_hook(app.window, 2, 1L<<0, on_keypress, &app);
    mlx_loop_hook(app.mlx, render_loop, &app);
    mlx_loop(app.mlx);
    free(app.particles);
    mlx_destroy_window(app.mlx, app.window);
    mlx_destroy_display(app.mlx);
    free(app.mlx);
    printf("\n[System] Benchmark terminated successfully.\n");
    return (EXIT_SUCCESS);
}
