public class Compte {
	double solde;
	int num;
	
	
	public Compte( int num, int init) {
		this.num = num;
		this.solde = init;
	}
	
	public void retirer(int somme) {
		solde -= somme;
	}
	
	public void deposer(int somme) {
		solde += somme;
	}
	
	public double getSolde() {
		return solde;
	}
	
	public int getNum() {
	return num;
	}
}
