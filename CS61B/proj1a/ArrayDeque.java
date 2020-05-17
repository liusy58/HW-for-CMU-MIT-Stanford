public class ArrayDeque<T> {
    private int max_size;
    private T[] items;


    private int front;//队头指针
    private int rear;//队尾指针
    private int size;//实际大小

    public ArrayDeque()
    {
        size=0;
        front=rear=0;
        max_size=10;
        items = (T[]) new Object[max_size];
    }

    public ArrayDeque(ArrayDeque other)
    {
        size=other.size;
        front=other.front;
        rear=other.rear;
        int i=0;
        max_size=other.max_size;
        items = (T[]) new Object[max_size];
        while(i<other.items.length)
        {
            items[i]=(T)other.items[i];
            i++;
        }
    }

    public void addFirst(T item)
    {
        if(full())
        {
            max_size*=2;
            resize(max_size);
        }
        size+=1;
        front=(front-1+max_size)%max_size;
        System.out.println("the front is %d in addFirst");
        System.out.println(front);
        items[front]=(T)item;
    }

    public void addLast(T item)
    {
        if(full())
        {
            max_size*=2;
            resize(max_size);
        }
        size+=1;
        items[rear]=item;
        rear=(rear+1)%max_size;
    }

    public boolean isEmpty()
    {
        return front==rear;
    }


    public boolean full()
    {
        return (rear+1)%max_size == front;
    }


    public int size()
    {
        return size;
    }
    public void printDeque()
    {
        int _front=front;
        while(_front!=rear)
        {
            System.out.println(items[_front]);
            _front=(_front+1)%max_size;
        }
    }

    public T removeFirst()
    {
        if(isEmpty())
            return (T)null;
        size-=1;
        T res=(T)items[front];
        front=(front+1)%max_size;
        return res;
    }
    public T removeLast()
    {
        if(isEmpty())
            return (T)null;
        size-=1;
        T res=items[(rear-1)%max_size];
        rear=(rear-1)%max_size;
        return res;
    }
    private void resize(int capacity) {
        T[] a = (T[]) new Object[capacity];
        System.arraycopy(items, 0, a, 0, size);
        items = a;
    }
    public T get(int index)
    {
        if(index>=size)
            return (T)null;
        index=(index+front)%max_size;
        return items[index];
    }
}
