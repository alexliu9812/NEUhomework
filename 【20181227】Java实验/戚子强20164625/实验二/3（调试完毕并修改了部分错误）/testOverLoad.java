class Human{
double salary;
void setSalary(double a) {
	salary=a;
}

void setSalary(double a,double b) {
	salary=a+b;
	System.out.println("double double is called.");
}

void setSalary(double a,int b) {
	salary=a+b;
	System.out.println("double int is called.");
}


void printSalary()
{
   System.out.println("The salary is "+ salary);
}


}

class testOverLoad{
public static void main(String args[])
 {
    short i=10;
    Human man = new Human();
    man.setSalary(100.0, i);
 }
}