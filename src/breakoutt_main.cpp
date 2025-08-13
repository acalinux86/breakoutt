#include "./breakoutt.hpp"

#include <SDL2/SDL.h>
#include <GL/glew.h>

#define SCREEN_WIDTH  800 // Window width
#define SCREEN_HEIGHT 600 // Window height

void calculate_fps(double *last_time, double *frame_count)
{
    double current_time = (double) SDL_GetTicks() * 0.001f;
    (*frame_count)++;
    if (current_time - *last_time > 1.0f) {
        double fps = *frame_count / (current_time - *last_time);
        printf("FPS: %.2lf\n", fps);
        *frame_count = 0.0;
        *last_time = current_time;
    }
}

int main(void) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    int major;
    int minor;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
    printf("GL version %d.%d\n", major, minor);

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
        "Breatoutt",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
        );

    if (window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == NULL) {
        fprintf(stderr, "OpenGL context creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if (GLEW_OK != glewInit()) {
        fprintf(stderr, "Could not initialize GLEW!\n");
        return 1;
    }

    // 0 to disable VSync, 1 to enable
    int swapInterval = SDL_GL_SetSwapInterval(0);
    if (swapInterval != 0 ) {
        fprintf(stderr, "Setting Swap Interval Failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    double last_time = (double) SDL_GetTicks() * 0.001f;
    double frame_count = 0.0;

    bool quit = false;  // Main loop flag
    // Game loop
    while (!quit) {
        SDL_Event e; // Event handler
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        glClearColor(1.0f, 1.0f, 1.0f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        calculate_fps(&last_time, &frame_count);
        SDL_GL_SwapWindow(window);
    }

    // Destroy window
    SDL_DestroyWindow(window);
    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
