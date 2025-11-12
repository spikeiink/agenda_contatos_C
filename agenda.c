#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct agenda
{
    char nome[50];
    char telefone[20];
    char email[50];
};

void adicionarContato()
{
    struct agenda agenda;

    FILE *arquivo = fopen("contatos-salvos.txt", "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("=== Adicionar Novo contato ===\n");

    printf("Nome: ");
    fgets(agenda.nome, 50, stdin);
    agenda.nome[strcspn(agenda.nome, "\n")] = '\0';

    printf("Telefone: ");
    fgets(agenda.telefone, 20, stdin);
    agenda.telefone[strcspn(agenda.telefone, "\n")] = '\0';

    printf("E-mail: ");
    fgets(agenda.email, 50, stdin);
    agenda.email[strcspn(agenda.email, "\n")] = '\0';

    fprintf(arquivo, "%s, %s, %s\n", agenda.nome, agenda.telefone, agenda.email);

    fclose(arquivo);

    printf("Contato salvo com sucesso\n");
}

void alterarContato()
{
    FILE *arquivo, *temp;

    char linha[200];
    char search[50];
    int encontrado = 0;

    struct agenda agenda;

    arquivo = fopen("contatos-salvos.txt", "r");
    temp = fopen("temp.txt", "w");

    if (arquivo == NULL && temp == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    printf("== Digite o nome do contato que deseja alterar: ==\n");
    fgets(search, 50, stdin);
    search[strcspn(search, "\n")] = '\0';

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, search) != NULL)
        {
            encontrado = 1;
            printf("\n=== Contato encontrado ===\n");
            printf("Digite o novo nome: ");
            fgets(agenda.nome, 50, stdin);
            agenda.nome[strcspn(agenda.nome, "\n")] = '\0';

            printf("Digite o novo Telefone: ");
            fgets(agenda.telefone, 20, stdin);
            agenda.telefone[strcspn(agenda.telefone, "\n")] = '\0';

            printf("Digite o novo E-mail: ");
            fgets(agenda.email, 50, stdin);
            agenda.email[strcspn(agenda.email, "\n")] = '\0';

            fprintf(temp, "%s, %s, %s\n", agenda.nome, agenda.telefone, agenda.email);
        }
        else
        {
            fputs(linha, temp);
        }
    }

    fclose(temp);
    fclose(arquivo);

    remove("contatos-salvos.txt");
    rename("temp.txt", "contatos-salvos.txt");

    if (encontrado)
    {
        printf("Contato alterado com sucesso!\n");
        return;
    }

    printf("Contato não encontrado!\n");
}

void removerContato()
{
    FILE *arquivo, *temp;

    char linha[200];
    char search[50];
    int encontrado = 0;

    struct agenda agenda;

    arquivo = fopen("contatos-salvos.txt", "r");
    temp = fopen("temp.txt", "w");

    if (arquivo == NULL && temp == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    printf("== Digite o nome do contato que deseja remover: ==\n");
    fgets(search, 50, stdin);
    search[strcspn(search, "\n")] = '\0';

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, search) == NULL)
        {
            fputs(linha, temp);
        }
        else
        {
            encontrado = 1;
        }
    }

    fclose(temp);
    fclose(arquivo);

    remove("contatos-salvos.txt");
    rename("temp.txt", "contatos-salvos.txt");

    if (encontrado)
    {
        printf("Contato deletado com sucesso!\n");
        return;
    }

    printf("Contato não encontrado!\n");
}

void listarContatos()
{
    char linha[200];

    FILE *arquivo = fopen("contatos-salvos.txt", "r");

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (linha)
        {
            printf("\n%s\n", linha);
        }
    }

    return;
}

void buscarContatos()
{
    char linha[200];
    char search[50];
    int encontrado = 0;

    FILE *arquivo = fopen("contatos-salvos.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");

        return;
    }

    printf("== Pesquisar contato: ==\n");
    fgets(search, 50, stdin);
    search[strcspn(search, "\n")] = '\0';

    printf("\n== Resultado da busca ==\n");

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, search))
        {
            printf("\n%s", linha);
            encontrado = 1;
        }
    }

    printf("\n ================= \n");

    if (!encontrado)
    {
        printf("Nenhum resultado encontrado.\n");
    }

    fclose(arquivo);
    return;
}

int main()
{
    int opcao;

    do
    {
        printf("=== AGENDA DE CONTATOS ===\n");
        printf("1. Buscar contatos.\n");
        printf("2. Listar contatos.\n");
        printf("3. Adicionar contato.\n");
        printf("4. Alterar contato\n");
        printf("5. Excluir Contato\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            buscarContatos();
            break;
        case 2:
            listarContatos();
            break;
        case 3:
            adicionarContato();
            break;
        case 4:
            alterarContato();
            break;
        case 5:
            removerContato();
            break;

        default:
            break;
        }
    } while (opcao != 0);

    return 0;
}
