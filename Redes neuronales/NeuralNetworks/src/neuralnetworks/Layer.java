/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package neuralnetworks;

import readingdata.MNISTDatabase;

/**
 * Class which represents a layer full of neurons.
 * 
 * @author Lidia Sánchez Mérida
 */
public class Layer {
    
    private float weights[][];
    private float outputs[];
    private float inputs[][];
    
    /**
     * Constructor.
     * @param n_neurons number of neurons.
     * @param n_inputs number of inputs.
     */
    Layer(int n_neurons, int n_inputs) {
        weights = new float [n_neurons][n_inputs];
        inputs = new float[n_neurons][n_inputs];
        outputs = new float[n_neurons];
    }
    
    float[] getOutputs() {
        return outputs;
    }
    
    /**
     * Initialize the weights of every neuron of a layer.
     */
    void initializeWeights() {
        // Initialize weights
        float max = 1.0f, min = -1.0f;
        for (int neuron=0; neuron<weights.length; neuron++) {
            weights[neuron][0] = 0.0f;
            for (int weight=1; weight<weights[0].length; weight++) {
                weights[neuron][weight] = (float) Math.random() * (max - min) + min; 
            }
        }
    }
    
    /**
     * Initialize the inputs with the image of a set. This function will be used
     * for initializing the input and the hidden layer.
     * @param image the pixels of an image.
     */
    void initializeInputs(int image[][]) {
        // Normalizing
        float normalizedImages[][];
        normalizedImages = MNISTDatabase.normalize(image);
        int inputIndex;
        for (int neuron=0; neuron<inputs.length; neuron++) {
            inputIndex = 0;
            inputs[neuron][inputIndex] = 1.0f;
            inputIndex ++;
            for (int row = 0; row < normalizedImages[0].length; row++) {
                for (int col = 0; col < normalizedImages[0].length; col++) {
                    inputs[neuron][inputIndex] = normalizedImages[row][col];
                    inputIndex++;
                }
            }
        }
    }
    
    /**
     * Initialize the inputs of the output layer with the outputs of the hidden
     * layer.
     * @param hiddenOutputs outputs of the hidden layer.
     */
    void initializeInputs(float hiddenOutputs[]) {
        for (int neuron=0; neuron<inputs.length; neuron++) {
            for (int output=0; output<hiddenOutputs.length; output++) {
                inputs[neuron][output] = hiddenOutputs[output];
            }
        }
    }
    
    /**
     * Calculates the outputs of a layer with a sigmoidal function.
     */
    void forward() {
        float z;
        for (int neuron=0; neuron<outputs.length; neuron++) {
            z = weights[neuron][0];
            for (int input=0; input<inputs.length; input++) {
                z += weights[neuron][input]*inputs[neuron][input];
            }
            outputs[neuron] = (float) (1.0f/(1.0f+Math.exp(z)));
        }
    }
}
