/**
 * @(#)testString2.java
 *
 *
 * @author 
 * @version 1.00 2007/12/4
 */

public class testString2 {
        
    /**
     * Creates a new instance of <code>testString2</code>.
     */
    public testString2() {
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
       String s1 = new String("hello");
	   String s2 = new String("hello");
	   String s3 = "hello";
	   String s4 = "hello";
	   
	   System.out.println("s1==s2 is:" + (s1==s2));
	   System.out.println("s1.eqaul(s2) is:" + s1.equals(s2));
	   System.out.println("s3==s4 is:" + (s3==s4));
	   
	   System.out.println("s3.equal(s4) is:" + s3.equals(s4));
	 
    }
}
