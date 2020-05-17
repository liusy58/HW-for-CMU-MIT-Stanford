class LinkedListDeque<T>
{
    public class Node<T> {
        public T item;
        public Node next;
        public Node before;
        public Node(T value)
        {
            item=value;
            next=before=null;
        }
        public Node(T value,Node _before,Node _next)
        {
            item=value;
            before=_before;
            next=_next;
        }

    }
    private int size;
    private Node head;
    private Node tail;
    public LinkedListDeque()
    {
        size=0;
        head=new Node(0);
        tail=head;
    }
    public LinkedListDeque(LinkedListDeque other)
    {
        size = other.size();
        head=new Node(0);
        Node _other=other.head.next;
        while(_other!=null)
        {
            addLast((T) _other.item);
            _other=_other.next;
        }
    }
    public void addFirst(T item)
    {
        size+=1;
        head.next=new Node(item,head,head.next);
        if(size==1)
        {
            tail=head.next;
        }

    }
    public void addLast(T item)
    {
        size+=1;
        tail=new Node(item,tail,null);

        if(size==1)
        {
            head.next=tail;
        }


    }
    public boolean isEmpty()
    {
        return size==0;
    }

    public int size()
    {
        return size;
    }

    public void printDeque()
    {
        Node temp=head.next;
        while(temp!=null)
        {
            System.out.println(temp.item);
            temp=temp.next;
        }
    }

    public T removeFirst()
    {
        if(isEmpty())
            return (T)null;
        size-=1;
        T res=(T)head.next.item;
        head.next=head.next.next;
        return res;
    }

    public T removeLast()
    {
        if(isEmpty())
            return (T)null;
        size-=1;
        T res=(T)tail.item;
        tail=tail.before;
        return res;
    }

    public T get(int index)
    {
        Node res=head.next;
        while(index!=0) {
            res = res.next;
            --index;
        }
        return (T)res.item;
    }
//    public T getRecursive(int index)
//    {
//
//    }
}