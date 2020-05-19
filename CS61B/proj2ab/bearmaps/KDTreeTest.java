package bearmaps;

import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;

public class KDTreeTest {

    @Test
    public void testadd()
    {
        List<Point> points=new ArrayList<>();
        points.add(new Point(2,3));
        points.add(new Point(4,2));
        points.add(new Point(4,5));
        points.add(new Point(3,3));
        points.add(new Point(1,5));
        KDTree tree=new KDTree(points);
        tree.show();
    }
    @Test
    public void test_nearest()
    {
        List<Point> points=new ArrayList<>();
        points.add(new Point(2,3));
        points.add(new Point(4,2));
        points.add(new Point(4,5));
        points.add(new Point(3,3));
        points.add(new Point(1,5));
        KDTree tree=new KDTree(points);
        Point res=tree.nearest(0,7);
        assertNotNull(res);
        System.out.println(res.getX()+"  "+res.getY());
    }
}
