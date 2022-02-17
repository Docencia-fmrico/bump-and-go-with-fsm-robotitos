[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=6870054&assignment_repo_type=AssignmentRepo)
# fsm_bump_go

Primera Práctica del grupo **Robotitos** de Arquitectura Robótica Software.

## Autores:

* [Oriana Acosta Joaquim](o.acosta.2019@alumnos.urjc.es)
* [Jaime Avillera García](j.avilleira.2019@alumnos.urjc.es)
* [Juan Fernández Eva](j.fernandezev.2018@alumnos.urjc.es)
* [Francisco Gómez López](f.gomezl.2019@alumnos.urjc.es)

## Indice:
### 1. Introducción.
### 2. BumpGo Básico.
### 3. BumpGo Avanzado.
### 4. BumpGo Pro.

## 1.   Introducción.

Este proyecto consistirá en hacer uso del bumper y del laser del robot Kobuki para poder sortear obstáculos cuando los detecte. El proyecto se divide en 3 secciones: **BumpGo básico**, **BumpGo avanzado** y **BumpGo pro**. Este último se divide en 2, uno realizado sin herencia y otro con herencia.

El robot *Kobuki* se puede visualizar en esta imagen:
![KOBUKI](https://github.com/javilleira2019/sensoresactuadores2021-22/blob/master/kobuki.jpg)


## BumpGo Básico.

El robot kobuki deberá detectar si su *Bumper* ha sido presionado. y si es asi, girar a la izquierda para sortear el obstáculo.

## BumpGo Avanzado.

Al igual que en el básico, deberá detectar si su *Bumper* ha sido presionado. Dependiendo de donde se presione, girará en una dirección u otra (presionado a la derecha -> Giro a la izquierda y viceversa). Si es presionado en el centro, girará al igual que si se presiona a la derecha.

## BumpGo Pro.

El robot *Kobuki* junto al laser *rplidar* detectará si hay un objeto en su campo de rango. Si está a una distancia mínima, girará hacia el lado que este obstáculo no ha sido detectado.
