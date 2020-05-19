package bearmaps;
import java.util.List;

import static bearmaps.Point.distance;

public class KDTree {
    KDNode root;
    public class KDNode
    {
        private Point point;
        int level;
        private KDNode left_child;
        private KDNode right_child;
        KDNode(Point _point,int _level)
        {
            point=new Point(_point.getX(),_point.getY());
            level=_level;
            left_child=right_child=null;
        }
        public void show()
        {
            System.out.println("X:"+point.getX()+"  Y:"+point.getY()+"   Level:"+level);
        }
    }
    public KDTree(List<Point> points)
    {
        for(int i=0;i<points.size();++i)
            root=add(points.get(i),root,0);

    }
    public Point nearest(double x, double y)
    {
        Point res=new Point(0,0);
        Point target=new Point(x,y);
        Double min_dis=Double.MAX_VALUE;
        nearest_help(res,target,root,min_dis);
        return res;
    }

    public Point nearest_naive(double x, double y)
    {
        Point res=root.point;
        Point target=new Point(x,y);
        nearest_naive_help(target,root,res);
        return res;
    }
    private void nearest_naive_help(Point target,KDNode now,Point res)
    {
        if(now.point==null)
            return;
        if(distance(res,target)>distance(now.point,target))
            res=now.point;
        nearest_naive_help(target,now.left_child,res);
        nearest_naive_help(target,now.right_child,res);
    }
    private KDNode add(Point point,KDNode root,int level)
    {
        if(root==null)
            return new KDNode(point,level);
        if(level%2==0)
        {
            double x1=root.point.getX();
            double x2=point.getX();
            if(x1>x2)
                root.left_child=add(point,root.left_child,level+1);
            else
                root.right_child=add(point,root.right_child,level+1);
        }
        else
        {
            double y1=root.point.getY();
            double y2=point.getY();
            if(y1>y2)
                root.left_child=add(point,root.left_child,level+1);
            else
                root.right_child=add(point,root.right_child,level+1);
        }
        return root;
    }

    public void show()
    {
        show(root);
    }
    private void show(KDNode root)
    {
        if(root==null)
            return;
        show(root.left_child);
        root.show();;
        show(root.right_child);
    }

    private void nearest_help(Point res,Point target,KDNode now,Double min_dis)
    {
        if(now==null)
            return;
        Double dis=distance(now.point,target);
        if(dis<min_dis)
        {

            min_dis=dis;
            System.out.println("have changed! and the min_dis is "+min_dis);
            res.change(now.point);
            nearest_help(res,target,now.left_child,min_dis);
            nearest_help(res,target,now.right_child,min_dis);
        }
        else
        {
            if(now.level%2==1)
                nearest_help(res,target,now.right_child,min_dis);
            else
                nearest_help(res,target,now.left_child,min_dis);
        }
    }
}
