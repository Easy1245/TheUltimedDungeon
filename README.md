🏰 UltimateDungeon
----------------------
Een moderne C++ dungeon crawler gebouwd met C++17 en Qt Widgets. Verken kamers, versla vijanden, verzamel items en vind uiteindelijk de treasure om het spel te winnen.

Dit project werd ontwikkeld als school-/examenopdracht, met nadruk op Object-Oriented Programming, C++‑features, en Qt‑integratie.

🎮 Gameplay
- Start een New Game met een eigen naam

- Navigeer door kamers via genummerde uitgangen

- Verzamel items met take

- Vecht tegen vijanden met fight

- Versla eindbazen

- Vind en pak de treasure om te winnen

- Autosave via Qt QTimer (elke 15 seconden)

🧱 Architectuur & OOP
Klassenoverzicht
Game – centrale game‑flow en logica

Room – kamers met verbindingen, items, vijanden en treasure

Player – stats, inventory en acties

Enemy (abstract) – basis vijandklasse

Monster – concrete vijand (polymorfisme)

DungeonBuilder – genereert de volledige dungeon

SaveManager – save/load via file I/O

MainWindow – Qt GUI (widgets, signals/slots)

🧠 OOP‑Concepten
Encapsulation – private members + getters/setters

Inheritance – Monster erft van Enemy

Polymorphism – virtuele functies (attack(), takeDamage())

Abstract Base Class – Enemy bevat pure virtuals

Composition – Room bevat items, treasure en vijanden

Constructor forwarding & initializer lists

Copy constructors & destructors

⚙️ Gebruikte C++ Features
std::vector, std::unique_ptr

std::string

std::fstream voor save/load

std::exception + try/catch

std::thread / std::atomic (eerste autosave‑versie)

Qt QTimer (definitieve autosave)

Lambda’s

Const‑correctheid

Namespaces

Dynamisch geheugenbeheer

Templates (utility functies)

🖥️ GUI (Qt Widgets)
Ontwikkeld met Qt Creator

.ui‑bestanden (Qt Designer)

signals & slots

QMainWindow

QTextEdit voor game‑output

QLineEdit voor command input

QPushButton voor New Game / Continue

💾 Save System
Autosave elke 15 seconden

Handmatig opslaan bij afsluiten

Opgeslagen data:

Spelernaam

Health / Damage / Defense

Inventory

Current Room ID

🏆 Winconditie
Je wint wanneer je de treasure in de eindkamer opraapt (take).

📁 Projectstructuur

ultimateDungeon/
│── DungeonBuilder.*
│── Enemy.*
│── Monster.*
│── Player.*
│── Room.*
│── Game.*
│── SaveManager.*
│── Utils.h
│── main.cpp
│── mainwindow.*
│── mainwindow.ui
│── ultimateDungeon.pro


---

## 📌 Status

✔ Project compileert  
✔ Project crasht niet  
✔ Volledig speelbaar  
✔ OOP & C++ vereisten behaald  
✔ Qt GUI geïntegreerd  

---

## 👤 Auteur

- **Naam:** Jonas Vanmarsenille
- **Opleiding:** Elektronica ICT
- **Jaar:** 2025

---

🎉 **Veel speelplezier in UltimateDungeon!**
