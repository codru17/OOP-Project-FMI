# Hospital Management System

C++17 OOP project: management of patients, medical staff, appointments and departments in a hospital.

## Build

Requirements: g++ (C++17), CMake 3.14+.

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
./build/OOP-Project-FMI
```

## Structure

| Folder | Content |
|---|---|
| `include/model`, `src/model` | Domain classes (Pacient, Medic, Programare...) |
| `include/services`, `src/services` | Logic (Repository, Spital, FileManager) |
| `include/ui`, `src/ui` | Console / FTXUI interface |
| `data/` | CSV data files |
| `docs/` | UML diagrams |
