#version 460 core
uniform mat4 MVP;
in vec4 position;
in vec3 posColor;
out vec4 color;
void main() {
    gl_Position = MVP * position;
    color = vec4(posColor, 1.0f);
}
