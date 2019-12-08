/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package nns;

import java.text.DecimalFormat;
import java.util.Random;

/**
 * Class which represents a convolutional neural network.
 * 
 * @author Lidia Sánchez Mérida.
 */
public class CNN {

    //private static final int INPUT_LAYER_INDEX = 0;
    private static final int HIDDEN_LAYER_INDEX = 0;
    private static final int OUTPUT_LAYER_INDEX = 1;
    private static final int N_FULL_CONNECTED_LAYERS = 2;
    /**
     * Pixels of the image (28x28).
     */
    private static final int IMAGE_SIZE = 28;
    /**
     * Size of the input layer.
     */
    private static final int INPUT_LAYER_SIZE = IMAGE_SIZE*IMAGE_SIZE;

    /**
     * Size of the hidden layer.
     */
    private static final int HIDDEN_LAYER_SIZE = 256;

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
    
    private double[][] outputs;
    private double[][][] weights;
    private double[] outputErrors;
    private double[][] deltas;
    private double[][][] correctionWeights;
    ///////////////////////////////////////////////////////
    private static final int KERNEL_SIZE = 5;
    private static final int FEATURES_MAP_SIZE = 16;
    private static final int CONVOLVE_OUTPUTS_SIZE = IMAGE_SIZE - KERNEL_SIZE + 1;  //24
    private double[][][] convolveOutputs;
    
    private double kernel[][][];
    //private double[][][] kernelDeltas;
    //private double[] bias;
    //private double[] biasDeltas;
    
    private double[][][] convErrors;
    
    //private double[][][] convInputs;
    private double[][][] convInputDeltas;
    
    ////////////////////////////////////////////////////////
    private static final int S = 1;
    private static final int POOL_K_SIZE = 2;
    private static final int POOLING_OUTPUTS_SIZE = (CONVOLVE_OUTPUTS_SIZE - POOL_K_SIZE)/(S+1);    // 11
    private double[][][] poolingOutputs;
    private int[][][] switchX, switchY;
    private double[][][] poolInputDeltas;
    
