public class Launcher {
	public static void main(String args[]) {
		int TAILLE_MAX = 5;
		Compte[] comptes = new Compte[TAILLE_MAX];
		for(int k=0; k < TAILLE_MAX; k++) {
			comptes[k] = new Compte(k, (int)(Math.random() * 666));
		}
		Banque b1 = new Banque("B1", comptes, TAILLE_MAX);
		Banque b2 = new Banque("B2", comptes, TAILLE_MAX);
		Banque b3 = new Banque("B3", comptes, TAILLE_MAX);
		Banque b4 = new Banque("B3", comptes, TAILLE_MAX);
		Banque b5 = new Banque("B3", comptes, TAILLE_MAX);
		b1.start();
		b2.start();
		b3.start();
		b4.start();
		b5.start();
	}
}
