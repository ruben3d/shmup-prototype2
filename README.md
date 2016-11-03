# shmup-prototype2

This project is a proof of concept for a retro-styled shoot 'em up game, featuring modern per-pixel lighting and real-time color grading restricted to a 320x200 pixels resolution.

Each tile and sprite requires these maps:
- Diffuse color
- Specular
- Height
- Emission
- Normal (derived from the height map)

<img src="https://raw.githubusercontent.com/ruben3d/shmup-prototype2/master/doc/tiles-color.png" />
<img src="https://raw.githubusercontent.com/ruben3d/shmup-prototype2/master/doc/tiles-specular.png" />
<img src="https://raw.githubusercontent.com/ruben3d/shmup-prototype2/master/doc/tiles-height.png" />
<img src="https://raw.githubusercontent.com/ruben3d/shmup-prototype2/master/doc/tiles-emission.png" />

## Screenshots

[<img src="https://raw.githubusercontent.com/ruben3d/shmup-prototype2/master/doc/ss01.png" width="320" height="200" />](https://raw.githubusercontent.com/ruben3d/shmup-prototype2/master/doc/ss01.png)
[<img src="https://raw.githubusercontent.com/ruben3d/shmup-prototype2/master/doc/ss02.png" width="320" height="200" />](https://raw.githubusercontent.com/ruben3d/shmup-prototype2/master/doc/ss02.png)
[<img src="https://raw.githubusercontent.com/ruben3d/shmup-prototype2/master/doc/ss03.png" width="320" height="200" />](https://raw.githubusercontent.com/ruben3d/shmup-prototype2/master/doc/ss03.png)
[<img src="https://raw.githubusercontent.com/ruben3d/shmup-prototype2/master/doc/ss04.png" width="320" height="200" />](https://raw.githubusercontent.com/ruben3d/shmup-prototype2/master/doc/ss04.png)
[<img src="https://raw.githubusercontent.com/ruben3d/shmup-prototype2/master/doc/ss05.png" width="320" height="200" />](https://raw.githubusercontent.com/ruben3d/shmup-prototype2/master/doc/ss05.png)

## Build & Execute

The project requires SFML.

```
$ git clone https://github.com/ruben3d/shmup-prototype2.git
$ cd shmup-prototype2
$ mkdir build
$ cd build
$ cmake ../
$ make
$ cd bin && ./shmup && cd ..
```

## License

MIT License (see LICENSE in the repository).
