#include <iostream>
#include <vector>
#include <cmath>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>



#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

struct Neuron {
    float weight;
    float input;
    float bias;
};

//The sigmoid function creates the probability of the output being one
float calculateSigmoid(float z){
    return 1.0f / (1.0f + std::exp(-z));
}

//Calculate the penalty for how wrong it was
float calculateLoss(float y, float yhat){
    float output = (-(y*log(yhat)+(1-y)*log(1-yhat)));
    return output;
}

//If the gradient is positive z is too high push it down, else if it is negative push it up 
float calculateGradient(float y, float yhat){
    return yhat-y;
}

//Work out what the new z should be where alpha is the learning rate
float calculateNewz(float oldz, float gradient, float ALPHA){
    return oldz-(ALPHA*gradient);
}

float calculatez(float weight, float bias, float input){
    return (weight*input + bias);
}

float calculateNewWeight(float oldweight, float yhat, float y, float xinput, float ALPHA){
    return oldweight-(ALPHA*(yhat-y)*xinput);
}

float calculateNewBias(float oldbias, float yhat, float y, float ALPHA){
    return oldbias-(ALPHA*(yhat-y));
}

void UpdateNeuron(Neuron &neuron, float y, float ALPHA){
    float yhat = calculateSigmoid(calculatez(neuron.weight,neuron.bias,neuron.input));
    neuron.weight = calculateNewWeight(neuron.weight, yhat, y, neuron.input, ALPHA);
    neuron.bias = calculateNewBias(neuron.bias,yhat,y, ALPHA);    
}

void printNeuron(Neuron &neuron, float y){
    float z = calculatez(neuron.weight, neuron.bias, neuron.input);
    std::cout << "The weight is: " << neuron.weight << std::endl;
    std::cout << "The bias is: " << neuron.bias << std::endl;
    std::cout << "The xinput is: " << neuron.input << std::endl;
    std::cout << "The z is: " << z << std::endl;
    std::cout << "The loss is: " << calculateLoss(y, calculateSigmoid(z)) << std::endl;
    std::cout << "\n\n";
}


int main() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        return 1;
    }

    // Decide GL+GLSL versions (OpenGL 3.3 Core)
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Gradient Descent Visualiser", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // State
    float ALPHA = 0.01f;
    int iterations = 100;


    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Actual Code goes here
        ImGui::Begin("Gradient Descent");
        ImGui::Text("Parameters");
        ImGui::SliderFloat("Learning rate", &ALPHA, 0.001f, 1.0f, "%.4f");
        ImGui::SliderInt("Iterations", &iterations, 1, 1000);

        ImGui::End();



        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(nullptr);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

