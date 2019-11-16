/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mains;

import java.io.IOException;
import neuralnetworks.MultilayerNN;
import neuralnetworks.SimpleNN;
import readingdata.MNISTDatabase;

/**
 *
 * @author Lidia Sánchez Mérida
 */
public class Main {
    
    private static final int TIMES = 20;
    
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
        // Read the test images file
        int testImages[][][];
        path = "C:\\Users\\usuario\\Desktop\\IC\\Prácticas\\1\\";
        testImages = MNISTDatabase.readImages(path + MNISTDatabase.getTestImages());
        // Read the training labels file
        int testLabels[];
        testLabels = MNISTDatabase.readLabels(path +  MNISTDatabase.getTestLabels());
        
        ////////// PERCEPTRON ////////////
        /*System.out.println("\nPERCEPTRON\nTRAINING 20 EPOCS");
        SimpleNN perceptron = new SimpleNN();
        perceptron.train(images, labels, TIMES);
        System.out.println("\nTEST");
        perceptron.test(testImages, testLabels);*/
        
        ///////// MULTILAYER BACKPROPAGATION //////
        MultilayerNN backpropagation = new MultilayerNN();
        backpropagation.train(images, labels, 1);
    }
}
