#!/bin/bash
cd "$(dirname -- "$(readlink -fn -- "${0}")")"

./gpuimage texture_1.bmp texture_2.bmp texture_3.bmp
mv gpuimage.binary textures.binary

./gpuimage cube_1_px_right.bmp cube_1_nx_left.bmp cube_1_py_top.bmp cube_1_ny_bottom.bmp cube_1_pz_front.bmp cube_1_nz_back.bmp cube_2_px_right.bmp cube_2_nx_left.bmp cube_2_py_top.bmp cube_2_ny_bottom.bmp cube_2_pz_front.bmp cube_2_nz_back.bmp
mv gpuimage.binary cubemaps.binary
