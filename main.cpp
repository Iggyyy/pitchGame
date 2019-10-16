#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>

    float actualShapeX;
    float actualShapeY;
    float actualPlayerX;
    float actualPlayerY;
    float actualComputerX;
    float actualComputerY;
    bool game = true;
    bool set_nick = true;
    float circle_moving_speed = 5.f;
    float player_mov_speed = 20.f;
    double ballSpeed = -5;
    float shapeMoveY = 0;
    float computerDestination = 200;
    int duration;
    int rand();
    int pointer = 1;
    int countOfButtons = 3;
    int playerMovingDirection;
    int difficulty = 1;
    int timeAtEnd;
    int volumeMusic = 1;
    sf::Text timer;
    sf::Texture backgroundTexture;
    sf::CircleShape shape(10.f);
    sf::Texture ballTexture;
    sf::Sprite player;
    sf::Texture textureOfPlayer;
    sf::Sprite computerPlayer;
    sf::RenderWindow window(sf::VideoMode(700, 400, 32), "PONGGERS!");
    sf::Sprite background;
    sf::Font myFont;
    sf::Music music;
    std::clock_t start;
    int tab[5];
    std::string tabN[5];
    std::string nick;


void startSettingNickname();
void EndGame();
void mainMenu();
void loadGameTextures();
void gameLoop();
void SortResults();

