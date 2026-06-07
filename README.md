# 數位生態模擬器
## 文化大學 物件導向程式設計小專題
.
### 小組資料 & 分工
---
- **系級班級**：資訊工程學系1A
- **組別**：第10組
- **組長**：孫承志 
- **組員**：程千俊、阮平綠
---
- 孫承志：測試
- 程千俊：Github編輯、程式設計、邏輯整合、UML圖/報告撰寫、核心架構
- 阮平綠：無

### 遊戲介紹
---
- 本專題是一個用 C++ 製作的生態模擬器。玩家可以觀察植物、兔子和狼在地圖中的變化。植物會吸收資源成長，兔子會吃植物，狼會捕食兔子。系統會依照每一回合模擬生物的移動、繁殖、死亡與資源變化，讓使用者了解生態平衡的概念。

### 遊戲規則
---
- 遊戲以回合制進行，每一回合代表一天。系統會先更新水、陽光和養分等資源，接著植物會吸收資源成長並繁殖；兔子會移動並吃植物；狼會移動並捕食兔子。當生物能量不足或生命值歸零時就會死亡，能量足夠時則會繁殖。玩家可以透過地圖和統計資料觀察族群數量與生態平衡的變化。

### 遊戲玩法
---
- 玩家進入系統後，可以透過選單查看地圖、查看統計資料、模擬一天或連續模擬多天。遊戲中不需要直接控制每一隻生物，而是觀察植物、兔子與狼在每一回合中的自動行動。玩家可以新增不同生物，並透過族群數量、資源變化和地圖分布，判斷生態系統是否穩定。

### 遊戲執行 & 安裝方式
---
- 本專題使用 C++ 開發，不需要安裝額外圖形套件。下載專案後，接著在專案資料夾中開啟終端機，使用 g++ 或 clang++ 進行編譯。編譯完成後執行程式，即可進入 EcoSim 生態模擬器的選單畫面。
- 可以附上這段指令：g++ -std=c++17 main.cpp Entity.cpp Organism.cpp Plant.cpp Animal.cpp Resource.cpp World.cpp -o ecosim
./ecosim
- Mac 也可以使用：clang++ -std=c++17 main.cpp Entity.cpp Organism.cpp Plant.cpp Animal.cpp Resource.cpp World.cpp -o ecosim
./ecosim
- windows測試失敗可按以下步驟:
1.確定路徑沒有中文名
2.下載MSYS2，打開MSYS2 UCRT64輸入pacman -Syu，關掉重開輸入pacman -S mingw-w64-ucrt-x86_64-gcc
3.環境變數path加入C:\msys64\ucrt64\bin
4.開啟檔案後終端機輸入g++ -std=c++17 -finput-charset=UTF-8 -fexec-charset=BIG5 main.cpp Entity.cpp Organism.cpp Plant.cpp Animal.cpp Resource.cpp World.cpp -o ecosim.exe
5.再輸入.\ecosim.exe

### 遊戲畫面截圖
---
- **詳細遊戲介紹請參照短片：** https://youtu.be/IDd1wrXnkI8

---
- **顯示地圖 UI**

![遊戲畫面截圖](images/1.png)

- **顯示回合統計**

![遊戲畫面截圖](images/2.png)


- **顯示資源平均狀態**

![遊戲畫面截圖](images/3.png)

- **模擬一天**

![遊戲畫面截圖](images/4.png)

- **連續模擬 N 天**

![遊戲畫面截圖](images/5-1.png)

- **新增植物 Grass**

![遊戲畫面截圖](images/6.png)

- **新增兔子 Rabbit**

![遊戲畫面截圖](images/7.png)

- **新增狼 Wolf**

![遊戲畫面截圖](images/8.png)

- **連續模擬 N 天**

![遊戲畫面截圖](images/5-2.png)

- **重新初始化世界**

![遊戲畫面截圖](images/9.png)

- **離開**

---

- **UML圖**
（images/UML.png）


![遊戲畫面截圖](images/0.png)
