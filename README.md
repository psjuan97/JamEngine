# JamEngine
Engine using SDL 

## Aplicaciones recomendadas 
```
TILED https://www.mapeditor.org/
PPSSPP https://www.ppsspp.org/
El puto Gimp https://www.gimp.org/
```



## Dependencies

```
libtmx
SDL2
SDl2_IMAGE
SDL2_TTF
BOX2D
TinyXml2
```


## Compile

```
mkdir build && cd build
cmake .. 
make -j4 
```

## Notas
el audio tendra que estar en formato wav, para que pese menos sera MONO, sampleado a 22khz y usara 8 bits. Desde linux se puede convertir usando este comando
```
ffmpeg -i in.mp3 -acodec pcm_u8 -ac 2 -ar 22000 out.wav
```

En el tiled el "Formato de la capa de patrones puede ser base64 sin comprimir" y el "Orden de pintado del patron" tiene que ser de Derecha Abajo
<br>
Algunas texturas si son muy grandes no se cargan en la psp, una de 790 * 430 no carga, por ejemplo.


