public class Launcher {
	public static void main(String[] args) {
		Rdv rdv = new Rdv(4);
		
		Invite i1 = new Invite(rdv);
		Invite i2 = new Invite(rdv);
		Invite i3 = new Invite(rdv);
		Invite i4 = new Invite(rdv);
		
		i1.start();
		i2.start();
		i3.start();
		i4.start();
	}
}
