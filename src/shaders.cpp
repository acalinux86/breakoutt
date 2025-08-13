#include "./breakoutt.hpp"

char *read_file(const char *file_path, uint8_t *size)
{
    FILE *fp = fopen(file_path, "rb");
    if (fp == nullptr)
    {
        fprintf(stderr, "Failed to open file %s: %s.\n", file_path, strerror(errno));
        return nullptr;
    }

    fseek(fp, 0, SEEK_END);
    uint32_t len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = (char*)calloc(len+1, sizeof(char));
    if (buffer == nullptr)
    {
        fprintf(stderr, "Failed to Allocate Memory For Buffer.\n");
        return nullptr;
    }

    size_t n = fread(buffer, 1, len, fp);
    assert(n == (size_t) len);

    if (ferror(fp) < 0)
    {
        fprintf(stderr, "fread failed!.\n");
        return nullptr;
    }

    buffer[len] = '\0';
    *size = len;

    fclose(fp);
    return buffer;
}

bool log_shader_error(GLuint Id)
{
    GLint result = GL_FALSE;
    int info_log_length;

    // Check the Programs
    glGetShaderiv(Id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(Id, GL_INFO_LOG_LENGTH, &info_log_length);

    if (info_log_length > 0)
    {
        char ErrorMessage[info_log_length];
        glGetShaderInfoLog(Id, info_log_length, nullptr, ErrorMessage);
        fprintf(stderr, "%s\n", &ErrorMessage[0]);
    }
    return result == GL_TRUE;
}

bool log_program_error(GLuint Id)
{
    GLint result = GL_FALSE;
    int info_log_length;

    // Check the Programs
    glGetProgramiv(Id, GL_LINK_STATUS, &result);
    glGetProgramiv(Id, GL_INFO_LOG_LENGTH, &info_log_length);

    if (info_log_length > 0)
    {
        char ErrorMessage[info_log_length + 1];
        glGetProgramInfoLog(Id, info_log_length, nullptr, ErrorMessage);
        fprintf(stderr, "%s\n", &ErrorMessage[0]);
    }
    return result == GL_TRUE;
}

GLuint compile_vertex(char *vertex_code)
{
    GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    if (vertex_code == nullptr) {
        fprintf(stderr, "Vertex Shader Source is nullptr\n");
        return 0;
    }
    printf("Compiling Vertex Shader Program...\n");
    glShaderSource(VertexShaderId, 1, (const GLchar* const*)&vertex_code, nullptr);
    glCompileShader(VertexShaderId);

    // Check Vertex Shader
    if (!log_shader_error(VertexShaderId)) {
        glDeleteShader(VertexShaderId);
        return 0;
    }
    printf("SuccessFully Compiled Vertex Shader.\n");
    return VertexShaderId;
}

GLuint compile_fragment(char *fragment_code)
{
    GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragment_code == nullptr) {
        fprintf(stderr, "Fragment Shader Source is nullptr.\n");
        return 0;
    }
    printf("Compiling Fragment Shader Program...\n");
    glShaderSource(FragmentShaderId, 1, (const GLchar* const*)&fragment_code, nullptr);
    glCompileShader(FragmentShaderId);

    // Check fragment Shader
    if (!log_shader_error(FragmentShaderId)) {
        glDeleteShader(FragmentShaderId);
        return 0;
    }
    printf("SuccessFully Compiled Fragment Shader.\n");
    return FragmentShaderId;
}

GLuint LoadShader(const char *vertex_file_path, const char *fragment_file_path)
{
    uint8_t v_len, f_len = 0;
    char *vertex_code = read_file(vertex_file_path, &v_len);
    char *fragment_code = read_file(fragment_file_path, &f_len);

    // Debug print the shader sources
    printf("Vertex shader source (%u bytes)\n", v_len);
    printf("Fragment shader source (%u bytes)\n", f_len);

    GLuint FragmentShaderId = compile_fragment(fragment_code);
    GLuint VertexShaderId = compile_vertex(vertex_code);

    if (FragmentShaderId == 0 || VertexShaderId == 0)
    {
        if (VertexShaderId) glDeleteShader(VertexShaderId);
        if (FragmentShaderId) glDeleteShader(FragmentShaderId);
        free(vertex_code);
        free(fragment_code);
        return 0;
    }

    // Link the Program
    printf( "Linking Programs...\n");
    GLuint ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);

    // Check the Program
    if (!log_program_error(ProgramId))
    {
        fprintf(stderr, "Program Linking Failed.\n");
        free(vertex_code);
        free(fragment_code);
        glDeleteProgram(ProgramId);
        ProgramId = 0;
        return 0;
    }
    printf("SuccessFully Linked Program.\n");
    printf("Detaching and Deleting Shaders...\n");

    // Detach Shaders
    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    // Delete Shader Id
    glDeleteShader(VertexShaderId);
    glDeleteShader(FragmentShaderId);
    printf("SuccessFully Detached and Deleted the Shaders.\n");

    // Free the shader buffers
    free(vertex_code);
    free(fragment_code);
    printf("SuccessFully Freed the Shader Buffers\n");
    return ProgramId; // return program id
}

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
