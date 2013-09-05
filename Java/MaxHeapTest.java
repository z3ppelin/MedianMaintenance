
/**
 * JUnit test for MaxHeap.
 *
 * @author      Bogdan Constantinescu <bog_con@yahoo.com>
 * @since       2013.07.08
 * @version     1.0
 * @link        GitHub  https://github.com/z3ppelin/MedianMaintenance
 * @licence     The MIT License (http://opensource.org/licenses/MIT); see LICENCE.txt
 */
import static org.junit.Assert.*;
import org.junit.*;
import java.util.Random;

public class MaxHeapTest {

    /**
     * Test case for MaxHeap.insert() with random elements.
     */
    @Test
    public void insertTest() {
        int i, j, heapDimension, max = 0, x;
        Random randomGenerator = new Random();
        heapDimension = 100 + randomGenerator.nextInt(200); //[100, 200)
        MaxHeap heap = new MaxHeap(heapDimension);
        for (i = 0; i < heapDimension; i++) {
            x = 1 + randomGenerator.nextInt(200);
            if (x > max) {
                max = x;
            }
            try {
                heap.insert(x);
            } catch (Exception ex) {
                fail("Exception was not expected to be thrown.");
            }
            assertEquals(heap.lastFreePos, i + 1);
            assertEquals(heap.values[0], max);
            for (j = 0; j < (heap.lastFreePos + 1) / 2 - 1; j++) {
                if ((j + 1) * 2 - 1 < heap.lastFreePos) {
                    assertTrue(heap.values[j] >= heap.values[(j + 1) * 2 - 1]);
                }
                if ((j + 1) * 2 < heap.lastFreePos) {
                    assertTrue(heap.values[j] >= heap.values[(j + 1) * 2]);
                }
            }
        }

        try {
            heap.insert(100);
            fail("Heap should be full.");
        } catch (Exception ex) {
            assertEquals(ex.getMessage(), "Heap overflow");
        }
    }

    /**
     * Test case for MaxHeap.extractMax();
     */
    @Test
    public void extractMaxTest() {
        int i, j, heapDimension;
        Random randomGenerator = new Random();
        heapDimension = 100 + randomGenerator.nextInt(200); // [100, 200)
        MaxHeap heap = new MaxHeap(heapDimension);

        try {
            heap.extractMax();
            fail("Heap should be empty.");
        } catch (Exception ex) {
            assertEquals(ex.getMessage(), "Empty heap");
        }

        for (i = 0; i < heapDimension; i++) {
            try {
                heap.insert(1 + randomGenerator.nextInt(200));
            } catch (Exception ex) {
                fail("Exception was not expected to be thrown.");
            }
        }

        for (i = 0; i < heapDimension; i++) {
            try {
                heap.extractMax();
            } catch (Exception ex) {
                fail("Exception was not expected to be thrown.");
            }
            assertEquals(heap.lastFreePos, heapDimension - i - 1);
            for (j = 0; j < (heap.lastFreePos + 1) / 2 - 1; j++) {
                if ((j + 1) * 2 - 1 < heap.lastFreePos) {
                    assertTrue(heap.values[j] >= heap.values[(j + 1) * 2 - 1]);
                }
                if ((j + 1) * 2 < heap.lastFreePos) {
                    assertTrue(heap.values[j] >= heap.values[(j + 1) * 2]);
                }
            }
        }

        try {
            heap.extractMax();
            fail("Heap should be empty.");
        } catch (Exception ex) {
            assertEquals(ex.getMessage(), "Empty heap");
        }
    }
}
