class Palindrome
{
    public Deque<Character> wordToDeque(String word)
    {
        Deque<Character> res=new ArrayDeque<>();
        for(int i=0;i<word.length();++i)
        {
            res.addLast(word.charAt(i));
        }
        return res;
    }
    private boolean isPalindrome_help(Deque<Character> queue)
    {
        if(queue.size()==1||queue.size()==0)
            return true;
        return queue.removeFirst()==queue.removeLast()&&isPalindrome_help(queue);
    }
    public boolean isPalindrome(String word){
        Deque<Character> queue=wordToDeque(word);
        return isPalindrome_help(queue);
    }

    public boolean isPalindrome(String word, CharacterComparator cc)
    {
        int len=word.length();
        for(int i=0;i<len/2;++i)
        {
            if(!cc.equalChars(word.charAt(i),word.charAt(len-1-i)))
                return false;
        }
        return true;
    }
}