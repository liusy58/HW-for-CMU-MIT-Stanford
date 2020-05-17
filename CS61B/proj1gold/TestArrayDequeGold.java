import static org.junit.Assert.*;
import org.junit.Test;

public class TestArrayDequeGold {
    @Test
    public void test()
    {
        StudentArrayDeque student=new StudentArrayDeque<Integer>();
        ArrayDequeSolution solution = new ArrayDequeSolution<Integer>();
        for (int i = 0; i < 8; i += 1) {
            double numberBetweenZeroAndOne = StdRandom.uniform();

            if (numberBetweenZeroAndOne < 0.5) {
                student.addLast(i);
                solution.addLast(i);
            } else {
                student.addFirst(i);
                solution.addFirst(i);
            }
        }
        student.printDeque();
        solution.printDeque();
        for (int i = 0; i < 8; i += 1) {
            double numberBetweenZeroAndOne = StdRandom.uniform();

            if (numberBetweenZeroAndOne < 0.5) {

                assertEquals(student.removeFirst(),solution.removeFirst());
            } else {
                assertEquals(solution.removeLast(),student.removeLast());
            }
        }

    }
}
