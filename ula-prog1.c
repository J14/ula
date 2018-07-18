#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define TAM 8

/*--------PROGRAMA QUE SIMULA OPERACOES DE UMA ULA (UNIDADE LOGICA E ARITMETICA)------
Operacoes:
- porta AND;
- porta OR;
- porta SOMA e SUBTRACAO;
- porta slt;
- porta NOR;
 Sao recebidas apenas duas entradas em DECIMAL, e entao convetidas para seu res-
pectivo valor em BINARIO. A saida eh o resultado da operacao em binario escolhida
pelo usuario.
REGRAS OVERFLOW:
ADICAO
Na adicao, ocorre overflow se dados dois operandos, ambos positivos ou ambos negativos,
produzirem um resultado de sinal oposto
SUBTRACAO
Ao subtrair um numero negativo de um positivo o resultado for negativo;
Ao subtrair um numero positivo de um numero negativo o resultado
for positivo
AUTORES:
- Joao Victor Oliveira
- Karoene da Silva Mendonca
*/

/* mostra o vetor no console */
void mostrarBinario(int vetor[]) {
	int i;
	for(i = TAM - 1; i >= 0 ; i--) {
		printf("%d", vetor[i]);
	}
	printf("\n");
}


/* preenche o vetor com zeros */
void zeradorVetor(int vetor[]) {
	int i;
	for(i = 0; i < TAM; i++) {
		vetor[i] = 0;
	}
}


/* complemento de 1 */
void inversorBit(int bin[]) {
	int i;
	for(i = 0; i < TAM; i++) {
		if (bin[i] == 0) {
			bin[i] = 1;
		} else {
			bin[i] = 0;
		}
	}
}


/* x elevado a y */
int potencia(int x, int y) {
	if (y == 0) return 1;

	else return x * potencia(x, y - 1);

}


/* binario para decimal */
int binTodec (int bin[]){
	int num = 0;
	int i = 0, y = 0;
	while (i < TAM){
		if (bin[i] == 1){
			num += potencia(2 , y);
		}
		i++;
		y++;
	}

	return num;
}


/*
 * converte um numero inteiro positivo para binario
 *
 * unsigned int num -> sem sinal
 * int num -> com sinal
 */
void decimalBinario(int num, int bin[]) {
	zeradorVetor(bin);
	int i = 0;
	while(num > 0) {
		bin[i++] = num % 2;
		num /= 2;
	}
}

void somador(int bin1[], int bin2[], int out[]) {
	int carry = 0;
	int i;
	for (i = 0; i < TAM; i++) {
		if (carry == 0) {
			if (bin1[i] == 0 && bin2[i] == 0) {
				out[i] = 0;
				carry = 0;
			} else if (bin1[i] == 0 && bin2[i] == 1) {
				out[i] = 1;
				carry = 0;
			} else if (bin1[i] == 1 && bin2[i] == 0) {
				out[i] = 1;
				carry = 0;
			} else if (bin1[i] == 1 && bin2[i] == 1) {
				out[i] = 0;
				carry = 1;
			}
		} else if (carry == 1) {
			if (bin1[i] == 0 && bin2[i] == 0) {
				out[i] = 1;
				carry = 0;
			} else if (bin1[i] == 0 && bin2[i] == 1) {
				out[i] = 0;
				carry = 1;
			} else if (bin1[i] == 1 && bin2[i] == 0) {
				out[i] = 0;
				carry = 1;
			} else if (bin1[i] == 1 && bin2[i] == 1) {
				out[i] = 1;
				carry = 1;
			}
		}
	}
}

int overflow_soma(int bin1[], int bin2[], int out[]){
    int overflow;
    if((bin1[TAM -1] == bin2[TAM -1]) && (bin1[TAM -1] != out[TAM -1])) {
         overflow = 1;
    }else{
         overflow = 0; 
    }
    return overflow;
}

void complementoDe2(int bin[]) {
	inversorBit(bin);
	int aux[TAM];
	zeradorVetor(aux);
	aux[0] = 1;
	somador(bin, aux, bin);
}


/*
 *
 * a subtracao de dois binarios usando a soma
 * de dois binarios, que se faz somando o primeiro binario
 * com o inverso do segundo binario(complemento de 2)
 *
 */

void subtrador(int bin1[], int bin2[], int out[]) {
	complementoDe2(bin2);

	somador(bin1, bin2, out);
}

int overflow_sub(int num1, int num2, int out[]){
    int overflow;
    if((num1 >= 0) && (num2 < 0) && (out[TAM -1] == 1) ){
        overflow = 1;
    }else{
         overflow = 0; 
    }
    return overflow;
}

/*
 * conversao de um inteiro negativo para binario
 *
 * passamos de negativo para positivo para convertermos em binario
 * para assim, com o complemento de 2, termos o binario negativo
 *
 *
 * caso especial : o numero -2147483648 nao existe seu correspondente
 * positivo, montamos o binario "manualmente"
 */

