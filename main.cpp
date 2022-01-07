#include "MinesweeperUtil.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

map<string, sf::Texture> TextureManager::textures;
int main() {

  bool debugg = false;
  bool GameOver = false;
  int flagCount = 0;
  unsigned int Winner = 400;
  LoadAssets();

  sf::Sprite digit;
  digit.setTexture(TextureManager::GetTexture(("digits")));
  digit.setTextureRect(sf::IntRect(0, 0, 21, 32));

  vector<Tile> tiles;
  int levelArray[400];
  LoadBoard(0, levelArray, tiles, 0, flagCount);
  sf::Sprite Restart;
  Restart.setTexture(TextureManager::GetTexture("face_happy"));
  Restart.setPosition(368, 512);
  sf::Sprite Debugger;
  Debugger.setTexture(TextureManager::GetTexture("debug"));
  Debugger.setPosition(496, 512);
  sf::Sprite Test1;
  Test1.setTexture(TextureManager::GetTexture("test_1"));
  Test1.setPosition(560, 512);
  sf::Sprite Test2;
  Test2.setTexture(TextureManager::GetTexture("test_2"));
  Test2.setPosition(624, 512);
  sf::Sprite Test3;
  Test3.setTexture(TextureManager::GetTexture("test_3"));
  Test3.setPosition(688, 512);

  sf::Sprite Backround;
  Backround.setTexture(TextureManager::GetTexture("tile_revealed"));

  sf::RenderWindow window(sf::VideoMode(800, 600),
                          "MineSweeper- DePascale COP3503",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(60);
  while (window.isOpen()) {
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    double x = ceil(pos.x / 32);
    double y = ceil(pos.y / 32);

    sf::Event event;
    while (window.pollEvent(event)) {

      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          unsigned int tileNum = static_cast<unsigned int>(25 * y + x);
          if (tileNum < 400 && GameOver == false &&
              Winner == false) { // game grid interaction
            if (tiles[tileNum].hidden == true &&
                tiles[tileNum].flagged == false) {
              tiles[tileNum].hidden = false;
              unhideAdjacent(tiles, tileNum);
              if (tiles[tileNum].hidden == false &&
                  tiles[tileNum].mine == true) {
                // Game over here......
                GameOver = true;
              }
            }
          }
          // Reset
          if (pos.x >= 368 && pos.x <= 432 && pos.y >= 512 && pos.y <= 576) {
            LoadBoard(0, levelArray, tiles, 1, flagCount);
            GameOver = false;
            debugg = false;
          }
          // debugg
          if (pos.x > 496 && pos.x <= 560 && pos.y >= 512 && pos.y <= 576) {
            if (debugg == false) {
              debugg = true;
            } else if (debugg == true) {
              debugg = false;
            }
          }
          // map1
          if (pos.x > 560 && pos.x <= 624 && pos.y >= 512 && pos.y <= 576) {
            LoadBoard(1, levelArray, tiles, 1, flagCount);
            GameOver = false;
            debugg = false;
          }
          // map2
          if (pos.x > 624 && pos.x <= 688 && pos.y >= 512 && pos.y <= 576) {
            LoadBoard(2, levelArray, tiles, 1, flagCount);
            GameOver = false;
            debugg = false;
          }
          // map3
          if (pos.x > 688 && pos.x <= 752 && pos.y >= 512 && pos.y <= 576) {
            LoadBoard(3, levelArray, tiles, 1, flagCount);
            GameOver = false;
            debugg = false;
          }

        } else if (event.mouseButton.button == sf::Mouse::Right) {
          unsigned int tileNum = static_cast<unsigned int>(25 * y + x);
          if (tiles[tileNum].flagged == false &&
              tiles[tileNum].hidden == true && GameOver == false) {
            tiles[tileNum].flagged = true;
            flagCount--;
          } else if (tiles[tileNum].flagged == true &&
                     tiles[tileNum].hidden == true && GameOver == false) {
            tiles[tileNum].flagged = false;
            flagCount++;
          }
        }
      }
    }

    Winner = GameStatus(tiles);
    window.clear(sf::Color(45, 45, 45));
    unsigned int index = 0;

    for (unsigned int i = 0; i < 16; i++) {
      for (unsigned int j = 0; j < 25; j++) {
        Backround.setPosition(j * 32, i * 32);
        tiles[index].sprite.setPosition(j * 32, i * 32);
        window.draw(Backround);
        if (tiles[index].mine == true) {
          tiles[index].sprite.setTexture(TextureManager::GetTexture("mine"));
          window.draw(tiles[index].sprite);
        }
        if (tiles[index].adjMineCount == 1) {
          tiles[index].sprite.setTexture(
              TextureManager::GetTexture("number_1"));
          window.draw(tiles[index].sprite);
        } else if (tiles[index].adjMineCount == 2) {
          tiles[index].sprite.setTexture(
              TextureManager::GetTexture("number_2"));
          window.draw(tiles[index].sprite);
        } else if (tiles[index].adjMineCount == 3) {
          tiles[index].sprite.setTexture(
              TextureManager::GetTexture("number_3"));
          window.draw(tiles[index].sprite);
        } else if (tiles[index].adjMineCount == 4) {
          tiles[index].sprite.setTexture(
              TextureManager::GetTexture("number_4"));
          window.draw(tiles[index].sprite);
        } else if (tiles[index].adjMineCount == 5) {
          tiles[index].sprite.setTexture(
              TextureManager::GetTexture("number_5"));
          window.draw(tiles[index].sprite);
        } else if (tiles[index].adjMineCount == 6) {
          tiles[index].sprite.setTexture(
              TextureManager::GetTexture("number_6"));
          window.draw(tiles[index].sprite);
        } else if (tiles[index].adjMineCount == 7) {
          tiles[index].sprite.setTexture(
              TextureManager::GetTexture("number_7"));
          window.draw(tiles[index].sprite);
        } else if (tiles[index].adjMineCount == 8) {
          tiles[index].sprite.setTexture(
              TextureManager::GetTexture("number_8"));
          window.draw(tiles[index].sprite);
        }

        if (tiles[index].hidden == true) {
          tiles[index].sprite.setTexture(
              TextureManager::GetTexture("tile_hidden"));
          window.draw(tiles[index].sprite);
        }
        if (tiles[index].flagged == true) {
          tiles[index].sprite.setTexture(TextureManager::GetTexture("flag"));
          window.draw(tiles[index].sprite);
        }
        if (tiles[index].mine == true && debugg == true) {
          tiles[index].sprite.setTexture(TextureManager::GetTexture("mine"));
          window.draw(tiles[index].sprite);
        }
        if (GameOver == true && tiles[index].mine == true) {
          tiles[index].hidden = false;

          tiles[index].sprite.setTexture(TextureManager::GetTexture("mine"));
          window.draw(tiles[index].sprite);
        }
        if (Winner == true && tiles[index].hidden == true &&
            tiles[index].mine == true) {
          tiles[index].flagged = true;
        }

        index++;
      }
    }
    if (GameOver == true) {
      Restart.setTexture(TextureManager::GetTexture("face_lose"));
    }
    if (GameOver == false) {
      Restart.setTexture(TextureManager::GetTexture("face_happy"));
    }
    if (Winner == true) {
      Restart.setTexture(TextureManager::GetTexture("face_win"));
      flagCount = 0;
    }
    if (flagCount >= 0 && flagCount < 100) {
      int ones = flagCount % 10;
      int tens = (flagCount / 10) % 10;
      digit.setTextureRect(sf::IntRect(tens * 21, 0, 21, 32));
      digit.setPosition(0, 512);
      window.draw(digit);
      digit.setTextureRect(sf::IntRect(((ones)*21), 0, 21, 32));
      digit.setPosition(21, 512);
      window.draw(digit);
    } else if (flagCount < 0 && flagCount > -100 && Winner != true) {
      int ones = abs(flagCount) % 10;
      int tens = (abs(flagCount) / 10) % 10;
      digit.setTextureRect(sf::IntRect(210, 0, 21, 32));
      digit.setPosition(0, 512);
      window.draw(digit);
      digit.setTextureRect(sf::IntRect(tens * 21, 0, 21, 32));
      digit.setPosition(21, 512);
      window.draw(digit);
      digit.setTextureRect(sf::IntRect(((ones)*21), 0, 21, 32));
      digit.setPosition(42, 512);
      window.draw(digit);
    } else if (flagCount <= -100 && Winner != true) {
      int ones = abs(flagCount) % 10;
      int tens = (abs(flagCount) / 10) % 10;
      int hundo = (abs(flagCount / 100)) % 10;
      digit.setTextureRect(sf::IntRect(210, 0, 21, 32));
      digit.setPosition(0, 512);
      window.draw(digit);
      digit.setTextureRect(sf::IntRect(hundo * 21, 0, 21, 32));
      digit.setPosition(21, 512);
      window.draw(digit);
      digit.setTextureRect(sf::IntRect(((tens)*21), 0, 21, 32));
      digit.setPosition(42, 512);
      window.draw(digit);
      digit.setTextureRect(sf::IntRect(((ones)*21), 0, 21, 32));
      digit.setPosition(63, 512);
      window.draw(digit);
    }

    window.draw(Restart);
    window.draw(Debugger);
    window.draw(Test1);
    window.draw(Test2);
    window.draw(Test3);
    window.display();
  }

  return 0;
}
