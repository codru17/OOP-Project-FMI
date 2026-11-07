# Notițe proiect game2d (jurnal de lucru cu Claude)

Rezumatul tuturor explicațiilor, deciziilor și stadiului proiectului.
Ultima actualizare: 2026-11-07.

---

## 0. Despre proiect

- **Ce:** game engine 2D simplist (platformer) în C++17, pentru proiectul de POO (anul 2 CTI).
- **Unde:** `~/.oop/OOP-Project-FMI/game2d`, repo GitHub `codru17/OOP-Project-FMI`, push direct pe `main`.
- **A înlocuit** proiectul spitalului, mutat în `~/hospital-management` (istoricul lui rămâne în git).
- **Librărie:** SFML 3.0.2 (grafică, fereastră, input, audio), descărcată automat de CMake (FetchContent), legată static.
- **Toolchain:** GCC 16.2 (WinLibs MinGW), CMake 4.4, Ninja.

### Reguli de lucru
- Claude **nu scrie cod** pentru proiect. Explică pașii, clasele, metodele și tipurile de date, apoi verifică ce scriu eu.
- La fiecare clasă: tipul fiecărui membru, tipul returnat și tipul parametrilor fiecărei metode.
- Claude rulează singur doar comenzi de verificare (citire, `g++ -fsyntax-only`) și le afișează explicate. Comenzile care schimbă ceva (build, commit, push) le rulez eu.
- Regula de arhitectură: **`engine/` nu include niciodată nimic din `game/`.**

### Comenzi uzuale (Git Bash)
```bash
cd ~/.oop/OOP-Project-FMI/game2d                        # go into the project
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug   # configure (first time only; downloads SFML)
cmake --build build                                     # compile + link
./build/game2d                                          # run the game
cd ~/.oop/OOP-Project-FMI && git add game2d && git commit -m "..." && git pull --rebase && git push origin main   # save to GitHub
```

### Structura folderelor
| Folder | Conținut |
|---|---|
| `include/engine`, `src/engine` | engine-ul reutilizabil (Game, Input, Entity...) |
| `include/game`, `src/game` | platformer-ul (Player, Platform, ...) |
| `assets/textures, fonts, sounds, levels` | resurse, copiate lângă .exe la build |
| `docs/` | UML, notițe |

---

## Planul

| Pas | Ce | Stare |
|---|---|---|
| 0 | Setup CMake + SFML 3 | ✅ |
| 1 | `Game`: fereastră + buclă cu pas fix | ✅ |
| 2 | `Input`: down / pressed / released | ✅ (commit `3a6aadd`) |
| 3 | `Entity` + `Player` + `Platform`: moștenire, polimorfism | **în lucru** |
| 4 | Fizică + coliziuni (+ debug overlay opțional) | |
| 5 | Scene + niveluri din fișiere text (grilă de caractere) | |
| 6 | Resurse (texturi, fonturi, sunete) | |
| 7 | Jocul propriu-zis | |
| 8 | UML + README | |
| 9 | **Opțional, dacă e timp:** editor de niveluri „nivel 2” cu Dear ImGui (ImGui-SFML): mod F1, click pe grilă pentru a pune sau șterge dale, paletă de dale, Save/Load în fișierul de nivel. Extra: Command pentru undo, State pentru Play/Edit, Factory pentru dale | |

---

## Pasul 1: clasa `Game`

### Câmpuri (`Game.h`)
| Câmp | Tip | Rol |
|---|---|---|
| `WIDTH`, `HEIGHT` | `static constexpr unsigned int` (1280, 720) | dimensiunea ferestrei; unsigned pentru că SFML folosește `sf::Vector2u` |
| `FRAMERATE_LIMIT` | `static constexpr unsigned int` (144) | FPS maxim la desenare |
| `TIME_STEP` | `static constexpr float` (1/60) | durata unui update; `1.0f / 60.0f`, pentru că `1/60` între întregi = 0 |
| `MAX_FRAME_TIME` | `static constexpr float` (0.25) | plafon anti-îngheț („spiral of death”) |
| `TITLE` | `static constexpr const char*` | titlul; `const` se referă la caractere (read-only), `constexpr` la pointer |
| `m_window` | `sf::RenderWindow` | fereastra; construită în lista de inițializare; necopiabilă, deci și `Game` e necopiabil |
| `m_clock` | `sf::Clock` | cronometru; `restart()` dă timpul scurs și repornește |
| `m_input` | `Input` | input-ul (compoziție, pasul 2) |
| `m_accumulator` | `float` | timp real încă nesimulat |
| `m_updateCount`, `m_debugTime` | `int`, `float` | debug: update-uri pe secundă |

