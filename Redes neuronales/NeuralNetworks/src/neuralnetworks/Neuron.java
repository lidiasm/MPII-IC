/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package neuralnetworks;

import java.util.Random;
import readingdata.MNISTDatabase;

/**
 * Class which represents a neuron.
 * 
 * @author Lidia Sánchez Mérida
 */
public class Neuron {
    
    private float inputs[];
    private float weights[];
    private float output;
    
    public Neuron() {
        output = 0.0f;
    }

    public float[] getInputs() {
        return inputs;
    }

    public void setInputs(float[] inputs) {
        this.inputs = inputs;
    }

    public float[] getWeights() {
        return weights;
    }

    public void setWeights(float [] weights) {
        this.weights = weights;
    }
    
    public void setWeight(int index, float new_value) {
        this.weights[index] = new_value;
    }

    public float getOutput() {
        return output;
    }
    
    public void initializeWeights(int size) {
        // Initializing the random number system outside 
        weights = new float[size];
        weights[0] = 0.0f;
        float max = 1.0f, min = -1.0f;
        // Random weights 
        for (int i = 1; i < weights.length; i++) {
            weights[i] = (float) Math.random() * (max - min) + min; 
        }
    }
    
    public void initializeInputs(int size, int images[][]) {
        inputs = new float[size];
        inputs[0] = 1.0f;
        // Pixels of the image
        int inputsIndex = 1;
        // Normalizing
        float normalizedImages[][];
        normalizedImages = MNISTDatabase.normalize(images);
        // We supose number of rows = number of cols
        for (int row = 0; row < normalizedImages[0].length; row++) {
            for (int col = 0; col < normalizedImages[0].length; col++) {
                inputs[inputsIndex] = normalizedImages[row][col];
                inputsIndex ++;
            }
        }
    }
    
    public float binaryActivationFuction() {
        int y = 0;
        for (int i = 0; i < weights.length; i++)
            y += (weights[i] * inputs[i]);
        
        return this.output = y >= 0 ? 1.0f : 0.0f;
    }
    
    public float sigmoidActivationFunction() {
        float z = weights[0];
        for (int i = 0; i < weights.length; i++) {
            z += (weights[i] * inputs[i]);
        }
        
        output = (float) (1.0f/(1.0f+Math.exp(-z)));
        return output;
        
    }
    
    public void adjustWeights(int desiredResponse) {
        for (int i = 0; i < weights.length; i++) {
            weights[i] = weights[i] + (desiredResponse * inputs[i]);
        }
    }
}
