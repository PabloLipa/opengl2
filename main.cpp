#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using std::cout;
using std::endl;

const unsigned int WIDTH = 800; 
const unsigned int HEIGHT = 600;

// Código-Fonte Vertex Shader
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// Código-Fonte Fragment Shader
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";




int main()
{
    // Inicializar biblioteca GLFW
    glfwInit();

    // Especificar versão do OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Instanciar GLFWwindow
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "DiarioOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Falha ao criar GLFWwindow!" << endl;
        return -1;
    }
    // Definir window como contexto atual da thread de chamada
    glfwMakeContextCurrent(window);

    // Verificar GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Nao foi possivel carregar o contexto OpenGL!" << std::endl;
        return -1;
    }

    // --------------------------------------------------------------------------------------------------
    

     // Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Shader Program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Verificar erros de vinculação
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "Erro ao vincular Shader Program" << endl;
        cout << infoLog << endl;
    }


    // Deletar shaders inutilizados
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Vertices do triângulo
    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f, // A
        0.0f,  0.5f, 0.0f,  // B  
        0.5f, -0.5f, 0.0f // C
    };

    // Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // Vincular VAO e VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copiar dados dos vertices para o VBO vinculado
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Atribuir ponteiros para os vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Desvincular VBO e VAO para não modificar acidentalmente
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //---------------------------------------------------------------------------------------------------






    // Loop de renderização principal
    while (!glfwWindowShouldClose(window))
    {
        // Especificar os valores de vermelho, verde, azul e alfa, para limpar os buffers de cores
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Definir qual ou quais buffers precisam ser limpos
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        // Vincular Vertex Array Object
        glBindVertexArray(VAO);
        // Desenhar vertices a partir do VAO, e definir a primitiva GL_TRIANGLES
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Trazer os "back buffers" para frente
        glfwSwapBuffers(window);

        // Processar todos os eventos pendentes
        glfwPollEvents();
    }

    glfwDestroyWindow(window); // Opcional
    glfwTerminate(); // Terminar biblioteca GLFW

    return 0;
} 