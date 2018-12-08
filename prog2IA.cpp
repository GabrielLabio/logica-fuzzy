#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

double refriFraco(int refri, double ml) { 
	if(refri==1) {
		if(ml<56)
			return 0;
		else if(56<=ml && ml<58)
			return (ml-56)/(58-56);
		else if(58<=ml && ml<=60)
			return 1;
		else
			return 0;
	}
	else {
		if(ml<66)
			return 0;
		else if(66<=ml && ml<68)
			return (ml-66)/(68-66);
		else if(68<=ml && ml<=70)
			return 1;
		else
			return 0;
	}
}

double refriSuave(int refri, double ml) { 
	if(refri==1) {
		if(ml<52)
			return 0;
		else if(52<=ml && ml<54)
			return (ml-52)/(54-52);
		else if(54<=ml && ml<56)
			return 1;
		else if(56<=ml && ml<=58)
			return (58-ml)/(58-56);
		else
			return 0;
	}
	else {
		if(ml<62)
			return 0;
		else if(62<=ml && ml<64)
			return (ml-62)/(64-62);
		else if(64<=ml && ml<66)
			return 1;
		else if(66<=ml && ml<=68)
			return (68-ml)/(68-66);
		else
			return 0;
	}
}

double refriForte(int refri, double ml) { 
	if(refri==1) {
		if(ml<50)
			return 0;
		else if(50<=ml && ml<52)
			return 1;
		else if(52<=ml && ml<=54)
			return (54-ml)/(54-52);
		else
			return 0;
	}
	else {
		if(ml<60)
			return 0;
		else if(60<=ml && ml<62)
			return 1;
		else if(62<=ml && ml<=64)
			return (64-ml)/(64-62);
		else
			return 0;
	}
}

double rumFraco(double ml) { 
	if(ml<10)
		return 0;
	else if(10<=ml && ml<15)
		return 1;
	else if(15<=ml && ml<=20)
		return (20-ml)/(20-15);
	else
		return 0;
	
}

double rumSuave(double ml) { 
	if(ml<15)
		return 0;
	else if(15<=ml && ml<20)
		return (ml-15)/(20-15);
	else if(20<=ml && ml<25)
		return 1;
	else if(25<=ml && ml<=27)
		return (27-ml)/(27-25);
	else
		return 0;
}

double rumForte(double ml) { 
	if(ml<23)
		return 0;
	else if(23<=ml && ml<28)
		return (ml-23)/(28-23);
	else if(28<=ml && ml<=30)
		return 1;
	else
		return 0;
}

double gelo(double ml) { 
	if(ml<20)
		return 0;
	else if(ml==20)
		return 1;
	else
		return 0;
}

double max(double x, double y, double z) {
	return (x<y) ? ((y<z) ? z : y) : ((x<z) ? z : x);
}

double min(double x, double y, double z) {
	return (x<y) ? ((x<z) ? x : z) : ((y<z) ? y : z);
}

double calcGrauPertinencia(double x1, double x2, double x3, double y1, double y2, double y3, double z1, double z2, double z3) {
	return	max(min(x1, x2, x3), min(y1, y2, y3), min(z1, z2, z3));	
}

double fraco(double refri, int tipo, double rum, double ge) {
	double rF = refriFraco(tipo, refri);
	double rumF = rumFraco(rum);
	double g = gelo(ge);
	double rumS = rumSuave(rum);
	double rS = refriSuave(tipo, refri);
	
	return calcGrauPertinencia(rF, rumF, g, rF, rumS, g, rS, rumF, g);	
}

double suave(double refri, int tipo, double rum, double ge) {
	double rFt = refriForte(tipo, refri);
	double rumF = rumFraco(rum);
	double g = gelo(ge);
	double rS = refriSuave(tipo, refri);
	double rumS = rumSuave(rum);
	double rF = refriFraco(tipo, refri);
	double rumFt = rumForte(rum);
	
	return calcGrauPertinencia(rFt, rumF, g, rS, rumS, g, rF, rumFt, g);
}

