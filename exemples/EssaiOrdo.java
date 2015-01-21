class EssaiThread extends Thread{
    public void run(){
	while (true){
	    System.out.print("#");
	}
    }
}
public class EssaiOrdo{
    public static void main(String[] args){
	EssaiThread thr = new EssaiThread();
	thr.start();
	while (true){
	    System.out.print(".");
	}
    }
}