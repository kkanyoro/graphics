#define _CRT_SECURE_NO_WARNINGS
#include <glad/glad.h>  // GLAD must be BEFORE GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

// SHADER SOURCE CODE (GLSL)
// VERTEX SHADER
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;    \n"
"layout (location = 1) in vec2 aTexCoord;\n"
"out vec2 TexCoord;                     \n"
"void main()                            \n"
"{                                      \n"
"   gl_Position = vec4(aPos, 1.0);      \n"
"   TexCoord = aTexCoord;               \n"
"}\0";

// FRAGMENT SHADER
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;                             \n"
"in vec2 TexCoord;                               \n"
"uniform sampler2D ourTexture;                   \n"
"uniform int mode;                               \n" // 0=Normal, 1=Invert, 2=Gray

"void main()                                     \n"
"{                                               \n"
"   vec4 texColor = texture(ourTexture, TexCoord); \n"
"                                                \n"
"   if(mode == 1) // INVERT                      \n"
"   {                                            \n"
"       FragColor = vec4(1.0 - texColor.rgb, 1.0); \n"
"   }                                            \n"
"   else if(mode == 2) // GRAYSCALE              \n"
"   {                                            \n"
"       // Human eyes are sensitive to Green, so we use the formula:\n"
"       float gray = dot(texColor.rgb, vec3(0.299, 0.587, 0.114)); \n"
"       FragColor = vec4(gray, gray, gray, 1.0);    \n"
"   }                                            \n"
"   else // NORMAL (Mode 0)                      \n"
"   {                                            \n"
"       FragColor = texColor;                    \n"
"   }                                            \n"
"}\n\0";

// GLOBAL VARIABLES
int currentMode = 0; // 0=Normal, 1=Invert, 2=Grayscale

// HELPER FUNCTIONS

unsigned int createShaderProgram() {
    // Compile Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Compile Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Link Program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

// Function to generate a checkerboard texture
unsigned int createTexture() {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Create a 64x64 colorful checkerboard pattern
    const int width = 64;
    const int height = 64;

    // Use malloc for dynamic memory
    unsigned char* data = (unsigned char*)malloc(width * height * 3);

    if (data == NULL) {
        printf("Failed to allocate memory for texture!\n");
        return 0;
    }
    // FIX END

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 3;
            // Determine if square is colored or white
            int checker = ((x / 8) + (y / 8)) % 2;

            if (checker == 0) {
                // Colorful Pattern
                data[index] = (unsigned char)(x * 4);      // R
                data[index + 1] = (unsigned char)(y * 4); // G
                data[index + 2] = 128;                    // B
            }
            else {
                // White
                data[index] = 255;
                data[index + 1] = 255;
                data[index + 2] = 255;
            }
        }
    }

    // Send data to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free the CPU memory since the GPU has a copy
    free(data);

    return textureID;
}

// INPUT HANDLING
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) currentMode = 0; // Normal
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) currentMode = 1; // Invert
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) currentMode = 2; // Grayscale
}

int main(void) {
    // INITIALIZE GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Q4: Shader Color Transforms", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // INITIALIZE GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // BUILD SHADERS & TEXTURE
    unsigned int shaderProgram = createShaderProgram();
    unsigned int texture = createTexture();

    // SETUP GEOMETRY
    float vertices[] = {
         0.7f,  0.7f, 0.0f,   1.0f, 1.0f, // Top Right
         0.7f, -0.7f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -0.7f, -0.7f, 0.0f,   0.0f, 0.0f, // Bottom Left
        -0.7f,  0.7f, 0.0f,   0.0f, 1.0f  // Top Left 
    };
    unsigned int indices[] = {
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture Coord Attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // RENDER LOOP
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);
        glUseProgram(shaderProgram);

        // Update the "mode" uniform
        int modeLoc = glGetUniformLocation(shaderProgram, "mode");
        glUniform1i(modeLoc, currentMode);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}