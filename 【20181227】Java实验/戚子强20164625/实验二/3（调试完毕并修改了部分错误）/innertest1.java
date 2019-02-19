class Outer
{
	int outer_i = 100;
	void test()
	{
		Inner in = new Inner();
		in.display();
	}
	class Inner
	{
		void display()
		{
		System.out.println("display: outer_i = " + outer_i);
		}
	}
}

class innertest1
{
	public static void main(String[] args)
	{
		Outer outer = new Outer();
		outer.test();
	}
}