- `static` = aparține clasei; `constexpr` = cunoscut la compilare și constant. Constantele evită „magic numbers”.
- Copierea e interzisă cu `= delete` (constructor de copiere + `operator=`).
- RAII + Rule of Zero: fereastra se închide singură în destructorul ei.
- Membrii se construiesc în ordinea declarării și se distrug în ordine inversă (`-Wreorder`).

### Metode
| Metodă | Tip | Acces | Rol |
|---|---|---|---|
| constructor | – | public | creează fereastra (`sf::VideoMode(sf::Vector2u{W,H})`, titlu), FPS limit, `setKeyRepeatEnabled(false)` |
| `run()` | `void` | public | bucla principală |
| `processEvents()` | `void` | private | golește coada de evenimente |
| `update(float dt)` | `void` | private | un pas de logică de 1/60 s |
| `render()` | `void` | private | `clear(culoare)` → `draw`... → `display()` |

### `run()`: bucla cu pas fix (fixed timestep + accumulator)
1. cât timp `isOpen()`:
2. `processEvents()`
3. `frameTime` = `m_clock.restart().asSeconds()`
4. `frameTime` = `std::min(frameTime, MAX_FRAME_TIME)`
5. `m_accumulator += frameTime`
6. **cât timp** `m_accumulator >= TIME_STEP`: `update(TIME_STEP)`; `m_accumulator -= TIME_STEP`
7. `render()` o dată

- Un cadru poate avea 0, 1 sau 2+ update-uri; în medie exact 60/s pe orice PC.
- `update(TIME_STEP)` = „simulează următoarele 16,67 ms din lume”. `dt` e fix, deci fizica e identică pe orice PC și nu „sare prin podea” la cadre lente.
- Analogie: update = camera care filmează la 60 fps; render = proiectorul care arată ultima imagine cât de des poate.
- Articol: „Fix Your Timestep!” – Glenn Fiedler.

### `update(dt)`
debug counter (adună `dt`, numără, la ≥ 1 s afișează și scade 1.0) → logica jocului (de la pasul 3: `update` pe fiecare entitate) → **`m_input.endStep()` ultimul**.

### `render()`
`clear` șterge cadrul vechi; `display` arată back buffer-ul (double buffering). `render` nu modifică starea jocului.

### `processEvents()`
- `while (auto event = m_window.pollEvent())`: `pollEvent()` returnează `std::optional<sf::Event>` (cutie plină sau goală); bucla golește **toată** coada în fiecare cadru.
- Dacă nu golești coada, Windows marchează fereastra „Not Responding”.
- primul rând: `m_input.handleEvent(*event)` (`*` scoate evenimentul din optional);
- `Closed` → `close()`; `KeyPressed` cu `code == Escape` → `close()`. `close()` nu oprește programul, doar face `isOpen()` false.

### `main.cpp`: `try` / `catch`
- Excepție = o funcție aruncă (`throw`) un obiect-eroare; execuția urcă prin apelanți (**stack unwinding**), distrugând variabilele locale (RAII), până la un `catch` potrivit.
- `catch (const std::exception& e)`: prinde orice excepție derivată (polimorfism); prin **referință** ca să nu apară **slicing**, iar `what()` (virtuală) dă mesajul exact; `const` pentru că doar citim.
- `catch (...)` prinde orice altceva; se pune ultimul. Ordinea e de la specific la general.
- Fără `try`, o excepție neprinsă → `std::terminate()`.
- `EXIT_FAILURE`/`EXIT_SUCCESS` din `<cstdlib>`; `std::cerr` e nebufferizat.
- `Game().run()` = obiect temporar. La o variabilă: fără `()` după nume (**most vexing parse**).

### SFML 3 vs SFML 2 (capcane)
- `VideoMode` primește **un** `sf::Vector2u`, nu două numere.
- `pollEvent()` fără parametri, returnează `std::optional`; nu există `event.type`.
- `is<T>()`, `getIf<T>()`; tastele sunt `sf::Keyboard::Key::Escape` (enum class).
- `sf::FloatRect` se construiește din doi vectori (poziție, mărime).
- Documentație: sfml-dev.org → Tutorials **3.0** + Migration Guide.

---

## Pasul 2: clasa `Input`

### Problema
Jocul are nevoie de 3 întrebări: **ținută** (`isDown`, mers), **tocmai apăsată** (`isPressed`, săritură), **tocmai eliberată** (`isReleased`, săritură variabilă). La fel ca `GetKey`/`GetKeyDown`/`GetKeyUp` din Unity.

### Ideea: două „fotografii”
| `m_current` | `m_previous` | Înseamnă |
|---|---|---|
| true | false | tocmai apăsată |
| true | true | ținută |
| false | true | tocmai eliberată |
| false | false | liberă |

