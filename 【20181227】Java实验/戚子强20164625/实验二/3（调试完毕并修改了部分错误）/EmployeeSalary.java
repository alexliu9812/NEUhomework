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

public class EmployeeSalary
{
	static void salaryOfEmployee(Employee clerk)
	{
		clerk.salary(); 
	}

	public static void main(String[] args)
	{
		Secretary s=new Secretary();
		Manager m=new Manager();		
		EmployeeSalary.salaryOfEmployee(s);
		EmployeeSalary.salaryOfEmployee(m);
	}
}
