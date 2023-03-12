#include<stdio.h>
#include<math.h>

void draw_score(int,int);
void draw_field(int, int, int, int, int, int, int, int);
int ball_collision(int, int, int, int, int, int);

int main() {
//---Здесь задаются переменные-------------------------------------------------------------------------------------

    //задаём начальные координаты нашего поля
    int left_border = 1;
    int upper_border = 1;
    int right_border = 80; 
    int lower_border = 25;
    
    //задаём начальные координаты игроков. Мы делим на 2, чтобы игроки находились посередине. -3, потому что у нас платформа в 3 полосочки.
    const int default_player1_y = lower_border / 2 - 3;
    const int default_player2_y = lower_border / 2 - 3;
    int player1_y = default_player1_y;
    int player2_y = default_player2_y;
    //задаём начальные значения очков
    int player1_score = 0, player2_score = 0;

    //задаём начальные координаты мяча
    int default_ball_x = 40;
    int default_ball_y = 13;
    int ball_x = default_ball_x;
    int ball_y = default_ball_y;

    //задаём мячу начальное движение
    int ball_vertical_movement = -1;
    int ball_horizontal_movement = -1;

//---Здесь начинается тело нашей игры------------------------------------------------------------------------------

    //совершаем первую отрисовку перед циклом, чтобы хоть что-то видеть
    draw_score(player1_score, player2_score);
    draw_field(left_border, upper_border, right_border, lower_border, player1_y, player2_y, ball_x, ball_y);

    while(player1_score != 21 || player2_score != 21) {
        //переменные для управления игроками. input_number считывает букву, enter лишь ожидает от вас нажатия на enter.
        char input_player;
        char enter;
        //переменная для проверки корректного нажатия кнопки.
        int correct_symbol = 1;
        //функции ввода. действуют во время начала каждой итерации. через них как раз вводится правильная клавиша: 
        //('a', 'z','k', 'm') + клавиша ввода - enter.
        input_player = getc(stdin);
        enter = getc(stdin);

        //switch - это if на спидах. можно просто и легко проверить, какая клавиша нажата и какое действие нужно совершить
        //на всякий загуглите и посмотрите, как это работает
        switch(input_player) {
            case 'a':
            case 'A':
                if(player1_y > upper_border + 1) 
                    player1_y -= 1;
                break;
            case 'z':
            case 'Z':
                if(player1_y < lower_border - 3)
                    player1_y +=1;
                break;
            case 'k':
            case 'K':
                if(player2_y > upper_border + 1)
                    player2_y -=1;
                break;
            case 'm':
            case 'M':
                if(player2_y < lower_border - 3)
                    player2_y +=1;
                break;
            case ' ':
                break;
            //default - ситуация рассматривает случай, когда ни один из вышеобозначенных ситуаций не подошёл. 
            //мы будем считать, что это некорректный ввод  
            default:
                 correct_symbol = 0;
                break;
        }

        //---Идёт проверка на корректность введённого символа------------------------------------------------------

        if(correct_symbol) {
            //printf("%d %d", player1_y, player2_y);
            //draw_score(player1_score, player2_score);

            //Здесь идёт наша главная отрисовка (см. функцию draw_field ниже)
            draw_field(left_border, upper_border, right_border, lower_border, player1_y, player2_y, ball_x, ball_y);

            //Здесь идёт проверка на столкновения мяча в разных ситуациях (см. функцию ball_collision)
            switch (ball_collision(ball_x, ball_y, player1_y, player2_y, upper_border, lower_border)) {
                case 1:
                    //т.к мы столкнулись с верхней границей, то нам нужно поменять направление движения по вертикали
                    ball_vertical_movement *= -1;
                    ball_y += ball_vertical_movement;
                    ball_x += ball_horizontal_movement;
                    printf("Сработала коллизия верхней горизонтальной границы!\n");
                break;
                case 2:
                    //т.к мы столкнулись с верхней границей, то нам нужно поменять направление движения по вертикали
                    ball_vertical_movement *= -1;
                    ball_y += ball_vertical_movement;
                    ball_x += ball_horizontal_movement;
                    printf("Сработала коллизия нижней горизонтальной границы!\n");
                break;
                case 3:
                    //т.к мы столкнулись с персонажем, то нужно поменять направление движения по горизонтали
                    ball_horizontal_movement *= -1;
                    ball_x += ball_horizontal_movement;
                    ball_y += ball_vertical_movement; 
                    printf("Сработала коллизия левого игрока!\n");
                break;
                case 4:
                    //т.к мы столкнулись с персонажем, то нужно поменять направление движения по горизонтали
                    ball_horizontal_movement *= -1;
                    ball_x += ball_horizontal_movement;
                    ball_y += ball_vertical_movement; 
                    printf("Сработала коллизия правого игрока!\n");
                break;
                case 5:
                    //здесь мы рассматриваем ситуацию, когда мячик вышел за границу левого(первого) игрока
                    ball_x = default_ball_x;
                    ball_y = default_ball_y;
                    player1_y = default_player1_y;
                    player2_y = default_player2_y;
                    player2_score += 1;
                    printf("Очко за вторым игроком!\n");
                break;
                case 6:
                    //здесь мы рассматриваем ситуацию, когда мячик вышел за границу правого(второго) игрока
                    ball_x = default_ball_x;
                    ball_y = default_ball_y;
                    player1_y = default_player1_y;
                    player2_y = default_player2_y;
                    player1_score += 1;
                    printf("Очко за первым игроком!\n");
                default:
                    ball_x += ball_horizontal_movement;
                    ball_y +=ball_vertical_movement;
                break;
            }
        }
        else {
            printf("Неверный ввод!\n");
        }
    }
    if(player1_score == 21) {
        printf("Победа за игроком 1!");
    }
    else {
        printf("Победа за игроком 2!");
    }
    return 0;
}

//функция, которая отрисовывает счётчик
void draw_score(int player1_score, int player2_score) {
    printf("\t\t\t\tScore: %d | %d\n", player1_score, player2_score);
}

//функция, которая отрисовывает всё
void draw_field(int x1, int y1, int x2, int y2, int player1_y, int player2_y, int ball_x, int ball_y) {

    for(int y = y1; y <= y2; y++) {
        for(int x = x1; x <= x2; x++) {
            if(y == y1 || y == y2)
                printf("-");
            else if (y == ball_y && x == ball_x)
                printf("o"); 
            else if(y >= player1_y && y <= (player1_y + 2) && x == 5)
                printf("|");
            else if(y >= player2_y && y <= (player2_y + 2) && x == 75) 
                printf("|");
            else if(x == x1 || x == x2 || x == 40)
                printf("|");
            else
                printf(" ");
        }
        printf("\n");    
    }
}


//функция, которая обрабатывает разные случаи 
int ball_collision(int ball_x, int ball_y, int player1_y, int player2_y, int upper_border, int lower_border) {
    if(ball_y == upper_border + 1) {
        return 1;
    } else if(ball_y == lower_border - 1) {
        return 2;
    } else if(ball_x == 6 && (ball_y == player1_y || ball_y == player1_y + 1 || ball_y == player1_y + 2) ) {
        return 3;
    } else if(ball_x == 74 && (ball_y == player2_y || ball_y == player2_y + 1 || ball_y == player2_y + 2) ) {
        return 4;
    } else if(ball_x == 1 && ball_x != 80) {
        return 5;
    } else if(ball_x == 80 && ball_x != 1)
        return 6;
}
