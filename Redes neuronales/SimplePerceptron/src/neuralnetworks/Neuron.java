/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package neuralnetworks;

/**
 * Class which represents a type of neuron. Its activation function returns 1
 * if wi*xi >= 0 or 0 if it's not.
 * 
 * @author Lidia Sánchez Mérida
 */
public class Neuron {
    
    private float inputs[];
    private float weights[];
    private int isActivated;
    
    public Neuron() {
        isActivated = 0;
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

    public int isActivated(int [][]pixels) {
        binaryActivationFuction();
        return isActivated;
    }

    public void setIsActivated(int isActivated) {
        this.isActivated = isActivated;
    }
    
    private void binaryActivationFuction() {
        int y = 0;
        for (int i = 0; i < weights.length; i++)
            y += (weights[i] * inputs[i]);
        
        this.isActivated = y >= 0 ? 1 : 0;
    }
    
    /**
     * 
     * @param desiredResponse +1 if the neuron should have been activated, -1 if
     * the neuron shouldn't have.
     */
    public void adjustWeights(int desiredResponse) {
        for (int i = 0; i < weights.length; i++) {
            weights[i] = weights[i] + (desiredResponse * inputs[i]);
        }
    }
    
    public String toString() {
        String show = "\nIs activated? " + isActivated + "\nWeights: ";
        for (int iWeight = 0; iWeight < weights.length; iWeight++) show += weights[iWeight] + ", ";
        show += "\nInputs: ";
        for (int iInput = 0; iInput < inputs.length; iInput++) show += inputs[iInput] + ", ";
        return show;
    }
}