    public CNN() {
        kernel = new double[FEATURES_MAP_SIZE][KERNEL_SIZE][KERNEL_SIZE];
        //bias = new double[FEATURES_MAP_SIZE];
       // convInputs = new double[FEATURES_MAP_SIZE][CONVOLVE_OUTPUTS_SIZE][CONVOLVE_OUTPUTS_SIZE];
        convolveOutputs = new double[FEATURES_MAP_SIZE][CONVOLVE_OUTPUTS_SIZE][CONVOLVE_OUTPUTS_SIZE];
        
        convInputDeltas = new double[FEATURES_MAP_SIZE][KERNEL_SIZE][KERNEL_SIZE];
        //kernelDeltas = new double[FEATURES_MAP_SIZE][KERNEL_SIZE][KERNEL_SIZE];
        convErrors = new double[FEATURES_MAP_SIZE][CONVOLVE_OUTPUTS_SIZE][CONVOLVE_OUTPUTS_SIZE];
        //biasDeltas = new double[CONV_K_SIZE];
        
        //////////////////////
        poolingOutputs = new double[FEATURES_MAP_SIZE][POOLING_OUTPUTS_SIZE][POOLING_OUTPUTS_SIZE];
        switchX = new int[FEATURES_MAP_SIZE][POOLING_OUTPUTS_SIZE][POOLING_OUTPUTS_SIZE];
        switchY = new int[FEATURES_MAP_SIZE][POOLING_OUTPUTS_SIZE][POOLING_OUTPUTS_SIZE];
        poolInputDeltas = new double[FEATURES_MAP_SIZE][CONVOLVE_OUTPUTS_SIZE][CONVOLVE_OUTPUTS_SIZE];  //24x24
        for (int f=0; f<FEATURES_MAP_SIZE; f++) {
            for (int i=0; i<CONVOLVE_OUTPUTS_SIZE; i++) {
                for (int j=0; j<CONVOLVE_OUTPUTS_SIZE; j++) {
                    poolInputDeltas[f][i][j] = 0.0;
                }
            }
        }
        
        ///////////////////////
        // Weihts of the hidden and the output layer
        initializeWeights();
        
        // Outputs of the hidden and the output layer.
        outputs = new double[N_FULL_CONNECTED_LAYERS][];
        outputs[HIDDEN_LAYER_INDEX] = new double[HIDDEN_LAYER_SIZE*FEATURES_MAP_SIZE];
        outputs[OUTPUT_LAYER_INDEX] = new double[OUTPUT_LAYER_SIZE];
        // Initialize the errors of the outputs array.
        outputErrors = new double[OUTPUT_LAYER_SIZE];
        
        // Initialize deltas array.
        deltas = new double[N_FULL_CONNECTED_LAYERS][];
        deltas[HIDDEN_LAYER_INDEX] = new double[HIDDEN_LAYER_SIZE];
        deltas[OUTPUT_LAYER_INDEX] = new double[OUTPUT_LAYER_SIZE];
        
        // Initializing the future corrections of the weights.
        initializeCorrectionWeights();
    }
    /**
     * Initialize the kernels of each feature map.
     */
    private void initializeKernels() {
        Random random = new Random(0);
        double min=-1.0, max=1.0;
        for (int m=0; m<FEATURES_MAP_SIZE; m++) {
            for (int k1=0; k1<KERNEL_SIZE; k1++) {
                for (int k2=0; k2<KERNEL_SIZE; k2++) {
                    kernel[m][k1][k2] = min + random.nextDouble() *(max-min);
                }
            }
        }
    }
    /**
     * Initialize the weights of the hidden layer.
     */
    private void initializeWeights() {
        weights = new double[N_FULL_CONNECTED_LAYERS][][];
        // Hidden layer.
        weights[HIDDEN_LAYER_INDEX] = new double[HIDDEN_LAYER_SIZE][];
        for (int h=0; h<HIDDEN_LAYER_SIZE; h++) {
            weights[HIDDEN_LAYER_INDEX][h] = new double[FEATURES_MAP_SIZE*POOLING_OUTPUTS_SIZE*POOLING_OUTPUTS_SIZE];
        }
        // Output layer.
        weights[OUTPUT_LAYER_INDEX] = new double[OUTPUT_LAYER_SIZE][];
        for (int o=0; o<OUTPUT_LAYER_SIZE; o++) {
            weights[OUTPUT_LAYER_INDEX][o] = new double[HIDDEN_LAYER_SIZE*FEATURES_MAP_SIZE];
        }
        // Random weights
        Random random;
        double max = 0.1, min = -0.1;
        for (int layer=0; layer<N_FULL_CONNECTED_LAYERS; layer++) {
            for (int neuron=0; neuron<weights[layer].length; neuron++) {
                random = new Random(0);
                //weights[layer][neuron][0] = 0.0;
                for (int i=0/*i=1*/; i<weights[layer][neuron].length; i++) {
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
        correctionWeights = new double[N_FULL_CONNECTED_LAYERS][][];
        // Hidden layer.
        correctionWeights[HIDDEN_LAYER_INDEX] = new double[HIDDEN_LAYER_SIZE][];
        for (int h=0; h<HIDDEN_LAYER_SIZE; h++) {
            correctionWeights[HIDDEN_LAYER_INDEX][h] = new double[FEATURES_MAP_SIZE*POOLING_OUTPUTS_SIZE*POOLING_OUTPUTS_SIZE];
        }
        // Output layer.
        correctionWeights[OUTPUT_LAYER_INDEX] = new double[OUTPUT_LAYER_SIZE][];
        for (int o=0; o<OUTPUT_LAYER_SIZE; o++) {
            correctionWeights[OUTPUT_LAYER_INDEX][o] = new double[HIDDEN_LAYER_SIZE*FEATURES_MAP_SIZE];
        }
        // Initialize the correction of the weights to 0.
        for (int lw=0; lw<N_FULL_CONNECTED_LAYERS; lw++) {
            for (int i=0; i<correctionWeights[lw].length; i++) {
                for (int j=0; j<correctionWeights[lw][i].length; j++) {
                    correctionWeights[lw][i][j] = 0.0;
                }
            }
        }
    }
    /**
     * Convolve method which applies a kernel to the current image to get a
     * 24x24 feature image.
     * @param f_filter current map.
     * @param pixel1 current row pixel of the image.
     * @param pixel2 current col pixel of the image.
     * @param image current image.
     * @return convolve value.
     */
    private double convolve(int f_filter, int pixel1, int pixel2, float[][] image) {
        double result = 0.0;
        for (int k1=0; k1<KERNEL_SIZE; k1++) {
            for (int k2=0; k2<KERNEL_SIZE; k2++) {
                result += kernel[f_filter][k1][k2] * image[pixel1+k1][pixel2+k2];
            }
        }
        return result;
    }
    /**
     * Calculates the outputs of the convolutional layer. In order to do it,
     * it calculates the 24x24 features of each map.
     * @param image current image.
     */
    private void convolutionalForward(float[][] image) {
        for (int f=0; f<FEATURES_MAP_SIZE; f++) {   // 16 maps
            for (int i=0; i<CONVOLVE_OUTPUTS_SIZE; i++) {   // 24x24
                for (int j=0; j<CONVOLVE_OUTPUTS_SIZE; j++) {
                    convolveOutputs[f][i][j] = convolve(f, i, j, image);
                }
            }
        }
    }
    /**
     * Max pooling method. It calculates the maximum value between K elements of
     * an image made by the convolutional layer.
     * @param i row index of the pixel of an image.
     * @param j col index of the pixel of an image.
     * @return the maximum value between k elements.
     */
    private double maxPooling(int i, int j) {
        int x_coord, y_coord;
        double max = Double.NEGATIVE_INFINITY, pixel;
        for (int f=0; f<FEATURES_MAP_SIZE; f++) {
            for (int k1=1; k1<=POOL_K_SIZE; k1++) {
                for (int k2=1; k2<=POOL_K_SIZE; k2++) {
                    x_coord = S*(i-1)+k1;   // ????????????
                    y_coord = S*(j-1)+k2;
                    pixel = convolveOutputs[f][x_coord][y_coord];
                    if (pixel > max) {
                        max = pixel;
                        switchX[f][i][j] = x_coord;
                        switchY[f][i][j] = y_coord;
                    }
                }
            }
        }
        return max;
    }
    /**
     * Calculates the outputs of the pooling layer applying max pooling. In order
     * to do it, it calculates images of 11x11.
     */
    private void poolingForward() {
        for (int f=0; f<FEATURES_MAP_SIZE; f++) {
            for (int i=0; i<POOLING_OUTPUTS_SIZE; i++) {
                for (int j=0; j<POOLING_OUTPUTS_SIZE; j++) {
                    // Max pool
                    poolingOutputs[f][i][j] = maxPooling(i, j);
                }
            }
        }
    }
    /**
     * Feed forward of the hidden layer. Calculates the outputs with the pooling
     * outputs and the sigmoidal function.
     */
    private void fullConnectedLayersForward() {
        // For the hidden layer. It takes the outputs of the pooling layer as inputs.
        double sum;
        int outputsHiddenLayer = 0, weightsHiddenLayer;
        for (int h=0; h<HIDDEN_LAYER_SIZE; h++) {
            weightsHiddenLayer = 0;
            for (int f=0; f<FEATURES_MAP_SIZE; f++) {   // Cada neurona de la capa oculta recibe las 16 imágenes 11x11????
                sum = 0.0;
                for (int i=0; i<POOLING_OUTPUTS_SIZE; i++) {
                    for (int j=0; j<POOLING_OUTPUTS_SIZE; j++) {
                        sum += weights[HIDDEN_LAYER_INDEX][h][weightsHiddenLayer]*poolingOutputs[f][i][j];
                        weightsHiddenLayer++;
                    }
                }
                outputs[HIDDEN_LAYER_INDEX][outputsHiddenLayer] = (1.0 / (1.0 + Math.exp(-sum)));
                outputsHiddenLayer++;
            }
        }
        // For the output layer. It takes the outputs of the hidden layer as inputs.
        for (int i=0; i<OUTPUT_LAYER_SIZE; i++) {
            outputsHiddenLayer = 0;
            sum = 0.0;
            for (int j=0; j<weights[OUTPUT_LAYER_INDEX][i].length; j++) {
                sum += weights[OUTPUT_LAYER_INDEX][i][j]*outputs[HIDDEN_LAYER_INDEX][outputsHiddenLayer];
                outputsHiddenLayer++;
            }
            
            outputs[OUTPUT_LAYER_INDEX][i] = (1.0 / (1.0 + Math.exp(-sum)));
        }
    }
    /**
     * Feed forward process.
     * @param image 
     */
    private void feedForward(float[][] image) {
        convolutionalForward(image);
        poolingForward();
        fullConnectedLayersForward();
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
            deltas[OUTPUT_LAYER_INDEX][o] = outputErrors[o] * 
                outputs[OUTPUT_LAYER_INDEX][o] * (1 - outputs[OUTPUT_LAYER_INDEX][o]); //y(1-y)
            for (int h=0; h<weights[OUTPUT_LAYER_INDEX][o].length; h++) {
                correctionWeights[OUTPUT_LAYER_INDEX][o][h] = (LEARNING_RATE * deltas[OUTPUT_LAYER_INDEX][o]
                    * outputs[HIDDEN_LAYER_INDEX][h]) + (MOMENTUM * correctionWeights[OUTPUT_LAYER_INDEX][o][h]);
                weights[OUTPUT_LAYER_INDEX][o][h] += correctionWeights[OUTPUT_LAYER_INDEX][o][h];
            }
        }
    }
    /**
     * Backpropagation to update the weights of the hidden layer through the errors
     * of the output layer and its inputs, which are the outputs of the pooling layer.
     */
    private void backwardHiddenLayer() {
        int outHiddenIndex;
        for (int h=0; h<HIDDEN_LAYER_SIZE; h++) {
            double sum = 0;
            for (int j=0; j<OUTPUT_LAYER_SIZE; j++) {
                for (int out=0; out<weights[OUTPUT_LAYER_INDEX][j].length; out++) {
                    sum += deltas[OUTPUT_LAYER_INDEX][j] * weights[OUTPUT_LAYER_INDEX][j][out];
                }
            }
            outHiddenIndex = h;
            deltas[HIDDEN_LAYER_INDEX][h] = 0.0;
            for (int m=0; m<FEATURES_MAP_SIZE; m++) {
                deltas[HIDDEN_LAYER_INDEX][h] += sum * outputs[HIDDEN_LAYER_INDEX][outHiddenIndex]
                    * (1 - (outputs[HIDDEN_LAYER_INDEX][outHiddenIndex]));
                outHiddenIndex += HIDDEN_LAYER_SIZE;
            }
            // Pooling layer
            int weightsIndex = 0;
            for (int f=0; f<FEATURES_MAP_SIZE; f++) {
                for (int i=0; i<POOLING_OUTPUTS_SIZE; i++) {
                    for (int j=0; j<POOLING_OUTPUTS_SIZE; j++) {
                        correctionWeights[HIDDEN_LAYER_INDEX][h][weightsIndex] = (LEARNING_RATE * deltas[HIDDEN_LAYER_INDEX][h]
                            * poolingOutputs[f][i][j]) + (MOMENTUM * correctionWeights[HIDDEN_LAYER_INDEX][h][weightsIndex]);
                        weights[HIDDEN_LAYER_INDEX][h][weightsIndex] += (correctionWeights[HIDDEN_LAYER_INDEX][h][weightsIndex]);
                        weightsIndex++;
                    }
                }
            }
        }
    }
    /**
     * Backpropagation between the hidden layer and the max pooling layer.
     * It connects the error of the hidden layer to the max neuron. 
     */
    private void backwardMaxPooling() {
        int max_x, max_y;
        for (int h=0; h<HIDDEN_LAYER_SIZE; h++) {
            for (int f=0; f<FEATURES_MAP_SIZE; f++) {
                for (int i=0; i<POOLING_OUTPUTS_SIZE; i++) {
                    for (int j=0; j<POOLING_OUTPUTS_SIZE; j++) {
                        max_x = switchX[f][i][j];
                        max_y = switchY[f][i][j];
                        poolInputDeltas[f][max_x][max_y] = deltas[HIDDEN_LAYER_INDEX][h];   // pool deltas inicializado a 0 en el constructor
                    }
                }
            }
        }
    }
    /**
     * Backpropagation between the pooling layer and the convolutional layer. It
     * updates the kernel of each feature map considering the errors of the maximum
     * inputs and the pixels of the image which are connected.
     * @param image current training image. 
     */
    private void backwardConvolve(float[][] image) {
        double /*sum,*/ delta;
        for (int f=0; f<FEATURES_MAP_SIZE; f++) {
            //sum = 0.0;
            for (int i=0; i<CONVOLVE_OUTPUTS_SIZE; i++) {
                for (int j=0; j<CONVOLVE_OUTPUTS_SIZE; j++) {
                    delta = poolInputDeltas[f][i][j];
                    for (int k1=0; k1<KERNEL_SIZE; k1++) {
                        for (int k2=0; k2<KERNEL_SIZE; k2++) {
                            kernel[f][k1][k2] += delta*image[i+k1][j+k2]; /// kernelDeltas
                        }
                    }
                }
            }
        }
    }
    /**
     * Backpropagation process.
     * @param label current training label.
     * @param image current training image.
     */
    private void backpropagation(int label, float[][] image) {
        getOutputErrors(label);
        backwardOutputLayer();
        backwardHiddenLayer();
        backwardMaxPooling();
        backwardConvolve(image);
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
     * Train CNN.
     * @param trainingImages normalized training images.
     * @param trainingLabels labels of the training images.
     * @param times training epochs.
     * @param testImages normalized test images.
     * @param testLabels labels of the test images.
     */
    public void train(float trainingImages[][][], int trainingLabels[], int times, 
        float testImages[][][], int testLabels[]) {
        DecimalFormat d = new DecimalFormat(".###");
        double error;
        for (int time=1; time<=times; time++) {
            error = 0.0;
            for (int image=0; image< trainingImages.length; image++) {
                feedForward(trainingImages[image]);
                backpropagation(trainingLabels[image], trainingImages[image]);
                if (getPrediction() != trainingLabels[image]) error++;
            }
            System.out.println("Time "+time+" / Training rate error: "
                +d.format(error / trainingImages.length * 100.0)+"%");
        }
    }
    /**
     * Test the CNN trained with the test images.
     * @param images pixels of the test images.
     * @param labels labels of the test images.
     */
    public void test(float[][][] images, int[] labels) {
        double error = 0.0f;
        DecimalFormat d = new DecimalFormat(".###");
        for (int image=0; image< images.length; image++) {
            feedForward(images[image]);
            if (getPrediction() != labels[image]) error++;
        }
        System.out.println("Test rate error: "+d.format(error / images.length * 100.0)+"%");
    }
}
