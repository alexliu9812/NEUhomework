class DevideByMinusException extends Exception{
	int devisor;
	public DevideByMinusException(String msg,int devisor)
	{
		super(msg);
		this.devisor=devisor;
	}
	public int getDevisor()
	{
		return devisor;
	}
}

class TestException4
{
	static public int devide(int x,int y) throws ArithmeticException,DevideByMinusException
	{

		if(y<0)
		  throw new DevideByMinusException("被除数为负",y);		
    int result=x/y;
		return x/y;
	}
	
	public static void main(String []args){
    for (int i=0; i<2; i++){
	  try {
      System.out.println("The result is:"+ devide(10, -5));
    } 
    catch ( DevideByMinusException e){
       e.printStackTrace();
       System.out.println("Error" + e.getMessage());
       System.out.println("devisor =" + e.getDevisor());
       System.exit(0);
    }
    finally{
    System.out.println("i="+i);
    }
    }
   System.out.println("program is over!");
  }
}
