/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
//import nns.CNN;
import nns.MultilayerNN;
import nns.MultilayerNN2HiddenLayers;
import readingData.MNISTDatabase;
import nns.SimpleNN;

/**
 * Main class.
 * 
 * @author Lidia Sánchez Mérida.
 */
public class Main {
    
    /**
     * Training epochs for the perceptron experiments.
     */
    private static final int TEST_PERCEPTRON_TIMES = 50;
    /**
     * Times to get the best test error rate with the Perceptron.
     */
    private static final int BEST_PERCEPTRON_TIMES = 40;
    /**
     * Learning rate for the Perceptron.
     */
    private static final double PERCEPTRON_LEARNING_RATE = 0.7;
    /**
     * Training epochs for the multilayer neural network experiments.
     */
    private static final int TEST_MULTILAYER_TIMES = 100;
    /**
     * Times to get the best test error rate with a multilayer.
     */
    private static final int BEST_MULTILAYER_TIMES = 55;
    /**
     * Default hidden layer size.
     */
    private static final int HIDDEN_LAYER_SIZE = 256;
    /**
     * Default momentum.
     */
    private static final double MOMENTUM = 0.7;
    /**
     * Default learning rate.
     */
    private static final double LEARNING_RATE = 0.07;
    /**
     * Pixels of the training images.
     */
    private static int[][][] trainingImages;
    /**
     * Normalized pixels of the training images.
     */
    private static float[][][] normalizedTrainingImages;
    /**
     * Labels of the training images.
     */
    private static int[] trainingLabels;
    /**
     * Pixels of the test images.
     */
    private static int[][][] testImages;
    /**
     * Normalized pixels of the test images.
     */
    private static float[][][] normalizedTestImages;
    /**
     * Labels of the test images.
     */
    private static int[] testLabels;
    
