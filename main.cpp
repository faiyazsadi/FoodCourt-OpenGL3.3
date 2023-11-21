//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "curve.h"
#include "model.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "stb_image.h"
#include "cube.h"
#include "sphere.h"
#include "Cylinder.h"
//#include "cylinder2.h"

#include <iostream>
#include <map>

using namespace std;

std::map<string, Cube> Cubes;
std::map<string, Cylinder> Cylinders;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);

glm::mat4 transform(glm::mat4 alTogether, glm::vec3 scale, glm::vec3 transform, glm::vec3 rotate);

void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void room(map<string, Cube> &Cubes, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void table(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void chair(map<string, Cube>& Cubes, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);

void food_court(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void cart1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void cart2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void round_table(Shader& lightingShader, glm::mat4 alTogether);
void round_chair(Shader& lightingShader, glm::mat4 alTogether);
void round_table_chair(Shader& lightingShader, glm::mat4 alTogether);

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

// camera
Camera camera(glm::vec3(30.0f, 20.0f, 100.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);


// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(30.0f,  5.50f,  40.0f), /// Spot
    glm::vec3(15.0f,  1.5f,  40.0f),   /// Point 1
    glm::vec3(20.0f,  50.5f,  40.5f), /// Sun
    glm::vec3(25.0f,  1.5f,  40.0f) // point 2
};


PointLight spotLight(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    1.0f, 1.0f, 1.0f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number // spot
);

PointLight pointLight1(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    1.0f, 1.0f, 1.0f,      // diffuse
    1.0f, 1.0f, 1.0f,         // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number // point 1
);

PointLight pointLight2(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    1.0f, 1.0f, 1.0f,      // diffuse
    1.0f, 1.0f, 1.0f,         // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number // point 2
);


PointLight dirLight(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    1.0f, 1.0f, 1.0f,      // diffuse
    1.0f, 1.0f, 1.0f,         // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number //directional
);

// light settings
bool onOffPointToggle = true;
bool onOffSpotToggle = true;
bool onOffDirectToggle = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

void genTexture(std::string diffPath, std::string specPath, std::string key, float shininess, float repX, float repY) {
    unsigned int DiffMap = loadTexture(diffPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int SpecMap = loadTexture(specPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(DiffMap, SpecMap, shininess, 0.0f, 0.0f, repX, repY);
    Cubes.insert({ key, cube });
}

void genTextureCylinder(float baseR = 1, float topR = 1, std::string diffPath = "", std::string specPath = "", std::string key = "", float shininess = 32, float repX = 0, float repY = 0
    
) {
    unsigned int DiffMap = loadTexture(diffPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int SpecMap = loadTexture(specPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cylinder table_top = Cylinder(baseR, topR, 1, 36, 1, false, 3,
        glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0),
        DiffMap, SpecMap, shininess);

    Cylinders.insert({ key, table_top });
}


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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderWithTexture.vs", "fragmentShaderWithTexture.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    
    // Model Loading 
    Shader modelShader("1.model_loading.vs", "1.model_loading.fs");
    //Shader modelShader("vertexShaderWithTexture.vs", "fragmentShaderWithTexture.fs");

    /*Model cooktop("./resources/cooktop/11633_Cooktop_v1_L3.obj");
    Model oven("./resources/oven/oven.obj");
    Model monitor("./resources/monitor/10120_LCD_Computer_Monitor_v01_max2011_it2.obj");
    Model microwave("./resources/microwave/10122_Microwave_Oven_v1_L3.obj");*/

    // Generate Textures
    genTexture("deez.png", "deez.png", "deez", 32.0f, 1.0f, 1.0f);
    genTextureCylinder(1, 1, "default_texture.png", "default_texture.png", "table_top", 32, 0, 0);
    genTextureCylinder(1, 1, "default_texture.png", "default_texture.png", "table_stand", 32, 0, 0);
    genTextureCylinder(1, .5, "default_texture.png", "default_texture.png", "table_bottom", 32, 0, 0);

    string defaultDiffPath1 = "default_texture.png";
    string defaultSpecPath1 = "default_texture.png";

    unsigned int defaultDiffMap1 = loadTexture(defaultDiffPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int defaultSpecMap1 = loadTexture(defaultSpecPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube default_cube = Cube(defaultDiffMap1, defaultSpecMap1, 32.0f, 0.0f, 0.0f, 10.0f, 10.0f);
    Cubes.insert({ "default_cube", default_cube });


    string diffuseMapPath1 = "back_wall.jpg";
    string specularMapPath1 = "back_wall.jpg";

    unsigned int diffMap1 = loadTexture(diffuseMapPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap1 = loadTexture(specularMapPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube back_wall = Cube(diffMap1, specMap1, 32.0f, 0.0f, 0.0f, 10.0f, 10.0f);
    Cubes.insert({ "back_wall", back_wall });

    // -------------------------------------------------------
    string diffuseMapPath2 = "back_wall.jpg";
    string specularMapPath2 = "back_wall.jpg";

    unsigned int diffMap2 = loadTexture(diffuseMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = loadTexture(specularMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube left_wall = Cube(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cubes["left_wall"] = left_wall;
    // -------------------------------------------------------
    string diffuseMapPath3 = "table_surf.jpg";
    string specularMapPath3 = "table_surf.jpg";

    unsigned int diffMap3 = loadTexture(diffuseMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap3 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube table_surf = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cubes["table_surf"] = table_surf;

    // -------------------------------------------------------
    string diffuseMapPath4 = "table_leg.jpg";
    string specularMapPath4 = "table_leg.jpg";

    unsigned int diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap4 = loadTexture(specularMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube table_leg = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cubes["table_leg"] = table_leg;

    // ------------------------------------------------------
    string diffuseMapPath5 = "chair_surf.jpg";
    string specularMapPath5 = "chair_surf.jpg";

    unsigned int diffMap5 = loadTexture(diffuseMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap5 = loadTexture(specularMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube chair_surf = Cube(diffMap5, specMap5, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cubes["chair_surf"] = chair_surf;

    //-------------------------------------------------------
    string diffuseMapPath6 = "chair_leg.jpg";
    string specularMapPath6 = "chair_leg.jpg";

    unsigned int diffMap6 = loadTexture(diffuseMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap6 = loadTexture(specularMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube chair_leg = Cube(diffMap6, specMap6, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cubes["chair_leg"] = chair_leg;


    // Cylinders

    /*Cylinder table_top = Cylinder(10, 10, 10, 36, 1, false, 3,
        glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0),
        defaultDiffMap1, defaultSpecMap1, 32);
    Cylinders["table_top"] = table_top;*/

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
   
    // Bezeir Object Control Points
    vector<float> controlPoints =
    {
        0.1300, 2.0200, 5.1000,
        -0.3600, 2.0250, 5.1000,
        -0.7350, 1.8650, 5.1000,
        -0.8300, 1.5400, 5.1000,
        -0.6350, 1.2200, 5.1000,
        -0.5250, 0.9850, 5.1000,
        -0.4950, 0.6400, 5.1000,
        -0.6550, 0.4600, 5.1000,
        -0.9600, 0.3300, 5.1000,
    };

    
    Curve obj = Curve(controlPoints, defaultDiffMap1, defaultSpecMap1, 32.0f);
    Sphere sphere = Sphere(5.0f, 36, 18, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 32, defaultDiffMap1, defaultSpecMap1, 0, 0, 1, 1);
    

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };

    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        

        // point light 1
        spotLight.setUpPointLight(lightingShader);
        // point light 2
        pointLight1.setUpPointLight(lightingShader);
        // point light 3
        dirLight.setUpPointLight(lightingShader);
        // point light 4
        pointLight2.setUpPointLight(lightingShader);


        

        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);
        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X * .3, scale_Y *.3, scale_Z * .3));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        lightingShader.setMat4("model", model);
      
        // room(Cubes, cubeVAO, lightingShader, tmp);
        food_court(cubeVAO, lightingShader, model);
        //cart1(cubeVAO, lightingShader, tmp);
        //cart2(cubeVAO, lightingShader, tmp);
        //sphere.drawSphereWithTexture(lightingShader, model);

        round_table_chair(lightingShader, model);
        
        glm::mat4 tempt = glm::mat4(1.0f);
        
        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        ourShader.setMat4("model", model);
        ourShader.setVec3("color", glm::vec3(1.0, 0.0, 0.0));

        

        glBindVertexArray(lightCubeVAO);
        //glBindVertexArray(shpareVAO);
        for (unsigned int i = 0; i <= 3; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            tempt = glm::translate(identityMatrix, glm::vec3(-20, -1, -30));
            ourShader.setMat4("model", model* tempt);
            if (i == 0)
            {
                if(spotLight.isOn())
                    ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
                else
                    ourShader.setVec3("color", glm::vec3(0.2f, 0.2f, 0.2f));
            }
            if (i == 1)
            {
                if (pointLight1.isOn())
                    ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
                else
                    ourShader.setVec3("color", glm::vec3(0.2f, 0.2f, 0.2f));
            }
            if (i == 2)
            {
                if (dirLight.isOn())
                    ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
                else
                    ourShader.setVec3("color", glm::vec3(0.2f, 0.2f, 0.2f));
            }
            if (i == 3)
            {
                if (pointLight2.isOn())
                    ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
                else
                    ourShader.setVec3("color", glm::vec3(0.2f, 0.2f, 0.2f));
            }

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLE_STRIP, 0, ind);
        }

        
        // Bezeir Curve Objects
        //obj.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 1.0f));

        // Loading Models
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X - 4.8, translate_Y + 1.2, translate_Z + 3));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X - 90), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z - 200), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X * .03, scale_Y *.03, scale_Z *.03));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        modelShader.use();
        modelShader.setMat4("projection", projection);
        modelShader.setMat4("view", view);
        modelShader.setMat4("model", model);
        //monitor.Draw(modelShader);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X + 3.3, translate_Y + 1.1, translate_Z + 1.5));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X - 90), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y - 90), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X * .05, scale_Y * .05, scale_Z * .05));
        model = translateMatrix * rotateZMatrix * rotateYMatrix * rotateXMatrix * scaleMatrix;
        modelShader.setMat4("model", model);
        //cooktop.Draw(modelShader);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X - 5, translate_Y - 1, translate_Z - 3));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X - 90), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + 90), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X * .02, scale_Y * .02, scale_Z * .02));
        model = translateMatrix * rotateZMatrix * rotateYMatrix * rotateXMatrix * scaleMatrix;
        modelShader.setMat4("model", model);
        //oven.Draw(modelShader);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X + 3.2, translate_Y + 1, translate_Z - 5));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X - 90), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X * .03, scale_Y * .02, scale_Z * .03));
        model = translateMatrix * rotateZMatrix * rotateYMatrix * rotateXMatrix * scaleMatrix;
        modelShader.setMat4("model", model);
        //microwave.Draw(modelShader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setVec3("material.emissive", glm::vec3(r/8, g/8, b/8));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}




void chair(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {
    float height = .1;
    float length = 1;
    float width = .4;
    float supporthight = .5;
    float supportwidth = .1;
    float supportlength = 0.1;

    // base
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length, height, length - .2));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 3));
    model = alTogether * translate * scale;
    //drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
    Cubes["chair_surf"].drawCubeWithTexture(lightingShader, model);

    // back
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, 0, 2.9));
    scale = glm::scale(model, glm::vec3(length, 1, .1));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 0));
    model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
    Cubes["chair_surf"].drawCubeWithTexture(lightingShader, model);

    //leg1
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, -.2, 3));
    scale = glm::scale(model, glm::vec3(supportlength, -supporthight, supportwidth));
    translate = glm::translate(model, glm::vec3(0.0, -0.5, 0.0));
    model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);
    Cubes["chair_leg"].drawCubeWithTexture(lightingShader, model);

    //leg2
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, -.2, 3.7));
    scale = glm::scale(model, glm::vec3(supportlength, -supporthight, supportwidth));
    translate = glm::translate(model, glm::vec3(0.0, -0.5, 0.0));
    model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);
    Cubes["chair_leg"].drawCubeWithTexture(lightingShader, model);

    //leg3
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(.9, -.2, 3));
    scale = glm::scale(model, glm::vec3(supportlength, -supporthight, supportwidth));
    translate = glm::translate(model, glm::vec3(0.0, -.5, 0.0));
    model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);
    Cubes["chair_leg"].drawCubeWithTexture(lightingShader, model);

    //leg4
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(.9, -.2, 3.7));
    scale = glm::scale(model, glm::vec3(supportlength, -supporthight, supportwidth));
    translate = glm::translate(model, glm::vec3(0.0, -.5, 0.0));
    model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);
    Cubes["chair_leg"].drawCubeWithTexture(lightingShader, model);
}





