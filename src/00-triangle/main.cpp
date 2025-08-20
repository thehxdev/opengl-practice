#include <iostream>
#include <string>

// OpenGL
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <common.hpp>

typedef float vec2[2];

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "ERROR: not enough arguments\n";
        std::cerr << "Usage: " << argv[0] << " <vertex-shader-file> <fragment-shader-file>" << std::endl;
        return -1;
    }

    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int err = 0;
    GLFWwindow *window;
    GLuint vao, buffer, program, pos_location;

    vec2 vertecies[3] = {
        { 0.f,  .6f },
        {-.5f, -.3f },
        { .5f, -.3f },
    };

    std::string vertex_shader_source{common::ReadFile(argv[1])};
    std::string fragment_shader_source{common::ReadFile(argv[2])};

    window = glfwCreateWindow(1040, 800, "Hello Triangle 0", nullptr, nullptr);
    if (!window) {
        err = -1;
        goto ret;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        err = -1;
        goto ret;
    }
    glfwSwapInterval(1);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);

    program = common::CreateShader(vertex_shader_source, fragment_shader_source);
    if (!program) {
        err = 1;
        goto ret;
    }
    glUseProgram(program);

    pos_location = glGetAttribLocation(program, "pos");
    glEnableVertexAttribArray(pos_location);
    glVertexAttribPointer(pos_location, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), nullptr);

    common::PrintInfo();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

ret:
    glfwTerminate();
    return err;
}
