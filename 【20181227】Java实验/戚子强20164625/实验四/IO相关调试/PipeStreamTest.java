import java.io.*;
class Sender extends Thread
{
	private PipedOutputStream out=new PipedOutputStream();
	public PipedOutputStream getOutputStream()
	{
		return out;
	}
	public void run()
	{
		String s=new String("PipedOutputStream,PipedInputStream");
		try
		{
			out.write(s.getBytes());
			out.close();
			}
			catch(IOException e)
			{
				System.out.println(e.getMessage());
			}
	}
}
class Receiver extends Thread
{
	private PipedInputStream in=new PipedInputStream();
	public PipedInputStream getInputStream()
	{
		return in;
	}
	public void run()
	{
		String s=null;
		byte[] buf=new byte[1024];
		try
		{
			int len=in.read(buf);
			s=new String(buf,0,len);
			System.out.println("the following message comes from sender:\n"+s);
			in.close();
		}
		catch(IOException e)
		{
			System.out.println(e.getMessage());
		
		}
	}
}	 

public class PipeStreamTest
{
	public static void main(String[] args)
	{
		try
		{
			Sender t1=new Sender();
			Receiver t2=new Receiver();
			PipedOutputStream out=t1.getOutputStream();
			PipedInputStream in=t2.getInputStream();
			out.connect(in);
			//in.connect(out);
			t1.start();
			t2.start();
			
		}
		catch(IOException e)
		{
			System.out.println(e.getMessage());
		}
	}
}