void room(map<string, Cube>& Cubes, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    /// floor
    float baseHeight = 0.01;
    float width = 8.0;
    float length = 8.5;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotateYMatrix;
    scale = glm::scale(model, glm::vec3(length + 4, baseHeight, length + 10));
    translate = glm::translate(model, glm::vec3(0, 0, 0));
    //model = alTogether * scale * translate;
    model = alTogether * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.565, 0.278, 0.173);
    Cubes["back_wall"].drawCubeWithTexture(lightingShader, model);


    /// left wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, 0, 0));
    scale = glm::scale(model, glm::vec3(baseHeight, width, length + 10));
    translate = glm::translate(model, glm::vec3(0, 0, 0));
    model = alTogether * translate2 * scale * translate;
    Cubes["back_wall"].drawCubeWithTexture(lightingShader, model);

    /// back wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, 0, 0));
    scale = glm::scale(model, glm::vec3(length + 4, width, baseHeight));
    translate = glm::translate(model, glm::vec3(0, 0, 0));
    model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, .059, 0.071, 0.102);
    Cubes["back_wall"].drawCubeWithTexture(lightingShader, model);

    float x = 0;
    for (int i = 0; i < 4; ++i) {
        // table
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate = glm::translate(model, glm::vec3(0.5, 0.5, 1 + x));
        rotateYMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = alTogether * translate * rotateYMatrix * glm::mat4(1.0f);
        table(cubeVAO, lightingShader, model);

        //chair
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate = glm::translate(model, glm::vec3(1, 0.5, -2.2 + x));
        rotateYMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = alTogether * translate * rotateYMatrix * glm::mat4(1.0f);
        chair(cubeVAO, lightingShader, model);

        //chair
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate = glm::translate(model, glm::vec3(2, 0.5, 6 + x));
        rotateYMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = alTogether * translate * rotateYMatrix * glm::mat4(1.0f);
        chair(cubeVAO, lightingShader, model);

        x += 3.5;
    }

    float z = 0;
    for (int i = 0; i < 2; ++i) {
        //  Large table
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate = glm::translate(model, glm::vec3(4.5, 0.5, 1 + z));
        scale = glm::scale(model, glm::vec3(1, 1, 2.5));
        rotateYMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = alTogether * translate * scale * rotateYMatrix * glm::mat4(1.0f);
        table(cubeVAO, lightingShader, model);

        //chair
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate = glm::translate(model, glm::vec3(6, 0.5, 9 + z));
        rotateYMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = alTogether * translate * rotateYMatrix * glm::mat4(1.0f);
        chair(cubeVAO, lightingShader, model);

        //chair
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate = glm::translate(model, glm::vec3(5, 0.5, -2.2 + z));
        rotateYMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = alTogether * translate * rotateYMatrix * glm::mat4(1.0f);
        chair(cubeVAO, lightingShader, model);

        x = 0;
        for (int i = 0; i < 3; ++i) {
            model = glm::mat4(1.0f);
            translate = glm::mat4(1.0f);
            translate = glm::translate(model, glm::vec3(9.8, 0.5, 1.5 + x + z));
            rotateYMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = alTogether * translate * rotateYMatrix * glm::mat4(1.0f);
            chair(cubeVAO, lightingShader, model);
            x += 1.5;
        }

        x = 0;
        for (int i = 0; i < 3; ++i) {
            model = glm::mat4(1.0f);
            translate = glm::mat4(1.0f);
            translate = glm::translate(model, glm::vec3(1, 0.5, 2.5 + x + z));
            rotateYMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = alTogether * translate * rotateYMatrix * glm::mat4(1.0f);
            chair(cubeVAO, lightingShader, model);
            x += 1.5;
        }
        z += 7;
    }
    
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime * 10);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime * 10);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime * 10);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime * 10);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    ////if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        pointLight1.turnOn(); 

    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        pointLight1.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        pointLight2.turnOn();

    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        pointLight2.turnOff();


    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        dirLight.turnOn();


    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
    {
        dirLight.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        spotLight.turnOn();


    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        spotLight.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {

        if(spotLight.isOn())
            spotLight.turnAmbientOn();
        if(pointLight1.isOn())
            pointLight1.turnAmbientOn();
        if (pointLight2.isOn())
            pointLight2.turnAmbientOn();
        if(dirLight.isOn())
            dirLight.turnAmbientOn();

    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {

        if (spotLight.isOn())
            spotLight.turnAmbientOff();
        if (pointLight1.isOn())
            pointLight1.turnAmbientOff();
        if (pointLight2.isOn())
            pointLight2.turnAmbientOff();
        if (dirLight.isOn())
            dirLight.turnAmbientOff();

    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {

        if (spotLight.isOn())
            spotLight.turnDiffuseOn();
        if (pointLight1.isOn())
            pointLight1.turnDiffuseOn();
        if (pointLight2.isOn())
            pointLight2.turnDiffuseOn();
        if (dirLight.isOn())
            dirLight.turnDiffuseOn();

    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {

        if (spotLight.isOn())
            spotLight.turnDiffuseOff();
        if (pointLight1.isOn())
            pointLight1.turnDiffuseOff();
        if (pointLight2.isOn())
            pointLight2.turnDiffuseOff();
        if (dirLight.isOn())
            dirLight.turnDiffuseOff();

    }


    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {

        if (spotLight.isOn())
            spotLight.turnSpecularOn();
        if (pointLight1.isOn())
            pointLight1.turnSpecularOn();
        if (pointLight2.isOn())
            pointLight2.turnSpecularOn();
        if (dirLight.isOn())
            dirLight.turnSpecularOn();
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        if (spotLight.isOn())
            spotLight.turnSpecularOff();
        if (pointLight1.isOn())
            pointLight1.turnSpecularOff();
        if (pointLight2.isOn())
            pointLight2.turnSpecularOff();
        if (dirLight.isOn())
            dirLight.turnSpecularOff();
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void cart2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {
    float length = 1;
    float height = 1;
    float width = 1;
    // name board
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height, width * .1));
    translate = glm::translate(model, glm::vec3(0.0, 5.0, 8));
    model = alTogether * translate * scale;
    Cubes["deez"].drawCubeWithTexture(lightingShader, model);

    // base
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height * .1, width * 8));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // back
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height * 6, width * .1));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // left
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * .10, height * 6, width * 8));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // right
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * .10, height * 6, width * 8));
    translate = glm::translate(model, glm::vec3(10.0, 0.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // right table top
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 1.5, height * .1, width * 8));
    translate = glm::translate(model, glm::vec3(0, 2.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // right table front
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * .10, height * 2, width * 8));
    translate = glm::translate(model, glm::vec3(1.4, 0.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // top
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height * .1, width * 8));
    translate = glm::translate(model, glm::vec3(0.0, 6.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // front
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height * 2, width * .1));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 8));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    //// front desk
    //model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //scale = glm::scale(model, glm::vec3(length * 10, height * .1, width * 1.5));
    //translate = glm::translate(model, glm::vec3(0.0, 2.0, 10));
    //model = alTogether * translate * scale;
    //Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // back table top
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height * .1, width * 1.5));
    translate = glm::translate(model, glm::vec3(0.0, 2.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // back table front
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height * 2, width * .1));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 1));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);
}

