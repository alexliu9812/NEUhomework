public class TryThis
 {
  int value = 10;        //成员变量

  public void showValue()
    {
     int value = 20;      //临时变量
     System.out.println("value 临时变量= "+value);
     System.out.println("this.value = "+this.value);
    }
  public static void main(String args[])
   {
    TryThis t = new TryThis();
    t.showValue();
   }
 }
