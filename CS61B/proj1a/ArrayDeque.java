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
        max_size=2;
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
            resize(max_size*2);
            printDeque();
        }
        size+=1;
        front=(front-1+max_size)%max_size;
        items[front]=(T)item;


    }

    public void addLast(T item)
    {
        if(full())
        {
            resize(max_size*2);
        }
        size+=1;
        items[rear]=item;
        rear=(rear+1+max_size)%max_size;
    }

    public boolean isEmpty()
    {
        return front==rear;
    }


    public boolean full()
    {
        return (rear+1+max_size)%max_size == front;
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
            _front=(_front+1+max_size)%max_size;
        }
    }

    public T removeFirst()
    {
        if(isEmpty())
            return (T)null;
        size-=1;
        T res=(T)items[front];
        front=(front+1+max_size)%max_size;
        return res;
    }
    public T removeLast()
    {
        if(isEmpty())
            return (T)null;
        size-=1;
        T res=items[(rear-1+max_size)%max_size];
        rear=(rear-1+max_size)%max_size;
        return res;
    }
    private void resize(int capacity) {
        System.out.println("now is in the resize function!");
        T[] a = (T[]) new Object[capacity];
//        int cnt=0;
//        while(cnt<size)
//        {
//            a[cnt]=(T)get(cnt);
//            cnt++;
//        }
//        max_size*=2;
//        front=0;
//        rear=size;
//        items = a;
        if(front<rear)
        {
            System.arraycopy(items,front,a,0,size-1);
        }
        else
        {
            System.arraycopy(items,front,a,0,size-front+1);
            System.arraycopy(items,0,a,size-front+1,rear);
        }
        max_size*=2;
        front=0;
        rear=size;
        items = a;
    }
    public T get(int index)
    {
        if(index>=size)
            return (T)null;
        index=(index+front+max_size)%max_size;
        return items[index];
    }
}