void cart1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {
    float length = 1;
    float height = 1;
    float width = 1;
    // name board
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height, width * .1));
    translate = glm::translate(model, glm::vec3(0.0, 5.0, 8));
    model = alTogether * translate * scale;
    Cubes["deez"].drawCubeWithTexture(lightingShader, model);

    // base
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height * .1, width * 8));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // back
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height * 6, width * .1));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // left
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * .10, height * 6, width * 8));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // right
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * .10, height * 6, width * 8));
    translate = glm::translate(model, glm::vec3(10.0, 0.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // right table top
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 1.5, height * .1, width * 8));
    translate = glm::translate(model, glm::vec3(8.5, 2.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // right table front
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * .10, height * 2, width * 8));
    translate = glm::translate(model, glm::vec3(9.0, 0.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // top
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height * .1, width * 8));
    translate = glm::translate(model, glm::vec3(0.0, 6.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // front
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height * 2, width * .1));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 8));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // front desk
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height * .1, width * 1.5));
    translate = glm::translate(model, glm::vec3(0.0, 2.0, 8));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // back table top
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height * .1, width * 1.5));
    translate = glm::translate(model, glm::vec3(0.0, 2.0, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // back table front
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height * 2, width * .1));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 1));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);
}

glm::mat4 transform(glm::mat4 alTogether, glm::vec3 sc, glm::vec3 tr, glm::vec3 ro) {
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    glm::mat4 rotateXMatrix = glm::mat4(1.0f);
    glm::mat4 rotateYMatrix = glm::mat4(1.0f);
    glm::mat4 rotateZMatrix = glm::mat4(1.0f);

    scale = glm::scale(model, sc);
    translate = glm::translate(model, tr);
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(ro.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(ro.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(ro.z), glm::vec3(0.0f, 0.0f, 1.0f));
    rotate = rotateXMatrix * rotateYMatrix * rotateZMatrix;

    model = alTogether * translate * rotate * scale;
    return model;
}

void food_court(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {
    float length = 1;
    float height = 1;
    float width = 1;

    // base
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    glm::mat4 rotateXMatrix = glm::mat4(1.0f);
    glm::mat4 rotateYMatrix = glm::mat4(1.0f);
    glm::mat4 rotateZMatrix = glm::mat4(1.0f);

    scale = glm::scale(model, glm::vec3(length * 100, height * .1, width * 100));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // left wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * .1, height * 30, width * 100));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // right wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * .1, height * 30, width * 100));
    translate = glm::translate(model, glm::vec3(100.0, 0.0, 0.0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);


    // back wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 100, height * 30, width * .1));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);


    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 2, height * 2, width * 2));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 100.0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + 90), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    rotate = rotateXMatrix * rotateYMatrix * rotateZMatrix;


    for (int i = 0; i < 3; ++i) {
        model = transform(alTogether, 
            glm::vec3(length * 2, height * 2, width * 2),
            glm::vec3(0.0, 0.0, 100.0 - i * 20.4), 
            glm::vec3(0, 90, 0));
        
        cart2(cubeVAO, lightingShader, model);

        model = transform(alTogether, 
            glm::vec3(length * 2, height * 2, width * 2),
            glm::vec3(100.0, 0.0, 80.0 - i * 20.4),
            glm::vec3(0, 270, 0));

        cart1(cubeVAO, lightingShader, model);
    }

    model = transform(alTogether,
        glm::vec3(1, 1, 1),
        glm::vec3(40.0, 7.1, 100.0),
        glm::vec3(0, 0, 0));
    for (int i = 0; i < 4; ++i) {
        model = transform(alTogether,
            glm::vec3(.8, .8, .8),
            glm::vec3(30.0, 7.1, 90.0 - i * 20),
            glm::vec3(0, 0, 0));
        round_table_chair(lightingShader, model);
    }

    for (int i = 0; i < 4; ++i) {
        model = transform(alTogether,
            glm::vec3(.8, .8, .8),
            glm::vec3(70.0, 7.1, 90.0 - i * 20),
            glm::vec3(0, 0, 0));
        round_table_chair(lightingShader, model);
    }
    
}


