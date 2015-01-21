class EssaiThread extends Thread {

    // lorsque l'on met static, c'est la meme variable 
    // qui est definie dans chaque thread.
    // private static long vart;

    // lorsque l'on ne met pas static, on a une variable par thread
    private long vart;

    /** constructeur permettant de nommer le processus */
    public EssaiThread(long t) {
        vart = t;
    }

    /** affiche son nom puis passe le controle au suivant */
    public void run(){

	
	for (int i = 0; i < 5; i++){
            System.out.println(getName() + " "+ vart+" i = "+i);
            //if ( i == 0 ) this.yield();    // passe la main
        }
    }
    
}

public class EssaiPriorite {
    
    public static void main(String args[]) {
    
	EssaiThread thread1 = new EssaiThread(1);
        EssaiThread thread2 = new EssaiThread(2);
        
	thread1.setPriority(Thread.MIN_PRIORITY);

	thread2.setPriority(Thread.MAX_PRIORITY);
	
	thread1.start();
	System.out.println("Debut thread 1");
	thread2.start();
	System.out.println("Debut thread 2");

	System.out.println("Priorité thread1 = " + thread1.getPriority()+
			"Priorité thread2 = " + thread2.getPriority()+
			"Priorité thread main = " + Thread.currentThread().getPriority());
	        
        for (int i = 0; i < 6; i++)
            System.out.println("je suis la tache principale !");
        

	// thread principal attend la fin des 2 threads
	try { 
	    thread1.join();
	    System.out.println("Fin thread 0!");
	    thread2.join();
	    System.out.println("Fin thread 1!");
	}
	catch(Exception e) {
	    System.out.println(e);
	}

    }

}
