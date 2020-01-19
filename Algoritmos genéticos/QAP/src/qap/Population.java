/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package qap;

/**
 * Class which represents the population of chromosomes.
 * 
 * @author Lidia Sánchez Mérida
 */
public class Population {
    /**
     * Array of chromosomes.
     */
    private Chromosome[] population;
    
    /**
     * Constructor.
     * @param size number of chromosomes.
     */
    public Population(int size) {
        population = new Chromosome[size];
    }
    /**
     * Creates a new generation of chromosomes.
     * @param chromosomeSize number of chromosomes.
     */
    public void initialize(int chromosomeSize) {
        for (int i=0; i<population.length; i++) {
            population[i] = new Chromosome();
            population[i].initialize(chromosomeSize);
            //population[i].calculateFitness(flows, distances);
        }
    }
    /**
     * Shows the details of the chromosomes of the current population.
     * @return 
     */
    @Override
    public String toString() {
        String resultado = "";
        for (int i=0; i<population.length; i++) {
            resultado += "\n\nChromosome "+i+population[i].toString();
        }
        return resultado;
    }
}
