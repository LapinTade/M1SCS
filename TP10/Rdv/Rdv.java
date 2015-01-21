public class Rdv {
	private int nbInvite;
	private int inviteRestant;
	
	public Rdv(int nbInvite) {
		this.nbInvite = nbInvite;
		this.inviteRestant = nbInvite;
	}
	
	synchronized void waitInvite() {
		inviteRestant--;
		
		if(inviteRestant == 0) {
			notifyAll();
			System.out.println("Tout le monde est là");
		} else {
			try {
				wait();
			} catch(InterruptedException ie){
            	ie.printStackTrace();
            }
		}
	}
}
