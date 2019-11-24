/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.io.IOException;
import readingData.MNISTDatabase;
import nns.MultilayerNN;
import nns.SimpleNN;

/**
 * Main class.
 * 
 * @author Lidia Sánchez Mérida.
 */
public class Main {
    
    /**
     * Training epochs.
     */
    private static final int TIMES = 50;
    
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
     * @param args the command line arguments
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws IOException {
        // TODO code application logic here
        // Training images.
        String path = "C:\\Users\\usuario\\Desktop\\IC\\Prácticas\\1\\";
        int[][][] trainingImages = MNISTDatabase.readImages(path + MNISTDatabase.getTrainingImages());
        float[][][] normalizedTrainingImages = getNormalizedImage(trainingImages);
        // Labels of the training images.
        int trainingLabels[] = MNISTDatabase.readLabels(path + MNISTDatabase.getTrainingLabels());
        
        // Test images.
        int testImages[][][] = MNISTDatabase.readImages(path + MNISTDatabase.getTestImages());
        float[][][] normalizedTestImages = getNormalizedImage(testImages);
        // Labels of the test images.
        int testLabels[] = MNISTDatabase.readLabels(path +  MNISTDatabase.getTestLabels());
        
        ////////// PERCEPTRON ////////////
        System.out.println("\nPERCEPTRON TRAINING "+TIMES+" EPOCHS");
        SimpleNN perceptron = new SimpleNN();
        perceptron.train(normalizedTrainingImages, trainingLabels, TIMES,
            normalizedTestImages, testLabels);

        MultilayerNN nn = new MultilayerNN();
        System.out.println("\nMULTILAYER TRAINING "+TIMES+" EPOCHS");
        nn.train(normalizedTrainingImages, trainingLabels, TIMES,
            normalizedTestImages, testLabels);
    }
}
