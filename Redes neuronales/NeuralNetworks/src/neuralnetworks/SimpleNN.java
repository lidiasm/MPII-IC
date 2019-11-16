/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package neuralnetworks;

import java.util.ArrayList;

/**
 * Simple neural network with 10 neurons.
 * @author Lidia Sánchez Mérida
 */
public class SimpleNN {
    
    private final static int N_NEURONS = 10;
    private ArrayList<Neuron> neurons; 
    
    public SimpleNN() {
        neurons = new ArrayList();
        for (int i=0; i<N_NEURONS; i++) neurons.add(new Neuron());
    }
    
    private void initializeNeuronsWeights(int size) {
        for (Neuron neuron: neurons) neuron.initializeWeights(size);
    }
    
    public void train(int images[][][], int labels[], int times) {
        int error = 0, size = (images[0].length * images[0].length) + 1;
        // Predictions for each neuron
        ArrayList<Float>predictions;
        // Initializing weights.
        initializeNeuronsWeights(size);
        for (int time = 0; time < times; time++) {
            for (int imageIndex = 0; imageIndex < images.length; imageIndex++) {   // Each image
                // Reinitializing the predictions
                predictions = new ArrayList();
                for (Neuron neuron: neurons) {    // Each neuron
                    // Initializing inputs
                    neuron.initializeInputs(size, images[imageIndex]);
                    // Activation function
                    float is_activated = neuron.binaryActivationFuction();
                    // Prediction of the current neuron
                    predictions.add(is_activated);
                    // Case 1: This neuron should have been activated but it's not.
                    if (is_activated == 0 && neurons.indexOf(neuron) == labels[imageIndex]) {
                        neuron.adjustWeights(1);
                    }
                    // Case 2: This neuron has been activated
                    else if (is_activated == 1) {
                        // It's activated but it shouldn't have been activated.
                        if (neurons.indexOf(neuron) != labels[imageIndex]) neuron.adjustWeights(-1);
                    }
                }

                // Calculating the error
                int digit = labels[imageIndex];
                if (predictions.get(digit) == 0)error++;
            }
            System.out.println("Time: "+time+" - N errors: "+error+" / "+((error*1.0)/(images.length*1.0))*100.0 + "%");
            error = 0;
        }
    }
    
     public void test(int images[][][], int labels[]) {
        int error = 0, size = (images[0].length * images[0].length)+1;
        // Predictions for each neuron
        ArrayList<Float>predictions;
        for (int imageIndex = 0; imageIndex < images.length; imageIndex++) {   // Each image
            predictions = new ArrayList();
            for (Neuron neuron: neurons) {    // Each neuron
                // Initializing inputs
                neuron.initializeInputs(size, images[imageIndex]);
                // Activation function
                float is_activated = neuron.binaryActivationFuction();
                // Prediction of the current neuron
                predictions.add(is_activated);
            }
            // Calculating the error
            int digit = labels[imageIndex];
            // The neuron = digit hasn't been activated -> Error
            if (predictions.get(digit) == 0) error++;
        }
        System.out.println("N errors: " + error + " / " + ((error*1.0)/(images.length*1.0))*100.0 + "%");        
    }
}
