# Barn Boss

A console-based farm management simulation game written in C++. Players grow crops, raise animals, trade on a shared market, and complete tasks to earn points and climb the scoreboard. The system supports multiple user accounts, each progressing independently through their own game cycle.

---

## Project Structure

```
oop_project/
├── src/
│   └── main.cpp                  
├── engine/
│   ├── GameEngine.h/cpp       
│   ├── CommandExecutor.h/cpp     
│   ├── Command.h/cpp            
│   └── Serializer.h/cpp        
├── models/
│   ├── User.h/cpp              
│   ├── Player.h/cpp              
│   ├── MarketManager.h/cpp       
│   ├── TaskManager.h/cpp        
│   ├── Farm.h/cpp                
│   ├── Barn.h/cpp               
│   ├── Plant.h/cpp               
│   ├── Animal.h/cpp             
│   ├── Market.h/cpp              
│   ├── Product.h/cpp            
│   ├── Task.h/cpp              
│   ├── TaskBoard.h/cpp          
│   └── Scoreboard.h/cpp          
├── services/
│   ├── UserService.h/cpp         
│   ├── MarketService.h/cpp      
│   ├── TaskService.h/cpp         
│   └── FarmService.h/cpp         
└── utils/
    ├── Exceptions.h/cpp         
    ├── IDGenerator.h/cpp         
    ├── Validator.h/cpp           
    └── Utils.h/cpp               
```

## Game Cycle Mechanic

Time in the game is measured in **cycles**, tracked individually per Player. A cycle advances each time a Player successfully executes an action that changes the game state. If a command fails due to invalid input or unmet conditions, the cycle does not advance.

Every time the cycle advances, all plants and animals in that Player's farm grow by +1. Each Player's farm progresses at their own pace — a Player who runs more actions will have faster-maturing crops than one who has been idle.

---

## Farm 

### Plants

| ID | Buy as | Market Price | Required Cycles | Produces |
|----|--------|-------------|-----------------|----------|
| 1 | WheatSeed | 10 | 3 | 1 Wheat |
| 2 | CornSeed | 15 | 4 | 1 Corn |


### Animals

| ID | Buy as | Market Price | Required Cycles | Produces |
|----|--------|-------------|-----------------|----------|
| 3 | Chicken | 25 | 3 | 1 Egg |
| 4 | Cow | 50 | 5 | 1 Milk |

### Expanding the Farm

Both cropland and farmland start at a capacity of 3 slots. Expansion costs increase with the current capacity and also require a minimum Score:

```
Cost           = 50 × current capacity
Required Score = current capacity × 10
```

---

## Market

The market starts with the following stock:

| ID | Product | Qty | Price |
|----|---------|-----|-------|
| 1 | WheatSeed | 20 | 10 |
| 2 | CornSeed | 20 | 15 |
| 3 | Chicken | 10 | 25 |
| 4 | Cow | 5 | 50 |
| 5 | Wheat | 20 | 15 |
| 6 | Corn | 20 | 20 |
| 7 | Egg | 15 | 30 |
| 8 | Milk | 10 | 60 |

---

## Task Board

The task board starts with two default tasks:

| ID | Deliver | Reward |
|----|---------|--------|
| 1 | 5 Wheat | 50 Balance + 10 Score |
| 2 | 3 Milk | 120 Balance + 20 Score |

---

## Scoreboard

`showScoreboard` lists all Players ranked by:
1. Highest Score
2. If tied — highest Balance

---

## Save & Load

The game state is automatically written to `savefile.txt` when you type `exit`. 
To wipe all progress and restart while the game is running, use the `reset` command.

---

## Commands Reference

### No login required
| Command | Description |
|---------|-------------|
| `register <username> <password> <type>` | Register a new user (`Player` / `MarketManager` / `TaskManager`) |
| `login <username> <password>` | Log in |
| `reset` | Wipe all progress and restore defaults in-place |
| `exit` | Save state to file and quit |

### Any logged-in user
| Command | Description |
|---------|-------------|
| `logout` | End the current session |
| `profileInfo` | Show id, username, type, and stats |
| `changePassword <old> <new>` | Change your password (min 3 characters) |
| `openMarketCatalog` | Show all products with quantities and prices |
| `showTaskBoard` / `showTasks` | Show all active tasks |
| `showScoreboard` | Show Player rankings |

