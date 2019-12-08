/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package nns;

/**
 * Class which represents a multilayer neural network with 2 hidden layers.
 * 
 * @author Lidia Sánchez Mérida
 */
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Random;

public class MultilayerNN2HiddenLayers {

    /**
     * Number of layers.
     */
    private static final int N_LAYERS = 4;
    /**
     * Index of the input layer. It'll be the first layer.
     */
    private static final int INPUT_LAYER_INDEX = 0;
    /**
     * Index of the first hidden layer. It'll be the second layer.
     */
    private static final int HIDDEN_LAYER1_INDEX = 1;
    /**
     * Index of the second hidden layer. It'll be the third layer.
     */
    private static final int HIDDEN_LAYER2_INDEX = 2;
    /**
     * Index of the output layer. It'll be the last layer.
     */
    private static final int OUTPUT_LAYER_INDEX = 3;
    /**
     * Number of layers which has weights. They will be the hidden and the output
     * layer.
     */
    private static final int N_LAYERS_WEIGHTS = 3;
    /**
     * Index of the weights of the first hidden layer.
     */
    private static final int HIDDEN1_WEIGHT_INDEX = 0;
    /**
     * Index of the weights of the second hidden layer.
     */
    private static final int HIDDEN2_WEIGHT_INDEX = 1;
    /**
     * Index of the weights of the output lyaer.
     */
    private static final int OUTPUT_WEIGHT_INDEX = 2;

    /**
     * Size of the input layer.
     */
    private static final int INPUT_LAYER_SIZE = (28*28) + 1;

    /**
     * Size of the hidden layer.
     */
    private static int HIDDEN_LAYER_SIZE;

    /**
     * Size of the output layer 10.
     */
    private static final int OUTPUT_LAYER_SIZE = 10;

    /**
     * Learning rate.
     */
    private static final double LEARNING_RATE = 0.07;

    /**
     * Momentum.
     */
    private static final double MOMENTUM = 0.7;

    /**
     * Outputs of each layer.
     */
    private double[][] outputs;

    /**
     * Weights array of each layer and each neuron.
     */
    private double[][][] weights;

    /**
     * Error of each neuron of the output layer.
     */
    private double[] outputErrors;

    /**
     * Error of each neuron of the hidden and the output layer.
     */
    private double[][] deltas;

    /**
     * Corrections of the weights of the hidden and output layer. These will be
     * added to the current weights.
     */
    private double[][][] correctionWeights;
    
    /**
     * Test predictions.
     */
    private ArrayList<Integer> testPredictions;

