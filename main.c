#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Vendedor {
    char codvendedor[15];
    char nomevendedor[50];
    float valorvenda;
    int mes;
    int ano;
    int codVenda;
};
int x;
void criaraqruivo() {
        FILE*arquivox;
        arquivox=fopen("arquivo.txt", "wb");

        if (arquivox == NULL) {
            printf("Erro, não foi possivel criar o arquivo!");
        }
        fclose(arquivox);
}

struct Vendedor reg[];;

static int contador=0;

int incluirregistro(int x) {
    static int contador = 0;
    int i;
    int encontrado = 0;
    struct Vendedor regtemporario;

        FILE* arquivox;
        arquivox = fopen("arquivo.txt", "ab");

            if (arquivox == NULL) {
                printf("Não foi possível criar o arquivo!\n");
                return 0;
            }

            printf("Quantos registros deseja incluir? ");
            scanf("%i", &x);

            for (i = 0; i < x; i++) {
                printf("\nInsira o código do vendedor: ");
                scanf("%s",reg[x].codvendedor);
                printf("\nInsira o nome do vendedor: ");
                scanf("%s", reg[x].nomevendedor);

                rewind(arquivox);

                while (fread(&regtemporario, sizeof(struct Vendedor), 1, arquivox)) {
                    if (strcmp(regtemporario.codvendedor, reg[x].codvendedor) == 0) {
                        printf("\nErro: código de vendedor já existe com outro nome.\n");
                        encontrado = 1;
                        break;
                    }
                }
                if (encontrado=0) {
                    continue;
                }

                printf("\nInsira o valor da venda: ");
                scanf("%f", &reg[x].valorvenda);
                do {
                    printf("\nInsira um mês para a venda: ");
                    scanf("%i", &reg[x].mes);
                } while (reg[x].mes < 1 || reg[x].mes > 12);
                do {
                    printf("\nInsira o ano da venda (2000-2050): ");
                    scanf("%i", &reg[x].ano);
                } while (reg[x].ano <= 1999 || reg[x].ano >= 2051);

                contador++;



               reg[x].codVenda = contador;
               fwrite(&reg[x], sizeof(struct Vendedor), 1, arquivox);
            }

            fclose(arquivox);
            return 1;


            if (incluirregistro(1)) {
            printf("Incluiu registro com sucesso!\n");
            } else {
            printf("Erro ao incluir registro!\n");
            }
            return 0;

}





