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

class TestException5
{
	static public int devide(int x,int y) 
	{
    try{
		   if(y<0)
		     throw new DevideByMinusException("被除数为负",y);		
       int result=x/y;
    }
    catch ( DevideByMinusException e){
       e.printStackTrace();
       System.out.println("Error" + e.getMessage());
       System.out.println("devisor =" + e.getDevisor());
       
    }
		return x/y;
	}
	
	public static void main(String []args){
	   devide(10, -5); 
  }
  
}
