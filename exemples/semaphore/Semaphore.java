/*
 * Classe semaphore générique
 */
public class Semaphore {
    private int valeur;
    
    public Semaphore(int d)    {
	valeur = d;
    }
    
    public synchronized void P(int n) {
	
	System.out.println( n + " Demande sem a " + valeur );
	
	while(valeur==0) {
	    
	    try {
		
		System.out.println( n + " mis en attente de sem");
		wait();
		System.out.println( n + " reveil de sem");
		
	    } catch (InterruptedException e) {	
		System.out.println("Erreur semaphore.P");
	    }
	}
	valeur--;
    }
    
    public synchronized void V(){
	valeur++;
	notify();
    }
    
}
