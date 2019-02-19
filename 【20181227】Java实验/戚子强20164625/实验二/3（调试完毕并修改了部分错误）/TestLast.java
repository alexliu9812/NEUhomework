class TestLast
{
  public static void main(String [] arg)
  {
    System.out.println(3<<32);  
    System.out.println(3<<33);
    int a=2;
    System.out.println(a+3*a++);
    a =2; 
    System.out.println((a++)+3*a);
  }
  
}