/**
 * @(#)tmp1.java
 *
 *
 * @author 
 * @version 1.00 2007/12/10
 */

public class tmp1 {
        
    /**
     * Creates a new instance of <code>tmp1</code>.
     */
    public tmp1() {
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Integer i1 = new Integer(5);
        Long    l1 = new Long(5l);
        
        System.out.println(i1.equals(l1));   
     //   System.out.println(i1.equals(5));        
    }
}
