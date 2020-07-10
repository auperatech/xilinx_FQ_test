# Xilinx_FQ_test
Test Repo to test Xilinx's Face Quality Model

**Dependencies**

- Xilinx AI SDK v2.0 +
- Boost Library v1.68
- OpenCV 3.3 +

## How to compile?

Please cross compile this program in your SDK environment by running

```
make -j
```

## How to run?

In your previous step you create the executable `face_quality`. you need to copy this to your target board and then run the following command:

```
./face_quality <input_root_dir> <#_of_threads>
```
