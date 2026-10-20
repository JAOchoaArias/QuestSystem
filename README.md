# Quest System — Blueprint & C++

## Descripción del proyecto

Este proyecto implementa y compara dos sistemas de misiones en Unreal Engine: uno desarrollado utilizando **Blueprints** y otro implementado en **C++**.

Ambos sistemas cuentan con sus propios archivos y niveles, pero comparten la misma estructura de funcionamiento y las mismas mecánicas de juego, permitiendo probar y comparar sus implementaciones.

## Estructura del proyecto

Los archivos del proyecto se encuentran organizados dentro de la siguiente ruta:

`Content/Quest/`

Dentro de esta carpeta se encuentran dos directorios principales:

- **Blueprint:** contiene los archivos correspondientes al sistema de misiones desarrollado con Blueprints.
- **CPP:** contiene los archivos correspondientes al sistema de misiones desarrollado en C++.

Cada una de estas carpetas cuenta con una carpeta `Level`, que contiene su respectivo **Level Instance**, configurado para funcionar con el sistema de misiones correspondiente.

De esta manera, cada implementación dispone de su propio nivel de pruebas.

## Distribución del mapa

En ambas instancias, el jugador comienza en el centro del mapa. Desde allí, puede desplazarse hacia los cuatro puntos cardinales para encontrar diferentes gestores de misiones.

Cada dirección representa un tipo de misión distinto.

### Misión Collect — Derecha

Al desplazarse hacia la derecha, el jugador encontrará una caja blanca que representa al **Quest Giver** (gestor de misiones).

Al acercarse e interactuar con él mediante la tecla `E`, recibirá la misión de tipo **Collect**.

Esta misión cuenta con sus respectivos objetos recolectables, que el jugador deberá encontrar y recoger para cumplir el objetivo.

### Misión Kill — Arriba

Al desplazarse hacia arriba, el jugador encontrará el gestor de la misión **Kill**, junto con los enemigos correspondientes.

El objetivo consiste en derrotar a los enemigos requeridos para completar la misión.

El jugador puede atacar utilizando la tecla `F`.

### Misión Interact — Izquierda

Al desplazarse hacia la izquierda, el jugador encontrará el gestor de la misión **Interact**, acompañado de los objetos con los que deberá interactuar.

El objetivo consiste en localizar e interactuar con los elementos correspondientes utilizando la tecla `E`.

### Misión Reach Location — Abajo

Al desplazarse hacia abajo, el jugador encontrará el gestor de la misión **Reach Location**.

Más abajo se encuentra la zona que debe descubrir para completar el objetivo.

Esta zona se revela automáticamente cuando el jugador ingresa en ella y activa el evento de *overlap*. No es necesario interactuar manualmente con el área.

## Controles

Los controles son los mismos para ambas implementaciones, tanto en Blueprint como en C++.

| Acción | Control |
|---|---|
| Mover al personaje (cámara Top Down) | Clic izquierdo sobre el mapa |
| Interactuar con los gestores de misiones | `E` |
| Interactuar con objetos de la misión Interact | `E` |
| Atacar a los enemigos | `F` |
| Descubrir la zona de Reach Location | Automático al ingresar en el área (*Overlap*) |

## Objetivo

El propósito del proyecto es implementar y probar cuatro tipos de misiones —**Collect, Kill, Interact y Reach Location**— mediante dos enfoques diferentes de desarrollo en Unreal Engine: Blueprints y C++.

La separación en instancias independientes permite ejecutar y evaluar ambos sistemas utilizando el mismo diseño de mapa, los mismos tipos de objetivos y los mismos controles.
