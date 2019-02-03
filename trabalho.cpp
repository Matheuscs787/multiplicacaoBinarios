#include<stdio.h>
#include<stdlib.h>

//funções usadas no programa
int transformar();
int multiplicacao();
int desalok();
///////////////////

//variaveis
int multiplicador, multiplicando;  //entradas
int tam=15, carry=0;
int cont = tam;
int sinX = 0, sinY = 0;  //variaveis para sinal do numero de transformação
bool sinal;  //usado para mostrar o sinal
int multiplicadorBinario[15], multiplicandoBinario[15];  //vetores para a entrada transformada em binario
int VetorA[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
/////////////////////////

int main(){
	transformar();  //chamo minha função que transforma os números de entrada em binario e depois a minha função de multiplicação
	multiplicacao();
	printf("\t\nResultado\n\n");
	
	if(sinal==true){//atribuindo o sinal
		VetorA[0]=1;
	}
    for (int relpers = 0; relpers < 15; relpers++){ //for pra printar os valores do primeiro vetor
    	printf("%d", VetorA[relpers]);
    }
    for (int relpers = 0; relpers < 15; relpers++){ //for pra printar os valores do segundo vetor
        printf("%d", multiplicadorBinario[relpers]);
   	}
   	//resultado printado
	printf("\n");
	system("pause");
}

int transformar(){  //função feita para transformar os numeros em binario

	printf("Digite o multiplicando: ");
	scanf("%d",&multiplicando);
	
	printf("Digite o multiplicador: ");
	scanf("%d",&multiplicador);
	
	if(multiplicador == 0 || multiplicando == 0){  //condição para verificar se um dos numeros de entrada é 0
		printf("\nUm dos numeros eh 0, portanto a resposta eh 0 \n");
		return 1;
	}
	else if(multiplicador > 32767 || multiplicando > 32767){ //se a entrada for maior que o 32767(maior numero de 15 bits) ele encerra o programa
		printf("\nUm dos valores ultrapassa o limite de tamanho\n");
		return 1;
	}
	else if(multiplicador < 0 && multiplicando < 0){  //condição para atribuir os sinais para mostrar o numero transformado
		sinY = 1;
		sinX = 1;
	}
	else if(multiplicador < 0 && multiplicando>0){  //condição para verificar se um numero é negativo
		sinal = true;
		sinY = 1;
	}
	else if(multiplicador >0 && multiplicando < 0){  //condição para verificar se um numero é negativo
		sinal = true;
		sinX = 1;
	}
	system("cls");
		//transformando os valores em binario
	for(int i=14;i>=0;i--){
		if(multiplicando%2==0){
			multiplicandoBinario[i]=0;
			multiplicando = multiplicando/2;
		}
		else{
			multiplicandoBinario[i]=1;
			multiplicando=multiplicando/2;
		}
	}
	for(int h=14;h>=0;h--){
		if(multiplicador%2==0){
			multiplicadorBinario[h]=0;
			multiplicador=multiplicador/2;
		}
		else{
			multiplicadorBinario[h]=1;
			multiplicador=multiplicador/2;
		}
	}
	///////printo os dois vetores com os valores de entrada transformados
	printf("Multiplicando transformado em binario: ");
	printf("%d", sinX);
	for (int aux = 0; aux < 15; aux++) {
        printf("%d", multiplicandoBinario[aux]);
    }
    printf("\nMultiplicador transformado em binario: ");
    printf("%d", sinY);
	for (int aux = 0; aux < 15; aux++) {
        printf("%d", multiplicadorBinario[aux]);
    }
	printf("\n");
}

int multiplicacao(){  //funcao que realiza a multiplicacao de fato
	int a = VetorA[14];
	
	while(cont > 0){
		if(multiplicadorBinario[14] == 0){//verifico se q0 é igual a 0, se ele for, chamo minha funcao para deslocar
			desalok();
		}
		else{ //se o q0 for 1, eu faco a + m e depois desloco
			for(int relper = 15; relper > 0; relper--){
				if(VetorA[relper] == 0 && multiplicandoBinario[relper] == 0 && carry == 0){
					VetorA[relper] = 0;
					carry = 0;
				}
				else if(VetorA[relper] == 0 && multiplicandoBinario[relper] == 0 && carry == 1){
					VetorA[relper] = 1;
					carry = 0;
				}
				else if(VetorA[relper] == 0 && multiplicandoBinario[relper] == 1 && carry == 0){
					VetorA[relper] = 1;
					carry = 0;
				}
				else if(VetorA[relper] == 0 && multiplicandoBinario[relper] == 1 && carry == 1){
					VetorA[relper] = 0;
					carry = 1;
				}
				else if(VetorA[relper] == 1 && multiplicandoBinario[relper] == 0 && carry == 0){
					VetorA[relper] = 1;
					carry = 0;
				}
				else if(VetorA[relper] == 1 && multiplicandoBinario[relper] == 0 && carry == 1){
					VetorA[relper] = 0;
					carry = 1;
				}
				else if(VetorA[relper] == 1 && multiplicandoBinario[relper] == 1 && carry == 0){
					VetorA[relper] = 0;
					carry = 1;
				}
				else if(VetorA[relper] == 1 && multiplicandoBinario[relper] == 1 && carry == 1){
					VetorA[relper] = 1;
					carry = 1;
				}
		    }
		    desalok();//depois da soma, chama a função que deslocar
		}
		cont--;	
	}	
}

int desalok(){ //função para deslocar
	
	int a = VetorA[14];
		    
	for(int relpers = 14;relpers >=0; relpers--){
	   	VetorA[relpers] = VetorA[relpers-1];
	}
			
	VetorA[0]=carry;
			
	for(int relpers = 14;relpers >=0; relpers--){
	   	multiplicadorBinario[relpers] = multiplicadorBinario[relpers-1];
	}
	multiplicadorBinario[0] = a;
}
