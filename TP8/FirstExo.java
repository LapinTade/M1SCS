class TryThread extends Thread {
	private int affichage;
	
	public TryThread (int affichage) {
		this.affichage = affichage;
	}
	
	public void run() {
		while(true) {
            System.out.print("ID: " + this.getId() + " nb: " + affichage + "\n");
            affichage++;
	    	yield();
		}
	}
}

public class FirstExo {
	public static void main(String args[]) {
		TryThread th1 = new TryThread(0);
		TryThread th2 = new TryThread(0);
		
		th1.start();
		th2.start();
	}
}
