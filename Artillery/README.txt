Lab 12 : Artillery
Howitzer, Projectile

------Times------
Ticket 1: 3:00

We are pulling in SOME of the files provided by the lab download, namely the following:
- howitzer.h
- testHowitzer.h
- testProjectile.h
- projectile.h
- projectile.cpp
- uiDraw.cpp
- uiDraw.h
- uiInteract.cpp
- uiInteract.h

We never made a physics file, and many of the tests and things in howitzer and projectile ask for methods that we don't have
or that must be renamed/given aliases.

David's compile command:
g++ *.cpp -o main.exe -lfreeglut -lopengl32 -lglu32
I had to include freeglut.dll to get this to run properly for my setup