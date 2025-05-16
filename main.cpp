#include <crow.h>
#include <chrono>
#include <iostream>
#include <thread>
#include "src/Game/Game.h"

int main() {
  // 创建游戏实例
  Game game;

  // 创建Crow应用
  crow::SimpleApp app;

  // 设置静态文件服务
  CROW_ROUTE(app, "/")
  ([]() {
    auto page = crow::mustache::load("index.html");
    return page.render();
  });

  // 添加静态文件服务
  CROW_ROUTE(app, "/js/<path>")
  ([](const std::string& path) {
    std::ifstream file("js/" + path);
    if (!file.is_open()) {
      return crow::response(404);
    }
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    return crow::response(content);
  });

  // API端点：获取游戏状态
  CROW_ROUTE(app, "/api/game-state")
  ([&game]() { return crow::response(game.getGameStateJson().dump()); });

  // API端点：更新游戏状态
  CROW_ROUTE(app, "/api/update")
  ([&game]() {
    game.update();
    return crow::response(200);
  });

// 使用系统默认浏览器打开网页
#ifdef _WIN32
  system("start http://localhost:8080");
#elif __APPLE__
  system("open http://localhost:8080");
#else
  system("xdg-open http://localhost:8080");
#endif

  // 启动服务器
  app.port(8080).multithreaded().run();

  return 0;
}