class TryRun implements Runnable {
	private int affichage;
	private String name;
	
	public TryRun (int aff) {
		this.affichage = aff;
	}
	
	public void run() {
		while(true) {
			long threadId = Thread.currentThread().getId();
            System.out.print("ID: " + threadId + " nb: " + affichage + "\n");
            affichage++;
		}
	}
}

public class FirstExoInt {
	public static void main(String args[]) {
		Thread th1 = new Thread(new TryRun(0));
		Thread th2 = new Thread(new TryRun(0));
		
		th1.setPriority(Thread.MIN_PRIORITY);
		th2.setPriority(Thread.MAX_PRIORITY);
		
		th1.start();
		th2.start();
	}
}
