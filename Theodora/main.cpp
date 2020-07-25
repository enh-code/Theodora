#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define GLSL(version, code) "#version " #version "\n" #code

//Vertex shader
const GLchar* vert = GLSL(330,
    layout(location = 0) in vec3 pos;
    layout(location = 1) in vec2 tex;

    out vec2 texCoord;

    uniform mat4 model;
    uniform mat4 projection;
    uniform mat4 view;

    void main()
    {
        gl_Position = projection * view * model * vec4(pos, 1.0);
        texCoord = tex;
    }
);

//Fragment shader
const GLchar* frag = GLSL(330, 
    out vec4 fragColor;

    in vec2 texCoord;

    uniform sampler2D texture1;

    void main()
    {
        fragColor = texture(texture1, texCoord);
    }
);

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
int CENTER_X = SCREEN_WIDTH / 2;
int CENTER_Y = SCREEN_HEIGHT / 2;

unsigned int VAO, VBO, TBO;

float vertices[] =
{
    //Position          //Texture
    -0.5,  0.5,  0.5,   0.0f, 1.0f, //Front
     0.5,  0.5,  0.5,   1.0f, 1.0f,
     0.5, -0.5,  0.5,   1.0f, 0.0f,
     0.5, -0.5,  0.5,   1.0f, 0.0f,
    -0.5, -0.5,  0.5,   0.0f, 0.0f,
    -0.5,  0.5,  0.5,   0.0f, 1.0f,

    -0.5,  0.5, -0.5,   0.0f, 1.0f, //Back
     0.5,  0.5, -0.5,   1.0f, 1.0f,
     0.5, -0.5, -0.5,   1.0f, 0.0f,
     0.5, -0.5, -0.5,   1.0f, 0.0f,
    -0.5, -0.5, -0.5,   0.0f, 0.0f,
    -0.5,  0.5, -0.5,   0.0f, 1.0f,

    -0.5,  0.5, -0.5,   0.0f, 1.0f, //Top
     0.5,  0.5, -0.5,   1.0f, 1.0f,
     0.5,  0.5,  0.5,   1.0f, 0.0f,
     0.5,  0.5,  0.5,   1.0f, 0.0f,
    -0.5,  0.5,  0.5,   0.0f, 0.0f,
    -0.5,  0.5, -0.5,   0.0f, 1.0f,

    -0.5, -0.5, -0.5,   0.0f, 1.0f, //Bottom
     0.5, -0.5, -0.5,   1.0f, 1.0f,
     0.5, -0.5,  0.5,   1.0f, 0.0f,
     0.5, -0.5,  0.5,   1.0f, 0.0f,
    -0.5, -0.5,  0.5,   0.0f, 0.0f,
    -0.5, -0.5, -0.5,   0.0f, 1.0f,

    -0.5,  0.5, -0.5,   1.0f, 1.0f, //Left
    -0.5,  0.5,  0.5,   1.0f, 0.0f,
    -0.5, -0.5,  0.5,   0.0f, 0.0f,
    -0.5, -0.5,  0.5,   0.0f, 0.0f,
    -0.5, -0.5, -0.5,   0.0f, 1.0f,
    -0.5,  0.5, -0.5,   1.0f, 1.0f,

     0.5,  0.5, -0.5,   1.0f, 1.0f, //Right
     0.5,  0.5,  0.5,   1.0f, 0.0f,
     0.5, -0.5,  0.5,   0.0f, 0.0f,
     0.5, -0.5,  0.5,   0.0f, 0.0f,
     0.5, -0.5, -0.5,   0.0f, 1.0f,
     0.5,  0.5, -0.5,   1.0f, 1.0f
};

void display(void);
void reshape(int width, int height);

int program;

int main(int argc, char** argv)
{
    GLenum error;

    //Init libraries
    glutInit(&argc, argv);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GL_CONTEXT_CORE_PROFILE_BIT);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("OpenGL");

    error = glewInit();
    if(error != GLEW_OK)
    {
        printf("GLEW failed to initialize! %s", glewGetErrorString(error));
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    //Generate and attach buffer/vertex array objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Generate texture object
    glGenTextures(1, &TBO);
    glBindTexture(GL_TEXTURE_2D, TBO);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //Load image
    int s, t, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("picture.jpg", &s, &t, &channels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, s, t, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);


    //Compile, link, and begin shader program
    int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vert, NULL);
    glCompileShader(vs);

    int success;
    char infoLog[512];
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &frag, NULL);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fs, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    glUseProgram(program);

    //Math from local coordinates to perspective view
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glutGet(GLUT_ELAPSED_TIME) * glm::radians(50.0f), glm::vec3(0.0, 1.0, 0.0));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 proj;
    proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    //Set uniform matrix variables
    int loc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
    loc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
    loc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(proj));

    //Set callbacks
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutMainLoop();

    //Not sure if this executes
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    return 0;
}

void display(void)
{
    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Math from local coordinates to perspective view
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glutGet(GLUT_ELAPSED_TIME) / 1000.0f * glm::radians(50.0f), glm::vec3(0.5, 1.0, 0.0));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 proj;
    proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    //Set uniform matrix variables
    int loc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
    loc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
    loc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(proj));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    CENTER_X = SCREEN_WIDTH / 2;
    CENTER_Y = SCREEN_HEIGHT / 2;
}
