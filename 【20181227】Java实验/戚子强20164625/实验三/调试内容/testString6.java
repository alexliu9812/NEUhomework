/**
 * @(#)testString6.java
 *
 *
 * @author 
 * @version 1.00 2007/12/9
 */

public class testString6 {
        
    /**
     * Creates a new instance of <code>testString6</code>.
     */
    public testString6() {
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        String s1="abc"; String s2 = "xyz";
        String s3;
       
        s1 = s2;
        System.out.println("s1=" + s1);
        System.out.println("s2=" + s2);
        s1 = s1 + "def";
        System.out.println("s1=" + s1);
        System.out.println("s2=" + s2);
    

    }
}
