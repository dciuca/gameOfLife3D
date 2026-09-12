```mermaid
classDiagram
    direction LR

    class GameLoop
    class Grid
    class PatternLibrary
    class InputHandler
    class Renderer
    class Config

    GameLoop --> Grid
    GameLoop --> Renderer
    GameLoop --> PatternLibrary
    GameLoop --> InputHandler
    GameLoop --> Config
    Config --> PatternLibrary
    PatternLibrary --> Grid
    Renderer --> Grid
```

%% === Proposed SOLID architecture decoupled from raylib ===

```mermaid
classDiagram
    direction TB

    class GameLoop
    class IRenderer {
        <<interface>>
    }
    class IInputHandler {
        <<interface>>
    }
    class CameraState
    class Grid
    class PatternLibrary
    class Config
    class RaylibRenderer
    class RaylibInputHandler
    %%class raylib

    GameLoop --> IRenderer
    GameLoop --> IInputHandler
    GameLoop --> Config
    GameLoop --> Grid

    RaylibRenderer ..|> IRenderer
    RaylibInputHandler ..|> IInputHandler

    RaylibRenderer --> Grid
    RaylibRenderer --> CameraState
    %%RaylibRenderer --> raylib

    RaylibInputHandler --> CameraState
    %%RaylibInputHandler --> raylib

    IRenderer --> CameraState
    IInputHandler --> CameraState

    Config --> PatternLibrary
    PatternLibrary --> Grid
```