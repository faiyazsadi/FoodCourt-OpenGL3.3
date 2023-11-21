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
#include <unordered_map>

using namespace std;

std::map<string, Cube> Cubes;
std::map<string, Cylinder> Cylinders;
std::unordered_map<string, Model> Models;

unsigned int diffMap1, diffMap2, diffMap3, diffMap4, diffMap5, diffMap6;
unsigned int specMap1, specMap2, specMap3, specMap4, specMap5, specMap6;

unsigned int ovenMap1, ovenMap2, grillMap;

unsigned int mp1, mp2, mp3, mp4, mp5, mp6;
float angP1, angP2, angP3, angP4, angP5, angP6;
float y2, y3, y4;

vector<float>glassp{
    0.0900, 1.8350, 5.1000,
0.0050, 1.8350, 5.1000,
-0.0850, 1.8400, 5.1000,
-0.1650, 1.8300, 5.1000,
-0.2950, 1.8300, 5.1000,
-0.3700, 1.8300, 5.1000,
-0.5400, 1.8350, 5.1000,
-0.4750, 1.7750, 5.1000,
-0.4100, 1.7350, 5.1000,
-0.3550, 1.6950, 5.1000,
-0.3300, 1.6100, 5.1000,
-0.3150, 1.5150, 5.1000,
-0.3200, 1.4400, 5.1000,
-0.3250, 1.3450, 5.1000,
-0.3900, 1.2200, 5.1000,
-0.4400, 1.0550, 5.1000,
-0.5300, 0.9800, 5.1000,
-0.5800, 0.8300, 5.1000,
-0.5750, 0.7000, 5.1000,
-0.6000, 0.6200, 5.1000,
-0.6000, 0.5500, 5.1000,
-0.5950, 0.4350, 5.1000,
-0.5650, 0.3050, 5.1000,
-0.5450, 0.2300, 5.1000,
-0.5300, 0.0300, 5.1000,
-0.5350, 0.1200, 5.1000,
};

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
    -0.9600, 0.3300, 5.1000
};

vector<float> ctrlBowl1 =
{
    0.2350, 1.8650, 5.1000,
    0.0800, 1.8850, 5.1000,
    -0.1300, 1.9000, 5.1000,
    -0.3100, 1.8450, 5.1000,
    -0.4000, 1.7000, 5.1000
};

vector<float> ctrlVase = {
0.0550, 2.0150, 5.1000,
-0.0700, 2.0250, 5.1000,
-0.2750, 2.0300, 5.1000,
-0.4150, 1.9400, 5.1000,
-0.4250, 1.7900, 5.1000,
-0.3300, 1.5950, 5.1000,
-0.2450, 1.4450, 5.1000,
-0.2150, 1.3100, 5.1000,
-0.2150, 1.1900, 5.1000,
-0.2050, 1.0800, 5.1000,
-0.2100, 0.9350, 5.1000,
-0.2300, 0.7800, 5.1000,
-0.2850, 0.6750, 5.1000
};

vector<float> ctrlBowl2 = {
    0.2450, 2.0050, 5.1000,
    0.1200, 2.0050, 5.1000,
    0.0200, 2.0100, 5.1000,
    -0.1300, 2.0300, 5.1000,
    -0.2800, 2.0150, 5.1000,
    -0.3850, 2.0150, 5.1000,
    -0.3900, 1.9200, 5.1000,
    -0.3900, 1.7700, 5.1000,
    -0.3800, 1.6050, 5.1000
};
vector<float> ctrlPlate = {
    -0.2500, 1.7000, 5.1000,
    -0.5150, 1.5950, 5.1000,
    -0.5750, 1.3700, 5.1000,
    -0.4050, 1.2300, 5.1000,
    -0.2250, 1.1850, 5.1000
};

vector<float> ctrlFlatPlate = {
    -0.2500, 1.7000, 5.1000,
    -0.5150, 1.5950, 5.1000,
    -0.5750, 1.3700, 5.1000,
    -0.4050, 1.2300, 5.1000,
    -0.2250, 1.1850, 5.1000
};

vector<float> ctrlDecor1 = {
    -0.1500, 1.9050, 5.1000,
    -0.3650, 1.8500, 5.1000,
    -0.4700, 1.7200, 5.1000,
    -0.5250, 1.5600, 5.1000,
    -0.4650, 1.4050, 5.1000,
    -0.3400, 1.3100, 5.1000,
    -0.1900, 1.2950, 5.1000
};

vector<float> ctrlDecor2 = {
    -0.0700, 2.0750, 5.1000,
    -0.0950, 1.9600, 5.1000,
    -0.1250, 1.8100, 5.1000,
    -0.2000, 1.6300, 5.1000,
    -0.2300, 1.4650, 5.1000,
    -0.2050, 1.2600, 5.1000,
    -0.1550, 1.1200, 5.1000,
    -0.0950, 0.8800, 5.1000
};
vector<float> ctrlDecor3 = {

    -0.1900, 2.0200, 5.1000,
    -0.5100, 2.0050, 5.1000,
    -0.7400, 1.8500, 5.1000,
    -0.7750, 1.5200, 5.1000,
    -0.6850, 1.2250, 5.1000,
    -0.4800, 1.0650, 5.1000,
    -0.2800, 1.0100, 5.1000
};

//Curve decor1(ctrlDecor1, diffMap1, diffMap1, 1.0f);
//Curve decor2(ctrlDecor2, diffMap1, diffMap1, 1.0f);
//Curve decor3(ctrlDecor3, diffMap1, diffMap1, 1.0f);
//Curve aa(ctrlPlate, diffMap1, diffMap1, 1);
//Curve bowl1(ctrlBowl1, diffMap1, diffMap1, 1.0f);
//Curve bowl2(ctrlBowl2, diffMap1, diffMap1, 1.0f);
//Curve vase(ctrlVase, diffMap1, diffMap1, 1.0f);
//Curve plate(ctrlPlate, diffMap1, diffMap1, 1.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);

