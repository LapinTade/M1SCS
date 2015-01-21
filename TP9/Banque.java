public class Banque extends Thread {
	Compte[] comptes;
	int taille;
	String nom;
	
	public Banque(String nom, Compte[] comptes, int taille) {
		this.nom = nom;
		this.comptes = comptes;
		this.taille = taille;
	}
	
	public void transfert(Compte source, Compte dest, int montant) {
		source.retirer(montant);
		dest.deposer(montant);
		System.out.print(this.nom + "> Trans " + source.getNum() + " --> " + dest.getNum() + " : " + montant + "$ \t|||\t\t");
	}
	
	public void recapBanque() {
		for(Compte cpt: comptes) {
			System.out.println("Compte numero " + cpt.getNum() + " Solde: " + cpt.getSolde());
		}
	}
	
	//@Overrides
	public void run() {
		int cpt1;
		int cpt2;
		int montant;
		int somme;
		while(true) {
			cpt1 = (int)(Math.random() * this.taille);
			cpt2 = (int)(Math.random() * this.taille);
			montant = (int)(Math.random() * 666);
			
			somme = 0;
			
			for(int k = 0; k < taille; k++) somme += comptes[k].getSolde();
			
			transfert(comptes[cpt1], comptes[cpt2], montant);
			System.out.println(somme);
		}
	}
}
