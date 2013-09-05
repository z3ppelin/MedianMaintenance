/**
 * Max heap structure.
 *
 * @author      Bogdan Constantinescu <bog_con@yahoo.com>
 * @since       2013.07.08
 * @version     1.0
 * @link        GitHub    https://github.com/z3ppelin/MedianMaintenance
 * @licence     The MIT License (http://opensource.org/licenses/MIT); see LICENCE.txt
 */
import java.util.Arrays;

public class MaxHeap {

    public int lastFreePos; // last free position in heap
    public int[] values; // heap 's elements

    /**
     * Constructor.
     *
     * @param heapDimension Heap 's dimension.
     */
    public MaxHeap(int heapDimension) {
        this.lastFreePos = 0;
        this.values = new int[heapDimension];
        Arrays.fill(this.values, Integer.MAX_VALUE);
    }

    /**
     * Inserts a new element into heap.
     *
     * @param   value       The element to insert.
     * @throws Exception    If heap is full.
     */
    public void insert(int value) throws Exception {
        if (this.lastFreePos == this.values.length) {
            throw new Exception("Heap overflow");
        }
        this.values[this.lastFreePos] = value;
        int childPos = this.lastFreePos, parentPos = (childPos - 1) / 2, aux;
        while (parentPos >= 0 && this.values[parentPos] < this.values[childPos]) {
            aux = this.values[parentPos];
            this.values[parentPos] = this.values[childPos];
            this.values[childPos] = aux;
            childPos = parentPos;
            parentPos = (childPos - 1) / 2;
        }
        this.lastFreePos++;
    }

    /**
     * Extracts max value (situated on first position in vector).
     * 
     * @return The max value in the heap.
     * @throws Exception If heap is empty.
     */
    public int extractMax() throws Exception {
        if (this.lastFreePos == 0) {
            throw new Exception("Empty heap");
        }
        int returnValue = this.values[0], aux;
        this.values[0] = this.values[this.lastFreePos - 1];
        this.values[this.lastFreePos - 1] = 0;
        this.lastFreePos--;
        
        /* bubble down */
        int parentPos = 0, leftChildPos = (parentPos + 1) * 2 - 1, rightChildPos = leftChildPos + 1, minChildPos;
        while ((leftChildPos < this.lastFreePos && this.values[parentPos] < this.values[leftChildPos])
                || (rightChildPos < this.lastFreePos && this.values[parentPos] < this.values[rightChildPos])) {
            minChildPos = leftChildPos;
            if (rightChildPos < this.lastFreePos && this.values[leftChildPos] < this.values[rightChildPos]) {
                minChildPos = rightChildPos;
            }
            aux = this.values[parentPos];
            this.values[parentPos] = this.values[minChildPos];
            this.values[minChildPos] = aux;
            parentPos = minChildPos;
            leftChildPos = (parentPos + 1) * 2 - 1;
            rightChildPos = leftChildPos + 1;
        }
        return returnValue;
    }
}
