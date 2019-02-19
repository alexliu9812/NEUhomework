interface MyInterface{
    void method1();
    int method2();
    int i=10;
}

class Super implements MyInterface{
  public void method1(){}
	public int method2(){return i;}
} 

class Derived extends Super implements MyInterface{
 public void method1(){}
	public int method2(){return i;}
}

