/**
 * @(#)testStringBuffer.java
 *
 *
 * @author 
 * @version 1.00 2007/12/9
 */

public class testStringBuffer {
        
    /**
     * Creates a new instance of <code>testStringBuffer</code>.
     */
    public testStringBuffer() {
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        StringBuffer s1 = new StringBuffer("abc");
        String s2;
        char [] c1={'d','e','f'};
        System.out.println(s1.capacity());
        System.out.println(s1.length());
        System.out.println(s1.reverse());
        System.out.println(s1);
        s1.setCharAt(1, 'a');
        System.out.println(s1);
        s1.append("abc");
        System.out.println(s1);
        s1.append(c1,1, 2);
        System.out.println(s1);
        s1.delete(0,2);
        System.out.println(s1);
        s1.insert(2,15);
        System.out.println(s1);
        s1.insert(2, c1, 0,2);
        System.out.println(s1);
    
    }
}