int excluirvendedor(const char* codigo) {

    FILE* arquivox;
    arquivox = fopen("arquivo.txt", "rb");

          if (arquivox == NULL) {
                printf("Erro ao executar a exclusão do vendedor!\n");
            return 0;
          }

          FILE* arquivoy;
          arquivoy = fopen("arquivo_temp.txt", "wb");

              if (arquivoy == NULL) {
                printf("Não foi possível criar o arquivo temporário para exclusão de vendedor!\n");
                fclose(arquivox);
                return 0;
              }

              while (fread(&reg, sizeof(struct Vendedor), 1, arquivox)) {
                if (strcmp(reg[x].codvendedor, codigo) != 0) {
                  fwrite(&reg[x], sizeof(struct Vendedor), 1, arquivoy);
                }
              }
              fclose(arquivox);
              fclose(arquivoy);
              remove("arquivo.txt");
              rename("arquivo_temp.txt", "arquivo.txt");

          return 1;
}
void alterarvenda(const char* codigo) {
        int alt = 0;
        char conferecodigo[15];
        float novovalor;
        int registro;
            FILE* arquivox;
            arquivox = fopen("arquivo.txt", "rb+");


            if (arquivox == NULL) {
                    printf("Erro na alteração de venda!\n");
                return;
            }
                        imprimeregistros();
                        printf("\nQual venda deseja alterar? ");
                        scanf("%i", &registro);
             while (fread(&reg, sizeof(struct Vendedor), 1, arquivox)) {
                    if (reg[x].codVenda == registro) {
                        printf("\nInsira o novo valor da venda: ");
                        scanf("%f", &novovalor);
                        reg[x].valorvenda = novovalor;
                        fseek(arquivox, -sizeof(struct Vendedor), SEEK_CUR);
                        fwrite(&reg, sizeof(struct Vendedor), 1, arquivox);
                        alt++;
                    break;
                }
            }





                        rewind(arquivox);
             while (fread(&reg, sizeof(struct Vendedor), 1, arquivox)) {
                    if (reg[x].codvendedor==codigo) {
                        reg[x].valorvenda = novovalor;
                        fseek(arquivox, -sizeof(struct Vendedor), SEEK_CUR);
                        fwrite(&reg, sizeof(struct Vendedor), 1, arquivox);
                        alt++;}}

            fclose(arquivox);
            if (alt > 0) {
                printf("Alterou %d venda(s) com sucesso!\n", alt);
            } else {
                printf("Erro ao alterar a venda! Digite uma venda valida.\n");
            }
}
void consultamaior() {
        float maiorV = 0.0;
        char nomeVend[50];
        int M = 0, A = 0;

              FILE* arquivox;
              arquivox = fopen("arquivo.txt", "rb");

              if (arquivox == NULL) {
                printf("Erro!\n");
                return;
              }

              while (fread(&reg, sizeof(struct Vendedor), 1, arquivox)) {
                if (reg[x].valorvenda > maiorV) {
                  maiorV = reg[x].valorvenda;
                  strcpy(nomeVend, reg[x].nomevendedor);
                   M= reg[x].mes;
                   A= reg[x].ano;
                }
              }
              fclose(arquivox);

              printf("A maior venda foi de: R$%.2f, \nRealizada pelo vendedor: %s \n na data: %d/%d\n", maiorV, nomeVend, M, A);
}
int ordenaregistros(const void *a, const void *b) {

    struct Vendedor *regx = (const struct Vendedor *) a;
    struct Vendedor *regy = (const struct Vendedor *) b;
                if (regx->ano < regy->ano) {
                    return -1;
                }
                if (regx->ano > regy->ano) {
                    return 1;
                }
                if (regx->mes < regy->mes) {
                    return -1;
                }
                if (regx->mes > regy->mes) {
                    return 1;
                }
                return 0;
}
void imprimeregistros() {
        int num = 0;
        int i;
        int numreg=0;
        struct Vendedor regT[1000];
              FILE* arquivox;
              arquivox= fopen("arquivo.txt", "rb");

              if (arquivox == NULL) {
                printf("\nErro,não foi possivel encontrar registros ao abrir o arquivo!\n");
                return;
              }
              while (fread(&regT[numreg], sizeof(struct Vendedor), 1, arquivox)) {
                numreg++;
                        }
                qsort(regT, numreg, sizeof(struct Vendedor), ordenaregistros);

            for (i= 0; i < numreg; i++) {
            printf("\n-------------------------------------\n");
            printf("Registro n:%i", regT[i].codVenda);
            printf("\nCódigo do vendedor: %s", regT[i].codvendedor);
            printf("\nNome do vendedor: %s", regT[i].nomevendedor);
            printf("\nValor da venda: %.2f", regT[i].valorvenda);
            printf("\nData: %i/%i", regT[i].mes, regT[i].ano);
            printf("\n-------------------------------------"); }

            fclose(arquivox);
}


float MaiorVendaPeriodo() {
              int mesInicio, mesFim, anoC;
              float maiorVenda = 0;
              char nomeVendedor[50];

              printf("Digite o mês de início: ");
              scanf("%d", &mesInicio);
              printf("Digite o mês de fim : ");
              scanf("%d", &mesFim);
              printf("Digite o ano: ");
              scanf("%d", &anoC);

              FILE* arquivox;
              arquivox = fopen("arquivo.txt", "rb");

              if (arquivox == NULL) {
                    printf("Erro, não foi possivel realizar a consulta!\n");
                return 0;
              }

              while (fread(&reg, sizeof(struct Vendedor), 1, arquivox)) {
                if (reg[x].ano == anoC && reg[x].mes >= mesInicio && reg[x].mes <= mesFim && reg[x].valorvenda > maiorVenda) {
                  maiorVenda = reg[x].valorvenda;
                  strcpy(nomeVendedor, reg[x].nomevendedor);
                }
              }

              fclose(arquivox);

              printf("\nA maior venda do periodo foi de R$ %.2f",maiorVenda);
}