glm::mat4 transform(glm::mat4 alTogether, glm::vec3 scale, glm::vec3 transform, glm::vec3 rotate);

void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void room(map<string, Cube> &Cubes, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void table(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void chair(map<string, Cube>& Cubes, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);

void food_court(unsigned int& cubeVAO, Shader& lightingShader, Shader& modelShader, glm::mat4 alTogether);
void cart1(unsigned int& cubeVAO, Shader& lightingShader, Shader& modelShader, glm::mat4 alTogether);
void cart2(unsigned int& cubeVAO, Shader& lightingShader, Shader& modelShader, glm::mat4 alTogether);
void round_table(Shader& lightingShader, glm::mat4 alTogether);
void round_chair(Shader& lightingShader, glm::mat4 alTogether);
void round_table_chair(Shader& lightingShader, glm::mat4 alTogether);
void decoration(Shader& lightingShader, Shader& modelShader, glm::mat4 alTogether);

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
Camera camera(glm::vec3(5.0f, 2.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

// Models
//Shader modelShader("1.model_loading.vs", "1.model_loading.fs");
//Model table_chair_model("./resources/table/Modern Elegant Chair and Table (OBJ).obj");
//Model table_chair_model("./resources/microwave/10122_Microwave_Oven_v1_L3.obj");

// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(30.0f,  5.50f,  30.0f), /// Spot
    glm::vec3(15.0f,  1.5f,  40.0f),   /// Point 1
    glm::vec3(20.0f,  50.5f,  40.5f), /// Sun
    glm::vec3(25.0f,  1.5f,  40.0f), // point 2

    glm::vec3(25.0f,  10.5f,  40.0f), // disco 1
    glm::vec3(25.0f,  1.5f,  40.0f), // disco 2
    glm::vec3(25.0f,  5.5f,  40.0f), // disco 3
    glm::vec3(25.0f,  7.5f,  40.0f) // disco 4
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

PointLight disco1(

    pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    1.0f, 1.0f, 1.0f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    5       // light number // spot
);

PointLight disco2(

    pointLightPositions[5].x, pointLightPositions[5].y, pointLightPositions[5].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    1.0f, 1.0f, 1.0f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    6       // light number // spot
);

PointLight disco3(

    pointLightPositions[6].x, pointLightPositions[6].y, pointLightPositions[7].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    1.0f, 1.0f, 1.0f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    7       // light number // spot
);

PointLight disco4(

    pointLightPositions[7].x, pointLightPositions[7].y, pointLightPositions[7].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    1.0f, 1.0f, 1.0f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    8       // light number // spot
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

void drawModel(Model& model, glm::mat4 alTogether);

glm::mat4 transform2(float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, a;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(tx, ty, tz));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(sx, sy, sz));
    a = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    return a;
}

float fridge_door2, fridge_door1, fridge_door_open2, fridge_door_open;
bool box2 = false;

void fridge(Cube& cube, Shader& lightingShader, Shader& lightingShader2, glm::mat4 model)
{

    //cube.setMaterialisticProperty(glm::vec3(0.8, 0.792, 0.792));
    cube.setTextureProperty(diffMap1, diffMap1, 32);
    glm::mat4 a = transform2(0, 0, -2.5, 0, 0, 0, 1.8 * 2, 3.2 * 2, 0.1 * 2);
    //cube.drawCubeWithMaterialisticProperty(lightingShader2, model * a);
    cube.drawCubeWithTexture(lightingShader, model * a);

    a = transform2(0, 0, -2.5, 0, 0, 0, 0.1 * 2, 3.2 * 2, 1.8 * 2);
    //cube.drawCubeWithMaterialisticProperty(lightingShader2, model * a);
    cube.drawCubeWithTexture(lightingShader, model * a);

    a = transform2(.9, 0, -2.5, 0, 0, 0, 0.1 * 2, 3.2 * 2, 1.8 * 2);
    //cube.drawCubeWithMaterialisticProperty(lightingShader2, model * a);
    cube.drawCubeWithTexture(lightingShader, model * a);

    a = transform2(0, 0, -2.5, 0, 0, 0, 1.8 * 2, 0.1 * 2, 1.8 * 2);
    //cube.drawCubeWithMaterialisticProperty(lightingShader2, model * a);
    cube.drawCubeWithTexture(lightingShader, model * a);

    a = transform2(0, 1.6, -2.5, 0, 0, 0, 1.9 * 2, 0.1 * 2, 1.8 * 2);
    //cube.drawCubeWithMaterialisticProperty(lightingShader2, model * a);
    cube.drawCubeWithTexture(lightingShader, model * a);

    a = transform2(0, 1.1, -2.5, 0, 0, 0, 1.8 * 2, 0.1 * 2, 1.8 * 2);
    //cube.drawCubeWithMaterialisticProperty(lightingShader2, model * a);
    cube.drawCubeWithTexture(lightingShader, model * a);

}

void fridgedoor(Cube& cube, Shader& lightingShader, Shader& lightingShader2, glm::mat4 model)
{

    cube.setMaterialisticProperty(glm::vec3(0.8, 0.792, 0.792));
    cube.setTextureProperty(diffMap1, diffMap1, 32.0f);
    glm::mat4 a = transform2(0, 0, -1.6, 0, -fridge_door_open, 0, 1.9 * 2, 2.2 * 2, 0.11 * 2);
    cube.drawCubeWithTexture(lightingShader, model * a);



    cube.setTextureProperty(diffMap1, diffMap1, 32.0f);
    a = transform2(0, 1.15, -1.6, 0, -fridge_door_open2, 0, 1.9 * 2, 1 * 2, 0.11 * 2);
    cube.drawCubeWithTexture(lightingShader, model * a);


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
    glfwSetKeyCallback(window, key_callback);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    Shader lightingShaderNoTexture("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    //Shader modelShader("vertexShaderWithTexture.vs", "fragmentShaderWithTexture.fs");
    Shader lightingShader("vertexShaderWithTexture.vs", "fragmentShaderWithTexture.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    Shader modelShader("1.model_loading.vs", "1.model_loading.fs");
    
    // Model 

    //Model backpack("./resources/backpack/backpack.obj");
    
     //Model rock("./resources/rock/rock.obj");
    Model table_chair_model("./resources/table/Modern Elegant Chair and Table (OBJ).obj");
    Model sofa("./resources/sofa/sofa.obj");
    Model woodswing("./resources/woodswing/Models and Textures/woodswing.obj");
    Models.insert({ "table_chair_model", table_chair_model });
    Models.insert({ "sofa", sofa });
    Models.insert({ "woodswing", woodswing });
    Model cooktop("./resources/cooktop/11633_Cooktop_v1_L3.obj");
    Models.insert({ "cooktop", cooktop });
    Model blender("./resources/blender/11628_kitchen_blender_v1_l2.obj");
    Models.insert({ "blender", blender });
    //Model wine("./resources/wine/Wine_bottle.obj");
    //Models.insert({ "wine", wine });
    Model microwave("./resources/microwave/10122_Microwave_Oven_v1_L3.obj");
    Models.insert({ "microwave", microwave });
    Model walloven("./resources/walloven/oven.obj");
    Models.insert({ "walloven", walloven });
    Model cooker("./resources/cooker/fogão_OBJ.obj");
    Models.insert({ "cooker", cooker });

    Model shrimp("./resources/shrimp/13560_Pot_of_Shrimp_Gumbo_v1_L3.obj");
    Models.insert({ "shrimp", shrimp });

    // Fire animation texture
//vector<unsigned int> texMap;
//unsigned int DiffMap;
//unsigned int SpecMap;
//for (int i = 0; i < 300; ++i) {
//    string diffPath = "./textures/fire/" + to_string(i + 1) + ".png";
//    DiffMap = loadTexture(diffPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
//    SpecMap = loadTexture(diffPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
//    texMap.push_back(DiffMap);
//    texMap.push_back(SpecMap);
//}
//Cube cube = Cube(texMap, DiffMap, SpecMap, 32, 0.0f, 0.0f, 1.0f, 1.0f);
//Cubes.insert({ "fire_animation", cube });

    // Generate Textures
    genTexture("deez.png", "deez.png", "deez", 32.0f, 1.0f, 1.0f);
    genTexture("./textures/vending/vending.jpg", "./textures/vending/vending.jpg", "vending", 32.0f, 1.0f, 1.0f);
    genTexture("./textures/starry/starry.jpg", "./textures/starry/starry.jpg", "starry", 32.0f, 1.0f, 1.0f);
    genTexture("./textures/abstract/abs1.jpg", "./textures/abstract/abs1.jpg", "abs1", 32.0f, 1.0f, 1.0f);

    genTexture("./textures/menu/p1.jpg", "./textures/menu/p1.jpg", "mp1", 32.0, 1.0, 1.0f);
    genTexture("./textures/menu/p2.jpeg", "./textures/menu/p2.jpeg", "mp2", 32.0, 1.0, 1.0f);
    genTexture("./textures/menu/p3.jpg", "./textures/menu/p3.jpg", "mp3", 32.0, 1.0, 1.0f);
    genTexture("./textures/menu/p4.png", "./textures/menu/p4.png", "mp4", 32.0, 1.0, 1.0f);
    genTexture("./textures/menu/p5.jpg", "./textures/menu/p5.jpg", "mp5", 32.0, 1.0, 1.0f);
    genTexture("./textures/menu/p6.png", "./textures/menu/p6.png", "mp6", 32.0, 1.0, 1.0f);

    genTextureCylinder(1, 1, "default_texture.png", "default_texture.png", "table_top", 32, 0, 0);
    genTextureCylinder(1, 1, "default_texture.png", "default_texture.png", "table_stand", 32, 0, 0);
    genTextureCylinder(1, .5, "default_texture.png", "default_texture.png", "table_bottom", 32, 0, 0);


    string ovenPath1 = "./textures/oven/oven.jpg";
    string ovenPath2 = "./textures/oven/oven2.jpg";
    ovenMap1 = loadTexture(ovenPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    ovenMap2 = loadTexture(ovenPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    string grillPath = "./textures/grill/grill.jpg";
    grillMap = loadTexture(grillPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    string defaultDiffPath1 = "default_texture.png";
    string defaultSpecPath1 = "default_texture.png";

    unsigned int defaultDiffMap1 = loadTexture(defaultDiffPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int defaultSpecMap1 = loadTexture(defaultSpecPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube default_cube = Cube(defaultDiffMap1, defaultSpecMap1, 32.0f, 0.0f, 0.0f, 10.0f, 10.0f);
    Cubes.insert({ "default_cube", default_cube });



    string diffuseMapPath1 = "back_wall.jpg";
    string specularMapPath1 = "back_wall.jpg";

    diffMap1 = loadTexture(diffuseMapPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap1 = loadTexture(specularMapPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube back_wall = Cube(diffMap1, specMap1, 32.0f, 0.0f, 0.0f, 10.0f, 10.0f);
    Cubes.insert({ "back_wall", back_wall });

    Cube cube(diffMap1, specMap1, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // -------------------------------------------------------
    string diffuseMapPath2 = "back_wall.jpg";
    string specularMapPath2 = "back_wall.jpg";

    diffMap2 = loadTexture(diffuseMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap2 = loadTexture(specularMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube left_wall = Cube(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cubes["left_wall"] = left_wall;
    // -------------------------------------------------------
    string diffuseMapPath3 = "table_surf.jpg";
    string specularMapPath3 = "table_surf.jpg";

    diffMap3 = loadTexture(diffuseMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap3 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube table_surf = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cubes["table_surf"] = table_surf;

    // -------------------------------------------------------
    string diffuseMapPath4 = "table_leg.jpg";
    string specularMapPath4 = "table_leg.jpg";

    diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap4 = loadTexture(specularMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube table_leg = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cubes["table_leg"] = table_leg;

    // ------------------------------------------------------
    string diffuseMapPath5 = "chair_surf.jpg";
    string specularMapPath5 = "chair_surf.jpg";

    diffMap5 = loadTexture(diffuseMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap5 = loadTexture(specularMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube chair_surf = Cube(diffMap5, specMap5, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cubes["chair_surf"] = chair_surf;

    //-------------------------------------------------------
    string diffuseMapPath6 = "chair_leg.jpg";
    string specularMapPath6 = "chair_leg.jpg";

    diffMap6 = loadTexture(diffuseMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap6 = loadTexture(specularMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube chair_leg = Cube(diffMap6, specMap6, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cubes["chair_leg"] = chair_leg;

    unsigned int a = loadTexture("table_surf.jpeg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap7 = loadTexture(specularMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    //Cube chair_leg = Cube(a, a, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
   // Cubes["chair_leg"] = chair_leg;
    // Cylinders

    /*Cylinder table_top = Cylinder(10, 10, 10, 36, 1, false, 3,
        glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0),
        defaultDiffMap1, defaultSpecMap1, 32);
    Cylinders["table_top"] = table_top;*/

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
   
    // Bezeir Object Control Points
    


    

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
        glClear(0x00004000 | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = transform(glm::mat4(1.0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
        

        /*decor1.draw(lightingShader, model, glm::vec3(1.0f, 0.0f, 1.0f));*/

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        modelShader.use();
        modelShader.setMat4("projection", projection);
        modelShader.setMat4("view", view);
        
        for (int i = 0; i < 4; ++i) {
            model = transform(glm::mat4(1.0f),
                glm::vec3(.015, .015, .015),
                glm::vec3(13.0, 0.0, 28.0 - i * 6),
                glm::vec3(0, 90, 0));

            modelShader.setMat4("model", model);
            //table_chair_model.Draw(modelShader);
        }

        for (int i = 0; i < 4; ++i) {
            model = transform(glm::mat4(1.0f),
                glm::vec3(.015, .015, .015),
                glm::vec3(18.0, 0.0, 28.0 - i * 6),
                glm::vec3(0, 90, 0));
            modelShader.setMat4("model", model);
            //table_chair_model.Draw(modelShader); 
        }

        

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

        //disco1.setUpPointLight(lightingShader);
        //disco2.setUpPointLight(lightingShader);
        //disco3.setUpPointLight(lightingShader);
        //disco4.setUpPointLight(lightingShader);

        model = transform(glm::mat4(1.0f), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
        lightingShaderNoTexture.use();
        lightingShaderNoTexture.setMat4("projection", projection);
        lightingShaderNoTexture.setMat4("view", view);


       /* model = transform2(0, 0, 0, 0, 0, 0, 1, 1, 1);
        lightingShaderNoTexture.setMat4("model", model);
        fridge(cube, lightingShader, lightingShaderNoTexture, model);
        fridgedoor(cube, lightingShader, lightingShaderNoTexture, model);*/

        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        
        lightingShader.setMat4("projection", projection);
        // camera/view transformation

        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X * .1, scale_Y *.1, scale_Z * .1));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        lightingShader.setMat4("model", model);
        //decoration(lightingShader, modelShader, model);
        // room(Cubes, cubeVAO, lightingShader, tmp);
        food_court(cubeVAO, lightingShader, modelShader, model);
        //cart1(cubeVAO, lightingShader, modelShader, model);
        //cart2(cubeVAO, lightingShader, modelShader, model);
        //sphere.drawSphereWithTexture(lightingShader, model);
        
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

        
        modelShader.use();
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
        float dist = camera.Position.x - .67;
        dist *= dist;
        dist *= camera.Position.y - .51;
        dist *= camera.Position.y - .51;
        dist *= camera.Position.z - 1.16;
        dist *= camera.Position.z - 1, 16;
        dist = sqrt(dist);

        if (dist <= 20.0f) {
            std::cout << "HERE" << std::endl;
            angP1 = 180;
        }
        
    }
    if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
        float dist = camera.Position.x - .67;
        dist *= dist;
        dist *= camera.Position.y - .51;
        dist *= camera.Position.y - .51;
        dist *= camera.Position.z - 1.16;
        dist *= camera.Position.z - 1, 16;
        dist = sqrt(dist);

        if (dist <= 20.0f) {
            std::cout << "HERE" << std::endl;
            angP2 = 180;
            y2 = .02;
        }

    }
    if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
        float dist = camera.Position.x - .67;
        dist *= dist;
        dist *= camera.Position.y - .51;
        dist *= camera.Position.y - .51;
        dist *= camera.Position.z - 1.16;
        dist *= camera.Position.z - 1, 16;
        dist = sqrt(dist);

        if (dist <= 20.0f) {
            std::cout << "HERE" << std::endl;
            angP3 = 180;
            y3 = .03;
        }

    }
    if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
        float dist = camera.Position.x - .67;
        dist *= dist;
        dist *= camera.Position.y - .51;
        dist *= camera.Position.y - .51;
        dist *= camera.Position.z - 1.16;
        dist *= camera.Position.z - 1, 16;
        dist = sqrt(dist);

        if (dist <= 20.0f) {
            std::cout << "HERE" << std::endl;
            angP4 = 180;
            y4 = .04;
        }

    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        float dist = camera.Position.x - .67;
        dist *= dist;
        dist *= camera.Position.y - .51;
        dist *= camera.Position.y - .51;
        dist *= camera.Position.z - 1.16;
        dist *= camera.Position.z - 1, 16;
        dist = sqrt(dist);

        if (dist <= 20.0f) {
            std::cout << "HERE" << std::endl;
            angP1 = angP2 = angP3 = angP4 = angP5 = angP6 = 0;
            y2 = y3 = y4 = 0;
        }

    }
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime * 2);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime * 2);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime * 2);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime * 2);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.01;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.01;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.01;
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

void cart2(unsigned int& cubeVAO, Shader& lightingShader, Shader& modelShader, glm::mat4 alTogether) {
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
    
    // curve objects for right bottom shelf
    Curve bowl1(ctrlBowl1, diffMap1, diffMap1, 1.0f);
    model = transform(alTogether, glm::vec3(.5, .5, .5), glm::vec3(9.7, 4.55, 7), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));
    model = transform(alTogether, glm::vec3(.5, .5, .5), glm::vec3(9.7, 4.65, 7), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));
    model = transform(alTogether, glm::vec3(.5, .5, .5), glm::vec3(9.7, 4.75, 7), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));

    Curve plate(ctrlPlate, diffMap1, diffMap1, 1.0f);
    model = transform(alTogether, glm::vec3(.8, .8, .5), glm::vec3(9.7, 5.1, 6.4), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));
    model = transform(alTogether, glm::vec3(.8, .8, .5), glm::vec3(9.7, 5.2, 6.4), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));
    model = transform(alTogether, glm::vec3(.8, .8, .5), glm::vec3(9.7, 5.3, 6.4), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));

    Curve vase(ctrlVase, diffMap1, diffMap1, 1.0f);
    model = transform(alTogether, glm::vec3(.6, .4, .6), glm::vec3(9.6, 4.4, 5.8), glm::vec3(180, 0, 0));
    vase.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));
    model = transform(alTogether, glm::vec3(.6, .4, .6), glm::vec3(9.6, 4.4, 5.4), glm::vec3(180, 0, 0));
    vase.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));
    model = transform(alTogether, glm::vec3(.6, .4, .6), glm::vec3(9.6, 4.4, 5.0), glm::vec3(180, 0, 0));
    vase.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));


    model = transform(alTogether, glm::vec3(1.2, 1.2, .5), glm::vec3(9.5, 5.9, 4.5), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));
    model = transform(alTogether, glm::vec3(1.2, 1.2, .5), glm::vec3(9.5, 5.9, 4.1), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));
    model = transform(alTogether, glm::vec3(1.2, 1.2, .5), glm::vec3(9.5, 5.9, 3.7), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));

    Curve glass(glassp, diffMap1, diffMap1, 1.0f);
    model = transform(alTogether, glm::vec3(.1, .13, .1), glm::vec3(9.5, 3.9, 3.1), glm::vec3(180, 0, 0));
    glass.draw(lightingShader, model, glm::vec3(1, 1, 1));
    model = transform(alTogether, glm::vec3(.1, .13, .1), glm::vec3(9.5, 3.9, 2.8), glm::vec3(180, 0, 0));
    glass.draw(lightingShader, model, glm::vec3(1, 1, 1));
    model = transform(alTogether, glm::vec3(.1, .13, .1), glm::vec3(9.5, 3.9, 2.4), glm::vec3(180, 0, 0));
    glass.draw(lightingShader, model, glm::vec3(1, 1, 1));
    model = transform(alTogether, glm::vec3(.1, .13, .1), glm::vec3(9.5, 3.9, 2.0), glm::vec3(180, 0, 0));
    glass.draw(lightingShader, model, glm::vec3(1, 1, 1));
    model = transform(alTogether, glm::vec3(.1, .13, .1), glm::vec3(9.5, 3.9, 1.6), glm::vec3(180, 0, 0));
    glass.draw(lightingShader, model, glm::vec3(1, 1, 1));

    // oven 1
    Cube oven;
    model = transform(alTogether, glm::vec3(1.5, 1, 1), glm::vec3(8, 2, 0), glm::vec3(0, 0, 0));
    oven.drawCubeWithTexture(lightingShader, model);
    model = transform(alTogether, glm::vec3(1.5, 1, .01), glm::vec3(8, 2, 1.01), glm::vec3(0, 0, 0));
    oven.setTextureProperty(ovenMap1, ovenMap1, 32.0);
    oven.drawCubeWithTexture(lightingShader, model);

    // oven 2
    model = transform(alTogether, glm::vec3(1.5, 1, 1), glm::vec3(0.5, 2, 0), glm::vec3(0, 0, 0));
    oven.drawCubeWithTexture(lightingShader, model);
    model = transform(alTogether, glm::vec3(1.5, 1, .01), glm::vec3(0.5, 2, 1.01), glm::vec3(0, 0, 0));
    oven.setTextureProperty(ovenMap2, ovenMap2, 32.0);
    oven.drawCubeWithTexture(lightingShader, model);


    // grill
    model = transform(alTogether, glm::vec3(1, .2, 1.5), glm::vec3(0.2, 2, 6), glm::vec3(0, 0, 0));
    oven.drawCube(lightingShader, model);
    model = transform(alTogether, glm::vec3(1, .01, 1.5), glm::vec3(0.2, 2.21, 6), glm::vec3(0, 0, 0));
    oven.setTextureProperty(grillMap, grillMap, 32.0);
    oven.drawCubeWithTexture(lightingShader, model);

    // blender
    model = transform(alTogether, glm::vec3(.02, .02, .02), glm::vec3(0.5, 3.1, 5), glm::vec3(90, 0, 0));
    modelShader.setMat4("model", model);
    Models["blender"].Draw(modelShader);
    model = transform(alTogether, glm::vec3(.02, .02, .02), glm::vec3(0.5, 3.1, 4), glm::vec3(90, 0, 0));
    modelShader.setMat4("model", model);
    Models["blender"].Draw(modelShader);

    // wine bottle
    model = transform(alTogether, glm::vec3(.03, .03, .03), glm::vec3(.8, 2.1, 3), glm::vec3(-90, 0, 0));
    modelShader.setMat4("model", model);
    Models["cooktop"].Draw(modelShader);

    // wall oven
    model = transform(alTogether, glm::vec3(.015, .015, .015), glm::vec3(9.4, .1, 6.5), glm::vec3(-90, 0, 0));
    model = transform(model, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, -90));
    modelShader.setMat4("model", model);
    Models["walloven"].Draw(modelShader);
    
    // cooker   
    model = transform(alTogether, glm::vec3(.02, .02, .02), glm::vec3(4, 2.1, .6), glm::vec3(0, -90, 0));
    modelShader.setMat4("model", model);
    Models["cooker"].Draw(modelShader);

    model = transform(alTogether, glm::vec3(.02, .02, .02), glm::vec3(6, 2.1, .6), glm::vec3(0, -90, 0));
    modelShader.setMat4("model", model);
    Models["cooker"].Draw(modelShader);

    // mug
    model = transform(alTogether, glm::vec3(.015, .015, .015), glm::vec3(4, 2.1, .6), glm::vec3(270, 0, 0));
    modelShader.setMat4("model", model);
    Models["shrimp"].Draw(modelShader);

    model = transform(alTogether, glm::vec3(.015, .015, .015), glm::vec3(6, 2.1, .6), glm::vec3(270, 0, 0));
    modelShader.setMat4("model", model);
    Models["shrimp"].Draw(modelShader);


    // for right top shelf
    // bowls
    float x = 0;
    float y = 1;
    float z = -.4;
    model = transform(alTogether, glm::vec3(.8, .8, .5), glm::vec3(9.7 + x, 5.1 + y, 1.4 + z), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));
    model = transform(alTogether, glm::vec3(.8, .8, .5), glm::vec3(9.7 + x, 5.1 + y, 1.8 + z), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));
    model = transform(alTogether, glm::vec3(.8, .8, .5), glm::vec3(9.7 + x, 5.1 + y, 2.2 + z), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));

    // bowls
    model = transform(alTogether, glm::vec3(.8, .8, .5), glm::vec3(9.7 + x, 5.1+ y, 3), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));
    model = transform(alTogether, glm::vec3(.8, .8, .5), glm::vec3(9.7 + x, 5.1 + y, 3.5), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));
    model = transform(alTogether, glm::vec3(.8, .8, .5), glm::vec3(9.7 + x, 5.1 + y, 4), glm::vec3(180, 0, 0));
    bowl1.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));

    // vase
    model = transform(alTogether, glm::vec3(.6, .4, .6), glm::vec3(9.6, 5.4, 5.5), glm::vec3(180, 0, 0));
    vase.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));
    model = transform(alTogether, glm::vec3(.6, .4, .6), glm::vec3(9.6, 5.4, 6), glm::vec3(180, 0, 0));
    vase.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));
    model = transform(alTogether, glm::vec3(.6, .4, .6), glm::vec3(9.6, 5.4, 6.5), glm::vec3(180, 0, 0));
    vase.draw(lightingShader, model, glm::vec3(1.0, 0.0, 1.0));

    //right top shelf
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * .8, height * .1, width * 8));
    translate = glm::translate(model, glm::vec3(9.2, 4.5, 0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    //right bottom shelf
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * .8, height * .1, width * 8));
    translate = glm::translate(model, glm::vec3(9.2, 3.5, 0));
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

    // front desk
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 10, height * .01, width * 1.5));
    translate = glm::translate(model, glm::vec3(0.0, 2.0, 8));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // Menu Card
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 1, height * .001, width * 1.5));
    translate = glm::translate(model, glm::vec3(5.0, 2.0, 8));
    glm::mat4 rotateXMatrix = glm::rotate(identityMatrix, glm::radians(angP6), glm::vec3(0.0f, 0.0f, 1.0f));
    model = alTogether * translate * rotateXMatrix * scale;
    Cubes["mp6"].drawCubeWithTexture(lightingShader, model);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 1, height * .001, width * 1.5));
    translate = glm::translate(model, glm::vec3(5.0, 2.1, 8));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(angP5), glm::vec3(0.0f, 0.0f, 1.0f));
    model = alTogether * translate * rotateXMatrix * scale;
    Cubes["mp5"].drawCubeWithTexture(lightingShader, model);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 1, height * .001, width * 1.5));
    translate = glm::translate(model, glm::vec3(5.0, 2.12 + y4, 8));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(angP4), glm::vec3(.0f, 0.0f, 1.0f));
    model = alTogether * translate * rotateXMatrix * scale;
    Cubes["mp4"].drawCubeWithTexture(lightingShader, model);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 1, height * .01, width * 1.5));
    translate = glm::translate(model, glm::vec3(5.0, 2.13 + y3, 8));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(angP3), glm::vec3(.0f, 0.0f, 01.0f));
    model = alTogether * translate * rotateXMatrix * scale;
    Cubes["mp3"].drawCubeWithTexture(lightingShader, model);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 1, height * .01, width * 1.5));
    translate = glm::translate(model, glm::vec3(5.0, 2.14 + y2, 8));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(angP2), glm::vec3(0.0f, 0.0f, 1.0f));
    model = alTogether * translate * rotateXMatrix * scale;
    Cubes["mp2"].drawCubeWithTexture(lightingShader, model);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 1, height * .01, width * 1.5));
    translate = glm::translate(model, glm::vec3(5.0, 2.15, 8));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(angP1), glm::vec3(0.0f, 0.0f, 1.0f));
    //glm::mat4 rotateYMatrix = glm::rotate(identityMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    //glm::mat4 rotateZMatrix = glm::rotate(identityMatrix, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    
    model = alTogether * translate * rotateXMatrix * scale;
    Cubes["mp1"].drawCubeWithTexture(lightingShader, model);

    std::cout << "Distance: " << sqrt((camera.Position.x - .67) * (camera.Position.x - .67) *
        (camera.Position.y - .51) * (camera.Position.y - .51) *
        (camera.Position.z - 1.16) * (camera.Position.z - 1.16)) << std::endl;

    cout << camera.Position.x << ' ' << camera.Position.y << ' ' << camera.Position.z << endl;


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

