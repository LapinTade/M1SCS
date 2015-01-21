//
// Prgm: exemple d'interruption de threads
//
// auteur : VF
//
// date : 26/ 09/ 11
//

public class EssaiInterrupt{
    public static void main(String[] args){
	EssaiThread et = new EssaiThread();
	et.start();
	try{
	    Thread.sleep(5000);
	}catch(InterruptedException e){ System.out.println("Thread main interrompu"+e);}
	et.interrupt();
    }
}
 
class EssaiThread extends Thread{
    public void run(){
	/*	for (int i = 0; i < 10; i++) {
	    //Pause for 4 seconds
	    try {
		Thread.sleep(4000);
	    } catch (InterruptedException e) {
		System.out.println("Interrupted");
		return;
	    }
	    //Print a message
	    System.out.println("bonjour");
	}
	*/
	for (int i = 0; i < 4 ; i++){
	    for(long t = 0; t < 1000000000; t++);
	    System.out.println(".");
	    if (Thread.interrupted()){
		System.out.println("j'ai été interrompu");
		return;
	    }
	}
    }
}