int main()
{
      window.setFramerateLimit(60);
 if(!music.openFromFile("Soundtrack.flac")){}
        music.play();
        music.setLoop(true);

    while(window.isOpen())
    {
        music.setVolume(volumeMusic);
        startSettingNickname();
        mainMenu();
        loadGameTextures();
        gameLoop();
        EndGame();
        playerMovingDirection=0;
        ballSpeed = -0.05;
    }



    return 0;
}
void gameLoop()
{
    sf::Music whistle;
    if(!whistle.openFromFile("whistle.flac")){}
        whistle.play();
        whistle.setVolume(50);
        music.setVolume(0);
        sf::Music stadium;
         if(!stadium.openFromFile("stadium.flac")){}
         stadium.play();
         stadium.setVolume(volumeMusic);

            srand(time(NULL));
         start = std::clock();
       std::string time;
    while (window.isOpen() && game == true)
    {

        if(shape.getPosition().x > window.getSize().x-1 || shape.getPosition().x <0 )
         {
             //timeAtEnd = duration;
             game=false;
             stadium.stop();
             music.setVolume(volumeMusic);
          break;
         }
        duration = (std::clock() - start)/(float) CLOCKS_PER_SEC;

        time = std::to_string(duration) + " seconds";
       //time = std::to_string(computerDestination);
        timer.setString(time);


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type==sf::Event::LostFocus)
                shape.setFillColor(sf::Color::Red);
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Escape)
               {

                game = false;
                stadium.stop();
                music.setVolume(volumeMusic);}
           // if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Right)
            //      player.move(sf::Vector2f(circle_moving_speed,0));
           // if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Left)
           //       player.move(sf::Vector2f(-circle_moving_speed,0));
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Down)
                    playerMovingDirection=1;
            if(event.type == sf::Event::KeyReleased && event.key.code==sf::Keyboard::Down )
                    playerMovingDirection =2;
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Up)
                    playerMovingDirection=3;
            if(event.type == sf::Event::KeyReleased && event.key.code==sf::Keyboard::Up )
                    playerMovingDirection =4;


        }

        switch(playerMovingDirection)
        {
            case 1: player.move(sf::Vector2f(0,circle_moving_speed));
                    break;
            case 2: player.move(sf::Vector2f(0,0));
                    break;
            case 3: player.move(sf::Vector2f(0,-circle_moving_speed));
                    break;
            case 4: player.move(sf::Vector2f(0,0));
                    break;
            default:
                    player.move(sf::Vector2f(0,0));
                    break;
        }

        actualShapeX = shape.getPosition().x;
        actualShapeY = shape.getPosition().y;
        actualPlayerX = player.getPosition().x;
        actualPlayerY = player.getPosition().y;
        actualComputerX = computerPlayer.getPosition().x;
        actualComputerY = computerPlayer.getPosition().y;


        if(actualShapeX-actualPlayerX<8.f && actualShapeY-actualPlayerY<64 && actualShapeY-actualPlayerY>-32 )
          {
            shape.setPosition(shape.getPosition().x+1,shape.getPosition().y);
           // shape.move(1.f*-ballSpeed,0.f);
           int angle = rand();
            ballSpeed *= -1 ;
            shapeMoveY = -ballSpeed*(angle%4);
            float imagineposX = shape.getPosition().x;
            float imagineposY = shape.getPosition().y;
            float shapeMoveY_imaginary = shapeMoveY;

            //int i = 0;
            while(imagineposX < window.getSize().x-7)
            {
                imagineposX += 1.f*ballSpeed;
                imagineposY += shapeMoveY_imaginary;
                if(imagineposY < 5) shapeMoveY_imaginary*=-1;
                else if (imagineposY> 395) shapeMoveY_imaginary*=-1;
            }
            computerDestination = imagineposY;
            //timer = std::to_string(imagineposY) + "y";
            // timer.setString(time);
            //shapee.setPosition(window.getSize().x-14, computerDestination);


          }
        else if (actualShapeY < 5)
        {
                shapeMoveY *= -1;

        }
        else if (actualShapeY > 395) shapeMoveY *= -1;
        else if (actualComputerX-actualShapeX<8.f && actualComputerY-actualShapeY<64 && actualComputerY-actualShapeY>-32)
            {
                int angle = rand();
                shape.setPosition(shape.getPosition().x-1,shape.getPosition().y);
                ballSpeed *= -1;
                shapeMoveY = -ballSpeed*(angle%2);
                computerDestination = (window.getSize().y);

            }
        //if(actualComputerY>396 || actualComputerY<4)
         //   computerDestination = (window.getSize().y/2);

        if(actualComputerY != computerDestination && actualComputerY > 2 && actualComputerY < window.getSize().y - 2)
        {
            if(actualComputerY < computerDestination)
                computerPlayer.move(0,ballSpeed);
            else if (actualComputerY > computerDestination)
                computerPlayer.move(0,-ballSpeed);
            if(actualComputerY > 2 && actualComputerY < 3)
                computerPlayer.setPosition(computerPlayer.getPosition().x, computerPlayer.getPosition().y + 1);



        }
        else
            computerPlayer.move(0,0);

        shape.move(ballSpeed+difficulty/2,shapeMoveY+difficulty/2);


        window.clear();

        window.draw(background);
        window.draw(timer);
        window.draw(computerPlayer);
        window.draw(player);
        window.draw(shape);
        window.display();
    }
}
void loadGameTextures()
{


    backgroundTexture.loadFromFile("background.png");

    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0,0,window.getSize().x, window.getSize().y));

    ballTexture.loadFromFile("ball.png");



    shape.setTexture(&ballTexture);
    shape.setPosition(window.getSize().x/2, window.getSize().y/2);

    if(!myFont.loadFromFile("font.otf"))
    {

    }
    timer.setFont(myFont);
    timer.setCharacterSize(32);
    timer.setColor(sf::Color::White);
    timer.setPosition(window.getPosition().x/2, 10);
    timer.setStyle(sf::Text::Bold);




    textureOfPlayer.loadFromFile("player.png");

    player.setTexture(textureOfPlayer);
    player.setTextureRect(sf::IntRect(0,0,14,64));
    player.setPosition(0,window.getSize().y/2-player.getTextureRect().height/2);

    computerPlayer.setTexture(textureOfPlayer);
    computerPlayer.setTextureRect(sf::IntRect(0,0,14,64));
    computerPlayer.setPosition(window.getSize().x-player.getTextureRect().width,window.getSize().y/2-player.getTextureRect().height/2);
}
void mainMenu()
{
    sf::Texture button_texture;
    button_texture.loadFromFile("buttonBackground.jpg");

  sf::RectangleShape buttonPlay;
    buttonPlay.setSize(sf::Vector2f(300, 50));
    buttonPlay.setPosition(window.getSize().x/2-buttonPlay.getSize().x/2, window.getSize().y/5-buttonPlay.getSize().y/2);
    buttonPlay.setFillColor(sf::Color(255, 255, 204));
    buttonPlay.setTexture(&button_texture);



    sf::RectangleShape buttonDifficulty;
    buttonDifficulty.setSize(sf::Vector2f(300, 50));
    buttonDifficulty.setPosition(window.getSize().x/2-buttonDifficulty.getSize().x/2, buttonPlay.getPosition().y+70);
    buttonDifficulty.setFillColor(sf::Color(255, 255, 204));
    buttonDifficulty.setTexture(&button_texture);

     sf::RectangleShape buttonVolume;
    buttonVolume.setSize(sf::Vector2f(300, 50));
    buttonVolume.setPosition(window.getSize().x/2-buttonVolume.getSize().x/2, buttonDifficulty.getPosition().y+70);
    buttonVolume.setFillColor(sf::Color(255, 255, 204));
    buttonVolume.setTexture(&button_texture);

 sf::Text instruction;
    instruction.setFont(myFont);
    instruction.setCharacterSize(32);
    instruction.setColor(sf::Color::Black);
    instruction.setPosition(window.getSize().x/2, window.getSize().y-64);
    instruction.setStyle(sf::Text::Bold);
    instruction.setString("ARROWS to choose button || ENTER to confirm");

     sf::Text difficulty_txt;
    difficulty_txt.setFont(myFont);
    difficulty_txt.setCharacterSize(44);
    difficulty_txt.setColor(sf::Color::Black);
    difficulty_txt.setPosition(buttonDifficulty.getPosition().x + buttonDifficulty.getSize().x-20, buttonDifficulty.getPosition().y);
    difficulty_txt.setStyle(sf::Text::Bold);

    sf::Text play_txt;
    play_txt.setFont(myFont);
    play_txt.setCharacterSize(44);
    play_txt.setColor(sf::Color::Black);
    play_txt.setPosition(buttonPlay.getPosition().x, buttonPlay.getPosition().y);
    play_txt.setStyle(sf::Text::Bold);
    play_txt.setString("PLAY");

    sf::Text difficulty_txt1;
    difficulty_txt1.setFont(myFont);
    difficulty_txt1.setCharacterSize(44);
    difficulty_txt1.setColor(sf::Color::Black);
    difficulty_txt1.setPosition(buttonDifficulty.getPosition().x, buttonDifficulty.getPosition().y);
    difficulty_txt1.setStyle(sf::Text::Bold);
    difficulty_txt1.setString("DIFFICULTY");

    sf::Text volume_txt;
    volume_txt.setFont(myFont);
    volume_txt.setCharacterSize(44);
    volume_txt.setColor(sf::Color::Black);
    volume_txt.setPosition(buttonVolume.getPosition().x, buttonVolume.getPosition().y);
    volume_txt.setStyle(sf::Text::Bold);
    volume_txt.setString("VOLUME");

      sf::Text volume_lvl;
    volume_lvl.setFont(myFont);
    volume_lvl.setCharacterSize(44);
    volume_lvl.setColor(sf::Color::Black);
    volume_lvl.setPosition(buttonVolume.getPosition().x + buttonVolume.getSize().x-20, buttonVolume.getPosition().y);
    volume_lvl.setStyle(sf::Text::Bold);


     if(!myFont.loadFromFile("font.otf"))
    {

    }
    bool play = false;
    while(play == false && window.isOpen())
    {




    switch(difficulty)
    {
        case 1: difficulty_txt.setString("1");
                    break;
        case 2: difficulty_txt.setString("2");
                    break;
        case 3: difficulty_txt.setString("3");
                    break;
        case 4: difficulty_txt.setString("4");
                    break;
        default:
            difficulty_txt.setString("1");
            break;
    }


    volume_lvl.setString(std::to_string(volumeMusic));
    music.setVolume(volumeMusic);



    sf::Sprite arrow;
    sf::Texture arrow_texture;
    arrow_texture.loadFromFile("arrow.png");
    arrow.setTexture(arrow_texture);

       if(pointer == 1)
                arrow.setPosition(buttonPlay.getPosition().x-50, buttonPlay.getPosition().y);
        else if(pointer == 2)
                arrow.setPosition(buttonDifficulty.getPosition().x-50, buttonDifficulty.getPosition().y);
        else if(pointer == 3)
                arrow.setPosition(buttonVolume.getPosition().x-50, buttonVolume.getPosition().y);
            //else
             //   arrow.setPosition(0,0);



    backgroundTexture.loadFromFile("menuBackground.jpg");
    background.setTexture(backgroundTexture);





      sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                play = true;
                window.close();
                music.stop();
            }
            if(event.type==sf::Event::LostFocus)
                shape.setFillColor(sf::Color::Red);
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Escape)
              {
                  play = true;
                window.close();
                music.stop();
              }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            {
                pointer++;
                if(pointer>countOfButtons)
                pointer=1;
            }
              if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            {
                 pointer--;
                if(pointer<1) pointer = countOfButtons;

            }
            if(event.type==sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                if(pointer==1) play = true;
                 if(pointer==2)
                {
                    difficulty++;
                    if(difficulty>4) difficulty = 1;
                }
                 if(pointer==3)
                {
                    volumeMusic++;
                    if(volumeMusic>10) volumeMusic=0;
                }
                //else if (pointer == 2)
            }




        }
        window.clear();

        window.draw(background);
        window.draw(buttonPlay);
        window.draw(buttonVolume);
        window.draw(buttonDifficulty);
        window.draw(arrow);
        window.draw(instruction);
        window.draw(difficulty_txt);
        window.draw(play_txt);
        window.draw(volume_txt);
        window.draw(difficulty_txt1);
        window.draw(volume_lvl);
        window.display();
    }

}
void EndGame()
{
      std::string line;
  std::ifstream myfile ("results.txt");
  if (myfile.is_open())
  {
      for(int i = 0; i<5; i++)
      {
        getline(myfile, line);
        tab[i] = atoi(line.c_str());
      }
    myfile.close();
  }


  std::ifstream myfilenicks ("nicknames.txt");
  if (myfilenicks.is_open())
  {
      for(int i = 0; i<5; i++)
      {
        std::getline(myfilenicks, line);
        tabN[i] = line;

      }
    myfilenicks.close();
  }

SortResults();
int wynik = duration;

if(wynik>tab[4])
{
    tab[4] = wynik;
    tabN[4] = nick;
    SortResults();
    //ZAPIS DO PLIKU SPOWROTEM
      std::ofstream file ("results.txt");
  if (file.is_open())
  {
    file << std::to_string(tab[0]) + "\n";
    file << std::to_string(tab[1]) + "\n";
    file << std::to_string(tab[2]) + "\n";
    file << std::to_string(tab[3]) + "\n";
    file << std::to_string(tab[4]) + "\n";

    file.close();
  }
      std::ofstream file1 ("nicknames.txt");
  if (file1.is_open())
  {
    file1 << tabN[0] + "\n";
    file1 << tabN[1] + "\n";
    file1 << tabN[2] + "\n";
    file1 << tabN[3] + "\n";
    file1 << tabN[4] + "\n";

    file1.close();
  }
}

 std::string ss;
    ss.append("Congratulations!\n\n 1. ");
    ss.append(std::to_string(tab[0]));
    ss.append(" sec " + tabN[0] + "\n 2. ");
    ss.append(std::to_string(tab[1]));
    ss.append(" sec " + tabN[1] + "\n 3. ");
    ss.append(std::to_string(tab[2]));
    ss.append(" sec " + tabN[2] + "\n 4. ");
    ss.append(std::to_string(tab[3]));
    ss.append(" sec " + tabN[3] + "\n 5. ");
    ss.append(std::to_string(tab[4]));
    ss.append(" sec " + tabN[4] + "\n ");

   backgroundTexture.loadFromFile("background.png");
    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0,0,window.getSize().x, window.getSize().y));

    sf::RectangleShape border;
    border.setSize(sf::Vector2f(200, 300));
    border.setFillColor(sf::Color::White);
    border.setPosition(window.getSize().x/2-border.getSize().x/2, window.getSize().y/2-border.getSize().y/2);

    sf::Text timeee;
    timeee.setFont(myFont);
    timeee.setCharacterSize(32);
    timeee.setColor(sf::Color::Black);
    timeee.setPosition(window.getSize().x/2 - 76, border.getPosition().y+32);
    timeee.setStyle(sf::Text::Bold);
    timeee.setString("You've survived " + std::to_string(duration) + " seconds");



    sf::Text test;
    test = timeee;
    test.setString(ss);
    test.setPosition(window.getSize().x/2 - 51, border.getPosition().y);


    sf::Text instruction;
    instruction = timeee;
    instruction.setPosition(window.getSize().x/2 + 135, window.getSize().y-64);
    instruction.setString("ESCAPE to continue to menu");
    while(window.isOpen()&& game==false)
    {


    sf::Event event;
    while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {


                window.close();
                game = true;
            }
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Escape)
                game=true;
        }
    window.clear();
    window.draw(background);
    window.draw(border);
    window.draw(instruction);
    window.draw(test);
    window.draw(timeee);
    window.display();
    }
}
void SortResults()
{
    for(int y = 0; y <5; y++)
    {


        for(int i = 0; i<4; i++)
        {
            if(tab[i] < tab[i+1])
            {
                std::swap(tab[i], tab[i+1]);
                std::swap(tabN[i], tabN[i+1]);
            }
        }
    }
}
void startSettingNickname()
{
 if(!myFont.loadFromFile("font.otf"))
    {

    }
 sf::Text text;

    text.setFont(myFont);
    text.setCharacterSize(64);
    text.setColor(sf::Color::Black);
    text.setPosition(window.getSize().x/2-150, window.getSize().y/2-100);
    text.setStyle(sf::Text::Bold);
   backgroundTexture.loadFromFile("menuBackground.jpg");
    background.setTexture(backgroundTexture);

    while(window.isOpen() && set_nick == true)
    {



    text.setString("ENTER YOUR NICKNAME: \n "+ nick +"\n Press ENTER to continue");



        sf::Event event;
    while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                set_nick = false;
            }
           if (event.type == sf::Event::TextEntered && nick.size() < 15){
                if(event.type == sf::Event::KeyPressed && event.key.code== sf::Keyboard::BackSpace){
                   nick.pop_back();
                   // std::cout << s << std::endl;
                }
                if (event.text.unicode < 128) {
                    nick.push_back((char)event.text.unicode);

                }
            }

        }


               // nick += character;




            window.clear();
            window.draw(background);
            window.draw(text);
            window.display();
        }
    }