### Player only
| Command | Description |
|---------|-------------|
| `checkBalance` | Show current balance |
| `checkScore` | Show current score |
| `checkBarn` | Show all barn item quantities |
| `checkFarm` | Show farm slot usage and free slots |
| `buyItem <id> <qty>` | Buy from the market |
| `sellItem <id> <qty>` | Sell to the market |
| `sowPlant <seedId>` | Plant a seed from your barn (1=Wheat, 2=Corn) |
| `addAnimal <animalId>` | Move an animal to the farm (3=Chicken, 4=Cow) |
| `harvest` | Collect all ready produce |
| `expandCropland` | Increase plant slot capacity by 1 |
| `expandFarmland` | Increase animal slot capacity by 1 |
| `completeTask <id>` | Deliver required goods and collect the reward |

### MarketManager only
| Command | Description |
|---------|-------------|
| `restock <id> <qty>` | Add stock to a product |
| `changePrice <id> <newPrice>` | Change a product's price |

### TaskManager only
| Command | Description |
|---------|-------------|
| `addTask <product> <qty> <rewardBalance> <rewardScore>` | Post a new task |
| `removeTask <id>` | Remove a task from the board |

---

## Example Session

```
========================================
                BARN BOSS
========================================

> register Ivan 1234 Player
User registered successfully!

> register AdminMarket mkt123 MarketManager
User registered successfully!

> register AdminTasks task123 TaskManager
User registered successfully!

> login Ivan 1234
Welcome, Ivan!

> profileInfo
ID: 1
Username: Ivan
Type: Player
Balance: 100
Score: 0

> openMarketCatalog
=== MARKET CATALOG ===
1. WheatSeed | Qty: 20 | Price: 10
2. CornSeed  | Qty: 20 | Price: 15
3. Chicken   | Qty: 10 | Price: 25
4. Cow       | Qty: 5  | Price: 50
5. Wheat     | Qty: 20 | Price: 15
6. Corn      | Qty: 20 | Price: 20
7. Egg       | Qty: 15 | Price: 30
8. Milk      | Qty: 10 | Price: 60

> buyItem 1 2
The purchase was successful!

> buyItem 3 1
The purchase was successful!

> sowPlant 1
Plants planted successfully!

> sowPlant 1
Plants planted successfully!

> addAnimal 3
Animals added successfully!

> harvest
Harvest completed!

> checkBarn
=== BARN ===
WheatSeed: 0
CornSeed: 0
Chicken: 0
Cow: 0
Wheat: 1
Corn: 0
Egg: 0
Milk: 0

> showTaskBoard
=== TASK BOARD ===
1. Deliver 5 Wheat → Reward: 50 Balance, 10 Score
2. Deliver 3 Milk → Reward: 120 Balance, 20 Score

> showScoreboard
=== SCOREBOARD ===
1. Ivan | Score: 0 | Balance: 55

> logout
Logged out successfully!

> login AdminTasks task123
Welcome, AdminTasks!

> addTask Corn 4 80 15
Task added successfully!

> logout
Logged out successfully!

> exit
Game saved successfully. Goodbye!
```

---

## Example Savefile

`savefile.txt` is plain text. Each line starts with a tag that identifies what follows:

```
NEXT_ID 4
USER Player 1 Ivan 1234 55 0 9
BARN Wheat 1
FARMCAP 3 3
PLANT Wheat 2 3 Wheat
USER MarketManager 2 AdminMarket mkt123
USER TaskManager 3 AdminTasks task123
MARKET 1 WheatSeed 10 18
MARKET 2 CornSeed 15 20
MARKET 3 Chicken 25 9
MARKET 4 Cow 50 5
MARKET 5 Wheat 15 20
MARKET 6 Corn 20 20
MARKET 7 Egg 30 15
MARKET 8 Milk 60 10
TASK 1 Wheat 5 50 10
TASK 2 Milk 3 120 20
TASK 3 Corn 4 80 15
```