### `Input.h`
| Membru | Tip | Acces |
|---|---|---|
| `KEY_COUNT` | `static constexpr std::size_t` = `sf::Keyboard::KeyCount` | private |
| `m_current`, `m_previous` | `std::array<bool, KEY_COUNT>` = `{}` (toate false) | private |
| `handleEvent` | `void (const sf::Event&)` | public |
| `endStep` | `void ()` | public |
| `isDown`, `isPressed`, `isReleased` | `bool (sf::Keyboard::Key) const` | public |
| `toIndex` | `static std::size_t (sf::Keyboard::Key)` | private |
| `isValid` | `static bool (sf::Keyboard::Key)` | private |

- Include `<SFML/Window.hpp>`, nu Graphics: Input nu desenează.
- `std::array`: se copiază cu `=`, are `fill()`. `std::size_t` = tipul pentru indici și dimensiuni.
- `const` după metodă = nu modifică obiectul (const-correctness); `static` = nu folosește date ale obiectului.
- Tipurile mici (enum, int, float) se trimit prin valoare; obiectele prin `const&`.
- `toIndex`/`isValid` sunt private: detalii de implementare (încapsulare, interfață publică minimă).

### `Input.cpp`
- `toIndex`: `static_cast<std::size_t>` (enum class nu se convertește singur).
- `isValid`: tasta ≠ `Key::Unknown` **și** index < `KEY_COUNT`. `Unknown` = −1, care convertit la size_t devine uriaș → acces în afara tabloului = comportament nedefinit. Contează ordinea (short-circuit `&&`).
- `isDown`/`isPressed`/`isReleased`: întâi `isValid`, apoi compară cele două tablouri.
- `endStep`: `m_previous = m_current`.
- `handleEvent`: `getIf<KeyPressed>` → true; `else if getIf<KeyReleased>` → false; `else if is<FocusLost>` → `m_current.fill(false)`.

### Explicații suplimentare (întrebări puse)
- **`FocusLost`**: la Alt+Tab, `KeyReleased` merge la alt program, iar tasta ar rămâne „jos” (stuck key). `fill(false)` resetează; `m_previous` neatins → `isReleased` apare o dată, ca la o eliberare normală.
- **`code`**: câmp din `sf::Event::KeyPressed`/`KeyReleased`, de tip `sf::Keyboard::Key`, adică tasta după layout. Structura mai are `scancode` (poziția fizică; contează la WASD pe AZERTY), `alt`, `control`, `shift`, `system`.
- **`is<T>()` vs `getIf<T>()`**: `is` → `bool` („e de tipul T?”), când nu ai nevoie de date (`Closed`, `FocusLost`). `getIf` → `const T*` sau `nullptr`, când citești date (`code`). Verifici `nullptr` înainte de `->`. `is` + `getIf` pe același tip = verificare dublă inutilă.
- **Spre ce arată pointerul din `getIf`**: spre structura `KeyPressed` din **interiorul** obiectului `event` (SFML ține evenimentul într-un `std::variant`). Nu copiază nimic, e `const`, și e valid doar cât trăiește `event` (o iterație). Nu se salvează; altfel devine dangling pointer.
- **`.` vs `->`**: `->` pe pointer sau `std::optional`; `.` pe obiect sau referință. `*` pe optional dă conținutul.

### Legătura cu `Game`
- `Input m_input` în `Game` = **compoziție** (has-a, romb plin în UML).
- `handleEvent(*event)` primul în bucla de evenimente; `endStep()` **ultimul** în `update`.
- `endStep` după fiecare **update**, nu după fiecare cadru: altfel 2 update-uri într-un cadru ar da `isPressed` de două ori (săritură dublă).
- Limitare: o atingere < 1/60 s între două update-uri se pierde.

### Concepte POO / C++ din pasul 2
Încapsulare, abstractizare, Single Responsibility, compoziție, const-correctness, metode statice, `std::array`, `std::size_t`, enum class + `static_cast`, if cu inițializator (C++17), pointer vs referință, short-circuit.

---

## Engine-ul nostru vs Unity / Unreal
- **La fel:** game loop cu pas fix (`FixedUpdate`), input (`GetKeyDown`), entități (`GameObject`), fizică/coliziuni, scene, resurse, randare.
- **Diferit:** fără editor vizual, doar 2D, SFML face partea de jos (OpenGL), moștenire clasică în loc de ECS, o singură platformă.
- Descriere corectă la prezentare: „engine 2D minimal, structurat pe aceleași sisteme ca motoarele comerciale, plus un platformer construit peste el”. Mai apropiat de MonoGame decât de Unity.

---

## Pasul 3: entitățile (în lucru)

### Ideea
Clasă de bază **abstractă** `Entity` (engine/) cu ce e comun; derivate `Player`, `Platform` (game/) care suprascriu `update`/`draw`. `Game` ține `std::vector<std::unique_ptr<Entity>>` și apelează `update`/`draw` pe toate. Alegerea versiunii se face **la rulare** (vtable) = **polimorfism**.

