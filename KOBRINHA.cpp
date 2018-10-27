#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>

void gotoxy(int x, int y) // Funcao para o gotoxy saltar de posicao para um ponto especifico da tela
{
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x,y});// Mover o cursor
}

int main(int argc, char* argv[]){
    int x, d = 2, t = 1, mx, my, cy[300] = {1, 2}, cx[300] = {7,7};
    int velo = 100, velo2 = 5;
    char niv, tecla = 'a';
    int opcao, pontos = 0, nivel = 1; // Niveis começando do 1

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

    srand(time(NULL)); // Srand gera valores aleatorios
    // Cordenadas x,y geradas aleatorio para aparecer a comida
    mx = (rand()% 49) + 1;
    my = (rand()% 17) + 1;

    velo = 200;  // Velocidade com que o cursor vai se mover

    while(tecla != 's'){

        // Função "kbhit()" retorna 0 se o usuário não está precionando nenhuma tecla. Caso contrário, retorna um valor diferente de 0.
        while(tecla != 's' && !(tecla = kbhit())){
            for(x = t; x > 0; x--){
                cx[x] = cx[x - 1];
                cy[x] = cy[x - 1];
            }

            if(d == 0)cx[0]--; // Move para a esquerda no eixo X
            if(d == 1)cy[0]--; // Move para baixo no eixo Y
            if(d == 2)cx[0]++; // Move para a direita no eixo X
            if(d == 3)cy[0]++; // Move para cima no eixo Y

            gotoxy(cx[t], cy[t]);
            printf(" ");
            if(mx == cx[0] && my == cy[0]){
                printf("\a"); // Som ao comer
                t++;  // t = tamanho da cobra
                pontos++;
                mx = (rand()%25) + 1;
                my = (rand()%17) + 1;
                velo -= 5; // velocidade 5 eh a maxima
                velo2 += 5; // vai da 2 e incrementa ate 5
            }

            gotoxy(cx[0],cy[0]);
            printf("%c", 1); // cursor que anda pela tela (cobrinha)

            gotoxy(mx, my);    // Posição do comida que vai aparecer na tela (aleatorio)
            printf("%c", 1);   // Comida que aparece pra cobra comer

            // Informações do jogo pontos, nivel e velociade atual
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

            for(x = 1; x < t; x++){
                if(cx[0] == cx[x] && cy[0] == cy[x])
                   tecla = 's';
            }
            if(cy[0] == 0 || cy[0] == 18 || cx[0] == 0 || cx[0] == 50)
                tecla = 's';

          } // Fim do while secundario

        if(tecla != 's')tecla = getch();
        if(tecla == 'K')d = 0;
        if(tecla == 'H')d = 1;
        if(tecla == 'M')d = 2;
        if(tecla == 'P')d = 3;

        // Verifica se a cobra bateu na borda
        if(cy[0] == 0 || cy[0] == 18 || cx[0] == 0 || cx[0] == 26)tecla = 's';

    } // Final do while principal

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
   getch();
  return 0;
}
