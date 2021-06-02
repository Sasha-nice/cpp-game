#include "Player.h"
#include <iostream>

bool Player::Moved() const
{
  if(coords.x == old_coords.x && coords.y == old_coords.y)
    return false;
  else
    return true;
}

void Player::ProcessInput(MovementDir dir, std::vector<std::vector<int>> map)
{
  int move_dist = move_speed * 1;
  switch(dir)
  {
    case MovementDir::UP:
      old_coords.y = coords.y;
      for(int i = 0; i < move_dist; i++) {
          if (map[(coords.y + 32) / 32][coords.x / 32] != 2 and map[(coords.y + 32) / 32][(coords.x + 31) / 32] != 2) {
              coords.y++;
          }
      }
      //coords.y += move_dist;
      break;
    case MovementDir::DOWN:
      old_coords.y = coords.y;
      for(int i = 0; i < move_dist; i++) {
          if (map[(coords.y - 1) / 32][coords.x / 32] != 2 and map[(coords.y - 1) / 32][(coords.x + 31) / 32] != 2) {
              if(coords.y < 40)
              std::cout << coords.x << coords.y << std::endl;
              coords.y--;
          }
      }
      break;
    case MovementDir::LEFT:
      old_coords.x = coords.x;
      for(int i = 0; i < move_dist; i++) {
          if (map[(coords.y) / 32][(coords.x - 1)/ 32] != 2 and map[(coords.y + 31) / 32][(coords.x - 1) / 32] != 2) {
              coords.x--;
          }
      }
      break;
    case MovementDir::RIGHT:
      old_coords.x = coords.x;
      for(int i = 0; i < move_dist; i++) {
          if (map[(coords.y + 1) / 32][(coords.x + 32)/ 32] != 2 and map[(coords.y + 31) / 32][(coords.x + 32) / 32] != 2) {
              coords.x++;
          }
      }
      break;
    default:
      break;
  }
}
int Player::CoordX() {
    return coords.x;
}
int Player::CoordY() {
    return coords.y;
}

void Player::Get(int room_num){
    std::cout << "num " << room_num << std::endl;
}
bool Player::CheckEn(Player enemy) {
    //std::cout << 123;
    int x = coords.x;
    int x1 = coords.x + 31;
    int y = coords.y;
    int y1 = coords.y + 31;
    int ex = enemy.coords.x;
    int ex1 = enemy.coords.x + 31;
    int ey = enemy.coords.y;
    int ey1 = enemy.coords.y + 31;
    if ((x >= ex and x <= ex1 and y <= ey1 and y >= ey) or  (x >= ex and x <= ex1 and y1 <= ey1 and y1 >= ey) or (x1 >= ex and x1 <= ex1 and y <= ey1 and y >= ey) or (x1 >= ex and x1 <= ex1 and y1 <= ey1 and y1 >= ey)) {
        return true;
        std::cout << 123;
    }
    return false;

}
bool Player::CheckP(std::vector<std::vector<int>> map) {
    if (map[coords.y / 32][coords.x / 32] == 5 or map[(coords.y + 31) / 32][coords.x / 32] == 5 or
        map[coords.y / 32][(coords.x + 31) / 32] == 5 or map[(coords.y + 31)/ 32][(coords.x + 31)/ 32] == 5) {
        return true;
    }
    return false;
}
bool Player::CheckE(std::vector<std::vector<int>> map) {
    if (map[coords.y / 32][coords.x / 32] == 6 or map[(coords.y + 31) / 32][coords.x / 32] == 6 or
        map[coords.y / 32][(coords.x + 31)/ 32] == 6 or map[(coords.y + 31)/ 32][(coords.x + 31)/ 32] == 6) {
        return true;
    }
    return false;
}