### `Entity` (`include/engine/Entity.h`, `src/engine/Entity.cpp`)
| Membru / metodă | Tip | Acces |
|---|---|---|
| `m_position` | `sf::Vector2f` (stânga-sus, px; y crește în jos) | private |
| `m_size` | `sf::Vector2f` | private |
| `m_velocity` | `sf::Vector2f` (px/s), implicit (0,0) | private |
| constructor | `(sf::Vector2f position, sf::Vector2f size)` | **protected** |
| destructor | **`virtual`**, `= default` | public |
| copiere / `operator=` | `= delete` (evită slicing) | public |
| `update` | `virtual void (float dt) = 0` | public |
| `draw` | `virtual void (sf::RenderTarget& target) const = 0` | public |
| `getPosition`, `getSize`, `getVelocity` | `sf::Vector2f () const` | public |
| `getBounds` | `sf::FloatRect () const` (pentru coliziuni, pasul 4) | public |
| `setPosition`, `setVelocity` | `void (sf::Vector2f)` | public |

- `= 0` → clasă abstractă, care nu poate fi instanțiată; derivatele sunt obligate să implementeze.
- Destructor virtual: obligatoriu când ștergi prin pointer la bază (altfel UB).
- `sf::RenderTarget&`: `RenderWindow` derivă din el (polimorfism în SFML).

### `Platform` (`game/`)
`sf::RectangleShape m_shape` (private); constructor `(sf::Vector2f position, sf::Vector2f size)`, care apelează întâi `Entity(...)` în lista de inițializare, apoi configurează forma (`setSize`, `setPosition`, `setFillColor`); `update(float) override` gol, cu parametru fără nume (evită warning-ul unused); `draw(...) const override` → `target.draw(m_shape)`. Pune mereu `override`.

### `Player` (`game/`)
| Membru | Tip |
|---|---|
| `MOVE_SPEED` | `static constexpr float` = 300 (px/s) |
| `SIZE` | `static constexpr float` = 48 |
| `m_input` | **`const Input&`**: dependency injection, inițializată obligatoriu în lista de inițializare |
| `m_shape` | `sf::RectangleShape` |
| constructor | `(sf::Vector2f position, const Input& input)` |

`update(dt)`: direcție = −1 (stânga/A), +1 (dreapta/D) → `setVelocity({dir * MOVE_SPEED, 0})` → poziție += viteză × dt → sincronizezi `m_shape` **aici** (pentru că `draw` e `const`). `draw` doar desenează.

### Modificări în `Game`
- `std::vector<std::unique_ptr<Entity>> m_entities`, declarat **după** `m_input` (distrugere în ordine inversă). Include `<memory>`, `<vector>`.
- Pointeri pentru că: bază abstractă, mărimi diferite, polimorfismul cere pointer sau referință. `unique_ptr` = proprietar unic, RAII, nu se copiază, doar se mută.
- `void addEntity(std::unique_ptr<Entity> entity)` (prin valoare = preia proprietatea; `std::move` în vector, din `<utility>`).
- `const Input& getInput() const`.
- `update`: range-for cu `auto&` (unique_ptr nu se copiază) → `->update(dt)`, înainte de `endStep`. `render`: `->draw(m_window)` între `clear` și `display`.
- `main.cpp`: variabilă `Game game;` (fără `()`), `addEntity(std::make_unique<Platform>(...))` pentru podea și 2–3 platforme, `addEntity(std::make_unique<Player>(poz, game.getInput()))`, apoi `run()`.

### Ordine de lucru
Entity.h → Entity.cpp → Platform → Game (container, addEntity, getInput, bucle) → main cu platforme (rulezi) → Player (rulezi).

### Teste
Platforme vizibile; jucătorul se mișcă lin cu ←/→; se oprește imediat; ← și → deodată = stă pe loc; Alt+Tab fără stuck key; cu `FRAMERATE_LIMIT` 30 aceeași viteză.

### Concepte noi
Clasă abstractă, virtuale pure, polimorfism la rulare (vtable), `override`, destructor virtual, slicing, `protected`, constructorul bazei în lista de inițializare, referință membru, dependency injection, `unique_ptr`, `make_unique`, move semantics, ordinea de distrugere a membrilor.

---

## Întrebări probabile la prezentare
- De ce pas fix și nu `dt` variabil?
- De ce `Input` are două tablouri? De ce `endStep` după fiecare update?
- De ce `isValid` (Key::Unknown = −1)? De ce `FocusLost`?
- De ce prindem excepțiile prin `const&`?
- De ce destructor virtual? Ce e object slicing?
- De ce `unique_ptr` în vector și nu obiecte?
- Compoziție vs moștenire: unde le folosim (Game has-a Input; Player is-a Entity).
- Ce e most vexing parse?
