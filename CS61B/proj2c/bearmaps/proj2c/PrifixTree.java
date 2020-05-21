package bearmaps.proj2c;


import bearmaps.hw4.streetmap.Node;
import bearmaps.proj2ab.Point;

import java.util.ArrayList;
import java.util.HashMap;

public class PrifixTree
{
    private int SIZE=26;
    private TrieNode root;//字典树的根
    private HashMap<String, String> lower2before;

    PrifixTree() //初始化字典树
    {
        root=new TrieNode();
        lower2before=new HashMap<String, String>();
    }

    private class TrieNode //字典树节点
    {
        private int num;//有多少单词通过这个节点,即由根至该节点组成的字符串模式出现的次数
        private TrieNode[]  son;//所有的儿子节点
        private boolean isEnd;//是不是最后一个节点
        private char val;//节点的值
        private boolean haveSon;

        TrieNode()
        {
            num=1;
            son=new TrieNode[SIZE];
            isEnd=false;
            haveSon=false;
        }
    }

    //建立字典树
    public void insert(String str) //在字典树中插入一个单词
    {

        if(str==null||str.length()==0)
        {
            return;
        }

        String temp=new String(str.toLowerCase());
        temp=temp.replaceAll("[^a-z]", "");
        lower2before.put(temp,str);
        TrieNode node=root;
        char[]letters=temp.toCharArray();
        System.out.println(temp);
        for(int i=0,len=temp.length(); i<len; i++)
        {

            int pos=letters[i]-'a';
            if(pos==-65)
            {
                System.out.println("Sorry"+letters[i]);
            }
            if(node.son[pos]==null)
            {
                node.haveSon = true;
                node.son[pos]=new TrieNode();
                node.son[pos].val=letters[i];
            }
            else
            {
                node.son[pos].num++;
            }
            node=node.son[pos];
        }
        node.isEnd=true;
    }

    //计算单词前缀的数量
    public int countPrefix(String prefix)
    {
        if(prefix==null||prefix.length()==0)
        {
            return-1;
        }
        TrieNode node=root;
        char[]letters=prefix.toCharArray();
        for(int i=0,len=prefix.length(); i<len; i++)
        {
            int pos=letters[i]-'a';
            if(node.son[pos]==null)
            {
                return 0;
            }
            else
            {
                node=node.son[pos];
            }
        }
        return node.num;
    }
    //打印指定前缀的单词
//    public String hasPrefix(String prefix)
//    {
//        if (prefix == null || prefix.length() == 0)
//        {
//            return null;
//        }
//        TrieNode node = root;
//        char[] letters = prefix.toCharArray();
//        for (int i = 0, len = prefix.length(); i < len; i++)
//        {
//            int pos = letters[i] - 'a';
//            if (node.son[pos] == null)
//            {
//                return null;
//            }
//            else
//            {
//                node = node.son[pos];
//            }
//        }
//        preTraverse(node, prefix);
//        return null;
//    }
//    // 遍历经过此节点的单词.
//    public void preTraverse(TrieNode node, String prefix)
//    {
//        if (node.haveSon)
//        {
//            for (TrieNode child : node.son)
//            {
//                if (child!=null)
//                {
//                    preTraverse(child, prefix+child.val);
//                }
//            }
//            return;
//        }
//        System.out.println(prefix);
//    }


    //在字典树中查找一个完全匹配的单词.
    public boolean has(String str)
    {
        if(str==null||str.length()==0)
        {
            return false;
        }
        TrieNode node=root;
        char[]letters=str.toCharArray();
        for(int i=0,len=str.length(); i<len; i++)
        {
            int pos=letters[i]-'a';
            if(node.son[pos]!=null)
            {
                node=node.son[pos];
            }
            else
            {
                return false;
            }
        }
        return node.isEnd;
    }

    //前序遍历字典树.
    public void preTraverse(TrieNode node)
    {
        if(node!=null)
        {
            System.out.print(node.val+"-");
            for(TrieNode child:node.son)
            {
                preTraverse(child);
            }
        }
    }

    public TrieNode getRoot()
    {
        return this.root;
    }

    public void hasPrefix(String prefix, ArrayList<String>res)
    {
        if (prefix == null || prefix.length() == 0)
        {
            return;
        }
        TrieNode node = root;
        char[] letters = prefix.toCharArray();
        for (int i = 0, len = prefix.length(); i < len; i++)
        {
            int pos = letters[i] - 'a';
            if (node.son[pos] == null)
            {
                return;
            }
            else
            {
                node = node.son[pos];
            }
        }
        String temp=new String(prefix);
        preTraverse(node,res,temp);
        return ;
    }
    //前序遍历字典树.
    public void preTraverse(TrieNode node,ArrayList<String>res,String temp)
    {
        if (node.haveSon)
        {
            for (TrieNode child : node.son)
            {
                if (child!=null)
                {
                    preTraverse(child, res,temp+child.val);
                }
            }
            return;
        }
       res.add(lower2before.get(temp));
    }

//    public static void main(String[]args)
//    {
//
//        PrifixTree tree=new PrifixTree();
//        String[]strs= {"banana","band","bee","absolute","acm",};
//        String[]prefix= {"ba","b","band","abc",};
//        for(String str:strs)
//        {
//            tree.insert(str);
//        }
//        System.out.println("haha");
////        System.out.println(tree.has("abc"));
////        tree.preTraverse(tree.getRoot());
////        System.out.println();
////        //tree.printAllWords();
////        System.out.println();
////        for(String pre:prefix)
////        {
////            int num=tree.countPrefix(pre);
////            System.out.println(pre+""+num);
////
////        }
//        for(String pre:prefix)
//        {
//            ArrayList<String>array=new ArrayList<>();
//            String temp=new String("");
//            tree.hasPrefix(pre,array);
//            System.out.println("The prefix is "+pre);
//            for(String str:array)
//                System.out.println(str);
//
//
//        }
//    }
}

