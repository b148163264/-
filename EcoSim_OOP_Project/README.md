# EcoSim 生態模擬器

這是一個大學物件導向程式設計期末專題等級的 C++ Demo。

## 專案特色

- 使用 C++17
- 使用 OOP 設計
- 分離式檔案架構
- 使用 STL vector、shared_ptr
- 使用多型 `vector<shared_ptr<Organism>>`
- 使用 2D Grid 地圖
- 支援回合制模擬
- 支援植物、兔子、狼的簡易食物鏈
- 支援資源系統：水、陽光、養分
- 支援天氣系統：晴天、陰天、下雨、乾旱
- 支援統計資料：族群數量、平均能量、死亡數、新生數

## 編譯方式

### Mac / Linux

```bash
g++ -std=c++17 main.cpp Entity.cpp Organism.cpp Plant.cpp Animal.cpp Resource.cpp World.cpp -o ecosim
./ecosim
```

或使用 Makefile：

```bash
make run
```

### VS Code 建議

1. 開啟此資料夾。
2. 開啟終端機。
3. 輸入：

```bash
g++ -std=c++17 main.cpp Entity.cpp Organism.cpp Plant.cpp Animal.cpp Resource.cpp World.cpp -o ecosim
./ecosim
```

## 圖例

- `G`：Grass 植物
- `R`：Rabbit 兔子
- `W`：Wolf 狼
- `*`：同一格有多個生物
- `.`：空地

## OOP 概念

### Encapsulation 封裝

類別資料成員皆使用 private，透過 getter/setter 或公開函式操作。

### Inheritance 繼承

```text
Entity
  ↓
Organism
  ↓
Plant / Animal
```

### Polymorphism 多型

World 使用：

```cpp
std::vector<std::shared_ptr<Organism>> organisms;
```

並統一呼叫：

```cpp
organism->act(*this);
```

不同類別會執行不同版本的 act()。

## 建議報告展示方式

1. 先說明專案動機：想模擬自然界中資源、生物、捕食、繁殖造成的族群變化。
2. 展示 UML。
3. 展示檔案架構。
4. 展示 OOP 三大概念：封裝、繼承、多型。
5. 執行程式，展示地圖與統計數據。
6. 連續模擬 20 天，觀察族群變化。
