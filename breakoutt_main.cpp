#include "./src/breakoutt.hpp"

#define SCREEN_WIDTH  800 // Window width
#define SCREEN_HEIGHT 600 // Window height
#define RADIUS 0.25f
#define ASPECT_RATIO ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)

struct Vertex {
    Vector3 Position;
    Color color;
    Vertex(Vector3 Position, Color color):
        Position(Position), color(color) {}
};

typedef ARRAY(Vertex) Vertices;
typedef ARRAY(uint32_t) Indices;

Vertices vertices = {nullptr, 0, 0};
Indices indices = {nullptr, 0, 0};

#define RED (Color(1.0f, 0.0f, 0.0f, 1.0f))
#define GREEN (Color(0.0f, 1.0f, 0.0f, 1.0f))
#define BLUE (Color(0.0f, 0.0f, 1.0f, 1.0f))

int randomNumber()
{
    int min = 1;
    int max = 3;
    return (rand() % (max - min + 1)) + min;
}

void buildCircle(int vCount)
{
    float angle = 360.0f / vCount;

    int triangleCount = vCount - 2;
    array_new(&indices, uint32_t);
    array_new(&vertices, Vertex);

    // positions
    for (int i = 0; i < vCount; i++)
    {
        float currentAngle = angle * i;
        float x = RADIUS * cosf(degreesToRadians(currentAngle)) * ASPECT_RATIO;
        float y = RADIUS * sinf(degreesToRadians(currentAngle)) * ASPECT_RATIO;
        float z = 0.0f;

        if (randomNumber() == 1) {
            array_append(Vertex, &vertices, Vertex(Vector3(x, y, z), RED));
        } else if (randomNumber() == 2) {
            array_append(Vertex, &vertices, Vertex(Vector3(x, y, z), BLUE));
        } else {
            array_append(Vertex, &vertices, Vertex(Vector3(x, y, z), GREEN));
        }
    }

    for (int i = 0; i < triangleCount; i++)
    {
        array_append(uint32_t, &indices, 0);
        array_append(uint32_t, &indices, i + 1);
        array_append(uint32_t, &indices, i + 2);
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

    buildCircle(12*30);

    GLuint VBO;
    GLuint VAO;
    GLuint EBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.count*sizeof(vertices.items[0]), vertices.items, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.count*sizeof(indices.items[0]), indices.items, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glUseProgram(ProgramId);

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

        // Update GPU buffer
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLE_FAN, indices.count, GL_UNSIGNED_INT, (void*) 0);
        calculate_fps(&last_time, &frame_count);
        SDL_GL_SwapWindow(window);
    }

    // Destroy window
    SDL_DestroyWindow(window);
    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
