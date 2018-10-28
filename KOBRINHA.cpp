#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<ctype.h>

// Enumeração
enum{facil = 300, medio = 200, dificil = 100, God = 50, SAIR = 27, Jogando = 1};

// Prototipos das funções
void instrucoes_do_jogo(void);
void Game_over(int pontos, int nivel);
void gotoxy(int x, int y);
void CriarBorda(void);
void Carregando(void);
int Menu(int *velo);

// Usado para mudar a cor das coisas
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int main(int argc, char* argv[]){
    srand(time(NULL)); // Usado para gerar valores aleatorios
    int x, d, tamanho, mx, my, velo;
    int velo2, opcao, pontos, nivel;
    char tecla;

    while(Jogando){

        // opcao 2 = instruções
        opcao = Menu(&velo);
        while(opcao == 2){
            opcao = Menu(&velo);
        }
        // Opcao 3 = Sair
        if(opcao == 3)break;

        Carregando(); // Tela "carregando jogo"

        // Função pra criar borda
        CriarBorda();

        // Coordenadas x,y geradas aleatorio para aparecer a comida
        mx = (rand()% 69) + 1;
        my = (rand()% 19) + 1;

        // Iniciando variaveis
        tecla = ' ';
        tamanho = 1;
        pontos = 0;
        nivel = 1;
        velo2 = 1;
        int cy[300] = {1, 2};
        int cx[300] = {7, 7};
        d = 2; // Começa andando para a direita

        SetConsoleTextAttribute(hConsole, 5);
        printf("\n ---------------------------- SNAKE GAME ------------------------------\n");
        SetConsoleTextAttribute(hConsole, 7);

        while(tecla != SAIR){  // 27 = ESC

            // Função "kbhit()" retorna 0 se o usuário não está precionando nenhuma tecla.
            // Caso contrário, retorna um valor diferente de 0.
            while(tecla != 27 && !(tecla = kbhit())){
                for(x = tamanho; x > 0; x--){
                    cx[x] = cx[x - 1];
                    cy[x] = cy[x - 1];
                }

                if(d == 0)cx[0]--; // Move para a esquerda no eixo X
                if(d == 1)cy[0]--; // Move para cima no eixo Y
                if(d == 2)cx[0]++; // Move para a direita no eixo X
                if(d == 3)cy[0]++; // Move para baixo no eixo Y

                gotoxy(cx[tamanho], cy[tamanho]);
                printf(" ");
                if(mx == cx[0] && my == cy[0]){
                    printf("\a"); // Som ao comer
                    tamanho++;  // t = tamanho da cobra
                    pontos++;
                    mx = (rand()%69) + 1;
                    my = (rand()%19) + 1;
                    if(velo != 2){
                        velo -= 2; // velocidade 5 eh a maxima
                        velo2 += 1; // vai da 2 e incrementa ate 5
                    }
                    if(velo2 % 5 == 0){
                        nivel++;
                    }
                }
                gotoxy(cx[0],cy[0]);
                printf("%c", 1);   // Cursor que anda pela tela (cobrinha)

                gotoxy(mx, my);    // Posição do comida que vai aparecer na tela (aleatorio)
                SetConsoleTextAttribute(hConsole, 12);
                printf("%c", 1);   // Comida que aparece pra cobra comer
                SetConsoleTextAttribute(hConsole, 7);

                // Informações do jogo pontos, nivel e velocidade atual
                gotoxy(55, 22);
                printf("\n Criado por: \n");
                printf(" Marcelo Lima e Luiz Eduardo\n");
                gotoxy(75, 6);
                printf("Pontos: %d", pontos);
                gotoxy(75, 4);
                printf("Nivel: %d", nivel);
                gotoxy(75, 2);
                printf("Velocidade: %d", velo2);

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
                if(cy[0] == 0 || cy[0] == 20 || cx[0] == 0 || cx[0] == 70){
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
  int opcao, dificuldade;
  system("cls");

  printf("\n ---------- SNAKE GAME --------- \n");
  printf("\n 1- Novo Jogo\n 2- Instrucoes\n 3- Sair\n ---> ");
  scanf("%d", &opcao);

  if(opcao == 1){
    system("cls");
    printf("\n\n ---------- SNAKE GAME --------- \n");
    printf("\n Escolha a dificuldade do jogo: ");
    printf("\n 1- Facil\n 2- Medio\n 3- Dificil\n 4- God \n --> ");
    scanf("%d", &dificuldade);

    // Adicionando a velocidade de acordo com a dificuldade escolhida
    dificuldade == 1 ? (*velo = facil) : (dificuldade == 2 ? (*velo = medio) : (dificuldade == 3 ? (*velo = dificil) : (*velo = God)));

    system("cls");
    return 0;
  }else if(opcao == 2){
    instrucoes_do_jogo();
    return 2;
  }else{
    system("cls");
    return opcao; // Retorna 3
  }
}
void Game_over(int pontos, int nivel){
   Sleep(1000);
   printf("\n\n\t BURRO!........\n\n");

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
   getch();
}
void CriarBorda(void){
    int x;

    SetConsoleTextAttribute(hConsole, 2);

    // Criação das bordas
    for(x=0; x < 20; x++)
	{
	    gotoxy(0,x); // Vertical esquerda
	    printf("%c", 178);
    }
    for(x=0; x < 70; x++)
	{
        gotoxy(x,0); // Horizontal superior
        printf("%c", 178);
    }
    for(x=0; x < 20; x++)
	{
        gotoxy(70,x); // Vertical direita
        printf("%c", 178);
    }
    for(x=0; x < 71; x++)
	{
        gotoxy(x,20); // Horizontal inferior
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
    printf("\n __________________________ Instrucoes __________________________\n\n");
    printf(" - Mover a cobra: Setas pra cima(W), baixo(S), direita(D) e esquerda(A)!\n");
    printf(" - Sair do jogo: Tecla Esc!\n");
    printf(" - Nao eh permitido encostar nas bordas!\n");
    printf(" - Nao eh permitido encostar na calda da cobra!\n");
    getch();
}
