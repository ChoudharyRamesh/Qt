@echo off
cd "C:\mycode\OPENGL\SceneGraphGL3\Shaders"
IF EXIST shader.vert.qsb ( del shader.vert.qsb )
IF EXIST shader.frag.qsb ( del shader.frag.qsb )
qsb --glsl "100 es,120,150" --hlsl 50 --msl 12 -o shader.vert.qsb vertex.vert
qsb --glsl "100 es,120,150" --hlsl 50 --msl 12 -o shader.frag.qsb fragment.frag
