#!/bin/sh

src_dir="data/frames"
dest_dir="data/"

ffmpeg -y -framerate 30 -i ${src_dir}/%5d.ppm -vf format=yuv420p ${dest_dir}/video.mp4
