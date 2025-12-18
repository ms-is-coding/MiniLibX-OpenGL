# MiniLibX OpenGL

---

> [!CAUTION]
> **42 Students:** Please exercise caution when using this library for your projects.
> It was developed by fellow students and may be considered cheating,
> depending on your campus's policies. Make sure you understand the implications
> of using it in your projects, and don't hesitate to ask the staff if you have
> any questions or concerns.

> [!NOTE]
> This library is designed for **Linux** (X11). It has not been tested on macOS.
> Contributions for macOS compatibility are welcome.

---

## Description

**MiniLibX OpenGL** is a modern, high-performance replacement for the outdated
[MiniLibX](https://github.com/42Paris/minilibx-linux) library.

Unlike the original version which relies on software rendering (CPU), this library leverages **OpenGL Hardware
Acceleration**. It implements a **Texture Streaming** architecture where the CPU writes to a pixel buffer, which is
then uploaded to the GPU as a texture. This results in:

- **Higher Performance:** 60 FPS+ constant, even with complex scenes.
- **Better Responsiveness**: Optimized event loop hooks.
- **Modern Features:** Alpha blending support, direct buffer access.

## Features

- [x] **Hardware Accelerated** rendering (OpenGL)
- [x] Full compatibility with the MiniLibX API
- [x] **XPM Image Loading** support (with transparency)
- [x] Multi-window management
- [x] robust Event handling (keyboard, mouse, window state)
- [ ] Font rendering
- [ ] Audio playback

## Getting Started

You can build the library by running the following commands:

```sh
git clone https://github.com/ms-is-coding/MiniLibX-OpenGL.git
cd MiniLibX-OpenGL
make
```

## Quick Example

This library is a drop-in replacement. Your existing code should work without modification.

```c++
#include "mlx.h"

int main(void)
{
    t_mlx       *mlx = mlx_init();
    t_window    *win = mlx_new_window(mlx, 800, 600, "Hello OpenGL");
    // Your rendering loop here...
    mlx_loop(mlx);
    return (0);
}
```

## API Reference Status

Below is the implementation status of the standard MiniLibX functions:

### Core & Windows

- [x] `mlx_init`
- [x] `mlx_new_window`
- [x] `mlx_clear_window`
- [x] `mlx_destroy_window`
- [x] `mlx_destroy_display`

### Drawing & Images

- [x] `mlx_pixel_put` (Optimized direct buffer write)
- [x] `mlx_new_image`
- [x] `mlx_get_data_addr`
- [x] `mlx_put_image_to_window`
- [x] `mlx_xpm_file_to_image`
- [x] `mlx_destroy_image`
- [ ] `mlx_get_color_value`
- [ ] `mlx_string_put`
- [ ] `mlx_set_font`
- [ ] `mlx_xpm_to_image`

### Events & Input

- [x] `mlx_loop`
- [x] `mlx_loop_hook`
- [x] `mlx_loop_end`
- [x] `mlx_hook`
- [x] `mlx_mouse_hook`
- [x] `mlx_key_hook`
- [x] `mlx_expose_hook`
- [x] `mlx_mouse_get_pos`
- [x] `mlx_mouse_move`
- [x] `mlx_mouse_hide`
- [x] `mlx_mouse_show`
- [x] `mlx_do_key_autorepeatoff`
- [x] `mlx_do_key_autorepeaton`
- [x] `mlx_do_sync`

### Extras

- [x] `mlx_get_screen_size`
- [ ] `mlx_window_move`

## License

MiniLibX OpenGL is released under the MIT License, see [LICENSE](LICENSE) for details.
