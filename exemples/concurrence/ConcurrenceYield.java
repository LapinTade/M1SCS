//*********************************************
//
// File: Concurrence.java
//
// Synopsis: méthode set synchronisée pour éviter 
//           un accès concurrent de plusieurs threads
// 
// Author: LP
//
// Date: 03/10/09
//
//***********************************************


class MaDonnee {   
    
    public int a, b;
    
    public synchronized void  set (int sa, int sb) {
    //public void set (int sa, int sb) { 
	a = sa; 
	//if (a < 10)  Thread.yield(); // pour méthode non synchronisée
	b = sb; 
    } 
}

class MonThread1 extends Thread {
    
    MaDonnee md;
    
    public MonThread1(MaDonnee ref) { 
	md = ref;   
    }

    public void run() {
	for (int i = 0 ; i < 10 ; i++) {
	    md.set(i, 10 + i); 
    	    Thread.yield();
	    System.out.println(Thread.currentThread().getName() + " a= "+md.a+" b= " + md.b);
	    //System.out.println(Thread.currentThread().getName() +" b= " + md.b);
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
	    md.set (20+i, 30 + i); 
	    Thread.yield(); 
	    System.out.println(Thread.currentThread().getName() + " a= " +md.a+ " b= " + md.b);
	    //System.out.println(Thread.currentThread().getName() +" b= " + md.b);
	}    
    }   
}

public class ConcurrenceYield {

    public static void main(String args[]) {

	try {
	    
	    MaDonnee md = new MaDonnee();

	    MonThread1 mt1 = new MonThread1(md);
	    MonThread2 mt2 = new MonThread2(md);

	    mt2.start();mt1.start();
	    
	    
	    mt1.join();
	    mt2.join();

	} catch (Exception ex) {
	    System.out.println(ex);
	}
    }
}

