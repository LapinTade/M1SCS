//
// Prgm: exemple de synchronisation wait/notify
//       méthodes synchronisées
//
// auteur : VF
//
// date : 26/ 09/ 11
//


class Counter{
    private int val;
    public synchronized void setCounter(int val){  
	this.val = val;
	notify();
    }
    public synchronized int getCounter(){ 
	try{
	    wait();
	}catch(InterruptedException e){
	    e.printStackTrace();
	}
	return val;
    }
}

class WaitClass extends Thread{
    Counter c;
    public WaitClass(Counter c){this.c=c;}
    public void run(){
	System.out.println(getName()+" Attente du compteur");
	System.out.println(getName()+" Le compteur attendu " + c.getCounter());
    }
}

class NotifyClass extends Thread {
    Counter c;
    public NotifyClass(Counter c){this.c=c;}
    public void run(){
	try{
	    sleep(1000);
	}catch(InterruptedException e){
	    e.printStackTrace();
	}
	int alea = (int)(Math.random()*10);
	System.out.println(getName()+" Valeur générée " + alea);
	c.setCounter(alea);
    }
}
public class CoordThreadsM{
    public static void main(String[] args){
	Counter c = new Counter();
	new WaitClass(c).start();
	new NotifyClass(c).start();
    }
}