void table(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{

    /*float hight = 0.04;
    float length = 0.5;
    float width = 0.3;
    float supporthight = 0.5;
    float supportwidth = 0.04;
    float supportlength = 0.04;*/

    float height = .1;
    float length = 2;
    float width = .7;
    float supporthight = 1;
    float supportwidth = .1;
    float supportlength = 0.1;

    // base
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length, height, length));
    translate = glm::translate(model, glm::vec3(0.0, supporthight + 4, 0.0));
    model = alTogether * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
    Cubes["table_surf"].drawCubeWithTexture(lightingShader, model);

    //leg1
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, 0.0, 0));
    scale = glm::scale(model, glm::vec3(supportlength, -supporthight, supportwidth));
    translate = glm::translate(model, glm::vec3(0.0, -0.5, 0.0));
    model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);
    Cubes["table_leg"].drawCubeWithTexture(lightingShader, model);

    //leg2
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, 0.0, length - .1));
    scale = glm::scale(model, glm::vec3(supportlength, -supporthight, supportwidth));
    translate = glm::translate(model, glm::vec3(0.0, -0.5, 0.0));
    model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);
    Cubes["table_leg"].drawCubeWithTexture(lightingShader, model);

    //leg3
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(length - supportwidth, 0.0, length - .1));
    scale = glm::scale(model, glm::vec3(supportlength, -supporthight, supportwidth));
    translate = glm::translate(model, glm::vec3(0.0, -.5, 0.0));
    model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);
    Cubes["table_leg"].drawCubeWithTexture(lightingShader, model);

    //leg4
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(length - supportwidth, 0.0, supportlength - .1));
    scale = glm::scale(model, glm::vec3(supportlength, -supporthight, supportwidth));
    translate = glm::translate(model, glm::vec3(0.0, -.5, 0.0));
    model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);
    Cubes["table_leg"].drawCubeWithTexture(lightingShader, model);
}

