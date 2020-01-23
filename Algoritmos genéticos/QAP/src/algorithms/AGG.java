/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package algorithms;

import java.util.Random;
import qap.Chromosome;
import qap.DataReader;

/**
 * Class which represents the standard evolutional algorithm with two different
 * cross operators: position cross and OX.
 * 
 * @author Lidia Sánchez Mérida
 */
public class AGG {
    /**
     * Array of chromosomes.
     */
    private Chromosome[] population;
    /**
     * Probability of mutation.
     */
    private double mutationProb;
    /**
     * Probability of crossing.
     */
    private double crossProb;
    
    /**
     * Constructor.
     * @param size
     * @param mProb
     * @param cProb 
     */
    public AGG(int size, double mProb, double cProb) {
        population = new Chromosome[size];
        mutationProb = mProb;
        crossProb = cProb;
    }
    /**
     * Creates a new generation of chromosomes and calculates the fitness for
     * each one.
     */
    public void initialize() {
        for (int i=0; i<population.length; i++) {
            population[i] = new Chromosome();
            population[i].initialize(DataReader.getNInstallations());
            population[i].calculateFitness();
        }
        this.sortPopulation();
    }
    /**
     * Sorts the population using the fitness of each chromosome. Thus the
     * first will be the best solutions.
     */
    public void sortPopulation() {
        Chromosome temp;
        for (int i=1; i<population.length; i++) {
            for (int j=i; j>0; j--) {
                if(population[j].getFitness() < population[j-1].getFitness()) {
                    temp = population[j];
                    population[j] = population[j-1];
                    population[j-1] = temp;
                }
            }
        }
    }
    /**
     * Chooses two permutation randomly and returns the one which has the best
     * fitness. This will be the one whose index is lower because the population
     * is ordered by their fitness.
     * @return index of the best permutation between two.
     */
    public int tournamentBinarySelection() {
        Random r = new Random();
        int p1 = r.nextInt(population.length);
        int p2 = r.nextInt(population.length);
        while (p1 == p2) {
            p2 = r.nextInt(population.length);
        }
        if (p1 < p2) return p1;
        return p2;
    }
    /**
     * Checks if a location is already set in the permutation array.
     * @param permutation permutation to check.
     * @param el location to search.
     * @return true if the location is in the array, false if it's not.
     */
    public boolean checkDuplicates(int[] permutation, int el) {
        boolean duplicates = false;
        for (int i=0; i<permutation.length; i++) {
            if (permutation[i] == el) {
                return true;
            }
        }
        return duplicates;
    }
    /**
     * Returns a new chromosome by crossing two of the population. The common
     * genes of the fathers will remain in the son.
     * @param c1 father one.
     * @param c2 father two.
     * @return new chromosome.
     */
    public Chromosome crossPositionOperator(Chromosome c1, Chromosome c2) {
        Chromosome c = new Chromosome();
        Random r = new Random();
        int per3[] = new int[c1.getPermutation().length];
        // Initialize the permutation of the son to -1
        for (int i=0; i<per3.length; i++) per3[i] = -1;
        // Common genes
        for (int i=0; i<c1.getPermutation().length; i++) {
            if (c1.getPermutation()[i] == c2.getPermutation()[i])
                per3[i] = c1.getPermutation()[i];
        }
        // Rest of the permutation
        for (int i=0; i<per3.length; i++) {
            if (per3[i] == -1) {
                int gene = r.nextInt(per3.length);
                while (checkDuplicates(per3, gene)) {
                    gene = r.nextInt(per3.length);
                }
                per3[i] = gene;
            }
        }
        c.setPermutation(per3);
        c.calculateFitness();
        return c;
    }
    /**
     * 
     * @param c1
     * @param c2
     * @return 
     */
    public Chromosome crossOXOperator(Chromosome c1, Chromosome c2) {
        Chromosome son = new Chromosome();
        int per3[] = new int[c1.getPermutation().length];
        // Initialize the permutation of the son to -1
        for (int i=0; i<per3.length; i++) per3[i] = -1;
        // Get the substring in the center of the father 1
        int mean_element = c1.getPermutation().length/2;
        int first_element = mean_element - (mean_element/2);
        int last_element = mean_element + (mean_element/2);
        for (int i=first_element; i<=last_element; i++) {
            per3[i] = c1.getPermutation()[i];
        }
        // Complete the son with the father 2
        for (int i=0; i<per3.length; i++) {
            if (per3[i] == -1) {
                per3[i] = c2.getPermutation()[i];
            }
        }
        son.setPermutation(per3);
        son.calculateFitness();
        return son;
    }
    /**
     * Chooses a chromosome of the population randomly and exchanges two genes
     * choosen randomly too. It repeates the process as many times as genes it
     * has to mutate.
     */
    public void mutationOperator() {
        int genesToMutate = (int) this.mutationProb*(population.length*DataReader.getNInstallations());
        Random r = new Random();
        int chromToMutate = r.nextInt(population.length);
        int gene1, gene2;
        for (int g=0; g<genesToMutate; g++) {
            gene1 = r.nextInt(DataReader.getNInstallations());
            gene2 = r.nextInt(DataReader.getNInstallations());
            // They have to be different
            while (gene1 == gene2) {
                gene2 = r.nextInt(DataReader.getNInstallations());
            }
            // Exchange genes
            population[chromToMutate].mutateOperator(gene1, gene2);
        }
        population[chromToMutate].calculateFitness();
    }
    /**
     * 
     * @param ntimes 
     */
    public void aggCrossPosition(int ntimes) {
        Chromosome[] previousPopulation;
        Chromosome[] fathers = new Chromosome[population.length];
        Chromosome[] sons = new Chromosome[population.length];
        int nCrosses = (int) (crossProb*(population.length/2) + 1);
        int crossFather = 0, father;
        Chromosome son1, son2;
        for (int n=0; n<ntimes; n++)  {
            sortPopulation();
            previousPopulation = population;
            // Fathers
            for (int i=0; i<population.length; i++) {
                father = tournamentBinarySelection();
                fathers[i] = population[i];
            }
            // Cross position operator
            for (int c=0; c<nCrosses; c++) {
                son1 = this.crossPositionOperator(fathers[crossFather], fathers[crossFather+1]);
                son2 = this.crossPositionOperator(fathers[crossFather], fathers[crossFather+1]);
                sons[crossFather] = son1;
                sons[crossFather] = son2;
                crossFather += 2;
            }
            // Complete the population with the non crossed fathers
            for (int f=crossFather; f<fathers.length; f++) {
                sons[f] = fathers[f];
            }
            // Mutation
            population = sons;
            this.mutationOperator();
            // Sort population
            sortPopulation();
            // Elitism: the best father remains in the population.
            boolean bestFatherFound = false;
            for (int bf=0; bf<population.length && !bestFatherFound; bf++) {
                if (previousPopulation[0] == population[bf])
                    bestFatherFound = true;
            }
            if (!bestFatherFound) {
                population[population.length-1] = previousPopulation[0];
            }
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
            resultado += "\nChromosome "+i+population[i].toString();
        }
        return resultado;
    }
}
