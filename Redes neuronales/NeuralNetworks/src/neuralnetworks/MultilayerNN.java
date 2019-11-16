/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package neuralnetworks;

import java.util.ArrayList;

/**
 * Class which represents a multilayer neural network.
 * 
 * @author Lidia Sánchez Mérida.
 */
public class MultilayerNN {
    
    private final static int SIZE_WEIGHTS_INPUTS = (28*28)+1;
    private final static int SIZE_INPUT_LAYER = SIZE_WEIGHTS_INPUTS;
    private final static int SIZE_HIDDEN_LAYER = 256;
    private final static int SIZE_OUTPUT_LAYER = 10;
    private final static float LEARNING_RATE = 0.1f;
    private final static float MOMENTUM = 0.9f;
    private final static int INDEX_INPUT_LAYER = 0;
    private final static int INDEX_HIDDEN_LAYER = 1;
    private final static int INDEX_OUTPUT_LAYER = 2;
    
    /**
     * Layers.
     */
    private ArrayList<Layer> layers = new ArrayList();
    
    /**
     * Constructor. Create and initialize the layers.
     */
    public MultilayerNN() {
        // Create three layers
        layers.add(new Layer(SIZE_INPUT_LAYER, SIZE_WEIGHTS_INPUTS));
        layers.add(new Layer(SIZE_HIDDEN_LAYER, SIZE_WEIGHTS_INPUTS));
        layers.add(new Layer(SIZE_OUTPUT_LAYER, SIZE_WEIGHTS_INPUTS));  
    }
    
    /**
     * Initialize the inputs of every layer.
     * @param image the pixels of an image.
     */
    private void initializingInputsLayers(int image[][]) {
        // Initialize the inputs of the input and hidden layer with the images
        layers.get(INDEX_INPUT_LAYER).initializeInputs(image);
        layers.get(INDEX_HIDDEN_LAYER).initializeInputs(image);
        
        // Initialize the inputs of the output layer with the outputs of the hidden layer
        layers.get(INDEX_HIDDEN_LAYER).forward();
        layers.get(INDEX_OUTPUT_LAYER).initializeInputs(layers.get(INDEX_HIDDEN_LAYER).getOutputs());
    }
    
    /**
     * Calculate the outputs of the multilayer neural network.
     */
    private void feedForward() {
        for (Layer layer: layers) layer.forward();
        for (int i=0; i<layers.get(INDEX_OUTPUT_LAYER).getOutputs().length; i++)
            System.out.println(layers.get(INDEX_OUTPUT_LAYER).getOutputs()[i]);
    }
    
    /**
     * Train the multilayer neural network with the training images and labels.
     * @param images
     * @param labels
     * @param times 
     */
    public void train(int images[][][], int labels[], int times) {
        // Initialize the weights of every neuron of each layer
        for (Layer layer: layers) layer.initializeWeights();
        // Each image
        for (int time = 0; time < times; time++) {
            for (int image=0; image<images.length; image++) {
                //System.out.println("\nIMAGE "+image);
                initializingInputsLayers(images[0]); // Initializing inputs
                feedForward();  // Calculate the outputs for the current image
            }
        }
    }
}
