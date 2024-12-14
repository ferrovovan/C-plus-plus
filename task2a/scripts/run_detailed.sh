#!/usr/bin/bash

echo_green() {
	local text="$1"
	echo -e "\n\033[0;32m$text\033[0m"  # Вывод текста с зелёным цветом
}

echo_green "Работа"
matrix_dir="./config/matrices/"

echo_green "Balanced Trade-off"
matrix="Balanced Trade-off.conf"
# detailed
./build/PrisonersDilemmaSim AlwaysCooperate AlwaysDefect Eye4Eye --mode=detailed --steps=10 --matrix="$matrix_dir$matrix"