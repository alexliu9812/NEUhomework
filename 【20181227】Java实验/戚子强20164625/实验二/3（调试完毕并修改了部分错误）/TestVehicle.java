interface Vehicle {
public void drive(); 
}

class TestVehicle{
public static void main(String[] args) {
Vehicle v = new Vehicle(){
public void drive(){
System.out.println("Driving a car!"); 
}
}; 
v.drive(); 
}
}