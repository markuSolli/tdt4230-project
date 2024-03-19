#!/bin/sh

src_dir="data/frames"
dest_dir="data/images"

for file in "$src_dir"/*.ppm; do
    filename=$(basename -- "$file")
    filename_no_ext="${filename%.*}"

    ffmpeg -y -i ${src_dir}/${filename} $dest_dir/${filename_no_ext}.png
done
