class statictest3
{ 
   private static int count=0;
   
   public void finalize()
   {
     System.out.println("finalize is done! count="+count);
     count--;
     System.gc();
   }
   
   public statictest3(){
         count=count+1;
  }

  public static void main(String[] as)
  {
    statictest3 a1;
    for (;;){
       a1 = new statictest3();
       System.out.println(statictest3.count);   //100
    }
  }
}
