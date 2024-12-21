#!/usr/bin/bash

echo_green() {
	local text="$1"
	echo -e "\n\033[0;32m$text\033[0m"  # Вывод текста с зелёным цветом
}

echo_green "Работа"
./build/SoundProcessor -c configs/config.txt test.wav  music/district_four.wav music/funkorama.wav
celluloid test.wav
