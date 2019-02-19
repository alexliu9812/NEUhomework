import java.util.*;
/**
 * @(#)testHashTable1.java
 *
 *
 * @author 
 * @version 1.00 2007/12/10
 */

public class testHashTable1 {
        
    /**
     * Creates a new instance of <code>testHashTable1</code>.
     */
    public testHashTable1() {
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
    	Hashtable numbers=new Hashtable();
  		numbers.put("one",new Integer(1));
  		numbers.put("two",new Integer(2));
  		numbers.put("three",new Integer(3));
  	//	Integer i1;
  	//	i1 = (Integer)numbers.put("two", new Integer(4));
  	//	System.out.println(i1.toString());
		Integer n=(Integer)numbers.get("two");
  		if (n!=null)
  		{
     		System.out.println("two="+n);
  		}
    }
}
