cls 
g++ -D__int64=int64_t -L C:\cygwin64\lib -Wl,--kill-at -shared -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" Solver.cpp -o Solver.dll
