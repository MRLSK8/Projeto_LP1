#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

// Enumeração
enum{facil = 300, medio = 200, dificil = 100, God = 50, SAIR = 27, Jogando = 1};

// Prototipos das funções
int Menu(int *velo);
void gotoxy(int x, int y);
void Game_over(int pontos);
void CriarBorda(void);

int main(int argc, char* argv[]){
    int x, d = 2, tamanho = 1, mx, my, cy[300] = {1, 2}, cx[300] = {7,7};
    int velo, velo2 = 5, opcao, pontos = 0, nivel = 1; // Niveis começando do 1
    char niv, tecla = 'a';


    while(Jogando){
        opcao = Menu(&velo);
        if(opcao == 2)break;

        // Função pra criar borda
        CriarBorda();

        srand(time(NULL)); // Srand gera valores aleatorios
        // Coordenadas x,y geradas aleatorio para aparecer a comida
        mx = (rand()% 49) + 1;
        my = (rand()% 17) + 1;

        printf("\n\t ---------- SNAKE GAME --------- \n");
        while(tecla != SAIR){  // 27 = ESC

            // Função "kbhit()" retorna 0 se o usuário não está precionando nenhuma tecla. Caso contrário, retorna um valor diferente de 0.
            while(tecla != 27 && !(tecla = kbhit())){
                for(x = tamanho; x > 0; x--){
                    cx[x] = cx[x - 1];
                    cy[x] = cy[x - 1];
                }

                if(d == 0)cx[0]--; // Move para a esquerda no eixo X
                if(d == 1)cy[0]--; // Move para baixo no eixo Y
                if(d == 2)cx[0]++; // Move para a direita no eixo X
                if(d == 3)cy[0]++; // Move para cima no eixo Y

                gotoxy(cx[tamanho], cy[tamanho]);
                printf(" ");
                if(mx == cx[0] && my == cy[0]){
                    printf("\a"); // Som ao comer
                    tamanho++;  // t = tamanho da cobra
                    pontos++;
                    mx = (rand()%25) + 1;
                    my = (rand()%17) + 1;
                    if(velo != 5){
                        velo -= 5; // velocidade 5 eh a maxima
                        velo2 += 5; // vai da 2 e incrementa ate 5
                    }
                }

                gotoxy(cx[0],cy[0]);
                printf("%c", 1);   // Cursor que anda pela tela (cobrinha)

                gotoxy(mx, my);    // Posição do comida que vai aparecer na tela (aleatorio)
                printf("%c", 1);   // Comida que aparece pra cobra comer

                // Informações do jogo pontos, nivel e velocidade atual
                gotoxy(55, 20);
                printf("\n Criado por: \n");
                printf(" Marcelo Lima e Luiz Eduardo\n");
                gotoxy(55, 5);
                printf("Pontos: %d", pontos);
                gotoxy(55, 3);
                printf("Nivel: %d", nivel);
                gotoxy(55, 1);
                printf("Velocidade: %d", velo2);

                // Velociadade da cobra
                Sleep(velo);

                // Verifica se a cobra bateu nela mesmo
                for(x = 1; x < tamanho; x++){
                    if(cx[0] == cx[x] && cy[0] == cy[x]){
                       tecla = SAIR;
                       Game_over(pontos);
                       break;
                    }
                }
                // Verifica se a cobra bateu na borda
                if(cy[0] == 0 || cy[0] == 18 || cx[0] == 0 || cx[0] == 50){
                    Game_over(pontos);
                    tecla = SAIR;
                }

              } // Fim do while secundario

            if(tecla != SAIR)tecla = getch();
            if(tecla == 'K')d = 0; // Seta pra esquerda
            if(tecla == 'H')d = 1; // Seta pra cima
            if(tecla == 'M')d = 2; // Seta pra direita
            if(tecla == 'P')d = 3; // Seta pra baixo

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
  printf("\n 1- Novo Jogo\n 2- Sair\n ---> ");
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
  }else{
    system("cls");
    return opcao;
  }
}
void Game_over(int pontos){
   Sleep(1000);

   printf("\n\n\t BURRO!........\n\n");
   // Limpa a tela
   system("cls");

   // Game over
   printf("\n\n\t       %c", 35);
   printf("\t%c", 35);

   printf("\n\n\t%c -_- Voce perdeu! -_- %c\n", 35, 35); // Exibir que perdeu
   printf("\n\t    %c Fez %d pontos %c\n\n", 35, pontos, 35); // Exibir pontuacao

   printf("\t       %c", 35);
   printf("\t%c", 35);

   printf("\n\n");
   Sleep(5000);
   getch();
}
void CriarBorda(void){
    int x;

    // Criação das bordas
    for(x=0; x < 18; x++)
	{
	    gotoxy(0,x); // Vertical esquerda
	    printf("%c", 178);
    }
    for(x=0; x < 50; x++)
	{
        gotoxy(x,0); // Horizontal superior
        printf("%c", 178);
    }
    for(x=0; x < 18; x++)
	{
        gotoxy(50,x); // Vertical direita
        printf("%c", 178);
    }
    for(x=0; x < 51; x++)
	{
        gotoxy(x,18); // Horizontal inferior
        printf("%c", 178);
    }
}
