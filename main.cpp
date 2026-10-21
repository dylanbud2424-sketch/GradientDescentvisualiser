#include <iostream>
#include <vector>
#include <cmath>

#define ALPHA 0.01

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
float calculateNewz(float oldz, float gradient){
    return oldz-(ALPHA*gradient);
}

float calculatez(float weight, float bias, float input){
    return (weight*input + bias);
}

float calculateNewWeight(float oldweight, float yhat, float y, float xinput){
    return oldweight-(ALPHA*(yhat-y)*xinput);
}

float calculateNewBias(float oldbias, float yhat, float y){
    return oldbias-(ALPHA*(yhat-y));
}

void UpdateNeuron(Neuron &neuron, float y){
    float yhat = calculateSigmoid(calculatez(neuron.weight,neuron.bias,neuron.input));
    neuron.weight = calculateNewWeight(neuron.weight, yhat, y, neuron.input);
    neuron.bias = calculateNewBias(neuron.bias,yhat,y);    
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

int main(){
    Neuron myNeuron = {-1.2,1.5,0.414};
    UpdateNeuron(myNeuron, 0);
    printNeuron(myNeuron, 0);
    UpdateNeuron(myNeuron, 0);
    printNeuron(myNeuron, 0);


/*
    float z = calculatezfromInputs(weight, bias, xinput);
    float yhat = sigmoid(z);
    float calculateLoss = loss(y, yhat);
    float gradientOutput = gradient(y, yhat);
    float newzCalc = newz(z,gradientOutput);
    float newWeight = calculateNewWeight(weight, yhat, y, xinput);
    float newBias = calculateNewBias(bias, yhat, y);

    std::cout << "\n\n";
    std::cout << "The original z is " << z << "\n" << std::endl;
    std::cout << "The probability that the output is 1 is " << yhat << "\n" << std::endl;
    std::cout << "The loss calculation (the penalty) is " << calculateLoss << "\n" << std::endl;
    std::cout << "The gradient calcultion is " << gradientOutput << "\n" << std::endl;
    std::cout << "The new z based should now be " << newzCalc << "\n" << std::endl; 
    std::cout << "The new weight should be " << newWeight << "\n" << std::endl;
    std::cout << "The new bias should be " << newBias << "\n" << std::endl;
*/
    return 0;
}