#include <iostream>
#include <vector>
#include <cmath>

//The sigmoid function creates the probability of the output being one
float sigmoid(float z){
    return 1.0f / (1.0f + std::exp(-z));
}

//Calculate the penalty for how wrong it was
float loss(float y, float yhat){
    float output = (-(y*log(yhat)+(1-y)*log(1-yhat)));
    return output;
}

//If the gradient is positive z is too high push it down, else if it is negative push it up 
float gradient(float y, float yhat){
    return yhat-y;
}

//Work out what the new z should be where alpha is the learning rate
float newz(float oldz, float gradient){
    float alpha = 0.01;
    return oldz-(alpha*gradient);
}

int main(){
    float y = 0;
    float z = -1.386;
    float yhat = sigmoid(z);
    float calculateLoss = loss(y, yhat);
    float gradientOutput = gradient(y, yhat);
    float newzCalc = newz(z,gradientOutput);
    std::cout << "\n\n";
    std::cout << "The original z is " << z << "\n" << std::endl;
    std::cout << "The probability that the output is 1 is " << yhat << "\n" << std::endl;
    std::cout << "The loss calculation (the penalty) is " << calculateLoss << "\n" << std::endl;
    std::cout << "The gradient calcultion is " << gradientOutput << "\n" << std::endl;
    std::cout << "The new z based should now be " << newzCalc << "\n" << std::endl; 
    return 0;
}