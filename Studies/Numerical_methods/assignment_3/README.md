IMPORTANTE: Se elimino la dependencia `eigen` de la carpeta principal para
evitar el antivirus de gmail, que lo marcaba como inseguro.

El codigo se puede compilar mediante `make`:
```
  $ make main
```

O mediante el ejecutable `compile` proporcionado por la catedra:
```
  $ ./compile.sh
```

El ejecutable `main` generado recibe los siguientes parametros:
```
  $ ./main <algorithm> <input file> <p> <niter> <eps>
```
  Donde `niter` y `eps` son parametros opcionales. El resto son obligatorios.