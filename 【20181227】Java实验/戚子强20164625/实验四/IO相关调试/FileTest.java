import java.io.*;

public class FileTest {

	public static void main(String[] args) {
        //File d=new File("d:\\javakejian");
        File d = new File("e:\\my");
        d.mkdir(); 
		File f=new File("e:\\my\\my file.txt");
	    //File f=new File("my file.txt");
                		
		try
		{
			f.createNewFile();
        }       
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
        File d1=new File("e:\\dir1");
        File d2=new File("e:\\dir1\\dir2");  
        d1.mkdir();
        d2.mkdir();
       
		String s[]=d.list();
		int i=s.length;
		while (i>0)
		{
			System.out.println(s[i-1]);
			i--;
		}
		//f.delete();
		System.out.println("File name:"+f.getName());
		System.out.println("File path:"+f.getPath());
		System.out.println("File absolute path:"+f.getAbsolutePath());
		System.out.println(f.exists()?"exists":"dose not exists");
		System.out.println(f.canRead()?"Can Read":"Can not read");
		System.out.println(f.canWrite()?"Can Write":"Can not Write");
		System.out.println(f.lastModified());

		System.out.println(f.getName());
		System.out.println(f.getParent());
	}
}
