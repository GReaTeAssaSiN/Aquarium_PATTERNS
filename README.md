# Aquarium Ecosystem Simulator

Учебный проект по дисциплине «Распределённые системы» (Term 3, 2026–2027):
7 лабораторных работ по паттернам проектирования GoF, реализуемых на одном
общем, постепенно растущем 2D-приложении «аквариум». Каждая лаба добавляет
1–2 паттерна поверх кода предыдущих лаб, не ломая уже реализованный функционал.

## Стек

- C++17
- SFML 3 (Graphics/Window/System)
- CMake 3.20+
- macOS + VS Code (C/C++, CMake Tools)

## Сборка и запуск

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
./Aquarium
```

## Управление

| Клавиша | Действие |
|---|---|
| `B` | Переключить биом (Freshwater → Reef → DeepSea → по кругу) |
| `Space` | Заспавнить рыбу |
| `F` | Заспавнить еду |
| `W` | Заспавнить водоросль |
| `D` | Заспавнить декорацию (камень/ракушка) |

## Статус

### Лаба 1 — Abstract Factory ✅

`AquariumFactory` — абстрактная фабрика с методами `MakeFish`, `MakeFood`,
`MakeWeed`, `MakeDecoration`. Три конкретных семейства (биома):
`FreshwaterFactory`, `ReefFactory`, `DeepSeaFactory` — переключаются в
рантайме без пересборки (клавиша `B`). Четыре иерархии абстрактных продуктов:
`Fish`, `Food`, `Weed`, `Decoration`.

### Дальше по плану

2. Prototype + Singleton — фабрика как синглтон, клонирование существ
3. Builder + Factory Method — сборка отчётов о состоянии аквариума
4. Adapter — `StackAdapter`/`QueueAdapter` поверх `std::vector`/`std::list`
5. Composite — `Shoal` (стая) как составной `AquaticEntity`
6. Chain of Responsibility — цепочка решений рыбы (хищник → еда → флокинг)
7. Command — команды с undo/redo, `MacroCommand` для пресетов