void decimalNegativoBinario(int num, int bin[]) {
	if (num > -2147483648) {
		num = -(num);
		decimalBinario(num, bin);
		complementoDe2(bin);
	} else {
		zeradorVetor(bin);
		bin[31] = 1;
	}
}

void andOpera(int bin1[], int bin2[], int out[]) {
	int i;
	for (i = 0; i < TAM; i++) {
			if (bin1[i] == 0 || bin2[i] == 0) {
				out[i] = 0;
			}
			 else  {
				out[i] = 1;
            }
	}
}

void orOpera(int bin1[], int bin2[], int out[]) {
	int i;
	for (i = 0; i < TAM; i++) {
			if (bin1[i] == 1 || bin2[i] == 1) {
				out[i] = 1;
			}
			 else  {
				out[i] = 0;
            }
	}
}


/*
 * rs - rt < 0 -> rs < rt -> 1
 * -> 0
 */
void stl_opera(int bin1[], int bin2[], int out[]) {
	int result[TAM];
    zeradorVetor(out);
	zeradorVetor(result);
    subtrador(bin1, bin2, result);
    if (result[TAM - 1] == 1)
        out[0] = 1;
}


void nor_opera(int bin1[], int bin2[], int out[]){
	zeradorVetor(out);
	inversorBit(bin1);
	inversorBit(bin2);
	andOpera(bin1, bin2, out);
	
}

int zero_out(int out[]){
	int i;
	for(i = 0; i < TAM; i++){
		if (out[i] == 1)
			return 0;	
	}
	return 1;
}



int main(void) {
	int bin1[TAM], bin2[TAM], out[TAM];
	int num1, num2, op;
	int n, aux, over, ov, overf;
	printf("----------- PROGRAMA QUE SIMULA OPERACOES DE UMA ULA -------------\n\n\n\n" );
	for(; ;){
	   	printf("Informe o primeiro numero inteiro: ");
		scanf("%d", &num1);
		printf("Informe o segundo numero inteiro: ");
		scanf("%d", &num2);
		if (num1 < 0){
		   	decimalNegativoBinario(num1, bin1);
		} else {
		   	decimalBinario(num1, bin1);
		}

		if (num2 < 0){
		  	    decimalNegativoBinario(num2, bin2);
		} else{
		   	   	decimalBinario(num2, bin2);
		}
	   	printf("%d = ", num1);
		mostrarBinario(bin1);
	   	printf("%d = ", num2);
		mostrarBinario(bin2);

		printf("\n[0] - AND\n");
		printf("[1] - OR\n");
		printf("[2] - SOMA\n");
		printf("[6] - SUBTRACAO\n\n");
		printf("[7] - SLT\n\n");
		printf("[12] - NOR\n\n");
		printf("digite a operacao desejada: ");
		scanf("%d" ,&op);
		switch (op){
			   	case 0:
	   				andOpera(bin1, bin2, out);
	 				printf("\n AND  \n");
	 			  	mostrarBinario(out);

	 				break;
				case 1:
			  	    orOpera(bin1, bin2, out);
	 				printf("\n OR \n");
					mostrarBinario(out);

	   	   			break;
				case 2:
	  	   			somador(bin1, bin2, out);
	 				printf("\nResultado da SOMA em BINARIO\n");
	 			    mostrarBinario(out);
	 			    printf("Resultado da SOMA em DECIMAL: %d", binTodec(out));                                
                    printf("\nbin1 %d", bin1[TAM -1]);
                    printf("\nbin2 %d", bin2[TAM -1]);
                    printf("\nout %d\n", out[TAM -1]);
                    over = overflow_soma(bin1, bin2, out);
                    printf("\nOcorreu overflow? (1 = S, 0 = N) = %d\n", over);
	 				break;
				case 6:
                                   
					subtrador(bin1, bin2, out);
					printf("\nResultado da SUBTRACAO em BINARIO: \n");
					mostrarBinario(out);
					printf("\nResultado da SUBTRACAO em DECIMAL: \n%d", binTodec(out));
                    overf = overflow_sub(num1, num2, out);                   
                    printf("\nOcorreu overflow? (1 = S, 0 = N) = %d\n", overf);
					break;
				case 7:
					printf("\nResultado do STL:\n");
					stl_opera(bin1, bin2, out);
					mostrarBinario(out);
					break;
				case 12:
					printf("\nResultado do NOR: \n");
					nor_opera(bin1, bin2, out);
					mostrarBinario(out);
					break;
				default: printf("opcao invalida");
		}
		aux = zero_out(out);
		printf("\nSaida Zero da ULA= %d", aux);
	printf("\n\n\nDeseja continuar a execucao do programa? \n Informe [1] pra continuar e qualquer tecla para sair\n");
	scanf("%d", &n);
	if (n == 1){
		printf("\n");
		continue;
	}else break;

}

	return 0;
}