float somaAno(int anoB){
   float somaA=0.0;
               FILE*arquivox;
               arquivox=fopen("arquivo.txt", "rb");
               if(arquivox==NULL){
                    printf("Erro ao realizar o somatório anual!\n");
                }
                while (fread(&reg, sizeof(struct Vendedor), 1, arquivox)){

                if( anoB== reg[x].ano){
                    somaA=somaA+reg[x].valorvenda;

                }  }
                printf("O valor das vendas anuais foi de: R$ %.2f",somaA);
        return somaA;
}
float somarVendas() {
        float soma =0;
            FILE* arquivox;
            arquivox = fopen("arquivo.txt", "rb");

            if (arquivox == NULL) {
                printf("Erro!\n");
                return 0;
            }


            while (fread(&reg, sizeof(struct Vendedor), 1, arquivox) && !feof(arquivox)) {
                soma = soma+reg[x].valorvenda;
            }


            printf("\nO valor total de todas as vendas é de: R$ %.2f",soma);
            return soma;
            fclose(arquivox);
}



void main(){
        setlocale(LC_ALL, "Portuguese");
    int opc,a;
    char codA[15];

            printf("Seja bem-vindo!Escolha uma das opções a seguir:");
            printf("\n 0: Criar novo arquivo :");
            printf("\n 1: Adicionar registro: ");
            printf("\n 2: Excluir vendedor: ");
            printf("\n 3: Alterar o valor das venda no arquivo:");
            printf("\n 4: Consultar o maior valor de venda obtido:");
            printf("\n 5: Consultar maior valor de venda, por período:");
            printf("\n 6: Soma dos valores de venda:");
            printf("\n 7: Obter soma do valor anual de venda:");
            printf("\n 8: Imprimir os registros na saida padrao: ");
            printf("\n 9: Excluir arquivo:");
            printf("\n10: Finalizar; \n\n ");

    while(opc != 10){

            printf("\nEscolha a opção desejada: ");
            scanf("%d", &opc);

        switch(opc){
            case 0:
                criaraqruivo(opc);
                printf("\nCriou arquivo!");
            continue;

            case 1:
                incluirregistro(opc);
                printf("Registro incluido com sucesso!");
            continue;

            case 2:

                printf("Insira o código do vendedor realizar a exclusão:  ");
                scanf("%s",codA);
                excluirvendedor(codA);
                int resultado = excluirvendedor(codA);
                if (resultado == 1) {
                  printf("Opção executada com sucesso,verifique se o vendedor foi excluido corretamente!\n");
                } else {
                  printf("Erro!\n");
                }

            continue;

            case 3:
                alterarvenda(codA);
                break;

                continue;

            case 4:
                consultamaior();
            continue;

            case 5:
                MaiorVendaPeriodo();

            continue;

            case 6:
                somarVendas();
            continue;

            case 7:
                printf("\nDigite o ano que deseja obter as somas das vendas:\n");
                scanf("%i",&a);
                somaAno(a);
            continue;

            case 8:
                imprimeregistros(opc);
                break;
            continue;

            case 9:
                remove("arquivo.txt");
                if (remove("arquivo.txt")){
                    printf("Arquivo removido com sucesso!");
                }
                break;

            continue;
            case 10 :
                system("cls");
                break;
            default:
                printf("Opção errada, tente novamente!");
                printf("\nEscolha uma opção: ");
                scanf("%i",&opc);
        }
    }
    printf("Finalizou o programa!");
    system("pause");
}
