/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mains;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Random;
import neuralnetworks.Neuron;
import readingdata.MNISTDatabase;

/**
 *
 * @author Lidia Sánchez Mérida
 */
public class SimplePerceptron {
    
    private ArrayList<Neuron> neurons;
    
    private void newNeuralNetwork() {
        neurons = new ArrayList();
        for (int i = 0; i < 10; i++)
            neurons.add(new Neuron());
    }
    
    private void initializeWeights(int size) {
        // Initializing the random number system outside 
         Random r = new Random(0);
        for (Neuron neuron: neurons) {
            float weights[] = new float[size];
            weights[0] = 0.0f;
            float max = 1.0f, min = -1.0f;
            // Random weights 
            for (int i = 1; i < weights.length; i++) {
                weights[i] = (float) Math.random() * (max - min) + min; 
            }
            neuron.setWeights(weights);
        }
    }
    
    private void initializeInputs(int size, int images[][]) {
        float inputs[] = new float[size];
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
        /*for (int row = 0; row < images.length; row++) {
            for (int col = 0; col < images.length; col++) {
                inputs[inputsIndex] = images[row][col];
                inputsIndex++;
            }
        }*/
        // Initializing the inputs of the neurons
        for (Neuron neuron: neurons) neuron.setInputs(inputs);
    }
    
    private void train(int images[][][], int labels[]) {
        int error = 0, prediction = -1, size = (images[0].length * images[0].length) + 1;
        // Initializing weights.
        initializeWeights(size);
        for (int e = 0; e < 10; e++) {
            for (int imageIndex = 0; imageIndex < images.length; imageIndex++) {   // Each image
                // Reinitializing de prediction
                prediction = 0;
                for (Neuron neuron: neurons) {    // Each neuron
                    // Initializing inputs
                    initializeInputs(size, images[imageIndex]);
                    // Activation function
                    int is_activated = neuron.isActivated(images[imageIndex]);
                    // Case 1: This neuron should have been activated but it's not.
                    if (is_activated == 0 && neurons.indexOf(neuron) == labels[imageIndex]) {
                        neuron.adjustWeights(1);
                    }
                    // Case 2: This neuron has been activated
                    else if (is_activated == 1) {
                        // Current prediction
                        prediction = neurons.indexOf(neuron);
                        // It's activated but it shouldn't have been activated.
                        if (neurons.indexOf(neuron) != labels[imageIndex]) neuron.adjustWeights(-1);
                    }
                }

                // Calculating the error
                if (prediction != labels[imageIndex]) error ++;
            }
            System.out.println("Errors: " + error);
            System.out.println("Errors %: " + ((error*1.0)/(images.length*1.0))*100.0);
            error = 0;
        }
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {        
        // Read the training images file
        int images[][][];
        String path = "C:\\Users\\usuario\\Desktop\\IC\\Prácticas\\1\\";
        images = MNISTDatabase.readImages(path + MNISTDatabase.getTrainingImages());
        
        // Read the training labels file
        int labels[];
        labels = MNISTDatabase.readLabels(path +  MNISTDatabase.getTrainingLabels());
    
        // Creating the 10 neurons
        SimplePerceptron perceptron = new SimplePerceptron();
        perceptron.newNeuralNetwork();
        ///// TRAINING
        perceptron.train(images, labels);
    }
}
