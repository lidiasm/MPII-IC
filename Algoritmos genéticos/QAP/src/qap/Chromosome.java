/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package qap;

import java.util.ArrayList;
import java.util.Random;

/**
 *
 * @author Lidia Sánchez Mérida
 */
public class Chromosome {
    /**
     * Ordered installations.
     */
    private int[] permutation;
    /**
     * Cost of the current solution.
     */
    private int fitness;
    
    /**
     * Constructor.
     */
    public Chromosome() {
        fitness = 0;
    }
    /**
     * Gets the current solution.
     * @return the current permutation.
     */
    public int[] getPermutation() {
        return permutation;
    }
    /**
     * Sets the current solution.
     * @param permutation new solution.
     */
    public void setPermutation(int[] permutation) {
        this.permutation = permutation;
    }
    /**
     * Gets the cost of the current solution.
     * @return cost of the current solution.
     */
    public int getFitness() {
        return fitness;
    }
    /**
     * Set the cost of the current solution.
     * @param fitness new cost of the current solution.
     */
    public void setFitness(int fitness) {
        this.fitness = fitness;
    }
    /**
     * Initializes the permutation randomly.
     * @param size number of installations.
     */
    public void initialize(int size) {
        permutation = new int[size];
        ArrayList<Integer> usedRandom = new ArrayList();
        Random r = new Random(); 
        int newRandomNumber;
        for (int i=0; i<permutation.length; i++) {
            newRandomNumber = r.nextInt(size);
            while (usedRandom.contains(newRandomNumber)) {
                newRandomNumber = r.nextInt(size);
            }
            permutation[i] = newRandomNumber;
            usedRandom.add(newRandomNumber);
        }
        calculateFitness();
    }
    /**
     * Calculates the cost of the current solution. It has to be minimum.
     */
    public void calculateFitness() {
        int[][] flows = DataReader.getFlows();
        int[][] distances = DataReader.getDistances();
        if (flows.length == distances.length) {
            for (int i=0; i<flows.length; i++) {
                for (int j=0; j<flows.length; j++) {
                    fitness += flows[i][j]*distances[permutation[i]][permutation[j]];
                }
            }
        }
    }
    /**
     * Exchanges the elements of two different position of the permutation.
     * @param pos1 first position to exchange.
     * @param pos2 second position to exchange.
     */
    public void mutateOperator(int pos1, int pos2) {
        int swap = permutation[pos1];
        permutation[pos1] = permutation[pos2];
        permutation[pos2] = swap;
    }
    /**
     * Shows the permutation and its fitness.
     * @return 
     */
    @Override
    public String toString() {
        String resultado = "\nFitness: "+fitness+"\nPermutation: ";
        for (int i=0; i<permutation.length; i++) {
            resultado += permutation[i] + " ";
        }
        return resultado;
    }
}
