/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package qap;

import algorithms.AGG;
import java.io.File;
import java.io.FileNotFoundException;

/**
 * Main class.
 * @author Lidia Sánchez Mérida
 */
public class QAP {

    /**
     * @param args the command line arguments
     * @throws java.io.FileNotFoundException
     */
    public static void main(String[] args) throws FileNotFoundException {
        // TODO code application logic here
        // Read data
        File f = new File("qap.datos/bur26a.dat");
        DataReader.readData(f);
        System.out.println(DataReader.printFile());
        // New chromosome
        Chromosome c = new Chromosome();
        c.initialize(DataReader.getNInstallations());
        System.out.println("First chromosome"+c.toString());
        // New ordered population
        
        /*// Cross position operator
        System.out.println("AGG CROSS POSITION OPERATOR");
        AGG standard = new AGG(5, 0.7, 0.001);
        Chromosome son = standard.crossPositionOperator(p1.getChromosomeOfThePopulation(0),
            p1.getChromosomeOfThePopulation(2));
        System.out.println("\nFather 1: "+p1.getChromosomeOfThePopulation(0).toString()+
            "\n\nFather 2: "+p1.getChromosomeOfThePopulation(2).toString()+"\n\nSon: "+son.toString());
        // Cross OX operator
        System.out.println("AGG CROSS OX OPERATOR");
        Chromosome sonOX = standard.crossOXOperator(p1.getChromosomeOfThePopulation(0),
            p1.getChromosomeOfThePopulation(2));
        System.out.println("\nFather 1: "+p1.getChromosomeOfThePopulation(0).toString()+
            "\n\nFather 2: "+p1.getChromosomeOfThePopulation(2).toString()+"\n\nSon: "+sonOX.toString());*/
    }
    
}
