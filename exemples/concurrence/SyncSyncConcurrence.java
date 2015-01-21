/*
  SyncSyncConcurrence
  	- méthodes set et affich synchronisées 
   - et de plus, les appels succesifs de set et affich sont réalisés 
     dans un bloc synchronisé
*/
class MaDonnee {

    public int a, b;
    public synchronized void set (int sa, int sb) {
	a = sa ; 
	b = sb ;
    }
    public synchronized void affich() {
	System.out.println(Thread.currentThread().getName() + " a = " + a + " b = " + b);
    }
}

class MonThread1 extends Thread {

    MaDonnee md;

    public MonThread1(MaDonnee ref) {
	md = ref;
    }

    public void run() {
	for (int i = 0 ; i < 10 ; i++) {	    	    
	    synchronized(md) {
		md.set(i, 10 + i);
		md.affich();
	    }
	    try{sleep(2);}catch(InterruptedException e){}
	}
    }
}

class MonThread2 extends Thread {

    MaDonnee md;

    public MonThread2(MaDonnee ref) {
	md = ref;
    }

    public void run() {
	for (int i = 0 ; i < 10 ; i++) {   
	    synchronized(md) {
		md.set(20 + i, 30 + i);
		md.affich();
	    }
		try{sleep(3);}catch(InterruptedException e){}
	}
    }
}

public class SyncSyncConcurrence {

    public static void main(String args[]) {

	try {
	    
	    MaDonnee md = new MaDonnee();

	    MonThread1 mt1 = new MonThread1(md);
	    MonThread2 mt2 = new MonThread2(md);

	    mt1.start();
	    mt2.start();
	    
	    mt1.join();
	    mt2.join();

	} catch (Exception ex) {
	    System.out.println(ex);
	}
    }
}

