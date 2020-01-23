/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package qap;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 *
 * @author Lidia Sánchez Mérida
 */
public class DataReader {
    /**
     * Number of installations.
     */
    private static int nInstallations;
    /**
     * Material flows.
     */
    private static int flows[][];
    /**
     * Distances between installations.
     */
    private static int distances[][];
    
    /**
     * Constructor.
     */
    public DataReader() {
        nInstallations = 0;
    }
    /**
     * Gets the number of installations.
     * @return number of installations.
     */
    public static int getNInstallations() {
        return nInstallations;
    }
    /**
     * Gets material flows of each installation.
     * @return every material flows.
     */
    public static int[][] getFlows() {
        return flows;
    }
    /**
     * Gets the distances of each installation.
     * @return every distance of each installation.
     */
    public static int[][] getDistances() {
        return distances;
    }
    /**
     * Read data from a file to initialize the number of installations, their
     * material flows and the distances between all of them.
     * @param f data file.
     * @throws FileNotFoundException 
     */
    public static void readData(File f) throws FileNotFoundException {
        Scanner sc = new Scanner(f);
        nInstallations = sc.nextInt();
        flows = new int[nInstallations][nInstallations];
        distances = new int[nInstallations][nInstallations];
        for (int i=0; i<nInstallations; i++) {
            for (int j=0; j<nInstallations; j++) {
                flows[i][j] = sc.nextInt();
            }
        }
        for (int i=0; i<nInstallations; i++) {
            for (int j=0; j<nInstallations; j++) {
                distances[i][j] = sc.nextInt();
            }
        }
    }
    /**
     * Shows the read file.
     * @return 
     */
    public static String printFile() {
        String result = "\nNumber of installations: "+nInstallations+"\nMaterial flows\n";
        String flowsString = "", distancesString = "";
        for (int i=0; i<nInstallations; i++) {
            for (int j=0; j<nInstallations; j++) {
                flowsString += flows[i][j] + " ";
                distancesString += distances[i][j] + " ";
            }
            flowsString += "\n";
            distancesString += "\n";
        }
        result += (flowsString + "\nDistances between installations\n" + distancesString);
        return result;
    }
}
