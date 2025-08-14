#include "./src/breakoutt.hpp"

#define SCREEN_WIDTH  800 // Window width
#define SCREEN_HEIGHT 600 // Window height
#define RADIUS 0.1f
#define ASPECT_RATIO ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)
#define FPS 60
#define DELTA_TIME   ((float) 1 / (float)FPS)
#define MAX_UPDATES 5
#define RED (Color(1.0f, 0.0f, 0.0f, 1.0f))
#define GREEN (Color(0.0f, 1.0f, 0.0f, 1.0f))
#define BLUE (Color(0.0f, 0.0f, 1.0f, 1.0f))
#define WHITE (Color(1.0f, 1.0f, 1.0f, 1.0f))

Indices BallIndices = {nullptr, 0, 0};
Vertices BallVertices = {nullptr, 0, 0};

Indices TileIndices = {nullptr, 0, 0};
Vertices TileVertices = {nullptr, 0, 0};

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

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

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

    Vector3 BallPos(0.0f, 0.0f, 0.0f);
    Vector3 BallVel(0.0f, 0.5f, 0.0f);

    Ball ball = Ball(BallPos, RADIUS, WHITE, BallVel, 12*10, BallIndices, BallVertices);
    ball.GenerateBall();
    ball.RenderBall();

    Vector3 TilePos = Vector3(0.0f, -0.9f, 0.0f);
    Vector3 TileSize = Vector3(0.1f, 0.05, 0.0f);
    Tile tile = Tile(TilePos, TileSize, GREEN, TileIndices, TileVertices);
    tile.GenerateTile();
    tile.RenderTile();

    glUseProgram(ProgramId);
    GLint aspectRatioLoc = glGetUniformLocation(ProgramId, "aspectRatio");
    if (aspectRatioLoc == -1) {
        printf("ERROR: Could not find aspectRatio uniform location\n");
    }
    glUniform1f(aspectRatioLoc, ASPECT_RATIO);

    bool quit = false;  // Main loop flag
    SDL_Event e; // Event handler
    auto previous_time = SDL_GetTicks();
    auto accumulated = 0.0f;

    // Game loop
    while (!quit) {
        auto current_time = SDL_GetTicks();
        auto frame_time = current_time - previous_time;
        previous_time = current_time;
        accumulated += frame_time / 1000.0f;

        // Handle events on queue
        while (SDL_PollEvent(&e)) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        int updates = 0;
        // Fixed timestep update
        while (accumulated >= DELTA_TIME && updates < MAX_UPDATES) {
            // Update ball position
            ball.Position.x += ball.Velocity.x * DELTA_TIME;
            ball.Position.y += ball.Velocity.y * DELTA_TIME;

            // Boundary checking (simple example)
            if (ball.Position.x + RADIUS > 1.0f || ball.Position.x - RADIUS < -1.0f) {
                ball.Velocity.x *= -1.0f;
            }
            if (ball.Position.y + RADIUS > 1.0f || ball.Position.y - RADIUS < -1.0f) {
                ball.Velocity.y *= -1.0f;
            }

            accumulated -= DELTA_TIME;
        }
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Regenerate ball vertices with new position
        ball.UpdateBall();

        // Update GPU buffer
        glBindVertexArray(ball.VAO);
        glDrawElements(GL_TRIANGLES, ball.indices.count, GL_UNSIGNED_INT, (void*) 0);
        glBindVertexArray(tile.VAO);
        glDrawElements(GL_TRIANGLES, tile.indices.count, GL_UNSIGNED_INT, (void*) 0);
        calculate_fps(&last_time, &frame_count);
        SDL_GL_SwapWindow(window);
    }

    // Destroy window
    SDL_DestroyWindow(window);
    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
