import java.io.*;
import java.util.*;
public class Exercise {

	public static void main(String[] args) throws Exception {
		File f=new File("e:\\hello.txt");
		BufferedReader br=new BufferedReader(new FileReader(f));
		Vector v=new Vector();
		String str;
		while((str=br.readLine())!=null)
		{
			v.add(str);
		}
		int size=v.size();
		for(int i=size-1;i>=0;i--)
		System.out.println((String)v.elementAt(i));
		
	}
}