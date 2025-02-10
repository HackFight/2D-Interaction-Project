#include "gl_renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

//####################
// OpenGL structs
//####################
const char* TEXTURES_ATLAS = RESOURCES_PATH "textures/textures_atlas.png";


//####################
// OpenGL structs
//####################
struct GLContext
{
	GLuint programID;
    GLuint textureID;
};


//####################
// OpenGL globals
//####################
static GLContext glContext;


//####################
// OpenGL functions
//####################
static void APIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* user)
{
    if (severity == GL_DEBUG_SEVERITY_LOW ||
        severity == GL_DEBUG_SEVERITY_MEDIUM ||
        severity == GL_DEBUG_SEVERITY_HIGH)
    {
        SM_ASSERT(false, "OpenGL Error: %s", message);
    }
    else
    {
        SM_TRACE((char*)message);
    }
}

bool init_gl()
{
    /*glDebugMessageCallback(&gl_debug_callback, nullptr);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_DEBUG_OUTPUT);*/

    GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertShaderSource = get_file_contents(RESOURCES_PATH "shaders/quad.vert");
    std::string fragShaderSource = get_file_contents(RESOURCES_PATH "shaders/unlit.frag");

    const char* vertShader = vertShaderSource.c_str();
    const char* fragShader = fragShaderSource.c_str();
    if (!vertShader || !fragShader)
    {
        SM_ASSERT(false, "Failed to load shaders!");
        return false;
    }

    glShaderSource(vertShaderID, 1, &vertShader, 0);
    glShaderSource(fragShaderID, 1, &fragShader, 0);

    glCompileShader(vertShaderID);
    glCompileShader(fragShaderID);

    //Test for succesfull vertex shader compilation
    {
        int success;
        char shaderLog[2048] = {};

        glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertShaderID, 2048, 0, shaderLog);
            SM_ASSERT(false, "Failed to compile vertex shader %s", shaderLog);
            return false;
        }
    }

    //Test for succesfull fragment shader compilation
    {
        int success;
        char shaderLog[2048] = {};

        glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragShaderID, 2048, 0, shaderLog);
            SM_ASSERT(false, "Failed to compile fragment shader %s", shaderLog);
            return false;
        }
    }

    glContext.programID = glCreateProgram();
    glAttachShader(glContext.programID, vertShaderID);
    glAttachShader(glContext.programID, fragShaderID);
    glLinkProgram(glContext.programID);

    glDetachShader(glContext.programID, vertShaderID);
    glDetachShader(glContext.programID, fragShaderID);
    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);



    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);



    //Texture loading with STBI
    {
        int width, height, channels;
        char* data = (char*)stbi_load(TEXTURES_ATLAS, &width, &height, &channels, 4);
        if (!data)
        {
            SM_ASSERT(false, "Couldn't load texture!");
            return false;
        }

        glGenTextures(1, &glContext.textureID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, glContext.textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    glEnable(GL_FRAMEBUFFER_SRGB);      //Set frame buffer to SRGB color space
    glDisable(0x809D);                  //Disable multisampling

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);

    return true;
}

void gl_render()
{
    glClearColor(0.2f, 0.5f, 0.3f, 1.0f);
    glClearDepth(0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(glContext.programID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}