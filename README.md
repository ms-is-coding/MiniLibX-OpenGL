# MiniLibX OpenGL

> [!CAUTION]
> Please exercise caution when using this library for your 42 projects.
> It was developed by a fellow student and may be considered cheating,
> depending on your campus's policies. Make sure you understand the implications
> of using it in your projects, and don't hesitate to ask the staff if you have
> any questions or concerns.

> [!NOTE]
> This library has not been tested on macOS. If you would like to contribute
> compatibility modifications, you are always welcome to submit a PR.

## Description

This project is a replacement for the outdated
[MiniLibX](https://github.com/42Paris/minilibx-linux) library, designed to
optimize rendering using OpenGL. It maintains a similar API while introducing
new features.

## Features

- [x] OpenGL rendering for improved performance
- [x] Compatibility with the MiniLibX API
- [ ] Loading XPM images
- [ ] Managing multiple windows
- [ ] Event handling
- [ ] Font rendering
- [ ] Audio playback

## Getting Started

You can build the library by running the following commands:
```sh
git clone https://github.com/ms-is-coding/MiniLibX-OpenGL.git
cd MiniLibX-OpenGL
make
```

## Usage

You can refer to the original MiniLibX's usage page, all of the APIs
are the same.

## Function reference

- [x] `mlx_init`
- [x] `mlx_new_window`
- [x] `mlx_clear_window`
- [x] `mlx_pixel_put`
- [ ] `mlx_new_image`
- [ ] `mlx_get_data_addr`
- [ ] `mlx_put_image_to_window`
- [ ] `mlx_get_color_value`
- [ ] `mlx_mouse_hook`
- [ ] `mlx_key_hook`
- [ ] `mlx_expose_hook`
- [x] `mlx_loop_hook`
- [x] `mlx_loop`
- [ ] `mlx_loop_end`
- [ ] `mlx_string_put`
- [ ] `mlx_set_font`
- [ ] `mlx_xpm_to_image`
- [ ] `mlx_xpm_file_to_image`
- [x] `mlx_destroy_window`
- [ ] `mlx_destroy_image`
- [x] `mlx_destroy_display`
- [ ] `mlx_hook`
- [ ] `mlx_do_key_autorepeatoff`
- [ ] `mlx_do_key_autorepeaton`
- [ ] `mlx_do_sync`
- [ ] `mlx_mouse_get_pos`
- [x] `mlx_mouse_move`
- [x] `mlx_mouse_hide`
- [x] `mlx_mouse_show`
- [ ] `mlx_get_screen_size`

> [!WARNING]
> All of the functions below are not present in the original MiniLibX, therefore
> you must only use them when IS_MLX_OPENGL is present. Make sure your code
> respects the norm :)

- [ ] WIP

## License

MiniLibX OpenGL is released under the MIT License, see [LICENSE](LICENSE) for
details
