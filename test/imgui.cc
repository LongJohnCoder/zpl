﻿#define STB_IMAGE_IMPLEMENTATION
#define ZPLGL_NO_FONTS
#define ZPL_PLATFORM
#define ZPL_IMPLEMENTATION
#define ZPL_GLGEN_IMPLEMENTATION
#define ZPLGL_IMPLEMENTATION
#include "zpl.h"
#include "stb_image.h"
#include "zpl_glgen.h"
#include "zpl_opengl.h"

// This example REQUIRES you to download the latest version of Dear ImGUI.
#include "imgui.h"
#include "imgui/imgui_impl_zpl_gl3.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    zpl_platform p_ = { 0 };
    zpl_platform *p = &p_;

    const int window_width = 1024;
    const int window_height = 768;

    zpl_platform_init_with_opengl(p, "OpenGL Test", window_width, window_height, NULL /*ZPL_WINDOW_FULLSCREENDESKTOP*/, 4, 1, false, true);
    zpl_platform_show_window(p);
    //zpl_platform_toggle_borderless(p);

    zpl_glgen_init();

    zplgl_basic_state state_ = { 0 };
    zplgl_basic_state *state = &state_;

    zplgl_bs_init(state, window_width, window_height);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImVec4 new_clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    f32 circle_x = window_width / 2;
    f32 circle_y = window_height / 2;

    ImGui::CreateContext();
    ImGui_ImplZPLGL3_Init(p);
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    b32 is_running = true;
    b32 drag_circle = false;

    // circle radius
    f32 r = 120.0f;
    f32 rr = r * r;

    for (;is_running;) {
        zpl_platform_update(p);
        ImGui_ImplZPLGL3_ProcessUpdate(p);

        glClearColor(new_clear_color.x, new_clear_color.y, new_clear_color.z, new_clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        if (p->window_is_closed ||
            p->keys[ZPL_KEY_ESCAPE]) {
            is_running = false;
        }

        if (p->mouse_buttons[ZPL_MOUSEBUTTON_LEFT] && !(io.WantCaptureMouse)) {
            f32 dx = (f32)p->mouse_x - circle_x;
            f32 dy = (f32)p->mouse_y - circle_y;
            f32 dd = (dx * dx + dy * dy);

            if (dd > rr && !drag_circle)
                goto no_change;

            circle_x += (f32)p->mouse_dx;
            circle_y += (f32)p->mouse_dy;
            f32 mag = (circle_y / (f32)window_height);

            new_clear_color.x = clear_color.x * mag;
            new_clear_color.y = clear_color.y * mag;
            new_clear_color.z = clear_color.z * mag;
            new_clear_color.w = 1.0f;

            drag_circle = true;
        }
        else {
            drag_circle = false;
        }

        no_change:

        ImGui_ImplZPLGL3_NewFrame(p);

        zplgl_bs_begin(state, window_width, window_height);
        {
            
            zplgl_color invc;
#define PP(x) (u8)(x*255.f)
            invc.r = PP(-clear_color.x);
            invc.g = PP(-clear_color.y);
            invc.b = PP(-clear_color.z);
            invc.a = PP(clear_color.w);
#undef PP
            zplgl_bs_draw_circle(state, circle_x, circle_y, r, invc);
        }
        zplgl_bs_end(state);

        // dear imgui
        {
            static float f = 0.0f;
            static int counter = 0;
            ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
            if (ImGui::ColorEdit3("clear color", (float*)&clear_color)) { // Edit 3 floats representing a color
                new_clear_color.x = clear_color.x;
                new_clear_color.y = clear_color.y;
                new_clear_color.z = clear_color.z;
                new_clear_color.w = 1.0f;
            }

            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            ImGui::Text("Mouse X: %d, Mouse Y: %d", p->mouse_x, p->mouse_y);

            zpl_local_persist const char *lorem = R"FOO(
Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.
Why do we use it?

It is a long established fact that a reader will be distracted by the readable content of a page when looking at its layout. The point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here', making it look like readable English. Many desktop publishing packages and web page editors now use Lorem Ipsum as their default model text, and a search for 'lorem ipsum' will uncover many web sites still in their infancy. Various versions have evolved over the years, sometimes by accident, sometimes on purpose (injected humour and the like).

Where does it come from?

Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of "de Finibus Bonorum et Malorum" (The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during the Renaissance. The first line of Lorem Ipsum, "Lorem ipsum dolor sit amet..", comes from a line in section 1.10.32.

The standard chunk of Lorem Ipsum used since the 1500s is reproduced below for those interested. Sections 1.10.32 and 1.10.33 from "de Finibus Bonorum et Malorum" by Cicero are also reproduced in their exact original form, accompanied by English versions from the 1914 translation by H. Rackham.
Where can I get some?

There are many variations of passages of Lorem Ipsum available, but the majority have suffered alteration in some form, by injected humour, or randomised words which don't look even slightly believable. If you are going to use a passage of Lorem Ipsum, you need to be sure there isn't anything embarrassing hidden in the middle of text. All the Lorem Ipsum generators on the Internet tend to repeat predefined chunks as necessary, making this the first true generator on the Internet. It uses a dictionary of over 200 Latin words, combined with a handful of model sentence structures, to generate Lorem Ipsum which looks reasonable. The generated Lorem Ipsum is therefore always free from repetition, injected humour, or non-characteristic words etc.
            )FOO";

            bool is_open = true;
            ImGui::Begin("Text Viewer", &is_open, ImVec2(120, 80));
            {
                ImGui::TextWrapped("%s", lorem);
            }
            ImGui::End();

            zpl_local_persist char buf[512] = { 0 };
            ImGui::InputText("Input", buf, 512);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        ImGui::Render();
        ImGui_ImplZPLGL3_RenderDrawData(ImGui::GetDrawData());
        zpl_platform_display(p);
        zpl_yield();
    }

    ImGui_ImplZPLGL3_Shutdown();
    ImGui::DestroyContext();

    zpl_platform_destroy(p);

    return ERROR_SUCCESS;
}