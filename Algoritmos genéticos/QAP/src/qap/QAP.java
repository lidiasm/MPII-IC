/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package qap;

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
        DataReader dr = new DataReader();
        dr.readData(f);
        System.out.println(dr.toString());
        Chromosome c = new Chromosome();
        c.initialize(dr.getNInstallations());
        c.calculateFitness(dr.getFlows(), dr.getDistances());
        System.out.println("First chromosome"+c.toString());
        Population p1 = new Population(5);
        p1.initialize(dr.getNInstallations());
        System.out.println("\nFirst population"+p1.toString());
    }
    
}
