#include <crow.h>
#include <chrono>
#include <iostream>
#include <thread>
#include "Game.h"

int main() {
  //创建游戏实例
  Game game;

  // 创建Crow应用
  crow::SimpleApp app;

  // 设置静态文件服务
  CROW_ROUTE(app, "/")
  ([]() { return crow::response(200, "ok"); });

  // API端点：获取游戏状态
  CROW_ROUTE(app, "/api/game-state")
  ([&game]() { return crow::response(game.getGameStateJson().dump()); });

  // 启动服务器
  app.port(8080).multithreaded().run();

  return 0;
}