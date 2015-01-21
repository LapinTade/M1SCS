//*********************************************
//
// File: CounterMultiCore.java
//
// Synopsis: shows that ++ is not atomic
//           
// 
// Author: LP
//
// Date: 03/10/09
//
//***********************************************

class MaDonnee {
    public int a;
    public MaDonnee() { a = 0; }
}

class MonThread extends Thread {
    MaDonnee md;
    int nbIter = 10000;

    public MonThread(MaDonnee ref) { md = ref; }
    public void run() { 
	for (int i = 0 ; i < nbIter ; i++) md.a++;  
    }
}

public class CounterMultiCore {
   
    public static void main(String args[]) {
	try {
	    MaDonnee md = new MaDonnee();
	    MonThread mt1 = new MonThread(md);
	    MonThread mt2 = new MonThread(md);
	    mt1.start();
	    mt2.start();
	    mt1.join();
	    mt2.join();
	    System.out.println( " a= " + md.a);
	} catch (Exception ex) {
	    System.out.println(ex);
	}
    }
}