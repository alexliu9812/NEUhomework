public class Test4
 {
  int value = 10;        //��Ա����
  public void showValue()
    {
     int value = 20;      //��ʱ����
     System.out.println("value ��ʱ����= "+value);
     System.out.println("this.value = "+this.value);
    }
  public static void main(String args[])
   {
    TryThis t = new TryThis();
    t.showValue();
   }
 }
