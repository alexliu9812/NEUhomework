/**
 * @(#)testVector1.java
 *
 *
 * @author 
 * @version 1.00 2007/12/10
 */
import java.util.*;
public class testVector1 {
        
    /**
     * Creates a new instance of <code>testVector1</code>.
     */
    public testVector1() {
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Vector v=new Vector();
		for(int i=0;i<10;i++)
		{
    		v.addElement(new Integer(i));
		}
	
    	Enumeration e=v.elements();
		while(e.hasMoreElements())
		{
			Integer intObj=(Integer)e.nextElement();
			System.out.print (intObj.intValue());
		}

    }
}
