//*********************************************
//
// File: Concurrence.java
//
// Synopsis: shows that the coherency between a and b is not always
//           guaranteed. In this case, just adding 
//           Thread.currentThread().getName() seems to generate some
//           context switch between a = sa and b = sb. 
// 
// Author: LP
//
// Date: 03/10/09
//
//***********************************************


class MaDonnee {

    int a, b;
    public void setA (int sa) {
	a = sa ; 
    }
    
    public void setB(int sb) {
	b = sb ; 
    }
    
}

class MonThread1 extends Thread {

    MaDonnee md;

    public MonThread1(MaDonnee ref) {
	md = ref;
    }

    public void run() {

	for (int i = 0 ; i < 50 ; i++) {
	    md.setA(i);
	    System.out.println(" ");
	    md.setB(10 + i);
	    System.out.println(this.getName() + 
			       " a = " + md.a + " b = " + md.b);
	}
    }
}

class MonThread2 extends Thread {

    MaDonnee md;

    public MonThread2(MaDonnee ref) {
	md = ref;
    }

    public void run() {

	for (int i = 0 ; i < 50 ; i++) {
	    md.setA(20 + i);
	    System.out.println(" ");
	    md.setB(30 + i);
	    System.out.println(this.getName() + 
			       " a = " + md.a + " b = " + md.b);
	}
    }
}

public class Concurrence {

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

