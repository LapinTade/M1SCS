class TryInterrupt extends Thread {
	private int affichage;
	private String name;
	boolean meow;
	
	public TryInterrupt () {
		super();
		meow = true;
	}
	
	public void run() {
		while(meow) {
			long threadId = getId();
            System.out.print("ID: " + threadId + " nb: " + affichage + "\n");
            affichage++;
            
            if(this.isInterrupted()) {
            	System.out.print("INTERRUPTED !");
            	meow = false;
            }
		}
	}
}

public class FirstExotInterrupt {
	public static void main(String args[]) {
		TryInterrupt th1 = new TryInterrupt();
		
		th1.start();
		
		try {
			Thread.sleep(200);
		} catch (InterruptedException e) {
			System.out.print("INTERRUPT! " + e);
		}
		
		//th1.interrupt();
		th1.meow = false;
	}
}
