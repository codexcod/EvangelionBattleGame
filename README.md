# :boom: EvangelionBattleGame Simulation :boom:


Corre el año 2050 y la humanidad se encuentra en peligro. El grupo Gohuer ubicado en Argentina ha estado
experimentando con la creación de robots biológicos, los Evitas. Tras varios experimentos ambiciosos y poco
controlados por la ERM (Ente Regulador de Mechas) la presencia de los Evitas ha llamado la atención de
unos devastadores seres alienígenas conocidos localmente como Ángeles. Todo comenzó cuando el grupo

Gohuer encontró en la Antártida un "Gigante blanco" yaciendo paralizado en un cráter de tamaño incon-
mensurable. Luego de investigaciones entendieron que ese ser almacenaba una energía capaz de destruir el

planeta en segundos. Sin embargo, el grupo fue un paso más allá y logro despertar al Gigante controlán-
dolo de tal manera para que se reprodujera con el proceso de fisión binaria (similar a lo que ocurre con las

amebas). Del "Gigante Blanco", denominado Lilith, se originaron m Evitas. Pero en Gohuer jugaron a ser
Dios, y decidieron ir un paso más allá. Los primeros Evitas se salieron de control y lograron absorber parte
del "núcleo" de su padre lo que les dio la capacidad, no deseada, de reproducirse, como su progenitor, un
máximo de m veces (podrían ser menos).
Como si esto fuera poco esta situación atrajo a los denominados Ángeles al planeta tierra, que intentan
destruir a los Evitas y también tienen un mecanismo de reproducción similar en donde cada uno puede
engendrar n descendientes (al progenitor común se lo conoce como Adam).
En esta guerra de seres descontrolados los humanos han pasado a un segundo plano...

![image](https://user-images.githubusercontent.com/68394259/165647877-4eddd8da-b49f-4b5b-abdc-0e57e26b861e.png)


Figure 1: Representación caricaturizada de un evita

Pero no todo esta perdido. Al parecer existe la posibilidad de que ambas colonias de Evitas y Ángeles se
extingan peleando entre ellas y, con suerte, el planeta aún sea un lugar habitable para los humanos que
aguardan en refugios especialmente diseñados bajo tierra. Se sospecha que si el poder de ataque de ambas
colonias se iguala en algún momento, desde GOHUER pueden forzar un enfrentamiento que haría que ambas
especies se extingan.
El jefe máximo del grupo GOHUER, el señor Gentoo Ricardi, quiere realizar simulaciones por computadora
para poder descubrir si realmente existen chances no despreciables de que ocurra este escenario. Para eso,
luego de entender el comportamiento de reproducción de cada colonia, ha conseguido un modelo matemático
que le permitirá responder la pregunta ¿Cuál es el día más cercano que debería forzarse el enfrentamiento
entre las colonias?. A su vez, nuestra tarea consiste en realizar simulaciones basadas en este modelo, pero
con un agregado...

El modelo de Gentoo discretiza el tiempo en días. Para simular la evolución de cada comunidad a lo largo
del tiempo, asume que todo comienza desde los ancestros comunes, Adam y Lilith.
