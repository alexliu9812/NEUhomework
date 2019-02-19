/**
 * @(#)testString3.java
 *
 *
 * @author 
 * @version 1.00 2007/12/4
 */

public class testString3 {
        
    /**
     * Creates a new instance of <code>testString3</code>.
     */
    public testString3() {
    	
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
       String s1 = new String("hello");
	   String s2 = new String("Hello");
       class tmp {
       	  
       }
       
       System.out.println("s1.eqaul(s2) is:" + s1.equals(s2));
       System.out.println("s1.equalIgnoreCase(s2) is:" + s1.equalsIgnoreCase(s2));

       tmp t = new tmp();
       System.out.println(t.toString());
       System.out.println(s1.toString());
    }
}
