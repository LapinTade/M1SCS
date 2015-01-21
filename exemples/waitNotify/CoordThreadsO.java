//
// Prgm: exemple de synchronisation wait/notify
//       objets synchronisés
// auteur : VF
//
// date : 26/ 09/ 11
//


class Counter{
    private int val;
    public void setCounter(int val){ this.val = val;}
    public int getCounter(){ return val;}
}

class WaitClass extends Thread{
    Counter c;
    public WaitClass(Counter c){this.c=c;}
    public void run(){
	System.out.println(getName()+" Attente du compteur");
	synchronized(c){
	    try{
		c.wait();
	    }catch(InterruptedException e){
		e.printStackTrace();
	    }
	}
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
	synchronized(c){
	    int val = (int)(Math.random()*10);
	    System.out.println(getName()+" Valeur générée " + val);
	    c.setCounter(val);
	    c.notify();
	}
    }
}
public class CoordThreadsO{
    public static void main(String[] args){
	Counter c = new Counter();
	new WaitClass(c).start();
	new NotifyClass(c).start();
    }
}

