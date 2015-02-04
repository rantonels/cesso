# cesso
Cesso is a lightweight UCI chessboard program optimized for very small resolutions (320x240). It is designed to be used with a Raspberry Pi in analog video alongside a chess engine.

Cesso is still **early in development** and is not even remotely playable yet.

## How do you pronounce 'cesso'?
"Chess-oh". Avoid in conversation with Italian ladies you are interested in not offending.

## Dependencies

### SDL2, SDL2-image

If you're on **Debian/Ubuntu**, install SDL2 through repositories:

```
sudo apt-get install libsdl2-dev libsdl2-image-dev
```

For any **other desktop distribution**, check your package installer downloader repository thingie and ask if they got some sdl2.

On a **Raspberry Pi**, at the moment of writing, there are no official binary packages for SDL2. You can download binaries or compile SDL2 thanks to this handy script:

```
wget https://www.dropbox.com/s/mpai8q1hpoju9xz/SDL2_install.sh
sh ./SDL2_install.sh
```

## Compilation

*Difficulty: extremely hard*

```cd``` to the cesso folder and run

```
make
```

## Running instructions

If you're already in an X11 session, run

```
./cesso
```

if, instead, you're in a nongraphical tty and you want to start a single X session for cesso, you must do

```
xinit /full/path/to/cesso
```

and maybe add a ```-F``` flag for fullscreen.

To get the full list of options, run

```
./cesso -h
```