    /**
     * Constructor.
     * @param nHiddenNeurons current hidden layers size.
     */
    public MultilayerNN2HiddenLayers(int nHiddenNeurons) {
        HIDDEN_LAYER_SIZE = nHiddenNeurons;
        // Test predictions
        testPredictions = new ArrayList();
        // Initialize outputs array.
        outputs = new double[N_LAYERS][];   // Outputs of the 3 layers.
        outputs[INPUT_LAYER_INDEX] = new double[INPUT_LAYER_SIZE]; 
        outputs[HIDDEN_LAYER1_INDEX] = new double[HIDDEN_LAYER_SIZE]; 
        outputs[HIDDEN_LAYER2_INDEX] = new double[HIDDEN_LAYER_SIZE]; 
        outputs[OUTPUT_LAYER_INDEX] = new double[OUTPUT_LAYER_SIZE]; 
        // Initialize weights array.
        initializeWeights();
        // Initialize the errors of the outputs array.
        outputErrors = new double[OUTPUT_LAYER_SIZE];
        // Initialize deltas array.
        deltas = new double[N_LAYERS_WEIGHTS][];
        deltas[HIDDEN1_WEIGHT_INDEX] = new double[HIDDEN_LAYER_SIZE];
        deltas[HIDDEN2_WEIGHT_INDEX] = new double[HIDDEN_LAYER_SIZE];
        deltas[OUTPUT_WEIGHT_INDEX] = new double[OUTPUT_LAYER_SIZE];
        // Initializing the future corrections of the weights.
        initializeCorrectionWeights();
    }
    /**
     * Initialize the array of weights of the hidden and the output layer.
     */
    private void initializeWeights() {
        weights = new double[N_LAYERS_WEIGHTS][][];
        // Hidden layer 1.
        weights[HIDDEN1_WEIGHT_INDEX] = new double[HIDDEN_LAYER_SIZE][];
        for (int h=0; h<HIDDEN_LAYER_SIZE; h++) {
            weights[HIDDEN1_WEIGHT_INDEX][h] = new double[INPUT_LAYER_SIZE];
        }
        // Hidden layer 2.
        weights[HIDDEN2_WEIGHT_INDEX] = new double[HIDDEN_LAYER_SIZE][];
        for (int h=0; h<HIDDEN_LAYER_SIZE; h++) {
            weights[HIDDEN2_WEIGHT_INDEX][h] = new double[HIDDEN_LAYER_SIZE];
        }
        // Output layer.
        weights[OUTPUT_WEIGHT_INDEX] = new double[OUTPUT_LAYER_SIZE][];
        for (int o=0; o<OUTPUT_LAYER_SIZE; o++) {
            weights[OUTPUT_WEIGHT_INDEX][o] = new double[HIDDEN_LAYER_SIZE];
        }
        // Random weights
        Random random;
        double max = 0.1, min = -0.1;
        for (int layer=0; layer<N_LAYERS_WEIGHTS; layer++) {
            for (int neuron=0; neuron<weights[layer].length; neuron++) {
                random = new Random(0);
                weights[layer][neuron][0] = 0.0;
                for (int i=1; i<weights[layer][neuron].length; i++) {
                    weights[layer][neuron][i] = min + random.nextDouble() *(max-min);
                }
            }
        }
    }
    /**
     * Creates and initializes the future corrections of the weights. They will
     * be added to the current weight which will allow the learning.
     */
    private void initializeCorrectionWeights() {
        correctionWeights = new double[N_LAYERS_WEIGHTS][][];
        // Hidden layer 1.
        correctionWeights[HIDDEN1_WEIGHT_INDEX] = new double[HIDDEN_LAYER_SIZE][];
        for (int h=0; h<HIDDEN_LAYER_SIZE; h++) {
            correctionWeights[HIDDEN1_WEIGHT_INDEX][h] = new double[INPUT_LAYER_SIZE];
        }
        // Hidden layer 2.
        correctionWeights[HIDDEN2_WEIGHT_INDEX] = new double[HIDDEN_LAYER_SIZE][];
        for (int h=0; h<HIDDEN_LAYER_SIZE; h++) {
            correctionWeights[HIDDEN2_WEIGHT_INDEX][h] = new double[HIDDEN_LAYER_SIZE];
        }
        // Output layer.
        correctionWeights[OUTPUT_WEIGHT_INDEX] = new double[OUTPUT_LAYER_SIZE][];
        for (int o=0; o<OUTPUT_LAYER_SIZE; o++) {
            correctionWeights[OUTPUT_WEIGHT_INDEX][o] = new double[HIDDEN_LAYER_SIZE];
        }
        // Initialize the correction of the weights to 0.
        for (int lw=0; lw<N_LAYERS_WEIGHTS; lw++) {
            for (int i=0; i<correctionWeights[lw].length; i++) {
                for (int j=0; j<correctionWeights[lw][i].length; j++) {
                    correctionWeights[lw][i][j] = .0;
                }
            }
        }
    }
    /**
     * Initialize the outputs of the input layer with the normalized pixels of 
     * the images.
     * @param image the normalized pixels of the images.
     */
    private void setOutputsFromImages(float[][] image) {
        for (int row=0; row<image.length; row++) {
            outputs[INPUT_LAYER_INDEX][0] = 1.0;    // Additional input for the bias
            for (int col=1; col<image[row].length; col++) {
                outputs[INPUT_LAYER_INDEX][row * image.length + col] = image[row][col];
            }
        }   
    }
    /**
     * Calculates the outputs of the output layer through every layer of the
     * neural network. The first layer has no weights and its outputs are its
     * inputs.
     */
    private void feedForward() {
        for (int layer=1; layer<N_LAYERS; layer++) {
            for (int i=0; i<outputs[layer].length; i++) {
                double sum = weights[layer - 1][i][0]/2;
                for (int j=0; j<outputs[layer - 1].length; j++) {
                    sum += weights[layer-1][i][j] * outputs[layer - 1][j];
                }
                outputs[layer][i] = (1.0 / (1.0 + Math.exp(-sum)));
            }
        }
    }
    /**
     * Calculates the errors of the outputs of the output layer.
     * @param label the current digit.
     */
    private void getOutputErrors(int label) {
        for (int output=0; output<OUTPUT_LAYER_SIZE; output++) {
            if (output == label) outputErrors[output] = 1.0 - outputs[OUTPUT_LAYER_INDEX][output];
            else outputErrors[output] = 0.0 - outputs[OUTPUT_LAYER_INDEX][output];
        }
    }
    /**
     * Backpropagation to update the weights of the output layer through 
     * the previous layer, which is the hidden layer. 
     */
    private void backwardOutputLayer() {
        for (int o=0; o<OUTPUT_LAYER_SIZE; o++) {
            deltas[OUTPUT_WEIGHT_INDEX][o] = outputErrors[o] * outputs[OUTPUT_LAYER_INDEX][o]
                    * (1 - outputs[OUTPUT_LAYER_INDEX][o]);
            for (int h=0; h<HIDDEN_LAYER_SIZE; h++) {
                correctionWeights[OUTPUT_WEIGHT_INDEX][o][h] = (LEARNING_RATE * deltas[OUTPUT_WEIGHT_INDEX][o]
                    * outputs[HIDDEN_LAYER2_INDEX][h]) + (MOMENTUM * correctionWeights[OUTPUT_WEIGHT_INDEX][o][h]);
                weights[OUTPUT_WEIGHT_INDEX][o][h] += correctionWeights[OUTPUT_WEIGHT_INDEX][o][h];
            }
        }
    }
    /**
     * Backpropagation to update the weights of the hidden layer through the errors
     * of the output layer and its inputs.
     */
    private void backwardHiddenLayer() {
        for (int h=0; h<HIDDEN_LAYER_SIZE; h++) {
            double sum = 0;
            for (int j=0; j<OUTPUT_LAYER_SIZE; j++) {
                sum += deltas[OUTPUT_WEIGHT_INDEX][j] * weights[OUTPUT_WEIGHT_INDEX][j][h];
            }
            deltas[HIDDEN2_WEIGHT_INDEX][h] = sum * outputs[HIDDEN_LAYER2_INDEX][h]
                * (1 - (outputs[HIDDEN_LAYER2_INDEX][h]));
            for (int i=0; i<HIDDEN_LAYER_SIZE; i++) {
                correctionWeights[HIDDEN2_WEIGHT_INDEX][h][i] = (LEARNING_RATE * deltas[HIDDEN2_WEIGHT_INDEX][h]
                    * outputs[HIDDEN_LAYER1_INDEX][i]) + (MOMENTUM * correctionWeights[HIDDEN2_WEIGHT_INDEX][h][i]);
                weights[HIDDEN2_WEIGHT_INDEX][h][i] += (correctionWeights[HIDDEN2_WEIGHT_INDEX][h][i]);
            }
        }
        for (int h=0; h<HIDDEN_LAYER_SIZE; h++) {
            double sum = 0;
            for (int j=0; j<HIDDEN_LAYER_SIZE; j++) {
                sum += deltas[HIDDEN2_WEIGHT_INDEX][j] * weights[HIDDEN2_WEIGHT_INDEX][j][h];
            }
            deltas[HIDDEN1_WEIGHT_INDEX][h] = sum * outputs[HIDDEN_LAYER1_INDEX][h]
                * (1 - (outputs[HIDDEN_LAYER1_INDEX][h]));
            for (int i=0; i<INPUT_LAYER_SIZE; i++) {
                correctionWeights[HIDDEN1_WEIGHT_INDEX][h][i] = (LEARNING_RATE * deltas[HIDDEN1_WEIGHT_INDEX][h]
                    * outputs[INPUT_LAYER_INDEX][i]) + (MOMENTUM * correctionWeights[HIDDEN1_WEIGHT_INDEX][h][i]);
                weights[HIDDEN1_WEIGHT_INDEX][h][i] += (correctionWeights[HIDDEN1_WEIGHT_INDEX][h][i]);
            }
        }
    }
    /**
     * Backpropagation algorithm.
     * @param label the current digit.
     */
    private void backPropagation(int label) {
        getOutputErrors(label);
        backwardOutputLayer();
        backwardHiddenLayer();
    }
    /**
     * Get the current prediction of the outputs of the output layer. In order
     * to do that the method calculates the neuron which has the maximum output.
     * @return the neuron which has the maximum output.
     */
    private int getPrediction() {
        int maxNeuron = 0;
        double maxOutput = outputs[OUTPUT_LAYER_INDEX][0];
        for (int out=1; out<OUTPUT_LAYER_SIZE; out++) {
            if (outputs[OUTPUT_LAYER_INDEX][out] > maxOutput) {
                maxOutput = outputs[OUTPUT_LAYER_INDEX][out];
                maxNeuron = out;
            }
        }
        return maxNeuron;
    }
    /**
     * Train the multilayer NN with 2 hidden layers. It tests it every 5 epochs.
     * @param trainingImages normalized training images.
     * @param trainingLabels labels of the training images.
     * @param times training epochs.
     * @param testImages normalized test images.
     * @param testLabels labels of the test images.
     * @param test true to test the nn each 5 epochs, false to not do it.
     * @throws java.io.IOException
     */
    public void train(float trainingImages[][][], int trainingLabels[], int times, 
        float testImages[][][], int testLabels[], boolean test) throws IOException {
        DecimalFormat d = new DecimalFormat(".###");
        double error;
        for (int time=1; time<=times; time++) {
            error = 0.0;
            for (int image=0; image< trainingImages.length; image++) {
                setOutputsFromImages(trainingImages[image]);
                feedForward();
                backPropagation(trainingLabels[image]);
                if (getPrediction() != trainingLabels[image]) error++;
            }
            if (test && time % 5 == 0) test(testImages, testLabels);
            else if (!test) System.out.println(d.format(error / trainingImages.length * 100.0));
        }
    }
    /**
     * Test the multilayer neural network trained with the test images.
     * @param images pixels of the test images.
     * @param labels labels of the test images.
     * @throws java.io.IOException
     */
    public void test(float[][][] images, int[] labels) throws IOException {
        double error = 0.0f;
        DecimalFormat d = new DecimalFormat(".###");
        int currentPrediction = 0;
        for (int image=0; image< images.length; image++) {
            setOutputsFromImages(images[image]);
            feedForward();
            currentPrediction = getPrediction();
            testPredictions.add(currentPrediction);
            if (currentPrediction != labels[image]) error++;
        }
        System.out.println(d.format(error / images.length * 100.0));
        writeTestResults();
    }
    /**
     * Writes the test labels got from the test method.
     * @throws IOException 
     */
    private void writeTestResults() throws IOException {
        String fichero = "./resultados/backpropagation_two_test.txt";
        System.out.println("Writing label predictions in "+ fichero);
        Writer wr = new FileWriter(fichero);
        for (Integer prediction: testPredictions) {
            wr.write(Integer.toString(prediction));
        }
        wr.close();
    }
}
