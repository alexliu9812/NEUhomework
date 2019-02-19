import java.io.*;
public class TestException3
{
	public static void main (String[] args)
	{
    try{
       FileInputStream s =  new FileInputStream("file.txt");
       int c = s.read();
    } 
    catch(IOException e){
     //  e.printStackTrace();
     }
    catch(FileNotFoundException e){
         e.printStackTrace();
     }


		System.out.println ("program ends");
	}
}