/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package nns;

import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Random;

/**
 * Class which represents a simple neural network with two layers, one input layer
 * and one output layer. It will be trained through perceptron algorithm.
 * 
 * @author Lidia Sánchez Mérida.
 */
public class SimpleNN {
    /**
     * Number of layers.
     */
    private static final int N_LAYERS = 2;
    /**
     * Size of the input layer.
     */
    private static final int INPUT_LAYER_SIZE = (28*28) + 1;
    /**
     * Size of the output layer.
     */
    private static final int OUTPUT_LAYER_SIZE = 10;
    /**
     * Index of the outputs of the input layer.
     */
    private static final int INPUT_LAYER_INDEX = 0;
    /**
     * Index of the outputs of the output layer.
     */
    private static final int OUTPUT_LAYER_INDEX = 1;
    /**
     * Weights of the output layer.
     */
    private double weights[][];
    /**
     * Outputs of the input and the output layer. The outputs of the input layer
     * will be its inputs.
     */
    private double outputs[][];
    /**
     * Test predictions.
     */
    private ArrayList<Integer> testPredictions;
    /**
     * Learning rate.
     */
    private double LEARNING_RATE;
    
    /**
     * Constructor of a simple neuronal network.
     * @param rate current learning rate.
     */
    public SimpleNN(double rate) {
        outputs = new double[N_LAYERS][];
        outputs[INPUT_LAYER_INDEX] = new double[INPUT_LAYER_SIZE];
        outputs[OUTPUT_LAYER_INDEX] = new double[OUTPUT_LAYER_SIZE];
        weights = new double[OUTPUT_LAYER_SIZE][INPUT_LAYER_SIZE];
        initializeWeights();
        LEARNING_RATE=rate;
        testPredictions = new ArrayList();
    }
    /**
     * Initialize the weights of the output layer.
     */
    private void initializeWeights() {
        Random random;
        double max = 0.1, min = -0.1;
        for (int output=0; output<OUTPUT_LAYER_SIZE; output++) {
            random = new Random(0);
            weights[output][0] = 0.0;   // Bias
            for (int w=1; w<INPUT_LAYER_SIZE; w++) {
                weights[output][w] = min + random.nextDouble() *(max-min);
            }
        }
    }
    /**
     * Initialize the outputs of the input layer with its inputs from the images.
     * @param image the normalized pixels of an image.
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
     * Calculates the outputs of the output layer with a lineal function 
     * through the outputs of the input layer.
     */
    private void getOutputs() {
        double y;
        for (int output=0; output<OUTPUT_LAYER_SIZE; output++) {
            y = 0.0;
            for (int in=0; in<INPUT_LAYER_SIZE; in++) {
                y += (weights[output][in] * outputs[INPUT_LAYER_INDEX][in]);
            }
            outputs[OUTPUT_LAYER_INDEX][output] = y >= 0 ? 1.0 : 0.0;
        }
    }
    /**
     * Gets the test predictions to write them in a file. If the neuron of the
     * current label is activated then it will be the prediction. If it's not,
     * whatever neuron which is activated will be the prediction.
     * @param label current label of the test image.
     */
    private void getTestPredictions(int label) {
        if (outputs[OUTPUT_LAYER_INDEX][label] == 1.0) testPredictions.add(label);
        else {
            for (int out=0; out<OUTPUT_LAYER_SIZE; out++) {
                if (outputs[OUTPUT_LAYER_INDEX][out] == 1.0) {
                    testPredictions.add(out);
                    break;
                }
            }
        }
    }
    /**
     * Update the weights of the output layer with the lineal function.
     * @param label the current digit of the training image.
     */
    private void updateWeights(int label) {
        for (int out=0; out<OUTPUT_LAYER_SIZE; out++) {
            // It should have been activated but it isn't.
            if (outputs[OUTPUT_LAYER_INDEX][out] == 0.0 && out == label) {
                for (int w=0; w<weights[out].length; w++) {
                    weights[out][w] += (LEARNING_RATE*outputs[INPUT_LAYER_INDEX][w]);
                }
            }
            // It shouldn't have been activated but it is.
            else if (outputs[OUTPUT_LAYER_INDEX][out] == 1.0 && out != label) {
                for (int w=0; w<weights[out].length; w++) {
                    weights[out][w] += (LEARNING_RATE*(-1)*outputs[INPUT_LAYER_INDEX][w]);
                }
            }
        }
    }
    /**
     * Train simple neural network with Perceptron algorithm. It tests the
     * NN every 5 epochs.
     * @param trainingImages normalized training images.
     * @param trainingLabels labels of the training images.
     * @param times training epochs.
     * @param testImages normalized test images.
     * @param testLabels labels of the test images.
     * @param test true to train the nn each 5 epochs, false to not do it.
     * @throws java.io.IOException
     */
    public void train(float trainingImages[][][], int trainingLabels[], int times, 
        float testImages[][][], int testLabels[], boolean test) throws IOException {
        double error;
        DecimalFormat d = new DecimalFormat(".###");
        for (int time=1; time<=times; time++) {
            error = 0.0;
            for (int image=0; image<trainingImages.length; image++) {
                setOutputsFromImages(trainingImages[image]);
                getOutputs();
                updateWeights(trainingLabels[image]);
                // Prediction
                if (outputs[OUTPUT_LAYER_INDEX][trainingLabels[image]] == 0.0) error++;
            }
            if (test && time % 5 == 0) test(testImages, testLabels);
            else if (!test) System.out.println(d.format(error / trainingImages.length * 100.0));
        }
    }
    /**
     * Test the NN.
     * @param images normalized pixels of the test images.
     * @param labels the labels of the test images.
     * @throws java.io.IOException
     */
    public void test(float images[][][], int labels[]) throws IOException {
        double error;
        DecimalFormat d = new DecimalFormat(".###");
        error = 0.0;
        for (int image=0; image<images.length; image++) {
            setOutputsFromImages(images[image]);
            getOutputs();
            getTestPredictions(labels[image]);
            // Prediction
            if (outputs[OUTPUT_LAYER_INDEX][labels[image]] == 0.0) error++;
        }
        System.out.println(d.format(error / images.length * 100.0));
        writeTestResults();
    }
    /**
     * Writes the test labels got from the test method.
     * @throws IOException 
     */
    private void writeTestResults() throws IOException {
        System.out.println("Writing label predictions in ./resultados/perceptron_test.txt");
        Writer wr = new FileWriter("./resultados/perceptron_test.txt");
        for (Integer prediction: testPredictions) {
            wr.write(Integer.toString(prediction));
        }
        wr.close();
    } 
}