double forte(double refri, int tipo, double rum, double ge) {
	double rFt = refriForte(tipo, refri);
	double rumS = rumSuave(rum);
	double g = gelo(ge);
	double rumFt = rumForte(rum);
	double rS = refriSuave(tipo, refri);
	
	return calcGrauPertinencia(rFt, rumS, g, rFt, rumFt, g, rS, rumFt, g);
}	

double calcMedia(double x1, double x2, double x3) {
	return (x1+x2+x3)/3;
}
	
double paladar(double refri, int tipo, double rum, double ge, char *paladar) {	
	double f = fraco(refri, tipo, rum, ge);
	double s = suave(refri, tipo, rum, ge);
	double F = forte(refri, tipo, rum, ge);
	
	double rF = refriFraco(tipo, refri);
	double rS = refriSuave(tipo, refri);
	double rFt = refriForte(tipo, refri);
	double rumF = rumFraco(rum);
	double rumS = rumSuave(rum);
	double rumFt = rumForte(rum);
	double g = gelo(ge);

	double medf = calcMedia(min(rF, rumF, g), min(rF, rumS, g), min(rS, rumF, g));
	double meds = calcMedia(min(rFt, rumF, g), min(rS, rumS, g), min(rF, rumFt, g));  
	double medF = calcMedia(min(rFt, rumS, g), min(rFt, rumFt, g), min(rS, rumFt, g));
		
	double m = max(f, s, F);
	double mMed;
	
	if(m==0) {	
		strcpy(paladar, "NÃO É CUBA LIBRE");
	}
	else {
		if(f==m && s==m && F==m) {
		
			mMed = max(medf, meds, medF);
		
			if(medf==mMed && meds==mMed && medF==mMed) {
				strcpy(paladar, "FORTE"); //porque o FORTE é o mais caro de todos
			}
			else if(medf==mMed && meds==mMed) {
				strcpy(paladar, "SUAVE"); //SUAVE é mais caro que FRACO
			}
			else if(medf==mMed && medF==mMed) {
				strcpy(paladar, "FORTE"); //FORTE é mais caro que FRACO
			}
			else if(meds==mMed && medF==mMed) {
				strcpy(paladar, "FORTE"); //FORTE é mais caro que SUAVE
			}
			else if(medf==mMed) {
				strcpy(paladar, "FRACO");
			}
			else if(meds==mMed) {
				strcpy(paladar, "SUAVE");
			}
			else if(medF==mMed) {
				strcpy(paladar, "FORTE");
			}	
		}
		else if(f==m && s==m) {
			
			mMed = max(medf, meds, 0);
			
			if(medf==mMed && meds==mMed) {
				strcpy(paladar, "SUAVE"); //SUAVE é mais caro que FRACO
			}
			else if(medf==mMed) {
				strcpy(paladar, "FRACO");
			}
			else if(meds==mMed) {
				strcpy(paladar, "SUAVE");
			}	
		}
		else if(f==m && F==m) {
			
			mMed = max(medf, medF, 0);
			
			if(medf==mMed && medF==mMed) {
				strcpy(paladar, "FORTE"); //FORTE é mais caro que FRACO
			}
			else if(medf==mMed) {
				strcpy(paladar, "FRACO");
			}
			else if(medF==mMed) {
				strcpy(paladar, "FORTE");
			}
		}
		else if(s==m && F==m) {
			
			mMed = max(meds, medF, 0);
			
			if(meds==mMed && medF==mMed) {
				strcpy(paladar, "FORTE"); //FORTE é mais caro que SUAVE
			}
			else if(meds==mMed) {
				strcpy(paladar, "SUAVE");
			}
			else if(medF==mMed) {
				strcpy(paladar, "FORTE");
			}	
		}
		else if(f==m) {
			strcpy(paladar, "FRACO");
		}
		else if(s==m) {	
			strcpy(paladar, "SUAVE");			
		}
		else if(F==m) {	
			strcpy(paladar, "FORTE");
		}
	}
	
	return m;
}

int dentroDoLimite(double ml) {
	if(0<=ml && ml<=100)
		return 1;
	return 0;
}

