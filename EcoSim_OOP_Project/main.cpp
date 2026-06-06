#include "World.h"
#include "Plant.h"
#include "Animal.h"
#include <iostream>
#include <limits>
#include <memory>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void showMenu() {
    std::cout << "\n========================================\n";
    std::cout << "        EcoSim 生態模擬器 OOP 專題\n";
    std::cout << "========================================\n";
    std::cout << "1. 顯示地圖 UI\n";
    std::cout << "2. 顯示回合統計\n";
    std::cout << "3. 顯示資源平均狀態\n";
    std::cout << "4. 模擬一天\n";
    std::cout << "5. 連續模擬 N 天\n";
    std::cout << "6. 新增植物 Grass\n";
    std::cout << "7. 新增兔子 Rabbit\n";
    std::cout << "8. 新增狼 Wolf\n";
    std::cout << "9. 重新初始化世界\n";
    std::cout << "0. 離開\n";
    std::cout << "請輸入選項：";
}

int main() {
    World world(20, 20);
    world.seedDefaultWorld();

    int choice = -1;
    while (choice != 0) {
        showMenu();
        if (!(std::cin >> choice)) {
            clearInput();
            std::cout << "輸入錯誤，請輸入數字。\n";
            continue;
        }

        if (choice == 1) {
            world.printMap();
        } else if (choice == 2) {
            world.printStatistics();
        } else if (choice == 3) {
            world.printResourcesSummary();
        } else if (choice == 4) {
            world.simulateTurn();
            world.printMap();
            world.printStatistics();
            world.printResourcesSummary();
        } else if (choice == 5) {
            int days;
            std::cout << "請輸入要模擬的天數：";
            std::cin >> days;
            if (days <= 0) {
                std::cout << "天數必須大於 0。\n";
                continue;
            }
            for (int i = 0; i < days; i++) {
                world.simulateTurn();
            }
            world.printMap();
            world.printStatistics();
            world.printResourcesSummary();
        } else if (choice == 6) {
            int x, y;
            std::cout << "輸入 x y 座標：";
            std::cin >> x >> y;
            if (world.isInside(x, y)) {
                world.addOrganism(std::make_shared<Plant>(x, y));
                std::cout << "已新增 Grass。\n";
            } else {
                std::cout << "座標超出地圖。\n";
            }
        } else if (choice == 7) {
            int x, y;
            std::cout << "輸入 x y 座標：";
            std::cin >> x >> y;
            if (world.isInside(x, y)) {
                world.addOrganism(std::make_shared<Animal>("Rabbit", x, y, false));
                std::cout << "已新增 Rabbit。\n";
            } else {
                std::cout << "座標超出地圖。\n";
            }
        } else if (choice == 8) {
            int x, y;
            std::cout << "輸入 x y 座標：";
            std::cin >> x >> y;
            if (world.isInside(x, y)) {
                world.addOrganism(std::make_shared<Animal>("Wolf", x, y, true));
                std::cout << "已新增 Wolf。\n";
            } else {
                std::cout << "座標超出地圖。\n";
            }
        } else if (choice == 9) {
            world = World(20, 20);
            world.seedDefaultWorld();
            std::cout << "世界已重新初始化。\n";
        } else if (choice == 0) {
            std::cout << "離開 EcoSim。\n";
        } else {
            std::cout << "沒有這個選項，請重新輸入。\n";
        }
    }

    return 0;
}
