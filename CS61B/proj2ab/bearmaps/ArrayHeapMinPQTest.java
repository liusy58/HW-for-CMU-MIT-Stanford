package bearmaps;

import org.junit.Test;
import static org.junit.Assert.*;
import java.util.Random;

public class ArrayHeapMinPQTest {



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
    @Test
    public void testtime()
    {
        System.out.println("Test time for my ArrayHeapMinPQ");
        ArrayHeapMinPQ<Integer> minHeap = new ArrayHeapMinPQ<>();
        Random rand = new Random();
        long start = System.currentTimeMillis();
        for (int j = 0; j < 20000; j += 1) {
            Double prio=rand.nextDouble();
            minHeap.add(j,prio);
        }
        long end = System.currentTimeMillis();
        System.out.println("Time elapsed: " + (end - start) / 1000.0 +  " seconds.");

        start = System.currentTimeMillis();
        for (int j = 0; j < 20000; j += 1) {
            minHeap.removeSmallest();
        }
        end = System.currentTimeMillis();
        System.out.println("Time elapsed: " + (end - start) / 1000.0 +  " seconds.");

        System.out.println("Test time for NavieHeapMinPQ");
        NaiveMinPQ<Integer> navie=new NaiveMinPQ<>();
        start = System.currentTimeMillis();
        for (int j = 0; j < 20000; j += 1) {
            Double prio=rand.nextDouble();
            navie.add(j,prio);
        }
        end = System.currentTimeMillis();
        System.out.println("Time elapsed: " + (end - start) / 1000.0 +  " seconds.");

        start = System.currentTimeMillis();
        for (int j = 0; j < 20000; j += 1) {
            navie.removeSmallest();
        }
        end = System.currentTimeMillis();
        System.out.println("Time elapsed: " + (end - start) / 1000.0 +  " seconds.");

    }
}