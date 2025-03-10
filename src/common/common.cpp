#include <fstream>
#include <iostream>
#include <cassert>

// OpenGL
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace common {

extern GLuint CompileShader(const char *src, GLenum type) {
    GLuint shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &src, nullptr);
    glCompileShader(shader_id);

    GLint compile_status;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE) {
        GLint length;
        char msg[1024];
        glGetShaderInfoLog(shader_id, 1024, &length, msg);
        std::cout << "ERROR: shader compilation error: " << msg << std::endl;
        glDeleteShader(shader_id);
        shader_id = 0;
    }

    return shader_id;
}

extern GLuint CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    GLuint program = glCreateProgram();
    GLuint vs = CompileShader(vertexShader.c_str(), GL_VERTEX_SHADER);
    GLuint fs = CompileShader(fragmentShader.c_str(), GL_FRAGMENT_SHADER);
    if (!vs || !fs)
        goto err;

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    GLint linking_status;
    glGetProgramiv(program, GL_LINK_STATUS, &linking_status);
    if (linking_status != GL_TRUE) {
        GLint length;
        char msg[1024];
        glGetShaderInfoLog(program, 1024, &length, msg);
        std::cout << "ERROR: program linking error: " <<  msg << std::endl;
        goto err;
    }

    glDetachShader(program, vs);
    glDetachShader(program, fs);
    goto ret;

err:
    glDeleteProgram(program);
    program = 0;

ret:
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

extern std::string ReadFile(const char *path) {
    std::ifstream fp{path};
    assert(fp.is_open());
    std::string data{std::istreambuf_iterator<char>(fp), std::istreambuf_iterator<char>()};
    return data;
}

extern void PrintInfo(void) {
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}

} // end namespace common
