interface MyInterface{
	void method1();
  int method2();
  int i=10;
}

class MyClass implements MyInterface{
   public void method1(){ }
   public int method2(){return i;}
}

class subClass extends MyClass
{}