class Employee
{
	void salary()
	{
		System.out.println(" Employee salary");
	}   
}
class Secretary extends Employee
{
	void salary()
	{
		System.out.println(" Secretary salary");
	}   
}
class Manager extends Employee
{
	void salary()
	{
		System.out.println(" Manager salary");
	}   
}

public class EmployeeSalary2
{
	static void salaryOfEmployee(Employee clerk)
	{
		clerk.salary(); 
	}

	public static void main(String[] args)
	{
		Secretary s=new Secretary();
		Manager m=new Manager();		
		EmployeeSalary2.salaryOfEmployee(s);
		EmployeeSalary2.salaryOfEmployee(m);
	}
}
