class StaticCode
{
	static String country;
	static
	{
		country = "china";
		System.out.println("StaticCode is loading");
	}
	StaticCode(){
		System.out.println("StaticCode is built");
	}
}
class TestStaticCode
{
	static
	{
		System.out.println("TestStaticCode is loading");
	}
	public static void main(String [] args)
	{
		System.out.println("begin executing main method");
		new StaticCode();
		new StaticCode();
	}
}