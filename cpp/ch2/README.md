Run tests: 

```bash
g++ tests.cpp tuple.cpp canvas.cpp -o test.out
./test.out

```

To run the virtual cannon:

```bash
g++ virtual_cannon_traced.cpp tuple.cpp canvas.cpp -o cannon.out
./cannon.out
convert flight_path.ppm flight_path.png
```

## Next Steps

1. Fix ambiguous references to vector.
1. Fix virtual_cannon_traced to be more modular
