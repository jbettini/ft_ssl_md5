#!/bin/bash

size=$((10 * 1024))

random_string=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w $size | head -n 1)


./ft_ssl md5 -q -s "$random_string"


echo -n "$random_string" | md5sum