void cart1(unsigned int& cubeVAO, Shader& lightingShader, Shader& modelShader, glm::mat4 alTogether) {
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

    Models["oven"].Draw(modelShader);

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

void vending_machine(Shader& lightingShader, glm::mat4 alTogether) {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    glm::mat4 rotateXMatrix = glm::mat4(1.0f);
    glm::mat4 rotateYMatrix = glm::mat4(1.0f);
    glm::mat4 rotateZMatrix = glm::mat4(1.0f);

    model = transform(alTogether, glm::vec3(4.1, 12, 6), glm::vec3(0, 0, 72), glm::vec3(0, 0, 0));
    Cubes[""].drawCubeWithTexture(lightingShader, model);

    model = transform(alTogether, glm::vec3(.1, 12, 6), glm::vec3(4.2, 0, 72), glm::vec3(0, 0, 0));
    Cubes["vending"].drawCubeWithTexture(lightingShader, model);

}

void photo_frame(Shader& lightingShader, glm::mat4 alTogether) {
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

    model = transform(alTogether, glm::vec3(3, 4, .3), glm::vec3(70, 15, 1), glm::vec3(0, 0, 0));
    Cubes[""].drawCubeWithTexture(lightingShader, model);
    model = transform(alTogether, glm::vec3(3, 4, .3), glm::vec3(70, 8, 1), glm::vec3(0, 0, 0));
    Cubes[""].drawCubeWithTexture(lightingShader, model);

    model = transform(alTogether, glm::vec3(4, 3, .3), glm::vec3(75, 18, 1), glm::vec3(0, 0, 0));
    Cubes[""].drawCubeWithTexture(lightingShader, model);
    model = transform(alTogether, glm::vec3(4, 6, .3), glm::vec3(75, 10, 1), glm::vec3(0, 0, 0));
    Cubes[""].drawCubeWithTexture(lightingShader, model);
    model = transform(alTogether, glm::vec3(4, 3, .3), glm::vec3(75, 5, 1), glm::vec3(0, 0, 0));
    Cubes[""].drawCubeWithTexture(lightingShader, model);

    model = transform(alTogether, glm::vec3(3, 4, .3), glm::vec3(81, 15, 1), glm::vec3(0, 0, 0));
    Cubes[""].drawCubeWithTexture(lightingShader, model);
    model = transform(alTogether, glm::vec3(3, 4, .3), glm::vec3(81, 8, 1), glm::vec3(0, 0, 0));
    Cubes[""].drawCubeWithTexture(lightingShader, model);
    
}

void food_court(unsigned int& cubeVAO, Shader& lightingShader, Shader& modelShader, glm::mat4 alTogether) {
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


    scale = glm::scale(model, glm::vec3(length * 120, height * .1, width * 140));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    photo_frame(lightingShader, alTogether);
    model = transform(alTogether, glm::vec3(1, 1, 1), glm::vec3(-30, 0, 0), glm::vec3(0, 0, 0));
    photo_frame(lightingShader, model);

    // Disco
    Sphere disco = Sphere(5.0f, 36, 18, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 32, diffMap1, diffMap1, 0, 0, 1, 1);
    scale = glm::scale(model, glm::vec3(length * 50, height * 50, width * 50));
    translate = glm::translate(model, glm::vec3(800.0, 300.0, 800.0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    rotate = rotateXMatrix * rotateYMatrix * rotateZMatrix;
    model = alTogether * translate * rotate * scale;
    disco.drawSphereWithTexture(lightingShader, model);


    // left wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * .1, height * 30, width * 140));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // right wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * .1, height * 30, width * 140));
    translate = glm::translate(model, glm::vec3(120.0, 0.0, 0.0));
    model = alTogether * translate * scale;
    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    // starry left wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * .1, height * 30, width * 40));
    translate = glm::translate(model, glm::vec3(0.1, 0.0, 0.0));
    model = alTogether * translate * scale;
    Cubes["starry"].drawCubeWithTexture(lightingShader, model);

    // starry back wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 40, height * 30, width * .1));
    translate = glm::translate(model, glm::vec3(0.0, 0.0, 0.1));
    model = alTogether * translate * scale;
    //Cubes["abs1"].drawCubeWithTexture(lightingShader, model);

    // starry base
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 40, height * .1, width * 40));
    translate = glm::translate(model, glm::vec3(0.0, 0.1, 0.0));
    model = alTogether * translate * scale;
    Cubes["abs1"].drawCubeWithTexture(lightingShader, model);


    // starry right wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * .1, height * 30, width * 40));
    translate = glm::translate(model, glm::vec3(119.9, 0.0, 0.0));
    model = alTogether * translate * scale;
    Cubes["starry"].drawCubeWithTexture(lightingShader, model);

    // starry back wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 40, height * 30, width * .1));
    translate = glm::translate(model, glm::vec3(80.0, 0.0, 0.1));
    model = alTogether * translate * scale;
    //Cubes["abs1"].drawCubeWithTexture(lightingShader, model);

    // starry base
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 40, height * .1, width * 40));
    translate = glm::translate(model, glm::vec3(80.0, 0.1, 0.0));
    model = alTogether * translate * scale;
    Cubes["abs1"].drawCubeWithTexture(lightingShader, model);

    // starry mid base
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 40, height * .1, width * 40));
    translate = glm::translate(model, glm::vec3(40.0, 0.1, 0.0));
    model = alTogether * translate * scale;
    Cubes["abs1"].drawCubeWithTexture(lightingShader, model);

    // starry mid back
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 40, height * 30, width * .1));
    translate = glm::translate(model, glm::vec3(40, 0, 0.1));
    model = alTogether * translate * scale;
    //Cubes["abs1"].drawCubeWithTexture(lightingShader, model);


    // back wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length * 120, height * 30, width * .1));
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
            glm::vec3(0.0, 0.0, 140.0 - i * 20.4), 
            glm::vec3(0, 90, 0));
        
        cart2(cubeVAO, lightingShader, modelShader, model);

        model = transform(alTogether, 
            glm::vec3(length * 2, height * 2, width * 2),
            glm::vec3(120.0, 0.0, 120.0 - i * 20.4),
            glm::vec3(0, 270, 0));
        
        cart2(cubeVAO, lightingShader, modelShader, model);
        //cart1(cubeVAO, lightingShader, modelShader, model);
    }

    vending_machine(lightingShader, alTogether);
    model = transform(alTogether, glm::vec3(1, 1, 1), glm::vec3(0, 0, -8), glm::vec3(0, 0, 0));
    vending_machine(lightingShader, model);


    model = transform(alTogether, glm::vec3(1, 1, 1), glm::vec3(120, 0, 150), glm::vec3(0, 180, 0));
    vending_machine(lightingShader, model);
    model = transform(alTogether, glm::vec3(1, 1, 1), glm::vec3(120, 0, 142), glm::vec3(0, 180, 0));
    vending_machine(lightingShader, model);

    model = transform(alTogether,
        glm::vec3(1, 1, 1),
        glm::vec3(40.0, 7.1, 100.0),
        glm::vec3(0, 0, 0));
    for (int i = 0; i < 4; ++i) {
        model = transform(alTogether,
            glm::vec3(.8, .8, .8),
            glm::vec3(30.0, 7.1, 130.0 - i * 20),
            glm::vec3(0, 0, 0));
        //round_table_chair(lightingShader, model);
    }

    for (int i = 0; i < 4; ++i) {
        model = transform(alTogether,
            glm::vec3(.8, .8, .8),
            glm::vec3(75.0, 7.1, 130.0 - i * 20),
            glm::vec3(0, 0, 0));
        //round_table_chair(lightingShader, model);
    }

    for (int i = 0; i < 4; ++i) {
        model = transform(alTogether,
            glm::vec3(.05, .05, .05),
            glm::vec3(42.0, 0.0, 130.0 - i * 20),
            glm::vec3(0, 90, 0));

        modelShader.setMat4("model", model);
        Models["table_chair_model"].Draw(modelShader);

    }

    Cubes["default_cube"].drawCubeWithTexture(lightingShader, model);

    for (int i = 0; i < 4; ++i) {
        model = transform(alTogether,
            glm::vec3(.05, .05, .05),
            glm::vec3(62.0, 0.0, 130.0 - i * 20),
            glm::vec3(0, 90, 0));
        modelShader.setMat4("model", model);
        Models["table_chair_model"].Draw(modelShader);
    }

    for (int i = 0; i < 4; ++i) {
        model = transform(alTogether,
            glm::vec3(.05, .05, .05),
            glm::vec3(82.0, 0.0, 130.0 - i * 20),
            glm::vec3(0, 90, 0));
        modelShader.setMat4("model", model);
        Models["table_chair_model"].Draw(modelShader);
    }

    model = transform(alTogether,
        glm::vec3(5, 5, 5),
        glm::vec3(95.0, 0.0, 5),
        glm::vec3(0, 270, 0));
    modelShader.setMat4("model", model);
    Models["sofa"].Draw(modelShader);

    
    model = transform(alTogether,
        glm::vec3(2, 2, 2),
        glm::vec3(10, -2, 10),
        glm::vec3(0, 270, 0));
    modelShader.setMat4("model", model);
    Models["woodswing"].Draw(modelShader);

    model = transform(alTogether,
        glm::vec3(2, 2, 2),
        glm::vec3(30.0, -2, 10),
        glm::vec3(0, 270, 0));
    modelShader.setMat4("model", model);
    Models["woodswing"].Draw(modelShader);

    decoration(lightingShader, modelShader, alTogether);
}

void decoration(Shader& lightingShader, Shader& modelShader, glm::mat4 alTogether) {
    glm::mat4 model = transform(alTogether, glm::vec3(10, 5, 1),
        glm::vec3(10, 0, 0),
        glm::vec3(0, 0, 0));


    //Cubes["fire_animation"].drawCubeWithTexture(lightingShader, model);
    //for (int i = 0; i < 5; ++i) {
    //    unsigned int DiffMap;
    //    unsigned int SpecMap;
    //    for (int i = 0; i < 10; ++i) {
    //        string diffPath = "./textures/fire/" + to_string(i + 1) + ".png";
    //        DiffMap = loadTexture(diffPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    //        SpecMap = loadTexture(diffPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    //        Cube cube = Cube(DiffMap, SpecMap, 32, 0.0f, 0.0f, 0, 0);
    //        //Cubes.insert({ "fire_animation", cube });
    //        cube.drawCubeWithTexture(lightingShader, model);
    //    }
    //}



    
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


void drawModel(Model& model, glm::mat4 alTogether) {
    /*modelShader.use();
    modelShader.setMat4("projection", projection);
    modelShader.setMat4("view", view);
    modelShader.setMat4("model", alTogether);
    model.Draw(modelShader);*/
}