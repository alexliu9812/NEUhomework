class Car {
public void drive(){
System.out.println("Driving a car!"); 
}
}

class TestCar{
public static void main(String[] args) {
Car car = new Car(){
public void drive(){
System.out.println("Driving another car!"); 
}
}; 
car.drive(); 
}
}