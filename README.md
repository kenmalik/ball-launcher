
# Ball-Launcher

## Building

In order to build, navigate to the Ball-Launcher directory and run the following
commands:

```
mkdir build && cd build
cmake ../src && cmake --build .
```

Simply run the generated executable to play.

## Controls

### Color Selection

- R to select red
- G to select green
- B to select blue

### Loading

- E to load the selected color into the launcher

*The indicator will change color according to next color loaded in queue. If
there are no balls loaded, the indicator will be grey.

### Aiming

- Use left/right arrow keys to aim launcher

### Launching

- Space to launch

*If there are no balls loaded, you will recieve a stdout message saying the queue
is empty.