    /**
     * Normalizes the pixels of the images.
     * @param images the pixels of the images.
     * @return an array with the normalized pixels of each image.
     */
    private static float[][][] getNormalizedImage(int [][][] images) {
        float [][][] normalizedImage;
        normalizedImage = new float [images.length][images[0].length][images[0].length];
        for (int image=0; image<images.length; image++) {
            normalizedImage[image] = MNISTDatabase.normalize(images[image]);
        }
        return normalizedImage;
    }
    /**
     * Read the images and their labels for training and testing.
     * @throws IOException 
     */
    private static void initializeInputs() throws IOException {
        // Training images.
        String path = "C:\\Users\\usuario\\Desktop\\IC\\Prácticas\\1\\";
        trainingImages = MNISTDatabase.readImages(path + MNISTDatabase.getTrainingImages());
        normalizedTrainingImages = getNormalizedImage(trainingImages);
        // Labels of the training images.
        trainingLabels = MNISTDatabase.readLabels(path + MNISTDatabase.getTrainingLabels());
        
        // Test images.
        testImages = MNISTDatabase.readImages(path + MNISTDatabase.getTestImages());
        normalizedTestImages = getNormalizedImage(testImages);
        // Labels of the test images.
        testLabels = MNISTDatabase.readLabels(path +  MNISTDatabase.getTestLabels());
    }
    /**
     * Experiments with the simple neural network with Perceptron algorithm.
     * It tests different learning rates.
     */
    private static void perceptronExperiments() throws IOException {
        System.out.println("\nPERCEPTRON TRAINING "+TEST_PERCEPTRON_TIMES+" EPOCHS");
        ArrayList<Double> learningRates = new ArrayList(Arrays.asList(0.1, 0.2, 0.3,
            0.4, 0.5, 0.6 ,0.7 ,0.8, 0.9, 1.0));
        for (Double learningRate: learningRates) {
            System.out.println("\nLearning rate: " + learningRate);
            SimpleNN perceptron = new SimpleNN(learningRate);
            perceptron.train(normalizedTrainingImages, trainingLabels, TEST_PERCEPTRON_TIMES,
                normalizedTestImages, testLabels, true);
        }
    }
    /**
     * Experiments with the multilayer neural network with one hidden layer.
     */
    private static void multilayerExperiments() throws IOException {
        System.out.println("EXPERIMENTS WITH DIFFERENT LEARNING RATES.");
        ArrayList<Double> learningRates = new ArrayList(Arrays.asList(0.01, 0.04,
        0.07 , 0.1));
        for (Double learningRate: learningRates) {
            MultilayerNN nn = new MultilayerNN(learningRate, HIDDEN_LAYER_SIZE, MOMENTUM);
            System.out.println("\nMULTILAYER TRAINING "+TEST_MULTILAYER_TIMES+" EPOCHS");
            System.out.println("Learning rate: " + learningRate);
            nn.train(normalizedTrainingImages, trainingLabels, TEST_MULTILAYER_TIMES,
                normalizedTestImages, testLabels, false, true);
        }
        System.out.println("EXPERIMENTS WITH DIFFERENT MOMENTUMS.");
        ArrayList<Double> momentums = new ArrayList(Arrays.asList(0.1, 0.4, 
            0.7, 0.9));
        for (Double momentum: momentums) {
            MultilayerNN nn = new MultilayerNN(LEARNING_RATE, HIDDEN_LAYER_SIZE, momentum);
            System.out.println("MULTILAYER TRAINING "+TEST_MULTILAYER_TIMES+" EPOCHS");
            System.out.println("Momentum: " + momentum);
            nn.train(normalizedTrainingImages, trainingLabels, TEST_MULTILAYER_TIMES,
                normalizedTestImages, testLabels, false, true);
        }
        System.out.println("EXPERIMENTS WITH DIFFERENT SIZE OF THE HIDDEN LAYER.");
        ArrayList<Integer> hiddenLayerSize = new ArrayList(Arrays.asList(100, 256, 400));
        for (Integer size: hiddenLayerSize) {
            MultilayerNN nn = new MultilayerNN(LEARNING_RATE, size, MOMENTUM);
            System.out.println("MULTILAYER TRAINING "+TEST_MULTILAYER_TIMES+" EPOCHS");
            System.out.println("N hidden neurons: " + size);
            nn.train(normalizedTrainingImages, trainingLabels, TEST_MULTILAYER_TIMES,
                normalizedTestImages, testLabels, false, true);
        }
    }
    /**
     * Experiments with the CNN.
     */
    /*private static void cnnExperiments() {
        CNN cnn = new CNN();
        System.out.println("\nCNN TRAINING " + 2 + " EPOCHS");
        cnn.train(normalizedTrainingImages, trainingLabels, 2, normalizedTestImages, testLabels);
    }*/
    /**
     * Experiments.
     * @throws IOException 
     */
    private static void experiments() throws IOException {
        // Experiments menu
        System.out.println("1) Experiments with Perceptron algorithm.");
        System.out.println("2) Experiments with a multilayer neural network with one hidden layer.");
        System.out.println("5) Train CNN.");
        System.out.print("Choose one option: ");
        Scanner input = new Scanner(System.in);
        int option = input.nextInt();
        switch(option) {
            case 1:
                initializeInputs();
                perceptronExperiments();
                break;
            case 2:
                initializeInputs();
                multilayerExperiments();
                break;
            default:
                System.out.println("Opción incorrecta.");
                break;
        }
    }
    /**
     * Train and test one predictive model to show the training errors and the
     * test error along with the label predictions.
     * @throws IOException 
     */
    private static void trainAndTest() throws IOException {
        System.out.println("\n1) Perceptron.");
        System.out.println("2) Backpropagation with one hidden layer.");
        System.out.println("3) Backpropagation with one hidden layer and dropout.");
        System.out.println("4) Backpropagation with two hidden layers.");
        System.out.print("Choose one option: ");
        Scanner input = new Scanner(System.in);
        int option = input.nextInt();
        switch(option) {
            case 1:
                initializeInputs();
                SimpleNN perceptron = new SimpleNN(PERCEPTRON_LEARNING_RATE);
                System.out.println("Training Perceptron.....");
                perceptron.train(normalizedTrainingImages, trainingLabels, BEST_PERCEPTRON_TIMES,
                    normalizedTestImages, testLabels, false);
                System.out.println("Testing Perceptron.....");
                perceptron.test(normalizedTestImages, testLabels);
                break;
            case 2:
                initializeInputs();
                MultilayerNN nn = new MultilayerNN(LEARNING_RATE, HIDDEN_LAYER_SIZE, MOMENTUM);
                System.out.println("Training standard Backpropagation.....");
                nn.train(normalizedTrainingImages, trainingLabels, BEST_MULTILAYER_TIMES,
                    normalizedTestImages, testLabels, false, false);
                System.out.println("Testing standard Backpropagation.....");
                nn.test(normalizedTestImages, testLabels, false);
                break;
            case 3:
                initializeInputs();
                MultilayerNN nnDropOut = new MultilayerNN(LEARNING_RATE, HIDDEN_LAYER_SIZE, MOMENTUM);
                System.out.println("Training backpropagation with dropout.....");
                nnDropOut.train(normalizedTrainingImages, trainingLabels, 100,
                    normalizedTestImages, testLabels, true, false); // true = dropout / false = not test
                System.out.println("Testing backpropagation with dropout.....");
                nnDropOut.test(normalizedTestImages, testLabels, true); // true = dropout
                break;
            case 4:
                initializeInputs();
                MultilayerNN2HiddenLayers nn2 = new MultilayerNN2HiddenLayers(128);
                System.out.println("Training backpropagation with 2 hidden layers.....");
                nn2.train(normalizedTrainingImages, trainingLabels, BEST_MULTILAYER_TIMES,
                    normalizedTestImages, testLabels, false);
                System.out.println("Testing backpropagation with 2 hidden layers.....");
                nn2.test(normalizedTestImages, testLabels);
                break;
            default:
                break;
        }
    }
    /**
     * Main function.
     * @param args
     * @throws IOException 
     */
    public static void main(String[] args) throws IOException {
        // TODO code application logic hereSystem.out.println("MAIN MENU");
        System.out.println("1) Train and test.");
        System.out.println("2) Experiments.");
        System.out.print("Choose one option: ");
        Scanner input = new Scanner(System.in);
        int option = input.nextInt();
        switch(option) {
            case 1:
                trainAndTest();
                break;
            case 2:
                experiments();
                break;
            default:
                break;
        }
    }
}
