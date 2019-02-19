/**
 * @(#)testString5.java
 *
 *
 * @author 
 * @version 1.00 2007/12/5
 */

public class testString5 {
        
    /**
     * Creates a new instance of <code>testString5</code>.
     */
    public testString5() {

    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
      	String s = "happy happy";
      	String sub = "py";
    	int ch = 'a';
    	
        System.out.println("s is:" + s);
    	System.out.println("index(int char) of is " + s.indexOf(ch)); 
    	System.out.println("lastIndexOf  is " + s.lastIndexOf(ch));
    	System.out.println("index(int, int) is " + s.indexOf(ch, 5));
    	System.out.println("lastIndexOf(int, int) is " + s.lastIndexOf(ch, 5));
    	
        System.out.println();
    	System.out.println("index (String) of is " + s.indexOf(sub)); 
    	System.out.println("lastIndexOf (String) is " + s.lastIndexOf(sub));
    	System.out.println("index(String, int) is " + s.indexOf(sub, 5));
    	System.out.println("lastIndexOf(String, int) is " + s.lastIndexOf(sub, 5));
    	
    	System.out.println();
    	System.out.println("startWith(py) is " + s.startsWith(sub));
    	System.out.println("startWith(ha) is " + s.startsWith("ha"));
    	
    	System.out.println();
    	String s2 = " abc ";
    	System.out.println("the length is " + s2.length());
    	System.out.println(" abc ".trim().length());
    	
    }
}