int main() {
	setlocale(LC_ALL,"portuguese");
	int tipoRefri;
	double refri, rum, ge, gpEscolhido;
	char paladarEscolhido[20];
	char resp, nomeRefri[10];
	
	do {
		system("CLS");
		printf("CUBA LIVRE\n");
		printf("Digite 1 para Coca-Cola ou 2 para Pepsi-Cola em sua bebida: ");
		scanf("%d", &tipoRefri);
		
		if(tipoRefri == 1)
			strcpy(nomeRefri, "Coca-Cola");
		else
			strcpy(nomeRefri, "Pepsi");
		
		printf("\nQUANTIDADES DOS INGREDIENTES:\n");
		if(tipoRefri == 1)
			printf("- %s: 50ml a 60ml\n", nomeRefri);
		else
			printf("- %s: 60ml a 70ml\n", nomeRefri);
		printf("- Rum: 10ml a 30 ml\n");
		printf("- Gelo: 20ml\n\n");
		
		printf("Digite as quantidades em ml de %s, Rum e Gelo respectivamente, separadas por espaço.\n", nomeRefri);
		printf("(Caso hajam valores decimais, representar com ponto ao invés de vírgula):\n");
		scanf("%lf %lf %lf", &refri, &rum, &ge);
		
		while(dentroDoLimite(refri)==0 || dentroDoLimite(rum)==0 || dentroDoLimite(ge)==0) {
			printf("\n");
			printf("O usuário tem o direito de entrar apenas com quantidades de 0ml a 100ml.\n");
			if(dentroDoLimite(refri)==0) {
				printf("Digite novamente a quantidade em ml de %s: ", nomeRefri);
				scanf("%lf", &refri);
			}
			if(dentroDoLimite(rum)==0) {
				printf("Digite novamente a quantidade em ml de Rum: ");
				scanf("%lf", &rum);
			}
			if(dentroDoLimite(ge)==0) {
				printf("Digite novamente a quantidade em ml de Gelo: ");
				scanf("%lf", &ge);
			}
		}
		
		printf("\n");
		printf("- Grau de pertinência da bebidada para o paladar FRACO: %.3lf\n", fraco(refri, tipoRefri, rum, ge));
		printf("- Grau de pertinência da bebidada para o paladar SUAVE: %.3lf\n", suave(refri, tipoRefri, rum, ge));
		printf("- Grau de pertinência da bebidada para o paladar FORTE: %.3lf\n", forte(refri, tipoRefri, rum, ge));
		gpEscolhido = paladar(refri, tipoRefri, rum, ge, paladarEscolhido);
		printf("- Grau de pertinência final: %.3lf (%s)\n\n", gpEscolhido, paladarEscolhido);
		
		printf("PALADAR DO DRINK: %s\n", paladarEscolhido);	
		if(strcmp("FRACO", paladarEscolhido) == 0)
			printf("PREÇO: R$ 15.00\n");
		else if(strcmp("SUAVE", paladarEscolhido) == 0)
			printf("PREÇO: R$ 20.00\n");
		else if(strcmp("FORTE", paladarEscolhido) == 0)
			printf("PREÇO: R$ 25.00\n");
		
		if(gpEscolhido == 0) {
			printf("NÃO É UM DRINK CUBA LIBRE PORQUE:\n");
			if(refriFraco(tipoRefri, refri)==0 && refriSuave(tipoRefri, refri)==0 && refriForte(tipoRefri, refri)==0) {
				printf("- Foi colocada uma quantidade inadequada de %s\n", nomeRefri);
			}
			if(rumFraco(rum)==0 && rumSuave(rum)==0 && rumForte(rum)==0) {
				printf("- Foi colocada uma quantidade inadequada de Rum\n");
			}
			if(gelo(ge)==0) {
				printf("- Foi colocada uma quantidade inadequada de Gelo\n");
			}
		}
		
		printf("\nDeseja preparar outro Cuba Libre?(s/n): ");
		fflush(stdin);
		scanf("%c", &resp);
	}while(resp == 's');	
}
















