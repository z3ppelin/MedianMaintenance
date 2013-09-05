/**
 * Median Maintanence problem. This particular implementation prints the sum of
 * medians.
 *
 * @author      Bogdan Constantinescu <bog_con@yahoo.com>
 * @since       2013.07.08
 * @version     1.0
 * @link        GitHub    https://github.com/z3ppelin/MedianMaintenance
 * @licence     The MIT License (http://opensource.org/licenses/MIT); see LICENCE.txt
 */
import java.io.FileInputStream;
import java.util.*;

public class MedianMaintenance {

    /**
     * Main function. Reads vector, sorts it, and prints it.
     *
     * @param args Command line arguments.
     */
    public static void main(String[] args) {
        System.out.println("------ Begin Median Maintanence ------");
        int[] vector = null, medians = null;
        long start, end;
        long sumMedians = 0;
        int medianPos;
        MaxHeap maxHeap = null;
        MinHeap minHeap = null;

        /* read vector */
        try {
            if (args.length == 0) {
                throw new Exception("The input file must be given as an argument.");
            }
            vector = readVectorFromFile(args[0]);
            medians = new int[vector.length];
            minHeap = new MinHeap(vector.length);
            maxHeap = new MaxHeap(vector.length);
        } catch (Exception ex) {
            System.out.println("ERR. " + ex.getMessage());
            System.out.println("------- End Median Maintanence -------");
            System.exit(-1);
        }

        /* print read vector */
        //System.out.print("The read vector is: ");
        //printVector(vector);
        //System.out.println();

        /* start calculating the medians */
        start = System.currentTimeMillis();
        try {
            if (vector.length > 0) {
                maxHeap.insert(vector[0]);
                medians[0] = maxHeap.values[maxHeap.lastFreePos - 1];
                sumMedians += medians[0];
            }

            for (int i = 1; i < vector.length; i++) {
                if (vector[i] <= maxHeap.values[0]) {
                    maxHeap.insert(vector[i]);
                } else {
                    minHeap.insert(vector[i]);
                }

                /* rebalance heaps */
                if (minHeap.lastFreePos - maxHeap.lastFreePos > 1) {
                    maxHeap.insert(minHeap.extractMin());
                } else if (maxHeap.lastFreePos - minHeap.lastFreePos > 1) {
                    minHeap.insert(maxHeap.extractMax());
                }

                if (i % 2 == 1) {
                    medianPos = (i - 1) / 2;
                } else {
                    medianPos = i / 2;
                }
                if (maxHeap.lastFreePos - 1 >= medianPos) {
                    medians[i] = maxHeap.values[0];
                } else {
                    medians[i] = minHeap.values[0];
                }
                sumMedians += medians[i];
            }
        } catch (Exception ex) { // should not get here
            System.out.println("ERR. " + ex.getMessage());
        }
        end = System.currentTimeMillis();

        /* print results */
        System.out.println("Medians sum = " + sumMedians);

        //System.out.print("The medians are: ");
        //printVector(medians);
        //System.out.println();

        System.out.println("Elapsed: " + ((double) (end - start) / 100) + " seconds.");
        System.out.println("------- End Median Maintanence -------");
    }

    /**
     * Prints an array 's elements.
     *
     * @param v The vector to print.
     */
    public static void printVector(int[] v) {
        for (int i = 0; i < v.length; i++) {
            System.out.print(v[i] + " ");
        }
    }

    /**
     * Reads array from file.
     *
     * @param file The file where to read array from.
     * @return The read vector.
     * @throws Exception
     */
    public static int[] readVectorFromFile(String file) throws Exception {
        Scanner sc;
        FileInputStream fis = null;
        int n;
        int[] v;
        try {
            fis = new FileInputStream(file);
            sc = new Scanner(fis);
            if (!sc.hasNextInt()) {
                throw new Exception("Could not read the number of elements the vector has.");
            }
            n = sc.nextInt();
            v = new int[n];
            for (int i = 0; i < n; i++) {
                if (!sc.hasNextInt()) {
                    throw new Exception("Number of declared elements does not match with the one found in file.");
                }
                v[i] = sc.nextInt();
            }
            fis.close();
        } catch (Exception ex) {
            if (fis != null) {
                try {
                    fis.close();
                } catch (Exception e) {
                }
            }
            throw ex;
        }
        return v;
    }
}
