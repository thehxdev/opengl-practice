#include <iostream>
#include <cstring>
#include <string>
#include <limits.h>

// GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

// OpenGL
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <common.hpp>

typedef struct __vertex {
    glm::vec2 position;
    glm::vec3 color;
} vertex_t;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "ERROR: not enough arguments\n";
        std::cerr << "Usage: " << argv[0] << " vertex_shader_file fragment_shader_file" << std::endl;
        return -1;
    }

    int err = 0;
    GLFWwindow *window;
    GLuint vbo, program, vao, pos_location, mvp_location, posColor_location;

    vertex_t vertecies[3] = {
        {{  0.f,  .6f }, { 1.f, 0.f, 0.f }},
        {{  .5f, -.3f }, { 0.f, 1.f, 0.f }},
        {{ -.5f, -.3f }, { 0.f, 0.f, 1.f }},
    };

    glm::vec3 scale{1.3f, 1.3f, 1.3f};
    glm::vec3 rotation_axis{0.f, 0.f, 1.f};
    glm::mat4 scale_matrix = glm::scale(glm::mat4{1.f}, scale);

    // Initialize the library
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::string vertex_shader_source{common::ReadFile(argv[1])};
    std::string fragment_shader_source{common::ReadFile(argv[2])};

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(1040, 800, "Hello Triangle 1", nullptr, nullptr);
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

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);

    program = common::CreateShader(vertex_shader_source, fragment_shader_source);
    if (!program) {
        err = -1;
        goto ret;
    }
    glUseProgram(program);

    mvp_location = glGetUniformLocation(program, "MVP");
    pos_location = glGetAttribLocation(program, "position");
    posColor_location = glGetAttribLocation(program, "posColor");

    glEnableVertexAttribArray(pos_location);
    glVertexAttribPointer(pos_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, position));

    glEnableVertexAttribArray(posColor_location);
    glVertexAttribPointer(posColor_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, color));

    common::PrintInfo();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 rotation_matrix = glm::rotate((float)glfwGetTime(), rotation_axis);
        glm::mat4 projection_matrix = glm::ortho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glm::mat4 mvp = projection_matrix * rotation_matrix * scale_matrix;

        /* Draw triangle */
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) &mvp[0][0]);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

ret:
    glfwTerminate();
    return err;
}
