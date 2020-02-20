# From the command-line

**Visual Studio IDE** or **Build Tools for Visual Studio** required. Open *x64 Native Tools Command Prompt for VS 20nn*.  

Debug:
```
msbuild lukusana.sln -t:Build -p:Configuration=Debug;Platform=x64
```

Release:
```
msbuild lukusana.sln -t:Build -p:Configuration=Release;Platform=x64
```
