interface Runner
{
   int ID = 1;
   void run();
}

interface Flyer
{
   void fly();
}

interface Swimmer
{
   void swim();  
}

interface Animal extends Runner, Flyer
{
	void breathe();
}

abstract class Fish implements Animal
{
	  public void run()
	  //void run()
	  {
		System.out.println("fish is swimming");
	  }
	  public void breathe()
	  {
		System.out.println("fish is bubbling");
	  }
}


class Bird implements Animal
{
    public void run()
    { System.out.println("Bird is running");}
    public void breathe()
    { System.out.println("Bird is breathing"); }
    public void fly()
    { System.out.println("Bird is flying");}
}

 
abstract class LandAnimal implements Animal
{
	public void breathe()
	  {
	 	System.out.println("LandAnimal is breathing");
	  }
}

class Perfect extends  Bird implements Swimmer
{
   public void swim(){
   System.out.println("Perfect is swimming.");
   }
}

class testInterface2
{
   public static void main(String []args)
   {
    Bird bird = new Bird();
    Animal animal = new Bird();
    //LandAnimal landanimal = new Bird();
    Perfect perfect = new Perfect();
    
   
    bird.run();
    bird.breathe();
    bird.fly();
    
    animal.run();
    animal.breathe();
    animal.fly();
    
    perfect.run();
    perfect.breathe();
    perfect.fly();
    perfect.swim();
   }
}