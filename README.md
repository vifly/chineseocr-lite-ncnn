# Requirements
- C++ compiler support C++ 14
- CMake (at least 3.19)
- OpenMP
- OpenCV
- [ncnn](https://github.com/Tencent/ncnn)
- [args-parser](https://github.com/igormironchik/args-parser)

# Build
If you doesn't install args-parser, run:
```Bash
git submodule update --init --recursive
```

```Bash
mkdir build && cd build
cmake ..
make 
```

# Run
```Bash
cd build
./chineseocr-ncnn -i ../test.jpg -l 600

# See usage
./chineseocr-ncnn -h
```

# Credit
- [chineseocr_lite](https://github.com/DayBreak-u/chineseocr_lite)
