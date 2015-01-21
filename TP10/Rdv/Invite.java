public class Invite extends Thread {
	private Rdv rdv;
	
	public Invite (Rdv rdv) {
		this.rdv = rdv;
	}
	
	public void run() {
		try {
			sleep((int) (Math.random() * 2000));
			System.out.println(getName() + " est là");
			rdv.waitInvite();
		} catch (InterruptedException ie){
            ie.printStackTrace();
        }
	}
}
