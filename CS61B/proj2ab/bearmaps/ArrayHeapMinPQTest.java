package bearmaps;

import org.junit.Test;
import static org.junit.Assert.*;
import java.util.Random;

public class ArrayHeapMinPQTest {

    @Test
    public void testAdd() {
        ArrayHeapMinPQ<Integer> minHeap = new ArrayHeapMinPQ<>();
        minHeap.add(1, 1);
        minHeap.add(2, 2);
        minHeap.add(3, 3);
        minHeap.add(4, 4);
        minHeap.add(5, 2);
        minHeap.add(6, 3);
        assertTrue(minHeap.size() == 6);
    }

    @Test
    public void testContains() {
        ArrayHeapMinPQ<Integer> minHeap = new ArrayHeapMinPQ<>();
        minHeap.add(1, 1);
        minHeap.add(2, 2);
        minHeap.add(3, 3);
        minHeap.add(4, 4);
        minHeap.add(5, 2);
        minHeap.add(6, 3);
        assertTrue(minHeap.contains(2));
        assertFalse(minHeap.contains(0));
    }

    @Test
    public void testGetSmallest() {
        ArrayHeapMinPQ<Integer> minHeap = new ArrayHeapMinPQ<>();
        minHeap.add(1, 1);
        minHeap.add(2, 2);
        minHeap.add(3, 3);
        minHeap.add(4, 4);
        minHeap.add(5, 0);
        minHeap.add(6, 3);
        assertTrue(minHeap.getSmallest() == 5);
    }

    @Test
    public void testRemoveSmallest() {
        ArrayHeapMinPQ<Integer> minHeap = new ArrayHeapMinPQ<>();
        minHeap.add(1, 1);
        minHeap.add(2, 2);
        minHeap.add(3, 3);
        minHeap.add(4, 4);
        minHeap.add(5, 0);
        minHeap.add(6, 3);

        assertTrue(minHeap.removeSmallest() == 5);
        assertTrue(minHeap.size() == 5);

        assertTrue(minHeap.getSmallest() == 1);
    }

    @Test
    public void testChangePriority() {
        ArrayHeapMinPQ<Integer> minHeap = new ArrayHeapMinPQ<>();
        minHeap.add(1, 1);
        minHeap.add(2, 2);
        minHeap.add(3, 3);
        minHeap.add(4, 4);
        minHeap.add(5, 0);
        minHeap.add(6, 3);
        minHeap.changePriority(5, 5);
        minHeap.changePriority(6, 0);
        assertTrue(minHeap.getSmallest() == 6);
    }
    @Test
    public void testalll() {

        long start = System.currentTimeMillis();
        ArrayHeapMinPQ<Integer> minHeap = new ArrayHeapMinPQ<>();
        for (int i = 0; i < 200000; i += 1) {
            minHeap.add(i, 100000 - i);
        }
        long end = System.currentTimeMillis();
        System.out.println("Total time elapsed: " + (end - start) / 1000.0 +  " seconds.");
        int item=199999;
        for (int j = 0; j < 200000; j += 1) {
            assertTrue(minHeap.removeSmallest()==item);
            item--;

        }
        long start2 = System.currentTimeMillis();
        for (int i = 0; i < 200000; i += 1) {
            minHeap.add(i, 100 - i);
        }
        for (int j = 0; j < 200000; j += 1) {
            minHeap.changePriority(j, j + 1);
        }
        item=0;
        for (int j = 0; j < 200000; j += 1) {
            assertTrue(minHeap.removeSmallest()==item);
            item++;

        }

        long end2 = System.currentTimeMillis();
        System.out.println("Total time elapsed: " + (end2 - start2) / 1000.0 +  " seconds.");
    }

    @Test
    public void test() {
        Random rand = new Random();
        ArrayHeapMinPQ<Integer> minHeap = new ArrayHeapMinPQ<>();
        NaiveMinPQ<Integer> navie=new NaiveMinPQ<>();
        for (int j = 0; j < 20000; j += 1) {
            Double prio=rand.nextDouble();
            //System.out.println(prio);
            minHeap.add(j,prio);
            navie.add(j,prio);

        }
        //minHeap.show();

        //System.out.println();
        //System.out.println();
        //navie.show();
        for (int j = 0; j < 20000; j += 1) {
            //System.out.println(minHeap.removeSmallest()+"    "+navie.removeSmallest());

            //System.out.println("haha");
            assertTrue(minHeap.removeSmallest().equals(navie.removeSmallest()));

        }

    }
}