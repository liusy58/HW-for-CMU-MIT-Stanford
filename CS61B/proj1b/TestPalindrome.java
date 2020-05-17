import org.junit.Test;
import static org.junit.Assert.*;

public class TestPalindrome {
    // You must use this palindrome, and not instantiate
    // new Palindromes, or the autograder might be upset.
    static Palindrome palindrome = new Palindrome();

    @Test
    public void testWordToDeque() {
        Deque d = palindrome.wordToDeque("persiflage");
        String actual = "";
        for (int i = 0; i < "persiflage".length(); i++) {
            actual += d.removeFirst();
        }
        assertEquals("persiflage", actual);
    }
    @Test
    public void testisPindrome() {
        String str1="abacaba";
        String str2="abc";
        String str3="ccccccc";

        assertEquals(palindrome.isPalindrome(str1),true);
        assertEquals(palindrome.isPalindrome(str2),false);
        assertEquals(palindrome.isPalindrome(str3),true);

    }
    @Test
    public void testisPindrome2() {
        CharacterComparator cc=new OffByOne();
        assertFalse(palindrome.isPalindrome("aaa",cc));
        assertTrue(palindrome.isPalindrome("flake",cc));
    }

}
// Uncomment this class once you've created your Palindrome class. */