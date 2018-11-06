#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>

// Enumeração
enum{facil = 200, medio = 180, dificil = 150, God = 50, SAIR = 27, Jogando = 1};
enum{pontosf = 90, pontosm = 70, pontosd = 50, pontosg = 30};  // Pontos necessario para ganhar em cada dificuldade
enum{vertical_e = 23, vertical_d = 23, horizontal_s = 73, horizontal_i = 74}; // Tamanho das bordas

// Prototipos das funções
void instrucoes_do_jogo(void);
void Game_over(int pontos, int nivel);
void gotoxy(int x, int y);
void CriarBorda(void);
void Carregando(void);
int Menu(int *velo);
void venceu(void);

// Usado para mudar a cor das coisas
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int main(int argc, char* argv[]){
    srand(time(NULL)); // Usado para gerar valores aleatorios
    const int VELO_MAX = 40; // Quanto menor o valor, maior a velocidade
    int x, d, tamanho, mx, my, velo;
    int velo2, opcao, pontos, nivel;
    int auxpontos;
    char tecla, dificuldade[10];

    while(Jogando){

        // Verifica se a opcao escolhida foi sair
        if(Menu(&velo) == 2)break;
        system("cls");

        // Tela "carregando jogo, aguarde"
        //Carregando();

        // Função pra criar borda
        CriarBorda();

        // Salvando a dificuldade escolhida como string
        if(velo == facil){
            strcpy(dificuldade, "Facil");
            auxpontos = pontosf;
        }else if(velo == medio){
            strcpy(dificuldade, "Medio");
            auxpontos = pontosm;
        }else if(velo == dificil){
            strcpy(dificuldade, "Dificil");
            auxpontos = pontosd;
        }else if(velo ==  God){
            strcpy(dificuldade, "God");
            auxpontos = pontosg;
        }

        // Coordenadas x,y geradas aleatorio para aparecer a comida
        mx = (rand()% 71) + 1;
        my = (rand()% 20) + 1;

        // Iniciando variaveis
        tecla = ' ';
        tamanho = 1;
        pontos = 0;
        nivel = 1;
        velo2 = 1;
        int cy[300] = {1, 2};
        int cx[300] = {7, 7};
        d = 2; // Começa andando para a direita

        SetConsoleTextAttribute(hConsole, 5); // Usado pra mudar a cor das letras
        printf("\n ------------------------------ SNAKE GAME -------------------------------\n");
        SetConsoleTextAttribute(hConsole, 7);

        while(tecla != SAIR){ // SAIR = 27 = ESC

            // Função "kbhit()" retorna 0 se o usuário não está precionando nenhuma tecla.
            // Caso contrário, retorna um valor diferente de 0.
            while(tecla != SAIR && !(tecla = kbhit())){
                // Faz a cobra se mover
                for(x = tamanho; x > 0; x--){
                    cx[x] = cx[x - 1];
                    cy[x] = cy[x - 1];
                }

                if(d == 0)cx[0]--; // Move para a esquerda no eixo X
                if(d == 1)cy[0]--; // Move para cima no eixo Y
                if(d == 2)cx[0]++; // Move para a direita no eixo X
                if(d == 3)cy[0]++; // Move para baixo no eixo Y

                gotoxy(cx[tamanho], cy[tamanho]);
                printf(" "); // Limpa onde a cobra já passou

                if(mx == cx[0] && my == cy[0]){
                    printf("\a"); // Som ao comer
                    tamanho++;  // tamanho da cobra
                    pontos++;
                    mx = (rand()% 71) + 1;
                    my = (rand()% 20) + 1;
                    if(velo > VELO_MAX){
                        velo -= 5;
                        velo2 += 1;
                    }
                    if(pontos % 5 == 0){
                        nivel++;
                    }
                }
                // Verifica se ganhou
                if(strcmp(dificuldade,"Facil") == 0 && pontos == pontosf){
                    tecla = SAIR;
                    venceu();
                }else if(strcmp(dificuldade,"Medio") == 0 && pontos == pontosm){
                    tecla = SAIR;
                    venceu();
                }else if(strcmp(dificuldade,"Dificil") == 0 && pontos == pontosd){
                    tecla = SAIR;
                    venceu();
                }else if(strcmp(dificuldade,"God") == 0 && pontos == pontosg){
                    tecla = SAIR;
                    venceu();
                }

                gotoxy(cx[0],cy[0]);
                printf("%c", 22);   // Cursor que anda pela tela (cobrinha)

                gotoxy(mx, my);    // Posição do comida que vai aparecer na tela (aleatorio)
                SetConsoleTextAttribute(hConsole, 12);
                printf("%c", 1);   // Comida que aparece pra cobra comer
                SetConsoleTextAttribute(hConsole, 7);

                // Informações do jogo pontos, nivel e velocidade atual etc.
                gotoxy(55, 25);
                printf("\n Desenvolvido por: \n");
                printf(" Marcelo Lima e Luiz Eduardo\n");
                gotoxy(horizontal_s + 5, 12);
                SetConsoleTextAttribute(hConsole, 11);
                printf("Consiga %d pontos para vencer o jogo!", auxpontos);
                SetConsoleTextAttribute(hConsole, 7);
                gotoxy(horizontal_s + 5, 9);
                printf("Pontos: %d", pontos);
                gotoxy(horizontal_s + 5, 7);
                printf("Dificuldade: %s",dificuldade);
                gotoxy(horizontal_s + 5, 5);
                printf("Nivel: %d", nivel);
                gotoxy(horizontal_s + 5, 2);
                printf("Velocidade: %d", velo2);
                if(velo <= VELO_MAX){
                    gotoxy(horizontal_s + 5, 3);
                    SetConsoleTextAttribute(hConsole, 12);
                    printf("(Velocidade maxima atingida)");
                    SetConsoleTextAttribute(hConsole, 7);
                }
                gotoxy(117, 29);

                // Velociadade da cobra
                Sleep(velo);

                // Verifica se a cobra bateu nela mesmo
                for(x = 1; x < tamanho; x++){
                    if(cx[0] == cx[x] && cy[0] == cy[x]){
                       tecla = SAIR;
                       Game_over(pontos, nivel);
                       break;
                    }
                }
                // Verifica se a cobra bateu na borda
                if(cy[0] == 0 || cy[0] == vertical_e || cx[0] == 0 || cx[0] == horizontal_s){
                    Game_over(pontos, nivel);
                    tecla = SAIR;
                }

              } // Fim do while secundario

            if(tecla != SAIR)tecla = getch();
            tecla = toupper(tecla); // Transforma tecla digitada em maiusculo
            if(tecla == 'A' || tecla == 'K')d = 0; // pra esquerda
            if(tecla == 'W' || tecla == 'H')d = 1; // pra cima
            if(tecla == 'D' || tecla == 'M')d = 2; // pra direita
            if(tecla == 'S' || tecla == 'P')d = 3; // pra baixo

        } // Final do while principal
    } // Saindo do jogo

    system("cls");
  return 0;
}
void gotoxy(int x, int y) // Funcao para o gotoxy saltar de posicao para um ponto especifico da tela
{
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x,y});// Mover o cursor
}
int Menu(int *velo){
  int opcao = 1, dificuldade = 1;
  char tecla = ' ';
  system("cls");

  printf("\n ---------- SNAKE GAME --------- \n");

    gotoxy(2, 3);
    SetConsoleTextAttribute(hConsole, 5);
    printf("-> Novo Jogo ");
    SetConsoleTextAttribute(hConsole, 7);
    gotoxy(2, 5);
    printf("-> Sair");
    gotoxy(2, 3);

    while(tecla != 13){
        tecla = getch();
        tecla = toupper(tecla);

        if(tecla != 13)tecla = getch(); // 13 = tecla enter
        tecla = toupper(tecla); // Transforma tecla digitada em maiusculo

        if(tecla == 'H'){ // H = seta para cima
            gotoxy(2,3);
            SetConsoleTextAttribute(hConsole, 5);
            printf("-> Novo Jogo ");
            SetConsoleTextAttribute(hConsole, 7);
            gotoxy(2, 5);
            printf("-> Sair");
            gotoxy(2,3);
            opcao = 1;
        }
        if(tecla == 'P'){ // P = seta para baixo
            gotoxy(2, 3);
            printf("-> Novo Jogo ");
            gotoxy(2,5);
            SetConsoleTextAttribute(hConsole, 5);
            printf("-> Sair");
            SetConsoleTextAttribute(hConsole, 7);
            gotoxy(2,5);
            opcao = 2;
        }
    }

  if(opcao == 1){
    tecla = ' ';
    system("cls");

    printf("\n\n ---------- SNAKE GAME --------- \n");
    printf("\n \n Escolha a dificuldade do jogo: ");

    gotoxy(2, 7);
    SetConsoleTextAttribute(hConsole, 5);
    printf("-> Facil ");
    SetConsoleTextAttribute(hConsole, 7);
    gotoxy(2, 9);
    printf("-> Medio");
    gotoxy(2, 11);
    printf("-> Dificil");
    gotoxy(2, 13);
    printf("-> God ");
    gotoxy(2, 7);

    while(tecla != 13){
        tecla = getch();
        tecla = toupper(tecla);

        if(tecla != 13)tecla = getch();
        tecla = toupper(tecla); // Transforma tecla digitada em maiusculo

        if(tecla == 'H'){
            if(dificuldade > 1){
                dificuldade--;
            }
        }
        if(tecla == 'P'){
            if(dificuldade < 4){
                dificuldade++;
            }
        }
        if(dificuldade == 1){
            gotoxy(2, 7);
            SetConsoleTextAttribute(hConsole, 5);
            printf("-> Facil ");
            SetConsoleTextAttribute(hConsole, 7);
            gotoxy(2, 9);
            printf("-> Medio");
            gotoxy(2, 11);
            printf("-> Dificil");
            gotoxy(2, 13);
            printf("-> God ");
            gotoxy(2, 7);
        }else if(dificuldade == 2){
            gotoxy(2, 7);
            printf("-> Facil ");
            gotoxy(2, 9);
            SetConsoleTextAttribute(hConsole, 5);
            printf("-> Medio");
            SetConsoleTextAttribute(hConsole, 7);
            gotoxy(2, 11);
            printf("-> Dificil");
            gotoxy(2, 13);
            printf("-> God ");
            gotoxy(2, 9);
        }else if(dificuldade == 3){
            gotoxy(2, 7);
            printf("-> Facil ");
            gotoxy(2, 9);
            printf("-> Medio");
            gotoxy(2, 11);
            SetConsoleTextAttribute(hConsole, 5);
            printf("-> Dificil");
            SetConsoleTextAttribute(hConsole, 7);
            gotoxy(2, 13);
            printf("-> God ");
            gotoxy(2, 11);
        }else{
            gotoxy(2, 7);
            printf("-> Facil ");
            gotoxy(2, 9);
            printf("-> Medio");
            gotoxy(2, 11);
            printf("-> Dificil");
            gotoxy(2, 13);
            SetConsoleTextAttribute(hConsole, 5);
            printf("-> God ");
            SetConsoleTextAttribute(hConsole, 7);
            gotoxy(2, 13);
        }
    }

    // Adicionando a velocidade de acordo com a dificuldade escolhida
    dificuldade == 1 ? (*velo = facil) : (dificuldade == 2 ? (*velo = medio) : (dificuldade == 3 ? (*velo = dificil) : (*velo = God)));

    system("cls");
    instrucoes_do_jogo(); // Mostra as instrucoes do jogo!
    return 0;
  }else{
    system("cls");
    return opcao; // Retorna 2
  }
}
void Game_over(int pontos, int nivel){
   // Função sleep usada para aguarda um certo tempo,
   // 1000 = 1 segundo, 2000 = 2 segundo etc.
   Sleep(1000);
   // Limpa a tela
   system("cls");

   // Game over
   SetConsoleTextAttribute(hConsole, 5);
   printf("\n\t   -_- \t\t\t\t");
   printf("\n\n   -_-  Voce perdeu! -_- \n\n \t         -_-\t\n"); // Exibir que perdeu
   printf("\n\t  -_-  Fez %d pontos -_- \n\n\t\t         -_- \t\n\n", pontos); // Exibir pontuacao
   printf(" \t\t -_- Chegou no nivel %d -_- \n\n\t\t              -_- \n\n", nivel);
   SetConsoleTextAttribute(hConsole, 7);

   printf("\n\n");
   Sleep(4000);
}
void CriarBorda(void){
    int x;

    SetConsoleTextAttribute(hConsole, 2);

    // Criação das bordas
    for(x=0; x < vertical_e; x++)
	{
	    gotoxy(0,x); // Vertical esquerda
	    printf("%c", 178);
    }
    for(x=0; x < horizontal_s; x++)
	{
        gotoxy(x,0); // Horizontal superior
        printf("%c", 178);
    }
    for(x=0; x < vertical_d; x++)
	{
        gotoxy(horizontal_s,x); // Vertical direita
        printf("%c", 178);
    }
    for(x=0; x < horizontal_i; x++)
	{
        gotoxy(x,vertical_e); // Horizontal inferior
        printf("%c", 178);
    }
    SetConsoleTextAttribute(hConsole, 7);
}
void Carregando(void){
  int i;
  printf("\n\n Carregando, por favor aguarde...\n ");
  for(i = 0; i < 20; i++){
     printf("\xDB");
     Sleep(400);
  }
  system("cls");
}
void instrucoes_do_jogo(void){
    system("cls");
    printf("\n __________________________ Instrucoes do jogo __________________________\n\n");
    printf(" - Mover a cobra: Setas pra cima(W), baixo(S), direita(D) e esquerda(A)!\n");
    printf(" - Sair do jogo: Tecla Esc!\n");
    printf(" - Nao eh permitido encostar nas bordas!\n");
    printf(" - Nao eh permitido encostar na calda da cobra!\n");
    printf(" - Objetivo:\n\t-> Facil %d pontos para vencer.\n", pontosf);
    printf("\t-> Medio %d pontos para vencer.\n\t-> Dificil %d pontos para vencer.\n",pontosm, pontosd);
    printf(" \t-> God %d pontos para vencer.\n", pontosg);
    Sleep(1000);
    getch();
}
void venceu(void){
    Sleep(3000);
    system("cls");
    SetConsoleTextAttribute(hConsole, 3);
    printf("\n\n    PARABENS!!!\n Voce venceu o jogo!!\n\n");
    SetConsoleTextAttribute(hConsole, 7);

    SetConsoleTextAttribute(hConsole, 9);
    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n");
    printf("    _________________ \n\n");
    SetConsoleTextAttribute(hConsole, 7);

    Sleep(2000);
}










