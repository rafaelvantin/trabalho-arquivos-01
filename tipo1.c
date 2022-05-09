#include <stdio.h>
#include <stdlib.h>

#include "tipo1.h"
#include "aux_functions.h"

struct cabecalho1
{
    char status;
    int topo;
    char descricao[40];
    char desC1[22];
    char desC2[19];
    char desC3[24];
    char desC4[8];
    char codC5;
    char desC5[16];
    char codC6;
    char desC6[18];
    char codC7;
    char desC7[19];
    int proxRRN;
    int nroRegRem;
};

struct tipo1
{
    int id;
    int ano;
    int qtt;
    char sigla[2];
    char *cidade;
    char *marca;
    char *modelo;
    char removido;
    int prox;
    int tamCidade;
    int tamMarca;
    int tamModelo;
};

cabecalho1_t define_cabecalho()
{
    cabecalho1_t novo;
    
    novo.status = '1';
    novo.topo = -1;
    strcpy(novo.descricao, "LISTAGEM DA FROTA DOS VEÍCULOS NO BRASIL");
    strcpy(novo.desC1, "CODIGO IDENTIFICADOR: ");
    strcpy(novo.desC2, "ANO DE FABRICACAO: ");
    strcpy(novo.desC3, "QUANTIDADE DE VEICULOS: ");
    strcpy(novo.desC4, "ESTADO: ");
    novo.codC5 = '0';
    strcpy(novo.desC5, "NOME DA CIDADE: ");
    novo.codC6 = '1';
    strcpy(novo.desC6, "MARCA DO VEICULO: ");
    novo.codC7 = '2';
    strcpy(novo.desC7, "MODELO DO VEICULO: ");
    novo.proxRRN = 0;
    novo.nroRegRem = 0;
    
    return novo;
}

void inicializa_cabecalho(FILE *fp)
{
    cabecalho1_t cabec = define_cabecalho();
    
    fwrite(&cabec.status, sizeof(char), 1, fp);
    fwrite(&cabec.topo, sizeof(int), 1, fp);
    fwrite(cabec.descricao, sizeof(char), sizeof(cabec.descricao), fp);
    fwrite(cabec.desC1, sizeof(char), sizeof(cabec.desC1), fp);
    fwrite(cabec.desC2, sizeof(char), sizeof(cabec.desC2), fp);
    fwrite(cabec.desC3, sizeof(char), sizeof(cabec.desC3), fp);
    fwrite(cabec.desC4, sizeof(char), sizeof(cabec.desC4), fp);
    fwrite(&cabec.codC5, sizeof(char), 1, fp);
    fwrite(cabec.desC5, sizeof(char), sizeof(cabec.desC5), fp);
    fwrite(&cabec.codC6, sizeof(char), 1, fp);
    fwrite(cabec.desC6, sizeof(char), sizeof(cabec.desC6), fp);
    fwrite(&cabec.codC7, sizeof(char), 1, fp);
    fwrite(cabec.desC7, sizeof(char), sizeof(cabec.desC7), fp);
    fwrite(&cabec.proxRRN, sizeof(int), 1, fp);
    fwrite(&cabec.nroRegRem, sizeof(int), 1, fp);
}

void atualiza_status(FILE *fp, char status)
{
    //antigo = ftell()
    fseek(fp, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, fp);
    //fseek antigo  
}

void atualiza_topo(FILE *fp, int topo)
{
    fseek(fp, 1, SEEK_SET);
    fwrite(&topo, sizeof(int), 1, fp);
}

int get_proxRRN(FILE *fp)
{
    fseek(fp, 174, SEEK_SET);
    
    int proxRRN;
    fread(&proxRRN, sizeof(int), 1, fp);
    return proxRRN;
}

void atualiza_proxRRN(FILE *fp, int proxRRN)
{
    fseek(fp, 174, SEEK_SET);
    fwrite(&proxRRN, sizeof(int), 1, fp);
}

int get_nroRegRem(FILE *fp)
{
    fseek(fp, 178, SEEK_SET);

    int nroRegRem;
    fread(&nroRegRem, sizeof(int), 1, fp);
    return nroRegRem;
}

void atualiza_nroRegRem(FILE *fp, int nroRegRem)
{
    fseek(fp, 178, SEEK_SET);
    fwrite(&nroRegRem, sizeof(int), 1, fp);
}

void grava_registro(FILE *fp, tipo1_t dados)
{
    char codC5 = 0, codC6 = 1, codC7 = 2;

    fwrite(&dados.removido, sizeof(char), 1, fp);
    fwrite(&dados.prox, sizeof(int), 1, fp);
    
    fwrite(&dados.id, sizeof(int), 1, fp);
    fwrite(&dados.qtt, sizeof(int), 1, fp);
    fwrite(dados.sigla, sizeof(char), sizeof(dados.sigla), fp);
    
    fwrite(&dados.tamCidade, sizeof(int), 1, fp);
    fwrite(&codC5, sizeof(char), 1, fp);
    fwrite(dados.cidade, sizeof(char), sizeof(dados.cidade), fp);
    
    fwrite(&dados.tamMarca, sizeof(int), 1, fp);
    fwrite(&codC6, sizeof(char), 1, fp);
    fwrite(dados.marca, sizeof(char), sizeof(dados.marca), fp);
    
    fwrite(&dados.tamModelo, sizeof(int), 1, fp);
    fwrite(&codC7, sizeof(char), 1, fp);
    fwrite(dados.modelo, sizeof(char), sizeof(dados.modelo), fp);
}

tipo1_t le_registro_csv(FILE *fp)
{
    tipo1_t novo;
    char *aux;

    aux = read_till_delimitor();
    novo.id = atoi(aux);
    free(aux);

    aux = read_till_delimitor();
    novo.ano = atoi(aux);
    free(aux);

    aux = read_till_delimitor();
    strcpy(novo.cidade, aux);
    novo.tamCidade = sizeof(aux);
    free(aux);

    aux = read_till_delimitor();
    novo.qtt = atoi(aux);
    free(aux);

    aux = read_till_delimitor();
    strcpy(novo.sigla, aux);
    free(aux);


    aux = read_till_delimitor();
    strcpy(novo.marca, aux);
    novo.tamMarca = sizeof(aux);
    free(aux);
    
    aux = read_till_delimitor();
    strcpy(novo.modelo, aux);
    novo.tamModelo = sizeof(aux);
    free(aux);
}