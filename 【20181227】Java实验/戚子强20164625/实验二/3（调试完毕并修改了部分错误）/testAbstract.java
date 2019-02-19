abstract class A
{
  
  abstract int aa(int x, int y);
}

class B extends A{
  int aa (int x, int y)
  {
    return x+y;
  }
}
class testAbstract
{
  public static void main(String []args)
  {
   // A a = new A();
    B b = new B();
  }

}