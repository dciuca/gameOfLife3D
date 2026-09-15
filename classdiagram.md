
```mermaid
---
config:
  layout: elk
---
classDiagram
    direction LR

    class main

    class GameLoop {
        -ICamera m_camera
        -IRenderer m_renderer
        -IInputHandler m_inputHandler
    }
    class IRenderer {
        <<interface>>
    }
    class IInputHandler {
        <<interface>>
    }
    class ICamera {
        <<interface>>
        +yaw(float angle)
        +pitch(float angle)
        +zoom(float wheel)
    }

    class Grid
    class PatternLibrary
    class Config


    namespace Raylib {
        class RaylibRenderer
        class RaylibInputHandler
        class RaylibCamera
    }

    main *-- RaylibRenderer : composition root
    main *-- RaylibInputHandler : composition root
    main *-- RaylibCamera : composition root
    main *-- Grid : composition root
    main --> GameLoop : starts

    GameLoop --> IRenderer
    GameLoop --> IInputHandler
    GameLoop --> ICamera
    GameLoop --> Config
    GameLoop --> Grid

    RaylibRenderer ..|> IRenderer : implements
    RaylibInputHandler ..|> IInputHandler : implements
    RaylibCamera ..|> ICamera : implements

    RaylibRenderer --> Grid
    RaylibRenderer --> RaylibCamera: render3D
    RaylibInputHandler --> RaylibCamera: move cam

    IRenderer --> ICamera
    IInputHandler --> ICamera

    Config --> PatternLibrary
    PatternLibrary --> Grid

    classDef interface fill:#eef2ff,stroke:#818cf8,stroke-width:2px,color:#1e1b4b
    cssClass "IRenderer,IInputHandler,ICamera" interface
```