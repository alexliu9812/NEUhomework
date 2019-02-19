import java.io.*;
class MyID{
	public static void main(String args[])
	{
		try{
		   FileOutputStream fo = new FileOutputStream("Test.txt");
		   byte buf[] = "name".getBytes();
		   fo.write("mary".getBytes());
		   fo.write("age".getBytes());
		   fo.close();
		}
		catch(Exception e){
		}
		
	}
}