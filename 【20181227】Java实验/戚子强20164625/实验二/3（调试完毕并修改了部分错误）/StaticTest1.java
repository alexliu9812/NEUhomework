public class StaticTest1
{ 
  int age;
  boolean sex;
  String name;
  static long population;		//��̬����
  static void printPopulation(){}	//��̬����
  
  public static void main(String[] as)
  {
    StaticTest1 man = new StaticTest1();
    man.population = 100;
    System.out.println(StaticTest1.population);   //100
  }
}
