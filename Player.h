#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Image.h"
#include <vector>
struct Point
{
  int x;
  int y;
};

enum class MovementDir
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct Player
{
  explicit Player(Point pos = {.x = 10, .y = 10}) :
                 coords(pos), old_coords(coords) {};
  int CoordX();
  int CoordY();
  bool Moved() const;
  void ProcessInput(MovementDir dir, std::vector<std::vector<int>> map);
  void Draw(Image &screen, Image &cur, Image &character);
  void Draw1(Image &screen, Image &cur, Image &enem);
  void Ins(int x, int y);
  bool CheckP(std::vector<std::vector<int>> map);
  bool CheckE(std::vector<std::vector<int>> map);
  bool CheckEn(Player enemy);
  int CheckT(std::vector<std::vector<int>> map);
  int Set(int f);
  void Get(int room_num);
  int Check(std::vector<std::vector<int>>,std::vector<std::vector<int>> full, int room_num);
  void Spawn(int x, int y);
  void Spawn1(int x, int y, int dist, int napr);
  bool CheckHP();
  int hp = 32;
private:
  Point coords {.x = 10, .y = 10};
  Point old_coords {.x = 10, .y = 10};
  Pixel color {.r = 255, .g = 255, .b = 0, .a = 255};
  Pixel color1 {.r = 0, .g = 255, .b = 0, .a = 255};
  Pixel color2 {.r = 0, .g = 0, .b = 0, .a = 255};
  int move_speed = 4;
  int f;
  int dist;
  int enemy_dist;
  int enemy_napr;

};

#endif //MAIN_PLAYER_H
