# 42-fractol -- A Multithreading Fractal Visualizing Tool

> *Fractals are my bread and butter.* - Abraham Lincoln

![title](https://imgur.com/tC2A8u5.png)

## Install

1. brew install libxext; brew install libx11; brew install libpng
2. git clone [this repo]
3. make

## Visualize fractals

- run ./fractol to see usage
- press [h] in application to see available options
- scrollwheel to zoom
- you can change the color with the mouse and the keys [f]/[g] to get almost any kind of visualization you want

![colormouse](https://media.giphy.com/media/DijSeD9kZIYikhtrfa/giphy.gif)![colorfreq](https://media.giphy.com/media/PSDBI8MhDieF9Sx1Mr/giphy.gif)

## Save as png and record as png image sequence

- press [n] to save a snapshot of the current frame
- images will be saved into a folder named "captures"
- sequences will be saved into their own folders inside captures: captures/[image sequence name]
- all of these folders will be created by the program
- the resolution of the image will be taken from the application window size
- to change the window size, edit `WIN_W` and `WIN_H` in includes/fractol.h (you can also change the amount of iterations for each fractal there)

## How to easily create a gif/mp4/etc from recorded image sequence

1. run fractol, press m and begin recording
2. exit using esc and locate image sequence folder
3. run `ffmpeg -framerate [desired framerate] -i captures/[sequence folder]/%03d [outputfile.gif/etc]` (this will create a large file, resize according to need)

![zoom](https://media.giphy.com/media/KBWLlW8sdv3qdwElTY/giphy.gif)

## How it is done

1. I split the whole frame into four rectangles, checking for each if the boundaries of that rectangle are of the same color (or iteration value)
2. if so, I fill the rectangle with the same color
3. if not, I repeat step 1 for each rectangle
> The reason why this works is that these fractals are simply connected, meaning that if a certain color forms a loop then the inside of that loop must be of the same color.
> It's math, don't fret about it
> 
Below you can see the multithreading in action.

![method](https://media.giphy.com/media/SQVUCleIAQt9gHFe3f/giphy.gif)
