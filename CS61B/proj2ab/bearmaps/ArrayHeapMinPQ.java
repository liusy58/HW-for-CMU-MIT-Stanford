package bearmaps;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Collections;
import java.util.NoSuchElementException;
import org.junit.Test;
import static org.junit.Assert.assertEquals;


public class ArrayHeapMinPQ<T> implements ExtrinsicMinPQ<T>{

    public class ArrayNode<T>
    {
        private T item;
        private double priority;
        ArrayNode(T _item,double _priority)
        {
            priority=_priority;
            item=_item;
        }
        public int compareTo(ArrayNode other)
        {
            if(priority>other.priority)
                return 1;
            else if(priority<other.priority)
                return -1;
            return 0;
        }
    }

    private HashMap<T, Integer> item2index;
    private ArrayList<ArrayNode<T>> array;
    ArrayHeapMinPQ()
    {
        item2index=new HashMap<>();
        array=new ArrayList();
    }
    public void add(T item, double priority)
    {
        //assertEquals(array.size(),item2index.size());
        if(item2index.containsKey(item))
            throw new IllegalArgumentException("error!");
        ArrayNode new_node=new ArrayNode(item,priority);
        array.add(new_node);
        item2index.put(item,size()-1);
        modify_down2up(size()-1);

    }
    /* Returns true if the PQ contains the given item. */
    public boolean contains(T item)
    {
        //assertEquals(array.size(),item2index.size());
        return item2index.containsKey(item);
    }
    /* Returns the minimum item. Throws NoSuchElementException if the PQ is empty. */
    public T getSmallest()
    {
        //assertEquals(array.size(),item2index.size());
        if(size()==0)
            throw new NoSuchElementException("No such item!");
        return array.get(0).item;
    }
    /* Removes and returns the minimum item. Throws NoSuchElementException if the PQ is empty. */
    public T removeSmallest()
    {
        //assertEquals(array.size(),item2index.size());
        if(size()==0)
            throw new NoSuchElementException("No such item!");
        T res=getSmallest();
        delete(0);
        return res;
    }
    /* Returns the number of items in the PQ. */
    public int size()
    {
        return array.size();
    }
    /* Changes the priority of the given item. Throws NoSuchElementException if the item
     * doesn't exist. */
    public void changePriority(T item, double priority)
    {
        //assertEquals(array.size(),item2index.size());
        if(!contains(item))
            throw new NoSuchElementException("");
        int index=item2index.get(item);
        modify_down2up(index);
        modify_up2down(index);
    }
    private int parent(int index)
    {
        //assertEquals(array.size(),item2index.size());
        return (index-1)/2;
    }
    private void modify_down2up(int index)
    {
        //assertEquals(array.size(),item2index.size());
        if(index<=0)
            return;
        int parent_index=parent(index);
        if(array.get(parent_index).compareTo(array.get(index))==1)
        {
            item2index.put(array.get(parent_index).item,index);
            item2index.put(array.get(index).item,parent_index);
            Collections.swap(array, index, parent_index);
            modify_down2up(parent_index);
        }
    }
    private void modify_up2down(int index)
    {
        //System.out.println("in modify_up2down  "+index);
        //assertEquals(array.size(),item2index.size());
        if(index>=size())
            return;
        int smallest=index;
        int left=index*2+1;
        int right=index*2+2;
        ArrayNode target=array.get(index);
        if(left<size()&&array.get(left).compareTo(target)==-1)
        {
            smallest=left;
            target=array.get(smallest);
        }

        if(right<size()&&array.get(right).compareTo(target)==-1)
            smallest=right;
        if(index==smallest)
            return;
        T t1=array.get(smallest).item;
        T t2=array.get(index).item;
        item2index.put(t1,index);
        item2index.put(t2,smallest);
        Collections.swap(array, index, smallest);
        //System.out.println("in modify_up2down  Small   "+smallest);
        modify_up2down(smallest);
    }

    private void delete(int index)
    {
        //System.out.println("index is "+index);
       // assertEquals(array.size(),item2index.size());

        T res=array.get(index).item;
        Collections.swap(array,index,size()-1);
        array.remove(size()-1);
        item2index.remove(res);
        int _parent=parent(index);
        if(_parent<=0)
            modify_up2down(index);
        else if(array.get(_parent).compareTo(array.get(index))==1)
            modify_down2up(index);
        else
            modify_up2down(index);
//        modify_up2down(index);
//        modify_down2up(index);
    }
    public void show()
    {
        for(int i=0;i<size()&&i<100;++i)
        {
            System.out.println(array.get(i).item+"  "+array.get(i).priority);
        }
    }



}
