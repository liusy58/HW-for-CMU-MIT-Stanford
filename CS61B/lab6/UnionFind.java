public class UnionFind {

    // TODO - Add instance variables?
    private int []parent;
    private int cnt;
    private int []size;
    /* Creates a UnionFind data structure holding n vertices. Initially, all
       vertices are in disjoint sets. */
    public UnionFind(int n) {
        // TODO
        cnt=n;
        parent = new int[n];
        size=new int[n];
        for(int i=0;i<n;++i)
        {
            parent[i]=i;
            size[i]=1;
        }

    }

    /* Throws an exception if v1 is not a valid index. */
    private void validate(int vertex) {
        int n = parent.length;
        if (vertex < 0 || vertex >= n) {
            throw new IllegalArgumentException("index " + vertex + " is not between 0 and " + (n - 1));
        }
    }

    /* Returns the size of the set v1 belongs to. */
    public int sizeOf(int v1) {
        // TODO
        validate(v1);
        return size[v1];
    }

    /* Returns the parent of v1. If v1 is the root of a tree, returns the
       negative size of the tree for which v1 is the root. */
    public int parent(int v1) {
        // TODO
        validate(v1);
        if(parent[v1]==v1)
            return -size[v1];
        return parent[v1];

    }

    /* Returns true if nodes v1 and v2 are connected. */
    public boolean connected(int v1, int v2) {
        validate(v1);
        validate(v2);
        return find(v1)==find(v2);
    }

    /* Connects two elements v1 and v2 together. v1 and v2 can be any valid 
       elements, and a union-by-size heuristic is used. If the sizes of the sets
       are equal, tie break by connecting v1's root to v2's root. Unioning a 
       vertex with itself or vertices that are already connected should not 
       change the sets but may alter the internal structure of the data. */
    public void union(int v1, int v2) {
        validate(v1);
        validate(v2);
        int rootv1 = find(v1);
        int rootv2 = find(v2);
        if(rootv1==rootv2)
        {
            pathCompressed(v1,rootv1);
            pathCompressed(v2,rootv2);
            return;
        }
        if (size[rootv1] < size[rootv2]) {
            parent[rootv1] = rootv2;
            size[rootv2] += size[rootv1];
        }
        else {
            parent[rootv2] = rootv1;
            size[rootv1] += size[rootv2];
        }
        cnt--;

    }

    /* Returns the root of the set V belongs to. Path-compression is employed
       allowing for fast search-time. */
    public int find(int v1) {
        // TODO
        while(v1!=parent[v1])
        {
            v1=parent[v1];
        }
        return v1;
    }
    private void pathCompressed(int v1,int root)
    {
        int temp;
        while(v1!=parent[v1])
        {
            temp=parent[v1];
            parent[v1]=root;
            v1=temp;
        }
    }


}
