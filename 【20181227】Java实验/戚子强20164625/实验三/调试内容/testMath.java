/**
 * @(#)testMath.java
 *
 *
 * @author 
 * @version 1.00 2007/12/10
 */

public class testMath {
        
    /**
     * Creates a new instance of <code>testMath</code>.
     */
    public testMath() {
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        double d1;
        
        System.out.println(Math.sqrt(-1));
        d1 = Math.sqrt(-1);
        System.out.println(d1+1);
        
        System.out.println(Math.abs(Integer.MIN_VALUE) == Integer.MIN_VALUE);
        
        System.out.println(Math.ceil(10.1));
        System.out.println(Math.ceil(10));
        System.out.println(Math.ceil(10.9));
        System.out.println(Math.ceil(-10.1));
        System.out.println(Math.ceil(-10.9));
        
        System.out.println(Math.floor(10));
        System.out.println(Math.floor(10.1));
        System.out.println(Math.floor(10.9));
        System.out.println(Math.floor(-10.1));
        System.out.println(Math.floor(-10.9));
        
        System.out.println(Math.round(10.1));
        System.out.println(Math.round(10.9));
        System.out.println(Math.round(-10.1));
        System.out.println(Math.round(-10.9));
        System.out.println(Math.round(-10.5));
         
        System.out.println(Math.random());
        System.out.println(Math.random());
    }
}
