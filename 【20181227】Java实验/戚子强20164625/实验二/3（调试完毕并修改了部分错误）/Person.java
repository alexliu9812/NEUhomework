public class Person
{
	public void finalize()
	{
		System.out.println("the object is going!");
	}
	public static void main(String [] args)
	{
		new Person();
		new Person();
		new Person();
//  	System.gc();
		System.out.println("the program is ending!");
	}
}