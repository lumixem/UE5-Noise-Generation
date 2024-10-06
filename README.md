A project through which I'm exploring the structure of Unreal Engine 5, its rendering pipeline, and how to extend it.

I make use of the SceneViewExtension class, custom engine subsystem and a compute shader. 

- `FNoiseGenerationModule` is responsible for mapping the custom shader source directory to the engine
- `FNoiseGenSceneViewExtension` inherits from `FSceneViewExtensionBase`, intializes and adds the renderpass and subscribes it to the PostProcessingPass. See `GenerateNoise()` in NoiseGenSceneViewExtension.cpp
- `UNoiseGenerationSubsystem` is responsible for initializing the `FNoiseGenSceneViewExtension` SVE
- Shader creation happens in NoiseGenerationShaders.h & .cpp

The noise generation is based on [The Book of Shaders](https://thebookofshaders.com/11/)

It currently displays simple 2D noise from The Book of Shaders. I am planning to improve the noise generation, adding more variations (Perlin, White, Blue) and animating it.
![image](https://github.com/lumixem/UE5-Noise-Generation/assets/78048342/f99a8d5f-f06a-4891-9798-1876fc800cc7)

Sources:
- [Using SceneViewExtension to Extend the Rendering System](https://dev.epicgames.com/community/learning/knowledge-base/0ql6/unreal-engine-using-sceneviewextension-to-extend-the-rendering-system)
- [Render-Dependency-Graph-Documentation](https://github.com/staticJPL/Render-Dependency-Graph-Documentation)
- [Rendering Dependency Graph](https://mcro.de/c/rdg)

