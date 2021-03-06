#define STB_IMAGE_IMPLEMENTATION
#define STB_RECT_PACK_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define ZPL_PLATFORM
#define ZPL_IMPLEMENTATION
#define ZPL_GLGEN_IMPLEMENTATION
#define ZPLGL_IMPLEMENTATION
#include "zpl.h"
#include "stb_image.h"
#include "stb_rect_pack.h"
#include "stb_truetype.h"
#include "zpl_glgen.h"
#include "zpl_opengl.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    zpl_platform p_ = { 0 };
    zpl_platform *p = &p_;

    const int window_width = 640;
    const int window_height = 480;

    zpl_platform_init_with_opengl(p, "OpenGL Test", window_width, window_height, 0, 3, 3, false, true);

    zpl_glgen_init();

    zplgl_basic_state state_ = { 0 };
    zplgl_basic_state *state = &state_;

    
    zplgl_bs_init(state, window_width, window_height);

    b32 is_running = true;

    for (;is_running;) {
        zpl_platform_update(p);

        if (p->window_is_closed ||
            p->keys[ZPL_KEY_ESCAPE]) {
            is_running = false;
        }

        zplgl_bs_begin(state, window_width, window_height);
        {
            zplgl_bs_draw_circle(state, 320, 240, 32, zplgl_color_orange);
        }
        zplgl_bs_end(state);

        zpl_platform_display(p);
        zpl_sleep_ms(16);
    }

    zpl_platform_destroy(p);

    return ERROR_SUCCESS;
}