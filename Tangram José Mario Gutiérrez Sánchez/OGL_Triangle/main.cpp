#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location=1) in vec3 aColor;\n"
"out vec3 ourColor; \n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor.x, ourColor.y, ourColor.z, 1.0f); \n"
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Recorrido Virtual Horror Fest", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        1.0f, 1.0f, 0.0f,    0.349f, 0.015f, 0.643f,
        0.5f, 0.5f, 0.0f,    0.349f, 0.015f, 0.643f,
        0.0f, 1.0f, 0.0f,    0.349f, 0.015f, 0.643f, //TRIANGULO 1 MORADO


        0.0f, 1.0f, 0.0f,    0.349f, 0.015f, 0.643f,
        -0.5f, 0.5f, 0.0f,   0.349f, 0.015f, 0.643f,
        0.5f, 0.5f, 0.0f,    0.349f, 0.015f, 0.643f, //TRIANGULO 2 MORADO

        
       -1.0f, 0.0f, 0.0f,    0.254f, 0.835f, 0.984f,
       -1.0f, -1.0f, 0.0f,   0.254f, 0.835f, 0.984f,
       -0.5f, -0.5f, 0.0f,   0.254f, 0.835f, 0.984f, //TRIANGULO CELESTE


        0.0f, 0.0f, 0.0f,    1.0f, 0.533f, 0.121f,
       -0.5f, 0.5f, 0.0f,    1.0f, 0.533f, 0.121f,
        0.5f, 0.5f, 0.0f,    1.0f, 0.533f, 0.121f, //TRIANGULO NARANJA


        0.0f, 0.0f, 0.0f,    0.337f, 0.635f, 0.023f,
       -1.0f, -1.0f, 0.0f,    0.337f, 0.635f, 0.023f,
        1.0f, -1.0f, 0.0f,    0.337f, 0.635f, 0.023f, //TRIANGULO VERDE FUERTE
       

       -1.0f, 0.0f, 0.0f,     0.517f, 1.0f, 0.019f,
       -1.0f, 1.0f, 0.0f,     0.517f, 1.0f, 0.019f,
        0.0f, 1.0f, 0.0f,     0.517f, 1.0f, 0.019f, //TRIANGULO VERDE

        
        0.0f, 0.0f, 0.0f,     0.635f, 0.031f, 0.023f,
       -0.5f, 0.5f, 0.0f,     0.635f, 0.031f, 0.023f,
       -0.5f, -0.5f, 0.0f,    0.635f, 0.031f, 0.023f, //TRIANGULO 1 ROJO


       -1.0f, 0.0f, 0.0f,     0.635f, 0.031f, 0.023f,
       -0.5f, 0.5f, 0.0f,     0.635f, 0.031f, 0.023f,
       -0.5f, -0.5f, 0.0f,    0.635f, 0.031f, 0.023f, //TRIANGULO 2 ROJO

       0.0f, 0.0f, 0.0f,      0.988f, 0.996f, 0.125f,
       1.0f, 1.0f, 0.0f,      0.988f, 0.996f, 0.125f,
       1.0f, -1.0f, 0.0f,     0.988f, 0.996f, 0.125f, //TRIANGULO AMARILLO

        // 0.5f,  0.5f, 0.0f,  // top right
        // 0.5f, -0.5f, 0.0f,  // bottom right
        //-0.5f, -0.5f, 0.0f,  // bottom left
        //-0.5f,  0.5f, 0.0f,   // top left 
        //-1.0f,  -0.5f, 0.0f,  // top right
        //-1.0f,   0.5f, 0.0f,  // bottom right
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        3, 2, 1,   // second Triangle

        3, 2, 5,   // third Triangle
        5, 4, 2   // fourth Triangle
    };
    
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); //N??mero de elementos // referencia al buffer
    glGenBuffers(1, &EBO);


    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

    //ATRIBUTO DE POSICION
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //Column Major
    glEnableVertexAttribArray(0);
    //ATRIBUTO DE COLOR
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float))); //Column Major
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);/*(0.2f, 0.3f, 0.3f, 1.0f);*/
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glLineWidth(20.0);        
        glPointSize(20.0);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES , 0, 52);
        //glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


