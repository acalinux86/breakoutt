#include "./src/breakoutt.hpp"

#define SCREEN_WIDTH  800 // Window width
#define SCREEN_HEIGHT 600 // Window height

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
    int swapInterval = SDL_GL_SetSwapInterval(1);
    if (swapInterval != 0 ) {
        fprintf(stderr, "Setting Swap Interval Failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int getSwapInterVal = SDL_GL_GetSwapInterval();
    if (getSwapInterVal == 0) printf("Vsync Disabled\n");
    else printf("Vsync Enabled\n");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    double last_time = (double) SDL_GetTicks() * 0.001f;
    double frame_count = 0.0;

    GLuint ProgramId = LoadShader("shader/vertex_shader.vert", "shader/fragment_shader.frag");
    if (ProgramId == 0) return 1;
    printf("ProgramId: %u\n", ProgramId);

    bool quit = false;  // Main loop flag
    SDL_Event e; // Event handler
    // Game loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e)) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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
