# DitherTick
Tick over 100.000 Actors without fps drop.
Will match FPS target which is set as 100.

Original idea from Micah: https://github.com/aggressivemastery/DitherActorTickExampleUE532

This version is written in C++ and utilizes hardware so it will tick and spawn actors as fast as possible until it can't do anything.
Current max is ticking over 139.000 Actors.

Would probably tick 250.000 Actors on 60 FPS. We will see :)

Oh and don't look at abomination of a file called "SpawnSubsystem_Scripted". It does put a shame to my name but it was written as Presentation.