int Player::CheckT(std::vector<std::vector<int>> map) {

    if (map[coords.y / 32][coords.x / 32] == 4) {
        return 1;
    } else if(map[coords.y / 32 + 1][coords.x / 32] == 4) {
        return 2;
    } else if (map[coords.y / 32][coords.x / 32 + 1] == 4) {
        return 3;
    } else if (map[coords.y / 32 + 1][coords.x / 32 + 1] == 4) {
        return 4;
    }
    return 0;
}
int Player::Check(std::vector<std::vector<int>> map, std::vector<std::vector<int>> full, int room_num) {
    int i = room_num / 4;
    int j = room_num % 4;
    int room_type = full[i][j];
    if (room_type == 1) {
        if (map[coords.y / 32][coords.x / 32] == 3 or map[coords.y / 32 + 1][coords.x / 32] == 3 or
            map[coords.y / 32][coords.x / 32 + 1] == 3 or map[coords.y / 32 + 1][coords.x / 32 + 1] == 3) {
                //std::cout << "num:" << room_num;
                return room_num + 4;
        }
        return room_num;
    }
    if (room_type == 2) {
        if (map[coords.y / 32][coords.x / 32] == 3 or map[coords.y / 32 + 1][coords.x / 32] == 3 or
            map[coords.y / 32][coords.x / 32 + 1] == 3 or map[coords.y / 32 + 1][coords.x / 32 + 1] == 3) {
            if (coords.y < 512) {
                return room_num - 4;
            } else {
                return room_num + 4;
            }
        }
    }
    if (room_type == 3) {
        if (map[coords.y / 32][coords.x / 32] == 3 or map[coords.y / 32 + 1][coords.x / 32] == 3 or
            map[coords.y / 32][coords.x / 32 + 1] == 3 or map[coords.y / 32 + 1][coords.x / 32 + 1] == 3) {
            if (coords.y < 100) {
                return room_num - 4;
            } else if (coords.x > 800){
                return room_num + 1;
            }
        }
    }
    if (room_type == 4) {
        if (map[coords.y / 32][coords.x / 32] == 3 or map[coords.y / 32 + 1][coords.x / 32] == 3 or
            map[coords.y / 32][coords.x / 32 + 1] == 3 or map[coords.y / 32 + 1][coords.x / 32 + 1] == 3) {
            if (coords.y < 100) {
                return room_num - 4;
            } else if (coords.x > 800){
                return room_num + 1;
            } else if (coords.x < 200){
                return room_num - 1;
            }
        }
    }
    if (room_type == 5) {
        if (map[coords.y / 32][coords.x / 32] == 3 or map[coords.y / 32 + 1][coords.x / 32] == 3 or
            map[coords.y / 32][coords.x / 32 + 1] == 3 or map[coords.y / 32 + 1][coords.x / 32 + 1] == 3) {
            if (coords.y > 800) {
                return room_num - 4;
            } else if (coords.x > 800){
                return room_num + 1;
            }
        }
    }
    if (room_type == 6) {
        if (map[coords.y / 32][coords.x / 32] == 3 or map[coords.y / 32 + 1][coords.x / 32] == 3 or
            map[coords.y / 32][coords.x / 32 + 1] == 3 or map[coords.y / 32 + 1][coords.x / 32 + 1] == 3) {
            if (coords.y > 800) {
                return room_num + 4;
            } else if (coords.x < 200){
                return room_num - 1;
            }
        }
    }
    if (room_type == 7) {
        int r = 1;
    }
    return room_num;
}
void Player::Draw(Image &screen, Image &cur, Image &character)
{
  if(Moved())
  {
    for(int x = old_coords.x; x <= old_coords.x + 32; ++x)
    {
      for(int y = old_coords.y; y <= old_coords.y + 32; ++y)
      {
       screen.PutPixel(x, y, cur.GetPixel(x, y));
      }
    }
    old_coords = coords;
  }

  for(int y = coords.y + 4; y <= coords.y + 31; ++y)
  {
    for(int x = coords.x; x <= coords.x + tileSize; ++x)
    {
      screen.PutPixel(x, y, character.GetPixel(x - coords.x, y - coords.y));
    }
  }
    for(int y = coords.y; y <= coords.y + 4; ++y)
    {
        for(int x = coords.x; x <= coords.x + hp; ++x)
        {
            screen.PutPixel(x, y, color1);
        }
        for(int x = coords.x + hp + 1; x <= coords.x + tileSize; ++x)
        {
            screen.PutPixel(x, y, color2);
        }
    }
}
bool Player::CheckHP(){
    if (hp <= 0) return true;
    return false;
}
int Player::Set(int p) {
    f = p;
    dist = 0;
}
void Player::Ins(int x, int t) {
    if (enemy_napr == 1) {
       // std::cout << coords.y << " ";
        coords.y += t * f;
        //std::cout << coords.y << std::endl;
        dist += t;
        if (dist > enemy_dist) {
            f *= -1;
            dist = 0;
        }
    } else {
        coords.x += x * f;
        dist += x;
        if (dist > enemy_dist) {
            f *= -1;
            dist = 0;
        }
    }
}
void Player::Draw1(Image &screen, Image &cur, Image &enem)
{

    for(int x = old_coords.x; x <= old_coords.x + 32; ++x)
    {
        for(int y = old_coords.y; y <= old_coords.y + 32; ++y)
        {
            screen.PutPixel(x, y, cur.GetPixel(x, y));
        }
    }
        old_coords = coords;


    for(int y = coords.y; y <= coords.y + tileSize; ++y)
    {
        for(int x = coords.x; x <= coords.x + tileSize; ++x)
        {
            screen.PutPixel(x, y, enem.GetPixel(x - coords.x, y - coords.y));
        }
    }
}
void Player::Spawn(int x, int y) {
    old_coords.x = x;
    old_coords.y = y;
    coords.x = x;
    coords.y = y;
}
void Player::Spawn1(int x, int y, int dist, int napr) {
    old_coords.x = x;
    old_coords.y = y;
    coords.x = x;
    coords.y = y;
    enemy_dist = dist;
    enemy_napr = napr;
}