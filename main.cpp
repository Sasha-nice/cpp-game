#include "common.h"
#include "Image.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define GLFW_DLL
#include <unistd.h>
#include <GLFW/glfw3.h>
#include <string>
#include <ctime>

std::vector<std::vector<int>> map, full;
std::vector<int> vec, vec_full;
std::vector<int> sokr;

struct InputState
{
  bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
  GLfloat lastX = 400, lastY = 300; //исходное положение мыши
  bool firstMouse = true;
  bool captureMouse = true;  // Мышка захвачена нашим приложением или нет?
  bool capturedMouseJustNow = false;
} static Input;


GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


void OnKeyboardPressed(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		break;
  case GLFW_KEY_1:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    break;
  case GLFW_KEY_2:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    break;
	default:
		if (action == GLFW_PRESS)
      Input.keys[key] = true;
		else if (action == GLFW_RELEASE)
      Input.keys[key] = false;
	}
}

void processPlayerMovement(Player &player, std::vector<std::vector<int>> map)
{
  if (Input.keys[GLFW_KEY_W])
    player.ProcessInput(MovementDir::DOWN, map);
  else if (Input.keys[GLFW_KEY_S])
    player.ProcessInput(MovementDir::UP, map);
  if (Input.keys[GLFW_KEY_A])
    player.ProcessInput(MovementDir::LEFT, map);
  else if (Input.keys[GLFW_KEY_D])
    player.ProcessInput(MovementDir::RIGHT, map);
}

void OnMouseButtonClicked(GLFWwindow* window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    Input.captureMouse = !Input.captureMouse;

  if (Input.captureMouse)
  {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    Input.capturedMouseJustNow = true;
  }
  else
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}

void OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
  if (Input.firstMouse)
  {
    Input.lastX = float(xpos);
    Input.lastY = float(ypos);
    Input.firstMouse = false;
  }

  GLfloat xoffset = float(xpos) - Input.lastX;
  GLfloat yoffset = Input.lastY - float(ypos);

  Input.lastX = float(xpos);
  Input.lastY = float(ypos);
}


void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
  // ...
}


int initGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Controls: "<< std::endl;
    std::cout << "press right mouse button to capture/release mouse cursor  "<< std::endl;
    std::cout << "W, A, S, D - movement  "<< std::endl;
    std::cout << "press ESC to exit" << std::endl;
    return 0;
}
void DrawMap(Image &screenBuffer, Image &cur, int num) {
    std::string s;
    int i, j;
    i = num / 4;
    j = num % 4;
    if (full[i][j] == 1) s = "../resources/typea.txt";
    if (full[i][j] == 2) s = "../resources/typeb.txt";
    if (full[i][j] == 3) s = "../resources/typec.txt";
    if (full[i][j] == 4) s = "../resources/typed.txt";
    if (full[i][j] == 5) s = "../resources/typee.txt";
    if (full[i][j] == 6) s = "../resources/typef.txt";
    if (full[i][j] == 7) s = "../resources/typeq.txt";
    std::ifstream F(s);
    for (int i = 0; i < 1024; i += 32) {
        for (int j = 0; j < 1024; j += 32) {
            char a;
            F >> a;
            if (a == '.') {
                screenBuffer.drawTile(Image("../resources/test.png"), j, i);
                cur.drawTile(Image("../resources/test.png"), j, i);
                vec.push_back(1);
            } else if (a == '@'){
                vec.push_back(2);
                screenBuffer.drawTile(Image("../resources/ground.png"), j, i);
                cur.drawTile(Image("../resources/ground.png"), j, i);
            } else if (a == 'D') {
                vec.push_back(3);
                screenBuffer.drawTile(Image("../resources/door.png"), j, i);
                cur.drawTile(Image("../resources/door.png"), j, i);
            } else if (a == 'T') {
                if (sokr[num] == 1) {
                    vec.push_back(4);
                    screenBuffer.drawTile(Image("../resources/treasure.png"), j, i);
                    cur.drawTile(Image("../resources/treasure.png"), j, i);
                } else {
                    vec.push_back(1);
                    screenBuffer.drawTile(Image("../resources/test.png"), j, i);
                    cur.drawTile(Image("../resources/test.png"), j, i);
                }
            } else if (a == 'P') {
                vec.push_back(5);
                screenBuffer.drawTile(Image("../resources/Prize.png"), j, i);
                cur.drawTile(Image("../resources/Prize.png"), j, i);
            }
            else if (a == 'R') {
                vec.push_back(6);
                screenBuffer.drawTile(Image("../resources/end.png"), j, i);
                cur.drawTile(Image("../resources/end.png"), j, i);
            } else if(a == 'I') {
                vec.push_back(7);
                screenBuffer.drawTile(Image("../resources/test.png"), j, i);
                cur.drawTile(Image("../resources/test.png"), j, i);
            }
        }
        map.push_back(vec);
        vec.clear();
    }
}
bool f = true;
int CheckM(std::vector<std::vector<int>> map) {
    for (int i = 0; i < 32; i++) {
        for(int j = 0; j < 32; j++) {
            if (map[i][j] == 4) {
                return i * 32 + j;
            }
        }
    }
    return 0;
}
int kol_sokr() {
    int s = 0;
    for (auto i : sokr) {
        s += (1 - i);
    }
    return s;
}
int main(int argc, char** argv)
{
	if(!glfwInit())
    return -1;
    bool fade = false;
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow*  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "task1 base project", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback        (window, OnKeyboardPressed);
	glfwSetCursorPosCallback  (window, OnMouseMove); 
    glfwSetMouseButtonCallback(window, OnMouseButtonClicked);
	glfwSetScrollCallback     (window, OnMouseScroll);
	if(initGL() != 0)
		return -1;
  //Reset any OpenGL errors which could be present for some reason
	GLenum gl_error = glGetError();
	while (gl_error != GL_NO_ERROR)
		gl_error = glGetError();
	Point starting_pos{.x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 2};
	Point startt{.x = 100, .y = 100};
	Player player{starting_pos};
    Player enemy{startt};
	Image img("../resources/tex.png");
	Image screenBuffer(WINDOW_WIDTH, WINDOW_HEIGHT, 4);
    Image cur(WINDOW_WIDTH, WINDOW_HEIGHT, 4);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);  GL_CHECK_ERRORS;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL_CHECK_ERRORS;
    std::ifstream B("../resources/full.txt");
    int kol = 0;
    std::string s;
    while(getline(B, s)){
        for(auto a : s) {
            kol++;
            if (a == 'A') vec_full.push_back(1);
            if (a == 'B') vec_full.push_back(2);
            if (a == 'C') vec_full.push_back(3);
            if (a == 'D') vec_full.push_back(4);
            if (a == 'E') vec_full.push_back(5);
            if (a == 'F') vec_full.push_back(6);
            if (a == 'Q') vec_full.push_back(7);
        }
        full.push_back(vec_full);
        vec_full.clear();
    }
    for(int i = 0; i < kol; i++) {
        sokr.push_back(1);
    }
    for (auto i:full) {
        for (auto j : i) {
            //std::cout << j;
        }
        //std::cout << std::endl;
    }
    DrawMap(screenBuffer, cur, 0);
    int old_room_num = 0;
    int room_num = 0;
    int start = clock();
    //game loop
    int stx;
    int sty;
    for(int i = 0; i < 32; i++) {
        for(int j = 0; j < 32; j++) {
            if (map[i][j] == 7) {
                    stx = i * 32;
                    sty = j * 32;
            }
        }
    }
    player.Spawn(sty, stx);
    int hp_start = clock();
    enemy.Set(1);
    int kolw;
    int tim = 0;
    int fl = 0;
    int end;
    bool inv = false;
    enemy.Spawn1((24 * 32), 16 * 32, 96, 1);
	while (!glfwWindowShouldClose(window)) {
	    int hp_end = clock();
	    if (hp_end - hp_start > 1000000) {
	        player.hp -=1;
	        hp_start = hp_end;
	    }
	    if (player.CheckHP()) {
            screenBuffer.drawTile1(Image("../resources/gameover.png"));
            glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());
            GL_CHECK_ERRORS;

            glfwSwapBuffers(window);
            sleep(2);

            break;
	    }
        Image sr1(WINDOW_WIDTH, WINDOW_HEIGHT, 4);
        sr1.Copy(screenBuffer);
        while (Input.keys[GLFW_KEY_I]) {
            if(kol_sokr() == 0) screenBuffer.drawTile1(Image("../resources/inv0.png"));
            if(kol_sokr() == 1) screenBuffer.drawTile1(Image("../resources/inv1.png"));
            if(kol_sokr() == 2) screenBuffer.drawTile1(Image("../resources/inv2.png"));
            if(kol_sokr() == 3) screenBuffer.drawTile1(Image("../resources/inv3.png"));
            if(kol_sokr() == 4) screenBuffer.drawTile1(Image("../resources/inv4.png"));
            if(kol_sokr() == 5) screenBuffer.drawTile1(Image("../resources/inv5.png"));
            if(kol_sokr() == 6) screenBuffer.drawTile1(Image("../resources/inv6.png"));
            if(kol_sokr() == 7) screenBuffer.drawTile1(Image("../resources/inv7.png"));
            if(kol_sokr() == 8) screenBuffer.drawTile1(Image("../resources/inv8.png"));
            if(kol_sokr() == 9) screenBuffer.drawTile1(Image("../resources/inv9.png"));
            if(kol_sokr() == 10) screenBuffer.drawTile1(Image("../resources/inv10.png"));
            if(kol_sokr() == 11) screenBuffer.drawTile1(Image("../resources/inv11.png"));
            if(kol_sokr() == 12) screenBuffer.drawTile1(Image("../resources/inv12.png"));
            if(kol_sokr() == 13) screenBuffer.drawTile1(Image("../resources/inv13.png"));
            if(kol_sokr() == 14) screenBuffer.drawTile1(Image("../resources/inv14.png"));
            if(kol_sokr() == 15) screenBuffer.drawTile1(Image("../resources/inv15.png"));
            if(kol_sokr() == 16) screenBuffer.drawTile1(Image("../resources/inv16.png"));
            if(kol_sokr() == 17) screenBuffer.drawTile1(Image("../resources/inv17.png"));
            if(kol_sokr() == 18) screenBuffer.drawTile1(Image("../resources/inv18.png"));
            if(kol_sokr() == 19) screenBuffer.drawTile1(Image("../resources/inv19.png"));
            if(kol_sokr() == 20) screenBuffer.drawTile1(Image("../resources/inv20.png"));
            glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());
            GL_CHECK_ERRORS;
            glfwSwapBuffers(window);
            inv = true;
            glfwPollEvents();
        }
        if (inv) {
            screenBuffer.Copy(sr1);
            inv = false;
        }

        enemy.Ins(1, 1);
        Image tr("../resources/enemy.png");
        enemy.Draw1(screenBuffer, cur, tr);
        if(player.CheckEn(enemy)) {
            screenBuffer.drawTile1(Image("../resources/gameover.png"));
            glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());
            GL_CHECK_ERRORS;

            glfwSwapBuffers(window);
            sleep(2);

            break;
        };
            kolw = CheckM(map);
            end = clock();
            tim = (end - start) / 100000;
            if (tim >= 1 and sokr[room_num] == 1) {
                start = end;
                if (fl == 1) {
                    cur.drawTile(Image("../resources/Prize1.png"), (kolw % 32) * 32,
                                 (kolw / 32) * 32);
                    screenBuffer.drawTile(Image("../resources/Prize1.png"), (kolw % 32) * 32,
                                          (kolw / 32) * 32);
                    Image ch("../resources/3434.png");
                    player.Draw(screenBuffer, cur, ch);
                    fl = 0;
                } else {
                    cur.drawTile(Image("../resources/Prize2.png"), (kolw % 32) * 32, (kolw / 32) * 32);
                    screenBuffer.drawTile(Image("../resources/Prize2.png"), (kolw % 32) * 32,
                                          (kolw / 32) * 32);
                    Image ch("../resources/3434.png");
                    player.Draw(screenBuffer, cur, ch);
                    fl = 1;
                }
            }
            room_num = player.Check(map, full, room_num);
            if (old_room_num != room_num) {
                map.clear();
                float u = 0.95;
                for(int i = 0; i < 10; i++) {
                    screenBuffer.Fade(u);
                    glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());
                    GL_CHECK_ERRORS;
                    glfwSwapBuffers(window);
                    sleep(0.2);
                    u -= 0.05;
                    fade = true;
                }
                screenBuffer.Fade(0);
                glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());
                GL_CHECK_ERRORS;
                glfwSwapBuffers(window);
                DrawMap(screenBuffer, cur, room_num);
                if (old_room_num + 4 == room_num) {
                    for (int i = 0; i < tileSize; i++) {
                        if (map[1][i] == 3) {
                            player.Spawn(i * 32, 70);
                        }
                    }
                }
                if (old_room_num + 1 == room_num) {
                    for (int i = 0; i < tileSize; i++) {
                        if (map[i][1] == 3) {
                            player.Spawn(70, i * 32);
                        }
                    }
                }
                if (old_room_num - 1 == room_num) {
                    for (int i = 0; i < tileSize; i++) {
                        if (map[i][30] == 3) {
                            player.Spawn(1024 - 106, i * 32);
                        }
                    }
                }
                if (old_room_num - 4 == room_num) {
                    for (int i = 0; i < tileSize; i++) {
                        if (map[30][i] == 3) {
                            player.Spawn(i * 32, 1024 - 106);
                        }
                    }
                }
                if(full[room_num / 4][room_num % 4] == 1) {
                    enemy.Spawn1(300, 300, 64, 1);
                }
                if(full[room_num / 4][room_num % 4] == 2) {
                    enemy.Set(1);
                    enemy.Spawn1(21 * 32, 14 * 32, 288, 0);
                }
                if(full[room_num / 4][room_num % 4] == 3) {
                    enemy.Set(1);
                    enemy.Spawn1(20 * 32, 10 * 32, 320, 0);
                }
                if(full[room_num / 4][room_num % 4] == 4) {
                    enemy.Set(1);
                    enemy.Spawn1(320, 288, 64, 1);
                }
                if(full[room_num / 4][room_num % 4] == 5) {
                    enemy.Set(1);
                    enemy.Spawn1(7 * 32, 14 * 32, 64, 1);
                }
                if(full[room_num / 4][room_num % 4] == 6) {
                    enemy.Set(1);
                    enemy.Spawn1(20 * 32, 28 * 32, 160, 0);
                }
                if(full[room_num / 4][room_num % 4] == 7) {
                    enemy.Spawn1(12 * 32, 28 * 32, 64, 1);
                }
                old_room_num = room_num;
            }
            if (player.CheckT(map) == 1 and sokr[room_num] == 1) {
                map[player.CoordY() / 32][player.CoordX() / 32] = 1;
                cur.drawTile(Image("../resources/test.png"), (player.CoordX() / 32) * 32, (player.CoordY() / 32) * 32);
                screenBuffer.drawTile(Image("../resources/test.png"), (player.CoordX() / 32) * 32,
                                      (player.CoordY() / 32) * 32);
                Image ch("../resources/3434.png");
                player.Draw(screenBuffer, cur, ch);
                sokr[room_num] = 0;
                player.hp = 32;
            } else if (player.CheckT(map) == 2 and sokr[room_num] == 1) {
                map[player.CoordY() / 32][player.CoordX() / 32] = 1;
                cur.drawTile(Image("../resources/test.png"), (player.CoordX() / 32) * 32,
                             (player.CoordY() / 32 + 1) * 32);
                screenBuffer.drawTile(Image("../resources/test.png"), (player.CoordX() / 32) * 32,
                                      (player.CoordY() / 32 + 1) * 32);
                Image ch("../resources/3434.png");
                player.Draw(screenBuffer, cur, ch);
                sokr[room_num] = 0;
                player.hp = 32;
            } else if (player.CheckT(map) == 3 and sokr[room_num] == 1) {
                map[player.CoordY() / 32][player.CoordX() / 32] = 1;
                cur.drawTile(Image("../resources/test.png"), (player.CoordX() / 32 + 1) * 32,
                             (player.CoordY() / 32) * 32);
                screenBuffer.drawTile(Image("../resources/test.png"), (player.CoordX() / 32 + 1) * 32,
                                      (player.CoordY() / 32) * 32);
                Image ch("../resources/3434.png");
                player.Draw(screenBuffer, cur, ch);
                sokr[room_num] = 0;
                player.hp = 32;
            } else if (player.CheckT(map) == 4 and sokr[room_num] == 1) {

                map[player.CoordY() / 32][player.CoordX() / 32] = 1;
                cur.drawTile(Image("../resources/test.png"), (player.CoordX() / 32 + 1) * 32,
                             (player.CoordY() / 32 + 1) * 32);
                screenBuffer.drawTile(Image("../resources/test.png"), (player.CoordX() / 32 + 1) * 32,
                                      (player.CoordY() / 32 + 1) * 32);
                Image ch("../resources/3434.png");
                player.Draw(screenBuffer, cur, ch);
                sokr[room_num] = 0;
                player.hp = 32;
            }
            if (player.CheckP(map)) {
                screenBuffer.drawTile1(Image("../resources/victory.png"));
                glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());
                GL_CHECK_ERRORS;

                glfwSwapBuffers(window);
                sleep(2);

                break;
            }
            if (player.CheckE(map)) {
                screenBuffer.drawTile1(Image("../resources/gameover.png"));
                glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());
                GL_CHECK_ERRORS;

                glfwSwapBuffers(window);
                sleep(2);

                break;

            }
            GLfloat currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            glfwPollEvents();

            processPlayerMovement(player, map);
            Image ch("../resources/3434.png");
            player.Draw(screenBuffer, cur, ch);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            GL_CHECK_ERRORS;
            glRasterPos2f(-1, 1);
            glPixelZoom(1, -1);
            if(!fade) {
                glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());
                GL_CHECK_ERRORS;

                glfwSwapBuffers(window);
            } else {

                int t = 10;
                Image sr(WINDOW_WIDTH, WINDOW_HEIGHT, 4);
                sr.Copy(screenBuffer);
                float l = 0.1;
                for (int i = 10; i > 0; i--) {
                    screenBuffer.Copy(sr);

                    screenBuffer.Fade(l);
                    l += 0.09;

                    sleep(0.2);
                    glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());
                    GL_CHECK_ERRORS;

                    glfwSwapBuffers(window);
                }
                screenBuffer.Copy(sr);
                glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data());
                GL_CHECK_ERRORS;

                glfwSwapBuffers(window);
                fade = false;
            }

    }
	glfwTerminate();
	return 0;
}
