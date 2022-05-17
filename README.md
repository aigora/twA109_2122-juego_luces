# JUEGO DE LUCES

Un juego de velocidad y reflejo basado en una secuencia de luces aleatoria que el usuario debe seguir rápidamente.

### Modo de juego

Las luces roja, verde, azul y blanca se encenderán en orden aleatorio formando una secuencia, la cual tendrás que repetir mediante las teclas AWDS del ordenador. Si aciertas, ganarás puntos; si fallas, termina la partida.

Introduce tu nombre al inicio de la partida para que se guarden tus puntuaciones en un fichero.
Tambien es posible dar de baja a un jugador, ver la lista de jugadores y modificar un nombre.

#### Funcionamiento del Arduino

El programa de Arduino se encarga de generar la secuencia mediante un array de valores aleatorios (generados mediante la función random),
los cuales son enviados al ordenador. Más allá de esta acción, el código en Arduino se limita a seguir las "órdenes" enviadas desde el
ordenador; se comienza a ejecutar la función void loop() cuando se envía desde el ordenador la orden START, y una vez llegado al final
del bucle, se detiene hasta recibir la orden CONTINUAR.

En resumen, una vez generada y enviada la secuencia al ordenador, el Arduino se mantiene a la espera para recibir indicaciones, por lo
cual el juego se desarrolla esencialmente en el código fuente de C++ que se ejecuta en el ordenador, dependiendo del Arduino únicamente
para obtener la secuencia original de luces que el jugador repetirá en el teclado.
Las puntuaciones, así como el comienzo y final de partida, tienen lugar en el programa de C++.

## Integrantes del equipo

Celia Torrecillas (Celia-t22)

Qingyun Xu (QINGYUN-XU)

Amélie Nader Prieto (amelie-nader-prieto)

## Objetivos del trabajo

Programar con los conocimientos de informática obtenidos en clase.

Conocer lo más básico y fundamental de Arduino y ser capaces de desarrollar un programa en C++ que comparta datos con el Arduino de forma fluida y funcional.