void round_table(Shader& lightingShader, glm::mat4 alTogether) {
    glm::mat4 model = transform(alTogether, glm::vec3(5, 5, .2), glm::vec3(0, 0, 0), glm::vec3(90, 0, 0));
    Cylinders["table_top"].draw(lightingShader, model);

    model = transform(alTogether, glm::vec3(.3, 3.5, .3), glm::vec3(Cylinders["table_top"].getTopRadius() - .7, -3.5, Cylinders["table_top"].getTopRadius() - .7), glm::vec3(0, 0, 0));
    Cylinders["table_stand"].draw(lightingShader, model);

    model = transform(alTogether, glm::vec3(2.5, 2.5, .4), glm::vec3(0, -6.9, 0), glm::vec3(-90, 0, 0));
    Cylinders["table_bottom"].draw(lightingShader, model);
}

void round_chair(Shader& lightingShader, glm::mat4 alTogether) {
    glm::mat4 model = transform(alTogether, glm::vec3(.5, .5, .5), glm::vec3(0, -3.5, 6), glm::vec3(0, 0, 0));
    round_table(lightingShader, model);

    model = transform(alTogether, glm::vec3(.5, .5, .5), glm::vec3(0, -3.5, -6), glm::vec3(0, 0, 0));
    round_table(lightingShader, model);
}


void round_table_chair(Shader& lightingShader, glm::mat4 alTogether) {
    round_table(lightingShader, alTogether);
    round_chair(lightingShader, alTogether);
}